/********************************************************************************
** Form generated from reading UI file 'integration.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATION_H
#define UI_INTEGRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Integration
{
public:
    QProgressBar *progressBar;
    QTextBrowser *textBrowser;
    QLabel *labelLaTeX;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *lcdNumber;
    QSlider *horizontalSlider;
    QLabel *label_3;
    QTextBrowser *textBrowser_2;
    QLabel *label_4;
    QTextBrowser *textBrowser_3;
    QLabel *label_5;
    QTextBrowser *textBrowser_4;
    QLabel *label_6;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *Integration)
    {
        if (Integration->objectName().isEmpty())
            Integration->setObjectName("Integration");
        Integration->resize(1102, 519);
        progressBar = new QProgressBar(Integration);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(20, 100, 521, 23));
        progressBar->setValue(0);
        textBrowser = new QTextBrowser(Integration);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 120, 521, 192));
        labelLaTeX = new QLabel(Integration);
        labelLaTeX->setObjectName("labelLaTeX");
        labelLaTeX->setGeometry(QRect(30, 40, 231, 21));
        label = new QLabel(Integration);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 340, 58, 15));
        label_2 = new QLabel(Integration);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(290, 340, 151, 16));
        lcdNumber = new QLCDNumber(Integration);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(290, 370, 251, 41));
        horizontalSlider = new QSlider(Integration);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(720, 470, 311, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(Integration);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(630, 470, 101, 16));
        textBrowser_2 = new QTextBrowser(Integration);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(20, 370, 251, 41));
        label_4 = new QLabel(Integration);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 430, 58, 15));
        textBrowser_3 = new QTextBrowser(Integration);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(20, 460, 251, 41));
        label_5 = new QLabel(Integration);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(290, 430, 58, 15));
        textBrowser_4 = new QTextBrowser(Integration);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(290, 460, 251, 41));
        label_6 = new QLabel(Integration);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(630, 70, 421, 16));
        graphicsView = new QGraphicsView(Integration);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(630, 100, 401, 341));

        retranslateUi(Integration);

        QMetaObject::connectSlotsByName(Integration);
    } // setupUi

    void retranslateUi(QDialog *Integration)
    {
        Integration->setWindowTitle(QCoreApplication::translate("Integration", "Dialog", nullptr));
        labelLaTeX->setText(QCoreApplication::translate("Integration", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("Integration", "Result:", nullptr));
        label_2->setText(QCoreApplication::translate("Integration", "Time needed [in ms]:", nullptr));
        label_3->setText(QCoreApplication::translate("Integration", "Dimension:", nullptr));
        label_4->setText(QCoreApplication::translate("Integration", "Error:", nullptr));
        label_5->setText(QCoreApplication::translate("Integration", "\317\207\302\262:", nullptr));
        label_6->setText(QCoreApplication::translate("Integration", "Integral visualisation:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Integration: public Ui_Integration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATION_H
