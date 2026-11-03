#include "EventManager.h"
#include<iostream>
EventManager::EventManager(DatabaseManager& dbMgr/* args */):dbMgr(dbMgr)
{
}

EventManager::~EventManager()
{
}

std::chrono::system_clock::time_point getTimePoint(Date date)
{
    std::tm event_tm = {};

    event_tm.tm_hour = 0;
    event_tm.tm_min = 0;
    event_tm.tm_sec = 0;
    event_tm.tm_isdst = -1;
    event_tm.tm_mday = date.day;
    event_tm.tm_mon = date.mon - 1;
    event_tm.tm_year = date.year - 1900;
    auto event_time_t = std::mktime(&event_tm);
    return std::chrono::system_clock::from_time_t(event_time_t);
}
bool validateEventData(Event& event)
{
    Date startDate = event.dateRange.startDate;
    Date endDate = event.dateRange.endDate;

    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = std::localtime(&now_t);
    now_tm->tm_hour = 0;
    now_tm->tm_min = 0;
    now_tm->tm_sec = 0;
    auto current_time = std::chrono::system_clock::from_time_t(std::mktime(now_tm));

    auto start_event_time = getTimePoint(startDate);
    auto end_event_time = getTimePoint(endDate);
    auto thirty_days = std::chrono::hours(24)*30;
    auto lower_bound_day = current_time - thirty_days;
    auto upper_bound_day = current_time + thirty_days;
    if(!(start_event_time >= lower_bound_day && start_event_time <= upper_bound_day))
        return false;
    if(!(end_event_time >= lower_bound_day && end_event_time <= upper_bound_day))
        return false;
    return true;
}

bool EventManager::addATask(Task& task)
{

    if(!dbMgr.addATask(task))
    {
        qCritical()<<"[EventManager] Adding a Task unsuccessfull";
        return false;
    }
    std::cout<<"[EventManager] Adding a Task successfull"<<std::endl;
    
    return true;
}

bool EventManager::addAnEvent(Event& event)
{
    if(!validateEventData(event))
        return false;
    if(!dbMgr.addAnEvent(event))
    {
        qCritical()<<"[EventManager] Adding an Event unsuccessfull";
        return false;
    }
    std::cout<<"[EventManager] Adding an Event successfull"<<std::endl;
    
    return true;
}

bool EventManager::deleteATask(uint64_t taskId)
{
    if(!dbMgr.deleteATask(taskId))
    {
        qCritical()<<"[EventManager] Deleting a task unsuccessfull";
        return false;
    }
    std::cout<<"[EventManager] Deleting a task successfull"<<std::endl;
    
    return true;
}
bool EventManager::deleteAnEvent(uint64_t eventId)
{
    if(!dbMgr.deleteAnEvent(eventId))
    {
        qCritical()<<"[EventManager] Deleting an Event unsuccessfull";
        return false;
    }
    std::cout<<"[EventManager] Deleting an Event successfull"<<std::endl;
    
    return true;
}