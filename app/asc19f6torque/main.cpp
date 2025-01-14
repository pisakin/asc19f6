#include "../../src/casc19f6torque.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QApplication>
#include <QSettings>
#include <QDir>
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
 *  Главная функция приложения
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//
    QCoreApplication::setOrganizationName("VNIISignal");
    QCoreApplication::setOrganizationDomain("vniisignal.ru");
    QCoreApplication::setApplicationName("asc19F6Torque");

//  Q_INIT_RESOURCE(res);
//

// Установка русификации Qt
    QTranslator* qt_translator = new QTranslator();
    if (!qt_translator->load(QApplication::applicationDirPath() + "/qt_ru.qm"))
        delete qt_translator;
    else
        app.installTranslator(qt_translator);

// Установка стиля приложения
//    QApplication::setStyle("windows");

    QDialog dialog;
    dialog.setGeometry(100, 100, 800, 600);
    QVBoxLayout vBoxLayout;
    vBoxLayout.setContentsMargins(0, 0, 0, 0);
    vBoxLayout.setSpacing(0);
    dialog.setLayout(&vBoxLayout);

    CASC19F6Torque ascEMTorque;
    vBoxLayout.addWidget(&ascEMTorque);

    dialog.show();

    bool result = app.exec();
    return result;
}
