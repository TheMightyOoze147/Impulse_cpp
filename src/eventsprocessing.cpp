#include "../include/eventsprocessing.hpp"

// Перевод строки с временем ("HH:MM") в минуты
int timeToMinutes(const std::string& timeStr) {
    std::istringstream iss(timeStr);
    int hours, minutes;
    char delimiter;
    iss >> hours >> delimiter >> minutes;
    return hours * 60 + minutes;
}

// Перевод минут в строку "HH:MM"
std::string minutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

// Конструктор класса EventProcessor
EventProcessor::EventProcessor(ParseData& data) : data(data) {}

// Событие "клиент прибыл"
void EventProcessor::clientArrived(Event event) {
    std::cout << event.getTime() << " " << event.getType() << " " << event.getClient() << std::endl;
    // Перевод временных меток в минуты для сравнения времени прибытия и времени работы заведения
    std::time_t startTime = timeToMinutes(data.getOpenedTime());
    std::time_t endTime = timeToMinutes(data.getClosedTime());
    std::time_t eventTime = timeToMinutes(event.getTime());

    Client client(event);
    // Проверка клиента на прибытие ранее
    if (!client.arrivingCheck(data.getClients())) { // Если клиент не прибыл
        if (eventTime > startTime && eventTime < endTime) { // И если время прибытия укладывается в часы работы
            int dbID = client.findID(data.getClients()); 
            data.updateArrTime(dbID, event.getTime()); // Устанавливаем для нового клиента время прибытия и метку "прибыл"
            data.updateIsVisited(dbID, true);
        }
        else { // Иначе ошибка 13
            std::cout << event.getTime() + " 13 NotOpenYet" << std::endl;
        }
    }
    else { // Иначе ошибка 13
        std::cout << event.getTime() + " 13 YouShallNotPass" << std::endl;
    }
}

// Событие "клиент садится за стол"
void EventProcessor::clientTakeASeat(Event event) {
    std::cout << event.getTime() << " " << event.getType() << " " << event.getClient() << " " << event.getTable() << std::endl;
    Client client(event);
    std::vector<Table> tables = data.getTables(); // Вектор всех столов
    int tableID = std::stoi((event.getTable())) - 1; // Получаем ID стола, который хочет занять клиент
    if (client.arrivingCheck(data.getClients())) { // Если клиент прибыл
        if (tables[tableID].getIsBusy() == false) { // Если желаемый стол свободен
            int dbID = client.findID(data.getClients());
            data.setTables(tableID, true);
            data.updateTable(dbID, data.getTables()[tableID]); // Садим клиента за стол
            data.updateArrTime(dbID, event.getTime());
        }
        else { // Иначе ошибка 13
            std::cout << event.getTime() + " 13 PlaceIsBusy" << std::endl;
        }
    }
    else { // Иначе ошибка 13
        std::cout << event.getTime() + " 13 ClientUnknown" << std::endl;
    }
}

// Событие "клиент ожидает"
void EventProcessor::clientIsWaiting(Event event) {
    std::cout << event.getTime() << " " << event.getType() << " " << event.getClient() << std::endl;
    Client client(event);
    int dbID = client.findID(data.getClients()); // Ищем клиента для последующих действий в БД
    if ((int)queue.size() > data.getNumOfTables()) { // Если очередь будет больше, чем количество столов
        std::cout << event.getTime() + " 11 " + event.getClient() << std::endl; // Ошибка 11, клиент уходит
        data.updateIsVisited(dbID, false);
        data.updateLeaveTime(dbID, event.getTime());
    } 
    else if (!client.arrivingCheck(data.getClients())) { // Иначе если клиент не приходил
        std::cout << event.getTime() + " 13 ClientUnknown" << std::endl; // Ошибка 13
    }
    else {
        if (data.findFreeID() != -1) { // Иначе если свободные столы есть
            std::cout << event.getTime() + " 13 ICanWaitNoLonger!" << std::endl; // Ошибка 13
        }
        else { // Иначе добавляем клиента в очередь
            queue.push_back(data.getClients()[dbID]);
        }
    }
}

