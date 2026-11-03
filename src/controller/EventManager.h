#pragma once
#include "DatabaseManager.h"
class EventManager
{
private:
    DatabaseManager& dbMgr;
public:
    EventManager(DatabaseManager& dbMgr/* args */);
    ~EventManager();
    bool addAnEvent(Event& eventData);
    bool addATask(Task& task);
    bool deleteATask(uint64_t taskId);
    bool deleteAnEvent(uint64_t eventId);
    bool ifAnEventExist(uint64_t eventId);
    bool ifATaskExist(uint64_t taskId);
};
