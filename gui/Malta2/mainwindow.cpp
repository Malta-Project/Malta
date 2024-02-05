#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include <QMenuBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

// Some global variables
QString str = "int(0)(0)dx x";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ... and so on for the other labels


    ui->Display->setText(str);
    QPushButton *numButtons[22];
    for (int i = 0; i < 22; i++) {
        QString butName = "button_" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    // Create actions for the light and dark mode
    QAction *lightModeAction = new QAction("Light Mode", this);
    QAction *darkModeAction = new QAction("Dark Mode", this);
    QAction *aboutAction = menuBar()->addAction("About");

    // Connect the actions to their respective slots
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(lightModeAction, &QAction::triggered, this, &MainWindow::lightMode);
    connect(darkModeAction, &QAction::triggered, this, &MainWindow::darkMode);

    // Add the actions to the menu bar
    QMenu *settingsMenu = menuBar()->addMenu("Settings");
    QMenu *toggleModeMenu = settingsMenu->addMenu("Toggle Mode");
    toggleModeMenu->addAction(lightModeAction);
    toggleModeMenu->addAction(darkModeAction);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(displayVal+butVal);
    } else {
        QString newVal = displayVal + butVal;

    }
}


void MainWindow::lightMode()
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    palette.setColor(QPalette::WindowText, Qt::black);
    qApp->setPalette(palette);
}

void MainWindow::darkMode()
{
    QPalette palette;
    QColor customColor(60, 60, 60);  // Custom dark color
    palette.setColor(QPalette::Window, customColor);
    palette.setColor(QPalette::WindowText, Qt::white);
    qApp->setPalette(palette);
}

void MainWindow::about()
{
    About dialog(this);
    dialog.exec();
}
