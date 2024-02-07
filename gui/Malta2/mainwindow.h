#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    int numDim = 1;
    bool logEnabled = false;
    int numIter;
    int numVals;
    int numPts;
    int numThreads = 1;

private:
    Ui::MainWindow *ui;



private slots:
    void NumPressed();
    void lightMode();
    void darkMode();
    void about();
    void toggleLog();
    void updateLabel(int value);
};
#endif // MAINWINDOW_H
