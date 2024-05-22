#ifndef EVENTSPROCESSING_HPP
#define EVENTSPROCESSING_HPP

#include "dataparser.hpp"

class EventProcessor {
private:
    ParseData& data;
public:
    std::vector<Client> queue;
    EventProcessor(ParseData& data);

    void clientArrived(Event event);
    void clientTakeASeat(Event event);
    void clientIsWaiting(Event event);
    void clientIsLeaving(Event event);
    void processing();
    void ServiceClosed();

    std::vector<Table> getTables();
    std::vector<Client> getClients();
};

#endif