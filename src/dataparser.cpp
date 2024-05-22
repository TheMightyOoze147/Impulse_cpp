#include "../include/dataparser.hpp"

// Конструктор класса ParseData
ParseData::ParseData(std::vector<std::string> lines) {
    // Паттерны регулярных выражений для проверки числа и временной метки
    std::regex numberPattern("\\d+");
    std::regex timePattern("\\d\\d:\\d\\d \\d\\d:\\d\\d");

    // Проверка ивента на соответствие паттерну
    if (!std::regex_match(lines[0], numberPattern)) {
        throw std::invalid_argument(lines[0]);
    }
    if (!std::regex_match(lines[1], timePattern)) {
        throw std::invalid_argument(lines[1]);
    }
    if (!std::regex_match(lines[2], numberPattern)) {
        throw std::invalid_argument(lines[2]);
    }

    // Заполнение полей класса
    numOfTables = std::stoi(lines[0]);
    std::istringstream iss(lines[1]);
    iss >> openedTime >> closedTime;
    pricePerHour = std::stoi(lines[2]);
    for (size_t i = 3; i < lines.size(); i++) {
        events.push_back(Event(lines[i]));
    }
    for (auto i = 0; i < numOfTables; i++) {
        tables.push_back(Table(i + 1));
    }
    for (auto &event : events) {
        Client client(event);
        if (!client.findedInDB(clients)) {
            clients.push_back(client);
        }
    }
}

// Геттер столов
int ParseData::getNumOfTables() const {
    return numOfTables;
}

// Геттер времени открытия
const std::string& ParseData::getOpenedTime() const {
    return openedTime;
}

// Геттер времени закрытия
const std::string& ParseData::getClosedTime() const {
    return closedTime;
}

// Геттер цены за час у стола
int ParseData::getPricePerHour() const {
    return pricePerHour;
}

// Геттер вектора ивентов
const std::vector<Event>& ParseData::getEvents() const {
    return events;
}

// Геттер вектора столов
const std::vector<Table>& ParseData::getTables() const {
    return tables;
}

// Геттер вектора клиентов
const std::vector<Client>& ParseData::getClients() const {
    return clients;
}

// Поиск первого свободного стола
// Возвращает его индекс в векторе столов
int ParseData::findFreeID() {
    for (auto &table : tables) {
        if (table.getIsBusy() == false) {
            return (std::stoi(table.getNumber())-1);
        }
    }
    return -1;
}

// Сеттер поля IsBusy
void ParseData::setTables(int index, bool busy) {
    tables[index].setIsBusy(busy);
}

// Сеттер вектора столов
void ParseData::setTablesVec(std::vector<Table> newTables) {
    tables = newTables;
}

// Сеттер вектора клиентов
void ParseData::setClientsVec(std::vector<Client> newClients) {
    clients = newClients;
}

// Обновление поля времени прибытия
void ParseData::updateArrTime(int ID, std::string time) {
    clients[ID].setArrivedTime(time);
}

// Обновление поля времени отбытия
void ParseData::updateLeaveTime(int ID, std::string time) {
    clients[ID].setLeavedTime(time);
}

// Обновление поля статуса прибытия
void ParseData::updateIsVisited(int ID, bool value) {
    clients[ID].setIsVisited(value);
}

// Обновление поля стола клиента
void ParseData::updateTable(int ID, Table table) {
    clients[ID].setTable(table);
}