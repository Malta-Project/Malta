#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QDialog>

namespace Ui {
class Integration;
}

class Integration : public QDialog
{
    Q_OBJECT

public:
    explicit Integration(QWidget *parent = nullptr, int numDim = 1, int numIter = 1, int numVals = 1, int numThreads = 1, int numPts = 100, bool logEnabled = false, QString arg = "");
    ~Integration();

private:
    Ui::Integration *ui;
};

#endif // INTEGRATION_H
