/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDark_mode;
    QAction *actionLight_mode;
    QWidget *centralwidget;
    QSlider *ThreadNum;
    QLabel *label;
    QLineEdit *Display;
    QPushButton *button_1;
    QPushButton *button_2;
    QPushButton *button_4;
    QPushButton *button_3;
    QPushButton *button_5;
    QPushButton *button_7;
    QPushButton *button_6;
    QPushButton *button_15;
    QPushButton *button_11;
    QPushButton *button_9;
    QPushButton *button_12;
    QPushButton *button_8;
    QPushButton *button_14;
    QPushButton *button_10;
    QPushButton *button_13;
    QPushButton *button_16;
    QPushButton *button_21;
    QPushButton *button_19;
    QPushButton *button_20;
    QPushButton *button_17;
    QPushButton *button_18;
    QSpinBox *spinBox2;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox1;
    QLabel *label_4;
    QSpinBox *spinBox3;
    QPushButton *button_0;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *ThreadNumL;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(993, 941);
        actionDark_mode = new QAction(MainWindow);
        actionDark_mode->setObjectName("actionDark_mode");
        actionLight_mode = new QAction(MainWindow);
        actionLight_mode->setObjectName("actionLight_mode");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ThreadNum = new QSlider(centralwidget);
        ThreadNum->setObjectName("ThreadNum");
        ThreadNum->setGeometry(QRect(400, 490, 261, 41));
        ThreadNum->setMinimum(1);
        ThreadNum->setMaximum(10);
        ThreadNum->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 480, 131, 61));
        Display = new QLineEdit(centralwidget);
        Display->setObjectName("Display");
        Display->setGeometry(QRect(30, 300, 601, 101));
        QFont font;
        font.setPointSize(15);
        Display->setFont(font);
        Display->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        button_1 = new QPushButton(centralwidget);
        button_1->setObjectName("button_1");
        button_1->setGeometry(QRect(10, 550, 121, 100));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        button_1->setFont(font1);
        button_1->setMouseTracking(true);
        button_1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_2 = new QPushButton(centralwidget);
        button_2->setObjectName("button_2");
        button_2->setGeometry(QRect(150, 550, 121, 100));
        button_2->setFont(font1);
        button_2->setMouseTracking(true);
        button_2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_4 = new QPushButton(centralwidget);
        button_4->setObjectName("button_4");
        button_4->setGeometry(QRect(430, 550, 121, 100));
        button_4->setFont(font1);
        button_4->setMouseTracking(true);
        button_4->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_3 = new QPushButton(centralwidget);
        button_3->setObjectName("button_3");
        button_3->setGeometry(QRect(290, 550, 121, 100));
        QFont font2;
        font2.setPointSize(27);
        font2.setBold(true);
        button_3->setFont(font2);
        button_3->setMouseTracking(true);
        button_3->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_5 = new QPushButton(centralwidget);
        button_5->setObjectName("button_5");
        button_5->setGeometry(QRect(570, 550, 121, 100));
        button_5->setFont(font1);
        button_5->setMouseTracking(true);
        button_5->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_7 = new QPushButton(centralwidget);
        button_7->setObjectName("button_7");
        button_7->setGeometry(QRect(850, 550, 121, 100));
        button_7->setFont(font1);
        button_7->setMouseTracking(true);
        button_7->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_6 = new QPushButton(centralwidget);
        button_6->setObjectName("button_6");
        button_6->setGeometry(QRect(710, 550, 121, 100));
        button_6->setFont(font1);
        button_6->setMouseTracking(true);
        button_6->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_15 = new QPushButton(centralwidget);
        button_15->setObjectName("button_15");
        button_15->setGeometry(QRect(10, 790, 121, 100));
        button_15->setFont(font1);
        button_15->setMouseTracking(true);
        button_15->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_11 = new QPushButton(centralwidget);
        button_11->setObjectName("button_11");
        button_11->setGeometry(QRect(430, 670, 121, 100));
        QFont font3;
        font3.setPointSize(25);
        font3.setBold(true);
        button_11->setFont(font3);
        button_11->setMouseTracking(true);
        button_11->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_9 = new QPushButton(centralwidget);
        button_9->setObjectName("button_9");
        button_9->setGeometry(QRect(150, 670, 121, 100));
        button_9->setFont(font1);
        button_9->setMouseTracking(true);
        button_9->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_12 = new QPushButton(centralwidget);
        button_12->setObjectName("button_12");
        button_12->setGeometry(QRect(570, 670, 121, 100));
        button_12->setFont(font3);
        button_12->setMouseTracking(true);
        button_12->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_8 = new QPushButton(centralwidget);
        button_8->setObjectName("button_8");
        button_8->setGeometry(QRect(10, 670, 121, 100));
        button_8->setFont(font1);
        button_8->setMouseTracking(true);
        button_8->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_14 = new QPushButton(centralwidget);
        button_14->setObjectName("button_14");
        button_14->setGeometry(QRect(850, 670, 121, 100));
        QFont font4;
        font4.setPointSize(26);
        font4.setBold(true);
        button_14->setFont(font4);
        button_14->setMouseTracking(true);
        button_14->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_10 = new QPushButton(centralwidget);
        button_10->setObjectName("button_10");
        button_10->setGeometry(QRect(290, 670, 121, 100));
        button_10->setFont(font2);
        button_10->setMouseTracking(true);
        button_10->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_13 = new QPushButton(centralwidget);
        button_13->setObjectName("button_13");
        button_13->setGeometry(QRect(710, 670, 121, 100));
        QFont font5;
        font5.setPointSize(28);
        font5.setBold(true);
        button_13->setFont(font5);
        button_13->setMouseTracking(true);
        button_13->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,150,150);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_16 = new QPushButton(centralwidget);
        button_16->setObjectName("button_16");
        button_16->setGeometry(QRect(150, 790, 121, 100));
        button_16->setFont(font1);
        button_16->setMouseTracking(true);
        button_16->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_21 = new QPushButton(centralwidget);
        button_21->setObjectName("button_21");
        button_21->setGeometry(QRect(850, 790, 121, 100));
        button_21->setFont(font4);
        button_21->setMouseTracking(true);
        button_21->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_19 = new QPushButton(centralwidget);
        button_19->setObjectName("button_19");
        button_19->setGeometry(QRect(570, 790, 121, 100));
        button_19->setFont(font3);
        button_19->setMouseTracking(true);
        button_19->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_20 = new QPushButton(centralwidget);
        button_20->setObjectName("button_20");
        button_20->setGeometry(QRect(710, 790, 121, 100));
        button_20->setFont(font5);
        button_20->setMouseTracking(true);
        button_20->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_17 = new QPushButton(centralwidget);
        button_17->setObjectName("button_17");
        button_17->setGeometry(QRect(290, 790, 121, 100));
        button_17->setFont(font2);
        button_17->setMouseTracking(true);
        button_17->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        button_18 = new QPushButton(centralwidget);
        button_18->setObjectName("button_18");
        button_18->setGeometry(QRect(430, 790, 121, 100));
        button_18->setFont(font3);
        button_18->setMouseTracking(true);
        button_18->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(150,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        spinBox2 = new QSpinBox(centralwidget);
        spinBox2->setObjectName("spinBox2");
        spinBox2->setGeometry(QRect(140, 440, 161, 41));
        spinBox2->setMinimum(100);
        spinBox2->setMaximum(1000000);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 430, 131, 61));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 430, 131, 61));
        spinBox1 = new QSpinBox(centralwidget);
        spinBox1->setObjectName("spinBox1");
        spinBox1->setGeometry(QRect(800, 440, 161, 41));
        spinBox1->setMinimum(1);
        spinBox1->setMaximum(1000);
        spinBox1->setValue(42);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(650, 430, 131, 61));
        spinBox3 = new QSpinBox(centralwidget);
        spinBox3->setObjectName("spinBox3");
        spinBox3->setGeometry(QRect(470, 440, 161, 41));
        QFont font6;
        font6.setPointSize(10);
        spinBox3->setFont(font6);
        spinBox3->setMinimum(1);
        spinBox3->setMaximum(1000);
        spinBox3->setValue(10);
        button_0 = new QPushButton(centralwidget);
        button_0->setObjectName("button_0");
        button_0->setGeometry(QRect(670, 300, 271, 100));
        button_0->setFont(font1);
        button_0->setMouseTracking(true);
        button_0->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:20px;\n"
