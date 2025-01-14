#ifndef CASC19F6TYPES_H
#define CASC19F6TYPES_H

#include <QMetaType>
#include <QList>
#include <QString>
#include <QHash>
#include <QDateTime>
#include <QVariant>
#include <QRect>
#include <QSize>

//  Структура общих настроек
typedef struct TMASC19F6Settings
{
    int             id;
    int             mode;
    QString         dataDir = "";
    QString         naborDir = "";
//    TMOscScope      oscScope;
    int             type;
    int             address;
    int             timeOut;
    QString         portName;
    int             baudRate;
    int             parity;
    int             dataBit;
    int             stopBits;
    int             flowControl;

} TTMASC19F6Settings;
Q_DECLARE_METATYPE(TTMASC19F6Settings);
Q_DECLARE_METATYPE(TTMASC19F6Settings*);

#endif // CASC19F6TYPES_H
