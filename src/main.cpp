#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#include "DatabaseManager.h"
#include "EventManager.h" 
#include "Models.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
    cout<<"Starting the app \n"<<endl;
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if(!dbMgr.init("tasks.db"))
    {
        cout<<"Failed to initialize the event"<<endl;
        return -1;
    }
    EventManager eventMgr(dbMgr);
    MainWindow mainWindow(eventMgr);
    QDate today = QDate::currentDate();
    Task task;
    task.taskId = 1;
    task.subject = "hey";
    task.description = "subject";
    task.taskState = TaskState::Incomplete;
    Date startDate = {2026,11,4};
    Date endDate = {2026,11,5};
    DateRange dateRange = {startDate,endDate};
    if(!eventMgr.addATask(task))
    {
        cout<<"Adding a task not successfull"<<endl;
    }
    else
        cout<<"Added a task : "<<task.taskId<<endl;
    Event event;
    event.taskId = task.taskId;
    event.dateRange = dateRange;
    if(!eventMgr.addAnEvent(event))
    {
        cout<<"Adding an event not successfull"<<endl;
    }
    else
    {
        cout<<"Added an event : "<<event.eventId<<endl;
    }
    if(!eventMgr.deleteAnEvent(event.eventId))
    {
        cout<<"Deletion of an event not successfull"<<endl;
    }
    else
        cout<<"Deleted an event : "<<event.eventId<<endl;
    if(!eventMgr.deleteATask(task.taskId))
    {
        cout<<"Deletion of task not successfull"<<endl;
    }
    else
        cout<<"Deleted a task : "<<task.taskId<<endl;
    
    return app.exec();
 }