"	background-color:rgb(250,100,100);\n"
"	color:rgb(255,255,255);\n"
"	min-width:100px;\n"
"	min-height:100px;\n"
"	padding:0;\n"
"}"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(200, 40, 221, 211));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../../icons/malta_icon.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(450, 80, 331, 131));
        ThreadNumL = new QLabel(centralwidget);
        ThreadNumL->setObjectName("ThreadNumL");
        ThreadNumL->setGeometry(QRect(670, 500, 58, 15));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 993, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionDark_mode->setText(QCoreApplication::translate("MainWindow", "Dark mode", nullptr));
        actionLight_mode->setText(QCoreApplication::translate("MainWindow", "Light mode", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of Threads", nullptr));
        Display->setText(QCoreApplication::translate("MainWindow", "int(0)(1)dx x", nullptr));
        button_1->setText(QCoreApplication::translate("MainWindow", "\342\210\253(x)dx", nullptr));
        button_2->setText(QCoreApplication::translate("MainWindow", "y\313\243", nullptr));
        button_4->setText(QCoreApplication::translate("MainWindow", "\317\200", nullptr));
        button_3->setText(QCoreApplication::translate("MainWindow", "log\342\202\223(y)", nullptr));
        button_5->setText(QCoreApplication::translate("MainWindow", "\342\210\232x", nullptr));
        button_7->setText(QCoreApplication::translate("MainWindow", "e", nullptr));
        button_6->setText(QCoreApplication::translate("MainWindow", "e\313\243", nullptr));
        button_15->setText(QCoreApplication::translate("MainWindow", "ln(x)", nullptr));
        button_11->setText(QCoreApplication::translate("MainWindow", "sin\342\201\273\302\271(x)", nullptr));
        button_9->setText(QCoreApplication::translate("MainWindow", "sin(x)", nullptr));
        button_12->setText(QCoreApplication::translate("MainWindow", "cos\342\201\273\302\271(x)", nullptr));
        button_8->setText(QCoreApplication::translate("MainWindow", "\313\243/\341\265\247", nullptr));
        button_14->setText(QCoreApplication::translate("MainWindow", "cosh(x)", nullptr));
        button_10->setText(QCoreApplication::translate("MainWindow", "cos(x)", nullptr));
        button_13->setText(QCoreApplication::translate("MainWindow", "sinh(x)", nullptr));
        button_16->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        button_21->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        button_19->setText(QCoreApplication::translate("MainWindow", "a", nullptr));
        button_20->setText(QCoreApplication::translate("MainWindow", "b", nullptr));
        button_17->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        button_18->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of Points", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Number of Intervals", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Number of Iterations", nullptr));
        button_0->setText(QCoreApplication::translate("MainWindow", "Integrate!", nullptr));
        label_5->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:72pt; font-weight:700;\">Malta</span></p></body></html>", nullptr));
        ThreadNumL->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
