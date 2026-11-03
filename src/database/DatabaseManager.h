#pragma once
#include <QSqlDatabase>
#include <QSqlquery>
#include <QSqlError>
#include <optional>
#include "Models.h"
class DatabaseManager
{
private:
    QSqlDatabase m_db;
    bool createTables();
public:
    static DatabaseManager& instance()
    {
        static DatabaseManager inst;
        return inst;
    }
    bool init(const QString& dbPath);
    bool addAnEvent(Event& eventData);
    bool addATask(Task& task);
    bool deleteATask(uint64_t taskId);
    bool deleteAnEvent(uint64_t eventId);
};