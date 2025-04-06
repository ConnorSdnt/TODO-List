#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>  // Required for working with QTableWidget
#include "TaskManager.h"    // Include your TaskManager
#include "Task.h"           // Include your Task

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadTasks();  // Slot for loading tasks into the table
    void createDemoTasks();

private:
    Ui::MainWindow *ui;
    TaskManager taskManager;  // Declare a TaskManager instance

    // Any other private methods to help manage tasks can go here
};

#endif // MAINWINDOW_H
