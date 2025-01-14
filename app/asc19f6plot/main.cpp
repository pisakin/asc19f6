#include "../../src/casc19f6types.h"
#include "../../src/casc19f6plot.h"

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
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
 *  Чтение настроек
 */
void readSettings(TTMASC19F6Settings *asc19f6Settings)
{
// Определение каталога с файлами программы
    QDir dir(QCoreApplication::applicationDirPath());

// Подключение к ini файлу для получения настроек подключения
    QString fileConf = dir.absoluteFilePath("asc19f6.ini");

    QFile file(fileConf);

//    if (file.exists()) {
    QSettings settings(fileConf, QSettings::IniFormat);

// Получение настроек терминала
    settings.beginGroup("Main");
    asc19f6Settings->id = settings.value("id", 0).toInt();
    asc19f6Settings->mode = settings.value("mode", 0).toInt();
    asc19f6Settings->dataDir = settings.value("DataDir", "").toString();
    asc19f6Settings->naborDir = settings.value("NaborDir", "").toString();
    settings.endGroup();

    settings.beginGroup("Oven");
    asc19f6Settings->type = settings.value("Type", 1).toInt();
    asc19f6Settings->address = settings.value("Address", 1).toInt();
    asc19f6Settings->timeOut = settings.value("TimeOut", 300).toInt();
#ifdef __linux__
    asc19f6Settings->portName = settings.value("portName", "ttyS0").toString();
#elif _WIN32
    asc19f6plotSettings->portName = settings.value("portName", "COM1").toString();
#endif
    asc19f6Settings->baudRate = settings.value("baudRate", 9600).toInt();
    asc19f6Settings->parity = settings.value("parity", 0).toInt();
    asc19f6Settings->dataBit = settings.value("dataBit",8).toInt();
    asc19f6Settings->stopBits = settings.value("stopBits",1).toInt();
    asc19f6Settings->flowControl = settings.value("flowControl",0).toInt();
    settings.endGroup();

//  Установка стиля по умолчанию
//    setAppStyle();
/*
    } else {
        file.open(QIODevice::ReadWrite);
        file.close();
    }
*/
}


/*
 *
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//
    QCoreApplication::setOrganizationName("asc19f6plot");
    QCoreApplication::setOrganizationDomain("pisakin.com");
    QCoreApplication::setApplicationName("asc19f6plot");

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

    TMASC19F6Settings settings;
    TTMASC19F6Settings *asc19f6Settings = &settings;
    readSettings(asc19f6Settings);
/*
    asc19f6Settings->address = 4;
    asc19f6Settings->portName = "COM17";
    CASC19fDevice device(asc19f6Settings);
    CASC19fDevice *asc19f6Device = &device;
    asc19ffDevice->startDevice();

    Casc19f6plotTimer timer;
    Casc19f6plotTimer *asc19f6plotTimer = &timer;
    asc19f6plotTimer->setInterval(100);

    Casc19f6plotThread thread;
    Casc19f6plotThread *asc19f6plotThread = &thread;
    asc19f6plotDevice->moveToThread(asc19f6plotThread);
    asc19f6plotTimer->moveToThread(asc19f6plotThread);

    QObject::connect(asc19f6plotThread, SIGNAL(started()), asc19f6plotDevice, SLOT(startDevice()));
    QObject::connect(asc19f6plotDevice, SIGNAL(workFinished()), asc19f6plotDevice, SLOT(deleteLater()));

// automatically delete thread and task object when work is done:
    QObject::connect(asc19f6plotThread, SIGNAL(started()),    asc19f6plotTimer,  SLOT(start()));
    QObject::connect(asc19f6plotTimer,  SIGNAL(timeout()),    asc19f6plotDevice, SLOT(processTimer()));

    QObject::connect(asc19f6plotDevice, SIGNAL(workFinished()), asc19f6plotTimer,  SLOT(stop()));
    QObject::connect(asc19f6plotDevice, SIGNAL(workFinished()), asc19f6plotTimer,  SLOT(deleteLater()));
    QObject::connect(asc19f6plotDevice, SIGNAL(workFinished()), asc19f6plotThread, SLOT(quit()));

    QObject::connect(asc19f6plotThread, SIGNAL(finished()),   asc19f6plotTimer,  SLOT(stop()));
    QObject::connect(asc19f6plotThread, SIGNAL(finished()),   asc19f6plotThread, SLOT(deleteLater()));

    asc19f6plotThread->start();
*/

    QDialog dialog;
    dialog.setGeometry(100, 100, 800, 600);

    QVBoxLayout vBoxLayout;
    vBoxLayout.setContentsMargins(0, 0, 0, 0);
    vBoxLayout.setSpacing(0);

    CASC19F6Plot asc19fPlot;

    vBoxLayout.addWidget(&asc19fPlot);
    dialog.setLayout(&vBoxLayout);
    dialog.show();

    const bool result = app.exec();

//    asc19f6plotThread->quit();
//    asc19f6plotThread->terminate();
//    asc19f6plotThread->wait();

    return result;
}
