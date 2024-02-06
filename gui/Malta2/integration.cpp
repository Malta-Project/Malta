#include "integration.h"
#include "ui_integration.h"
#include "../../src/malta.h"
#include <iostream>
#include <sstream>
#include <streambuf>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTextStream>
#include <QString>

double integrand(std::vector<double> x) {
    return x[0]*x[1];
}

Integration::Integration(QWidget *parent, int numDim, int numIter, int numVals, int numThreads, int numPts, bool logEnabled, QString arg)
    : QDialog(parent)
    , ui(new Ui::Integration)
{
    ui->setupUi(this);
    ui->labelLaTeX->setText(arg);

    ui->textBrowser->setVisible(logEnabled);

    // created purely for debug purposes, will be deleticzky soon
    qDebug() << "The value of numDim is: " << numDim;
    qDebug() << "The value of numVals is: " << numVals;
    qDebug() << "The value of numIter is: " << numIter;
    qDebug() << "The value of numThreads is: " << numThreads;
    qDebug() << "The value of numPts is: " << numPts;
    qDebug() << "The value of logEnabled is: " << logEnabled;
    qDebug() << "The value of arg is: " << arg;

    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    Malta malta = Malta(numDim, numPts, numVals, numIter);
    double integral = malta.integrate(integrand, {{0.0, 4.0}, {0.0, 4.0}});
    std::cout.rdbuf(oldCoutStreamBuf);
    QString qstr = QString::fromStdString(oss.str());
    ui->textBrowser->setText(qstr);
    ui->textBrowser_2->setText(QString::number(integral));
}

Integration::~Integration()
{
    delete ui;
}


