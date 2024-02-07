#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include "integration.h"
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QPalette>
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QCursor>


// Some global variables
QString str = "int(0)(1)dx (x)";

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
    connect(ui->ThreadNum, SIGNAL(valueChanged(int)), this, SLOT(updateLabel(int)));




    // Add the actions to the menu bar
    QMenu *settingsMenu = menuBar()->addMenu("Settings");
    QMenu *toggleModeMenu = settingsMenu->addMenu("Toggle Mode");
    toggleModeMenu->addAction(lightModeAction);
    toggleModeMenu->addAction(darkModeAction);

    QAction *toggleLogAction = new QAction("Toggle Log", this);
    connect(toggleLogAction, &QAction::triggered, this, &MainWindow::toggleLog);
    settingsMenu->addAction(toggleLogAction);

    ui->button_0->setCursor(Qt::PointingHandCursor);
    ui->button_1->setCursor(Qt::PointingHandCursor);
    ui->button_2->setCursor(Qt::PointingHandCursor);
    ui->button_3->setCursor(Qt::PointingHandCursor);
    ui->button_4->setCursor(Qt::PointingHandCursor);
    ui->button_5->setCursor(Qt::PointingHandCursor);
    ui->button_6->setCursor(Qt::PointingHandCursor);
    ui->button_7->setCursor(Qt::PointingHandCursor);
    ui->button_8->setCursor(Qt::PointingHandCursor);
    ui->button_9->setCursor(Qt::PointingHandCursor);
    ui->button_10->setCursor(Qt::PointingHandCursor);
    ui->button_11->setCursor(Qt::PointingHandCursor);
    ui->button_12->setCursor(Qt::PointingHandCursor);
    ui->button_13->setCursor(Qt::PointingHandCursor);
    ui->button_14->setCursor(Qt::PointingHandCursor);
    ui->button_15->setCursor(Qt::PointingHandCursor);
    ui->button_16->setCursor(Qt::PointingHandCursor);
    ui->button_17->setCursor(Qt::PointingHandCursor);
    ui->button_18->setCursor(Qt::PointingHandCursor);
    ui->button_19->setCursor(Qt::PointingHandCursor);
    ui->button_20->setCursor(Qt::PointingHandCursor);
    ui->button_21->setCursor(Qt::PointingHandCursor);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if (butVal == "Integrate!") {
        int numIter = ui->spinBox1->value();
        int numPts = ui->spinBox2->value();
        int numVals = ui->spinBox3->value();
        int numThreads = ui->ThreadNum->value();

        QString displayVal = ui->Display->text();

        // Create a regular expression that matches integral expressions
        QRegularExpression re("int\\(.*?\\)\\(.*?\\)d.");

        // Find all matches of the regular expression in displayVal
        QRegularExpressionMatchIterator i = re.globalMatch(displayVal);

        // Count the matches
        int count = 0;
        while (i.hasNext()) {
            i.next();
            count++;
        }
        if (count > 5) {
            QMessageBox::critical(this, "Error", "The Malta-GUI only supports integration up to 5D. ");
        } else {
            numDim = count;
        }
        Integration *integrationWindow = new Integration(this, numDim, numIter, numVals, numThreads, numPts, logEnabled, displayVal = ui->Display->text());
        integrationWindow->show();

    } else if (butVal == "∫(x)dx") {
        QRegularExpression re("int\\(.*\\)\\(.*\\)dx");
        if (numDim == 5) {
            QMessageBox::critical(this, "Error", "The Malta-GUI only supports integration up to 5D. ");
        } else if (displayVal.contains(QRegularExpression("int\\(.*\\)\\(.*\\)da int\\(.*\\)\\(.*\\)dz int\\(.*\\)\\(.*\\)dy int\\(.*\\)\\(.*\\)dx"))) {
            displayVal = "int(0)(1)db " + displayVal;
            numDim = 5;
        } else if (displayVal.contains(QRegularExpression("int\\(.*\\)\\(.*\\)dz int\\(.*\\)\\(.*\\)dy int\\(.*\\)\\(.*\\)dx"))) {
            displayVal = "int(0)(1)da " + displayVal;
            numDim = 4;
        } else if (displayVal.contains(QRegularExpression("int\\(.*\\)\\(.*\\)dy int\\(.*\\)\\(.*\\)dx"))) {
            displayVal = "int(0)(1)dz " + displayVal;
            numDim = 3;
        } else if (displayVal.contains(QRegularExpression("int\\(.*\\)\\(.*\\)dx"))) {
            displayVal = "int(0)(1)dy " + displayVal;
            numDim = 2;
        } else {
            displayVal = "int(0)(1)dx " + displayVal;
            numDim = 1;
        }
    } else if (butVal == "clear") {
        displayVal = "";
        numDim = 0;
    } else if (butVal == "yˣ") {
        displayVal += "(y)^(x)";
    } else if (butVal == "π") {
        displayVal += "pi";
    } else if (butVal == "logₓ(y)") {
        displayVal += "log(y)/log(x)";
    } else if (butVal == "√x") {
        displayVal += "sqrt(x)";
    } else if (butVal == "eˣ") {
        displayVal += "(e)^(x)";
    } else if (butVal == "ˣ/ᵧ") {
        displayVal += "(x)/(y)";
    } else if (butVal == "sin⁻¹(x)") {
        displayVal += "asin(x)";
    } else if (butVal == "cos⁻¹(x)") {
        displayVal += "acos(x)";
    } else if (butVal == "ln(x)") {
        displayVal += "log(x)";
    } else {
        displayVal += butVal;
    }

    ui->Display->setText(displayVal);
}
void MainWindow::updateLabel(int value)
{
    ui->ThreadNumL->setText(QString::number(value));
}


void MainWindow::lightMode()
{
    // Set the style sheet for the spin boxes and the display
    ui->spinBox1->setStyleSheet("QSpinBox { background-color: white; color: black; }");
    ui->spinBox2->setStyleSheet("QSpinBox { background-color: white; color: black; }");
    ui->spinBox3->setStyleSheet("QSpinBox { background-color: white; color: black; }");
    ui->Display->setStyleSheet("QLineEdit { background-color: white; color: black; }");
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    palette.setColor(QPalette::WindowText, Qt::black);
    qApp->setPalette(palette);
}

void MainWindow::darkMode()
{
    // Set the style sheet for the spin boxes and the display
    ui->spinBox1->setStyleSheet("QSpinBox { background-color: #3C3C3C; color: white; }");
    ui->spinBox2->setStyleSheet("QSpinBox { background-color: #3C3C3C; color: white; }");
    ui->spinBox3->setStyleSheet("QSpinBox { background-color: #3C3C3C; color: white; }");
    ui->Display->setStyleSheet("QLineEdit { background-color: #3C3C3C; color: white; }");
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

void MainWindow::toggleLog()
{
    logEnabled = !logEnabled;

    // Show a message box
    if (logEnabled) {
        QMessageBox::information(this, "Log Status", "Log is enabled");
    } else {
        QMessageBox::information(this, "Log Status", "Log is disabled");
    }
}
