#include "integration.h"
#include "ui_integration.h"
#include "../../src/malta.h"
#include <cstdlib>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <fstream>

Integration::Integration(QWidget *parent, int numDim, int numIter, int numVals, int numThreads, int numPts, bool logEnabled, QString arg)
    : QDialog(parent)
    , ui(new Ui::Integration)
{
    ui->setupUi(this);
    std::string latex = "E = mc^2";

    std::ofstream out("equation.tex");
    out << "\\documentclass{standalone}\n\\begin{document}\n" << latex << "\n\\end{document}\n";
    out.close();

    // Call latex to convert .tex to .dvi, then dvipng to convert .dvi to .png.
    system("latex equation.tex && dvipng -o equation.png equation.dvi");

    QPixmap pixmap("equation.png");
    ui->labelLaTeX->setPixmap(pixmap);

    ui->textBrowser->setVisible(logEnabled);

    // created purely for debug purposes, will be deleticzky soon
    qDebug() << "The value of numDim is: " << numDim;
    qDebug() << "The value of numVals is: " << numVals;
    qDebug() << "The value of numIter is: " << numIter;
    qDebug() << "The value of numThreads is: " << numThreads;
    qDebug() << "The value of numPts is: " << numPts;
    qDebug() << "The value of logEnabled is: " << logEnabled;
    qDebug() << "The value of arg is: " << arg;
}

Integration::~Integration()
{
    delete ui;
}


