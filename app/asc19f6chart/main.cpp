#include "../../src/cascemchart.h"

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLocale>
#include <QTranslator>
#include <QTextStream>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QScreen>

void messageToFile(QtMsgType                type,
                   const QMessageLogContext &context,
                   const QString            &msg)
{
    QString fileName;
    fileName = "log-";
    fileName += QDateTime::currentDateTime().toString("yyyy_MM_dd");
    fileName += ".log";
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    switch (type) {
    case QtDebugMsg:
        out << " [[ Debug ]] " << msg  << " >> " << context.file;
        break;
    case QtInfoMsg:
        out << " [[ Info ]] " << msg << " >> " << context.file;
        break;
    case QtWarningMsg:
        out << " [[ Warning ]] " << msg << " >> " << context.file;
        break;
    case QtCriticalMsg:
        out << " [[ QtCriticalMsg ]] " << msg << " >> " << context.file;
        break;
    case QtFatalMsg:
        out << " [[ Fatal ]] " << msg << " >> " <<  context.file;
        break;
//    case QtSystemMsg:
//        out << "Debug: " << msg << context.file << endl;
//        break;
//    default:
//        out << "[[ Unknown ]] " << msg << " >> " <<  context.file << endl;
//        break;
    }
}

/*
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//
    QCoreApplication::setOrganizationName("ascEMChart");
    QCoreApplication::setOrganizationDomain("pisakin.com");
    QCoreApplication::setApplicationName("ascEMChart");

//  Q_INIT_RESOURCE(res);
//

// Установка русификации Qt
    QTranslator* qt_translator = new QTranslator();
    if (!qt_translator->load(QApplication::applicationDirPath() + "/qt_ru.qm"))
        delete qt_translator;
    else
        a.installTranslator(qt_translator);

// Установка стиля приложения
//    QApplication::setStyle("windows");

    QDialog dialog;
    dialog.setGeometry(0, 0, 800, 600);

    QVBoxLayout vBoxLayout;
    vBoxLayout.setContentsMargins(0, 0, 0, 0);
    vBoxLayout.setSpacing(0);
    dialog.setLayout(&vBoxLayout);


    CASCEMChart ascEMChart;
    vBoxLayout.addWidget(&ascEMChart);

    dialog.show();

    return a.exec();
}
