/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(400, 327);
        label = new QLabel(About);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 20, 131, 131));
        label->setPixmap(QPixmap(QString::fromUtf8("../../icons/malta_icon.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(About);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(190, 50, 171, 81));
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        label_2->setFont(font);
        label_3 = new QLabel(About);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 180, 361, 31));
        QFont font1;
        font1.setBold(false);
        label_3->setFont(font1);
        label_4 = new QLabel(About);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 200, 371, 31));
        label_4->setFont(font1);
        label_5 = new QLabel(About);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 220, 361, 31));
        label_5->setFont(font1);
        label_6 = new QLabel(About);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 240, 361, 31));
        label_6->setFont(font1);
        label_7 = new QLabel(About);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 290, 291, 16));
        QFont font2;
        font2.setUnderline(true);
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("<a href=\"http://www.example.com\">Click here</a>"));
        label_7->setTextFormat(Qt::AutoText);
        label_7->setOpenExternalLinks(true);
        label_7->setTextInteractionFlags(Qt::TextBrowserInteraction);

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("About", "Malta", nullptr));
        label_3->setText(QCoreApplication::translate("About", "Malta is a cross-platform numerical integration program.", nullptr));
        label_4->setText(QCoreApplication::translate("About", "It uses the VEGAS algorithm to perform fast multidimensional", nullptr));
        label_5->setText(QCoreApplication::translate("About", "integration. Programmed using C++ and Qt. Created for", nullptr));
        label_6->setText(QCoreApplication::translate("About", "the CiS-Project at the University of Hamburg (UHH).", nullptr));
        label_7->setText(QCoreApplication::translate("About", "<html><head/><body><p><a href=\"https://github.com/Malta-Project/Malta\"><span style=\" color:#308cc6;\">Link to the source code and manual on Github</span></a></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
