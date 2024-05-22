#include "../include/datatypes.hpp"

// Конструктор класса Event
Event::Event(std::string line) {
    // Регулярное выражение, соответствующее написанию строки ивента
    std::regex pattern("\\d\\d:\\d\\d \\d \\w+\\b( \\d+)?\\b");
    if (!std::regex_match(line, pattern)) {
        throw std::invalid_argument(line);
    }

    std::istringstream iss(line);
    iss >> time >> type >> client;
    if (type == "2") { // Если событие - смена стола
        iss >> table;
    }
}

// Геттер времени ивента
const std::string& Event::getTime() const {
    return time;
}

// Геттер типа (ID) ивента
const std::string& Event::getType() const {
    return type;
}

// Вектор имени клиента в ивенте
const std::string& Event::getClient() const {
    return client;
}

// Геттер номера стола в ивенте
const std::string& Event::getTable() const {
    return table;
}

// Для отлаживания - метод, чтобы вывести все поля класса
std::string Event::info() {
    return "{Event info}\nTime: " 
    + time + "\n" 
    + "Event ID: " + type + "\n" 
    + "Client name: " + client + "\n" 
    + "Table: " + table;
};

// Конструктор класса Table
Table::Table(int n) : number(std::to_string(n)) {}

// Геттер номера стола
const std::string& Table::getNumber() const {
    return number;
}

// Геттер статуса стола
bool Table::getIsBusy() const {
    return isBusy;
}

// Геттер времени, которое стол был в работе
const std::string& Table::getInWork() const {
    return inWork;
}

// Геттер заработанной суммы
int Table::getEarnings() const {
    return earnings;
}

// Для отлаживания - метод, чтобы вывести все поля класса
std::string Table::info() {
    return "{Table info}\nTable number: " 
    + number + "\n" 
    + "Is busy: " + std::to_string(isBusy) + "\n" 
    + "In work: " + inWork + "\n" 
    + "Earnings: " + std::to_string(earnings);
}

// Сеттер статуса стола
void Table::setIsBusy(bool value) {
    isBusy = value;
}

// Сеттер заработанной суммы
void Table::setEarnings(double value) {
    earnings = value;
}

// Сеттер времени в работе
void Table::setInWork(std::string value) {
    inWork = value;
}

// Конструктор для класса Client
Client::Client(Event event) : name(event.getClient()) {}

// Геттер имени клиента
const std::string& Client::getName() const {
    return name;
}

// Геттер времени прибытия клиента
const std::string& Client::getArrivedTime() const {
    return arrivedTime;
}

// Геттер времени отбытия клиента
const std::string& Client::getLeavedTime() const {
    return leavedTime;
}

// Геттер статуса посещения клиента
bool Client::getIsVisited() const {
    return isVisited;
}

// Геттер поля Table (класс Table) клиента
Table Client::getTable() const {
    return table;
}

// Сеттер времени прибытия
void Client::setArrivedTime(std::string time) {
    arrivedTime = time;
}

// Сеттер времени отбытия
void Client::setLeavedTime(std::string time) {
    leavedTime = time;
}

// Сеттер статуса посещения клиента
void Client::setIsVisited(bool value){
    isVisited = value;
}

// Сеттер поля стол клиента
void Client::setTable(Table tab) {
    table = tab;
}

// Метод для поиска клиента по имени в векторе клиентов (базе данных), возвращающий bool
bool Client::findedInDB(std::vector<Client> clientsDB) {
    auto it = std::find_if(clientsDB.begin(), clientsDB.end(), [&](const Client& client) {
        return client.getName() == name;
    });

    return it != clientsDB.end();
}

// Метод для поиска клиента по имени в векторе клиентов (базе данных), 
// возвращающий ID клиента в векторе
int Client::findID(std::vector<Client> clientsDB) {
    auto it = std::find_if(clientsDB.begin(), clientsDB.end(), [&](const Client& client) {
        return client.getName() == name;
    });

    if (it != clientsDB.end()) {
        return std::distance(clientsDB.begin(), it);
    } 
    else {
            return -1; // Возвращаем -1, если клиент не найден
    }
}

// Метод для проверки состояния прибытия клиента, возвращает bool
bool Client::arrivingCheck(std::vector<Client> clientsDB) {
    int ID = this->findID(clientsDB);
    return clientsDB[ID].isVisited;
}

// Для отлаживания - метод, чтобы вывести все поля класса
std::string Client::info() {
    return "{Client info}\nClient name: " 
    + name + "\n" 
    + "Arrived time: " + arrivedTime + "\n" 
    + "Leaved time: " + leavedTime + "\n" 
    + "Is visited: " + std::to_string(isVisited) + "\n"
    + table.info();
}
