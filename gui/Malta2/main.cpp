#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QSplashScreen>
#include <QMainWindow>
#include <QTranslator>
#include <QThread>
#include <QEventLoop>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap("splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit); // 1 second delay
    loop.exec();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Malta_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QThread::sleep(2);
    w.show();
    splash.finish(&w);
    return a.exec();
}

