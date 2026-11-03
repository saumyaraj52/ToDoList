#pragma once
#include <cstdint>
#include <string>
#include <QDate>
enum class TaskState
{
    Incomplete =0,
    Complete = 1
};

struct Task
{
    uint64_t taskId = 0;
    std::string subject;
    std::string description;
    TaskState taskState = TaskState::Incomplete;
};

#pragma once

#include <cstdint>
#include <string>
#include <QString>
#include <QDate>

struct Date {
    int year = 1970;
    int mon = 1;
    int day = 1;

    Date() = default;
    Date(int y, int m, int d) : year(y), mon(m), day(d) {}
    Date(const QDate& qdate) 
        : year(qdate.year()), mon(qdate.month()), day(qdate.day()) {}

    QString toString(const QString& format = "yyyy-MM-dd") const {
        return QDate(year, mon, day).toString(format);
    }
};

struct DateRange
{
    Date startDate;
    Date endDate;
};

struct Event
{
    uint64_t eventId = 0;
    uint64_t taskId = 0;
    DateRange dateRange;
};
