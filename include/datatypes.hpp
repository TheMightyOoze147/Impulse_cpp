#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex>
#include <iomanip>

class Event {
private:
    std::string time;
    std::string type;
    std::string client;
    std::string table;

public:
    Event(std::string line);

    const std::string& getTime() const;
    const std::string& getType() const;
    const std::string& getClient() const;
    const std::string& getTable() const;
    std::string info();
};

class Table {
private:
    std::string number;
    bool isBusy = false;
    std::string inWork = "0";
    int earnings = 0;

public:
    Table(int n);

    const std::string& getNumber() const;
    bool getIsBusy() const;
    const std::string& getInWork() const;
    int getEarnings() const;
    std::string info();

    void setIsBusy(bool value);
    void setEarnings(double value);
    void setInWork(std::string value);
};

class Client {
public:
    std::string name;
    std::string arrivedTime;
    std::string leavedTime;
    bool isVisited = false;
    Table table = Table(0);

public:
    Client(Event event);

    const std::string& getName() const;
    const std::string& getArrivedTime() const;
    const std::string& getLeavedTime() const;
    bool getIsVisited() const;
    Table getTable() const;

    void setArrivedTime(std::string time);
    void setLeavedTime(std::string time);
    void setIsVisited(bool value);
    void setTable(Table tab);

    bool findedInDB(std::vector<Client> clientsDB);
    int findID(std::vector<Client> clientsDB);
    bool arrivingCheck(std::vector<Client> clientsDB);
    std::string info();
};

#endif