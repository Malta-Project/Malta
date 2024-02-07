#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QDialog>
#include "../../src/malta.h"

namespace Ui {
class Integration;
}

class Integration : public QDialog
{
    Q_OBJECT

public:
    explicit Integration(QWidget *parent = nullptr, int numDim = 1, int numIter = 1, int numVals = 1, int numThreads = 1, int numPts = 100, bool logEnabled = false, QString arg = "");
    static QString arg;
    static double integrand(std::vector<double> v);
    static int numDim;
    void updatePlot(int value);
    ~Integration();




private:
    Ui::Integration *ui;
    Malta malta;

};

#endif // INTEGRATION_H
