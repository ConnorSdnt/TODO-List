#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TaskManager.h"
#include "Task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up the table columns
    ui->tableWidget->setColumnCount(3); //Title, Description, Status
    ui->tableWidget->setHorizontalHeaderLabels({"Title", "Description", "Status"});

    // Optionally, set row count to 0 initially (empty table)
    ui->tableWidget->setRowCount(0);

    // Adjust column widths
    ui->tableWidget->setColumnWidth(0, 150); // Title column
    ui->tableWidget->setColumnWidth(1, 300); // Description column
    ui->tableWidget->setColumnWidth(2, 100); // Status column

    createDemoTasks();

    // Fill the table with tasks
    loadTasks();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::createDemoTasks() {
    // Create some demo tasks and add them to the TaskManager

    // Task 1
    Task task1;
    task1.setID(0);
    task1.setTitle("Task 1");
    task1.setDescription("This is a description for task 1");
    task1.setCompleted(false); // Uncompleted task
    taskManager.addTask(task1);

    // Task 2
    Task task2;
    task2.setID(1);
    task2.setTitle("Task 2");
    task2.setDescription("This is a description for task 2");
    task2.setCompleted(true); // Completed task
    taskManager.addTask(task2);

    // Task 3
    Task task3;
    task3.setID(2);
    task3.setTitle("Task 3");
    task3.setDescription("This is a description for task 3");
    task3.setCompleted(false); // Uncompleted task
    taskManager.addTask(task3);
}

void MainWindow::loadTasks() {
    // Clear any existing rows
    ui->tableWidget->setRowCount(0);

    // Retrieve tasks from TaskManager (assuming TaskManager has a method to get tasks)
    for (auto& [taskID, task] : taskManager.getTasks()) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);  // Add a new row

        // Set task data for each column in the new row
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(task.getTitle())));  // Title
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(task.getDescription())));  // Description
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(task.getCompleted() ? "Completed" : "Un-completed"));  // Status
    }
}
