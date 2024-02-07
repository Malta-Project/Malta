#include "integration.h"
#include "ui_integration.h"
#include "../../src/malta.h"
#include <exprtk.hpp>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QRegularExpression>
#include <QTextStream>
#include <QString>
#include <vector>
#include <string>
#include <utility>
//#include <ceval/ceval.h>

QString Integration::arg = "";
int Integration::numDim = 1;

// double integrand(std::vector<double> x) {
//     return x[0];
// }





std::vector<std::pair<double, double>> extractLimits(QString& str) {
    QRegularExpression re("int\\((\\d+\\.?\\d*)\\)\\((\\d+\\.?\\d*)\\)d(\\w)");
    QRegularExpressionMatchIterator i = re.globalMatch(str);
    std::map<QString, std::pair<double, double>> limitsMap;

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        double lower = match.captured(1).toDouble();
        double upper = match.captured(2).toDouble();
        QString var = match.captured(3);
        limitsMap[var] = std::make_pair(lower, upper);
    }

    // Remove the 'int()()d(letter)' parts from the string
    str.remove(re);

    // Trim leading and trailing whitespace
    str = str.trimmed();

    // Create the limits vector in the order of dx, dy, etc.
    std::vector<std::pair<double, double>> limits;
    for (auto& var : {"x", "y", "z", "a", "b"}) { // Add more variables if needed
        if (limitsMap.count(var) > 0) {
            limits.push_back(limitsMap[var]);
        }
    }

    return limits;
}




Integration::Integration(QWidget *parent, int numDim, int numIter, int numVals, int numThreads, int numPts, bool logEnabled, QString arg)
    : QDialog(parent)
    , ui(new Ui::Integration)
    , malta(numDim, numPts, numVals, numIter)
{
    ui->setupUi(this);
    ui->labelLaTeX->setText(arg);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(numDim-1);


    ui->textBrowser->setVisible(logEnabled);

    // created purely for debug purposes, will be deleticzky soon
    // qDebug() << "The value of numDim is: " << numDim;
    // qDebug() << "The value of numVals is: " << numVals;
    // qDebug() << "The value of numIter is: " << numIter;
    // qDebug() << "The value of numThreads is: " << numThreads;
    // qDebug() << "The value of numPts is: " << numPts;
    // qDebug() << "The value of logEnabled is: " << logEnabled;
    // qDebug() << "The value of arg is: " << arg;
    std::vector<std::pair<double, double>> limits = extractLimits(arg);
    // qDebug() << "The new value of arg is: " << arg;
    // qDebug() << "The limits are: " << limits[0];
    Integration::arg = arg;
    Integration::numDim = numDim;
    ui->progressBar->setValue(20);

    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    malta.set_threads(numThreads);
    double integral = malta.integrate(Integration::integrand, limits);
    double error = malta.get_error();
    double chi2 = malta.get_chi2();
    std::cout.rdbuf(oldCoutStreamBuf);
    QString qstr = QString::fromStdString(oss.str());

    ui->textBrowser->setText(qstr);
    ui->textBrowser_2->setText(QString::number(integral));
    ui->textBrowser_3->setText(QString::number(error));
    ui->textBrowser_4->setText(QString::number(chi2));
    if (integral != 0.0) {
        ui->progressBar->setValue(100);
    }
    ui->lcdNumber->display(static_cast<int>(malta.get_integration_time_ms()));


    // Graphics magic
    QGraphicsScene *scene = new QGraphicsScene(this);

    std::vector<double> intervals = malta.get_intervals(0);
    int width = 401;
    int height = 341;

    QList<QColor> colors = {Qt::red, Qt::darkGray, Qt::blue, Qt::black, Qt::magenta, Qt::darkGreen, Qt::darkCyan};

    for(int i = 0; i < intervals.size()-1; ++i) {
        QColor color = colors[i % colors.size()];
        QBrush brush(color);
        double x1 = intervals[i]*width;
        double x2 = intervals[i+1]*width;
        double bandWidth = x2 - x1;
        QGraphicsRectItem *rect = scene->addRect(x1, 0, bandWidth, height, Qt::NoPen, brush);
    }

    // Draw points
    std::vector<double> points = malta.get_points(0);
    QPen pointPen(Qt::white);
    pointPen.setWidth(1);
    for(int i = 0; i < points.size(); ++i) {
        QGraphicsLineItem *point = scene->addLine(points[i]*width, height/2 - 5, points[i]*width, height/2 + 5, pointPen);
    }

    ui->graphicsView->setScene(scene);

    // Connect the horizontalSlider's valueChanged signal to updatePlot
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &Integration::updatePlot);

    // Call updatePlot initially to populate the QGraphicsView
    //updatePlot(ui->horizontalSlider->value());
}