// Событие "клиент уходит"
void EventProcessor::clientIsLeaving(Event event) {
    std::cout << event.getTime() << " " << event.getType() << " " << event.getClient() << std::endl;
    Client client(event);
    int dbID = client.findID(data.getClients());
    if (!client.arrivingCheck(data.getClients())) { // Если клиент не прибыл
        std::cout << event.getTime() + " 13 ClientUnknown" << std::endl; // Ошибка 13
    }
    else { // Иначе
        if (!queue.empty()) { // Если очередь не пуста, первый клиент из очереди занимает освободившееся место
            std::cout << event.getTime() + " 12 " + queue[0].getName() + " " + data.getClients()[dbID].getTable().getNumber() << std::endl;
            int queueDBID = queue[0].findID(data.getClients());
            data.updateArrTime(queueDBID, event.getTime());
            data.updateTable(queueDBID, data.getTables()[dbID]);

            queue.erase(queue.begin()); // Первый клиент очереди из неё выходит, поскольку теперь занимает место
            data.updateLeaveTime(dbID, event.getTime());
            data.updateIsVisited(dbID, false);
        }
        else { // Иначе клиент просто уходит
            data.updateLeaveTime(dbID, event.getTime());
            data.updateIsVisited(dbID, false);
        }
    }
}

// Метод для начала обработки всех ивентов
void EventProcessor::processing() {
    for (auto& event : data.getEvents()) {
        switch (stoi(event.getType())) {
            case 1:
                clientArrived(event);
                break;
            case 2:
                clientTakeASeat(event);
                break;
            case 3:
                clientIsWaiting(event);
                break;
            case 4:
                clientIsLeaving(event);
                break;
        }
    }
}

// Метод "заведение закрывается" - для генерации в конце дня
void EventProcessor::ServiceClosed() {
    std::vector<Client> clients = data.getClients();
    std::vector<Table> tables;

    // Сортировка клиентов по имени в алфавитном порядке
    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client&b) {
        return a.getName() < b.getName();
    });

    // Начало события 11 - все клиенты уходят
    for (auto& client : clients) {
        if (client.isVisited == true) { // Если клиент всё ещё в заведении
            std::cout << data.getClosedTime() + " 11 " + client.getName() << std::endl; // Клиент уходит
            client.setIsVisited(false);
            client.setLeavedTime(data.getClosedTime());
        }
        if (client.getTable().getIsBusy()){ // Если стол клиента занят
            client.table.setIsBusy(false); // Стол освобождается
            int diff = timeToMinutes(client.getLeavedTime()) - timeToMinutes(client.getArrivedTime()); // Подсчёт времени в работе
            client.table.setInWork(minutesToTime(diff)); 
            int hours = diff / 60;
            int minutes = diff % 60;
            if (minutes > 0) {
                hours++;
            }
            client.table.setEarnings(hours * data.getPricePerHour()); // Подсчёт выручки
            std::string targetNumber = client.table.getNumber();

            // Лямбда функция для поиска стола в списке столов
            auto isSameTable = [&](const Table& table) {
                return table.getNumber() == targetNumber;
            };
            auto it = std::find_if(tables.begin(), tables.end(), isSameTable); // Поиск столов в новом векторе столов

            if (it != tables.end()) { // Если стол найден, значит он уже обработан для другого пользователя
                int index = std::distance(tables.begin(), it);
                tables[index].setInWork(minutesToTime(timeToMinutes(tables[index].getInWork()) + timeToMinutes(client.table.getInWork()))); // Суммируем время работы клиента с временем в работе стола в целом
                tables[index].setEarnings(tables[index].getEarnings() + client.table.getEarnings()); // Суммируем выручку для стола клиента с выручкой стола в целом
            }
            else { // Если стол не найден, значит этот клиент за ним первый
                tables.push_back(client.getTable()); // Добавляем стол в вектор столов
            }
        }
    }
    data.setTablesVec(tables); // Обновляем данные в БД
    data.setClientsVec(clients); // Обновляем данные в БД

    // Выводим информацию по столам: <номер стола> <выручка> <время в работе>
    for (auto& table : data.getTables()) {
        std::cout << table.getNumber() << " " << table.getEarnings() << " " << table.getInWork() << std::endl;
    }
}

// Геттер вектора столов
std::vector<Table> EventProcessor::getTables() {
    return data.getTables();
}

// Геттер вектора клиентов
std::vector<Client> EventProcessor::getClients() {
    return data.getClients();
}