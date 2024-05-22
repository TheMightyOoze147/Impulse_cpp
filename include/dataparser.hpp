#ifndef DATAPARSER_HPP
#define DATAPARSER_HPP

#include "datatypes.hpp"

std::time_t stringToTime(std::string line);

class ParseData {
private:
    int numOfTables;
    std::string openedTime;
    std::string closedTime;
    int pricePerHour;
    std::vector<Event> events;
    std::vector<Table> tables;
    std::vector<Client> clients;

public:
    ParseData(std::vector<std::string> lines);
    int getNumOfTables() const;
    const std::string& getOpenedTime() const;
    const std::string& getClosedTime() const;
    int getPricePerHour() const;

    const std::vector<Event>& getEvents() const;
    const std::vector<Table>& getTables() const;
    const std::vector<Client>& getClients() const;

    int findFreeID();
    void setTables(int index, bool busy);
    void setTablesVec(std::vector<Table> newTables);
    void setClientsVec(std::vector<Client> newClients);
    void updateArrTime(int ID, std::string time);
    void updateLeaveTime(int ID, std::string time);
    void updateIsVisited(int ID, bool value);
    void updateTable(int ID, Table table);

};

#endif