Integration::~Integration()
{
    delete ui;
}

void Integration::updatePlot(int value) {
    QGraphicsScene *scene = new QGraphicsScene(this);

    std::vector<double> intervals = this->malta.get_intervals(value); // Use this->malta instead of malta
    int width = 401;
    int height = 341;

    QList<QColor> colors = {Qt::red, Qt::darkGray, Qt::blue, Qt::black, Qt::magenta, Qt::darkGreen, Qt::darkCyan};

    for(int i = 0; i < intervals.size()-1; ++i) {
        QColor color = colors[i % colors.size()];
        QBrush brush(color);
        double x1 = intervals[i]*width;
        double x2 = intervals[i+1]*width;
        double bandWidth = x2 - x1;
        QGraphicsRectItem *rect = scene->addRect(x1, 0, bandWidth, height, Qt::NoPen, brush);
    }

    // Draw points
    std::vector<double> points = this->malta.get_points(value); // Use this->malta instead of malta
    QPen pointPen(Qt::white);
    pointPen.setWidth(1);
    for(int i = 0; i < points.size(); ++i) {
        QGraphicsLineItem *point = scene->addLine(points[i]*width, height/2 - 5, points[i]*width, height/2 + 5, pointPen);
    }

    ui->graphicsView->setScene(scene);
}


// double Integration::integrand(std::vector<double> v) {
//     // Replace 'x' with v[0] and 'y' with v[1] in the QString
//     qDebug() << "arg before everythin: " << arg;
//     QString arg_new = arg;
//     switch (numDim) {
//         case 1:
//             arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
//             break;
//         case 2:
//             arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
//             arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
//             break;
//         case 3:
//             arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
//             arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
//             arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
//             break;
//         case 4:
//             arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
//             arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
//             arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
//             arg_new.replace(QRegularExpression("\\ba\\b"), QString::number(v[3]));
//             break;
//         case 5:
//             arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
//             arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
//             arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
//             arg_new.replace(QRegularExpression("\\ba\\b"), QString::number(v[3]));
//             arg_new.replace(QRegularExpression("\\bb\\b"), QString::number(v[4]));
//             break;
//     }


//     // Convert the QString to a std::string
//     qDebug() << "arg before conversion: " << arg_new;
//     std::string expression_string = arg_new.toStdString();

//     // Create a ceval parser and parse the expression
//     //ceval_tree(expression_string);
//     qDebug() << "integrand string: " << expression_string;
//     double result = ceval_result(expression_string);
//     qDebug() << "integrand result: " << result;

//     return result;
// }


double Integration::integrand(std::vector<double> v) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>     expression_t;
    typedef exprtk::parser<double>             parser_t;

    //qDebug() << "arg before everythin: " << arg;
    QString arg_new = arg;
    arg_new.replace(QRegularExpression("\\be\\b"), QString::number(2.718281));
    arg_new.replace(QRegularExpression("\\bpi\\b"), QString::number(3.141593));
    switch (numDim) {
    case 1:
        arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
        break;
    case 2:
        arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
        arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
        break;
    case 3:
        arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
        arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
        arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
        break;
    case 4:
        arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
        arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
        arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
        arg_new.replace(QRegularExpression("\\ba\\b"), QString::number(v[3]));
        break;
    case 5:
        arg_new.replace(QRegularExpression("\\bx\\b"), QString::number(v[0]));
        arg_new.replace(QRegularExpression("\\by\\b"), QString::number(v[1]));
        arg_new.replace(QRegularExpression("\\bz\\b"), QString::number(v[2]));
        arg_new.replace(QRegularExpression("\\ba\\b"), QString::number(v[3]));
        arg_new.replace(QRegularExpression("\\bb\\b"), QString::number(v[4]));
        break;
    }


    // Convert the QString to a std::string
    //qDebug() << "arg before conversion: " << arg_new;
    std::string expression_string = arg_new.toStdString();


    symbol_table_t symbol_table;
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    if (!parser.compile(expression_string, expression)) {
        std::cerr << "Error: " << parser.error() << std::endl;
        return 1;
    }

    return expression.value();
}
