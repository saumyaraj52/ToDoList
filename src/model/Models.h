#include <string>
enum class TaskState
{
    Incomplete,
    Complete
};

class Task
{
    uint64_t taskId;
    std::string subject;
    std::string description;
    TaskState taskState;
};

class Date
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

class DateRange
{
    Date startDate;
    Date endDate;
};

class Event
{
    uint64_t eventId;
    Task task;
    DateRange dateRange;
};
