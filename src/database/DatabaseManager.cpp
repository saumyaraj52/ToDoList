#include "DatabaseManager.h"
#include <QVariant>
#include<iostream>
using namespace std;

bool DatabaseManager::addAnEvent(Event& eventData)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO events (task_id, start_date,end_date)"
        "VALUES (:task_id,:start_date,:end_date);");
    query.bindValue(":task_id",QVariant::fromValue(eventData.taskId));
    query.bindValue(":start_date",eventData.dateRange.startDate.toString("yyyy-MM-dd"));
    query.bindValue(":end_date",eventData.dateRange.endDate.toString("yyyy-MM-dd"));

    if(!query.exec())
    {
        qCritical()<<"[DatabaseManager] Event not added to the Database"<<query.lastError().text();
        return false;
    }
    eventData.eventId = query.lastInsertId().toULongLong();
    cout<<"[DatabaseManager] added event to db : "<<eventData.eventId<<endl;
    return true;
}

bool DatabaseManager::addATask(Task& task)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO tasks (subject, description, state) VALUES (:subj, :desc, :state);");
    query.bindValue(":subj", QString::fromStdString(task.subject));
    query.bindValue(":desc", QString::fromStdString(task.description));
    query.bindValue(":state", static_cast<int>(task.taskState));

    if (!query.exec()) 
    {
        qCritical() << "[DatabaseManager] Task not added to the Database:" << query.lastError().text();
        return false;
    }

    task.taskId = query.lastInsertId().toULongLong();
    cout<<"[DatabaseManager] added task to db : "<<task.taskId<<endl;
    return true;
}

bool DatabaseManager::init(const QString& dbPath)
{
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);
    if(!m_db.open())
    {
        qCritical()<<"Failed to open DB"<<m_db.lastError().text();
        return false;
    }
    else
    {
        cout<<"DB opened successfully"<<endl;
    }
    return createTables();
}

bool DatabaseManager::createTables() {
    QSqlQuery query(m_db);

    // 1. Create tasks table
    bool okTasks = query.exec(
        "CREATE TABLE IF NOT EXISTS tasks ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  subject TEXT NOT NULL,"
        "  description TEXT,"
        "  state INTEGER DEFAULT 0"
        ");"
    );

    if (!okTasks) {
        qCritical() << "Failed to create tasks table:" << query.lastError().text();
        return false;
    }

    // 2. Create events table with foreign key linking to tasks
    bool okEvents = query.exec(
        "CREATE TABLE IF NOT EXISTS events ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  task_id INTEGER NOT NULL,"
        "  start_date TEXT NOT NULL,"
        "  end_date TEXT NOT NULL,"
        "  FOREIGN KEY(task_id) REFERENCES tasks(id) ON DELETE CASCADE"
        ");"
    );

    if (!okEvents) {
        qCritical() << "Failed to create events table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteATask(uint64_t taskId) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM tasks WHERE id = :id;");
    query.bindValue(":id", QVariant::fromValue(taskId));

    if (!query.exec()) 
    {
        qCritical() << "[DatabaseManager] Failed to delete task:" << query.lastError().text();
        return false;
    }

    std::cout << "[DatabaseManager] Deleted task #" << taskId << " from DB"<<std::endl;
    return true;
}

bool DatabaseManager::deleteAnEvent(uint64_t eventId) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM events WHERE id = :id;");
    query.bindValue(":id", QVariant::fromValue(eventId));

    if (!query.exec()) 
    {
        qCritical() << "[DatabaseManager Error] Failed to delete event:" << query.lastError().text();
        return false;
    }

    std::cout << "[DatabaseManager] Deleted event #" << eventId << " from DB"<<std::endl;
    return true;
}