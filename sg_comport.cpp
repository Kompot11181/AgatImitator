/*
модуль для работы с СОМ-портами
родной для Qt, дополнительные пакеты не нужны (в файл проекта *.pro нужно добавить: QT += serialport)
реализована сборка пакетов из 8-байтных кусков в 1 целый,
выдается сигнал packRecieved с содержимым пакета в виде QByteArray
настройки порта задаются при открытии (процедура SgComPort::open)
(в данном варианте - стандартные, пред-определенные; писалось под Гамму;
если понадобятся другие - нужно сделать, или загнать в заголовок функции open)
! в линуксе СОМ-порты открываются только из-под рута
для отладки в креаторе - нужно входить в систему под рутом;
учесть, что собьются настройки проекта, и изменятся права на файлы проекта
*/
#include "sg_comport.h"
#include <QDebug>
#include <QException>
#include <QProcess>
#include <QtSerialPort/QSerialPortInfo>

//==================================================
// получения списка всех стандартных скоростей СОМ-портов
QStringList SgComPort::getBitRateList()
{
    QStringList res;
    QString strBitRate;
    QString st;
    foreach (const qint32 &info, QSerialPortInfo::standardBaudRates()) {
        strBitRate = QString("%1").arg(info);
        res.append(strBitRate);
    }
    return res;
}

//==================================================
// получение списка всех существующих в системе СОМ-портов
// в формате СОМ1, СОМ2,... независимо от ОС
// (в линуксе они зовутся ttyS0, ttyS1,...; в БУВО они зовутся ttyAP0, ttyAP1,...)
QStringList SgComPort::getComList()
{
    QStringList res;
    QString st;

#if defined(Q_OS_LINUX)
    // штатная программа для компа с преобразователем RS422-RS485
    // не подходит - не видит плату преобразоваетелей и портов ttyAPX
    // решаем через загрузку процесса dmesg
    QProcess proc;
    proc.start("dmesg");    //|grep tty*");
    proc.waitForFinished();
    st = QString(proc.readAllStandardOutput());
    // поиск и сохранение в списке по регуляркам типа ttySXX и ttyAPXX
    int pos = 0;
    QRegExp rx("(ttyAP\\d{1,2}|ttyS\\d{1,2})");
    while ((pos = rx.indexIn(st, pos)) != -1) {
        res << rx.cap(1);
        pos += rx.matchedLength();
    }
#else
    //logMsg(msgInfo, "Старт в ОС не-Линукс");
    QString com_name;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        st = info.portName();
    #if defined(Q_OS_WIN)
        com_name = st;
    #elif defined(Q_OS_UNIX)
        // для преобразования к виду COM1, COM2...
        //com_name = "COM" + QString('0' + info.portName().remove(QRegExp("\\D")).toInt() + 1);
        // стандартные названия для системы
        com_name = st;
    #else
        com_name = st;
    #endif
        res.append(com_name);
    }
#endif
    res.sort();
    return res;
}
//==================================================
SgComPort::SgComPort(QObject *parent) : QObject(parent)
{
    com = new QSerialPort();
    // параметры порта - задаются при открытии
    //com->setBaudRate(QSerialPort::Baud9600);
    //com->setDataBits(QSerialPort::Data8);
    //com->setStopBits(QSerialPort::OneStop);
    //com->setParity(QSerialPort::NoParity);
    com->setFlowControl(QSerialPort::NoFlowControl);
    com->setReadBufferSize(1000);
    mode = "Closed";
    com_name = "";
    opened = false;
    connect(com, SIGNAL(readyRead()), SLOT(read()));
    connect(com, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(com_error(QSerialPort::SerialPortError)));
//	connect(&packComplete, SIGNAL(timeout()), SLOT(on_pack_complete()));
//	packComplete.setTimerType(Qt::PreciseTimer);
}

SgComPort::~SgComPort()
{
    if(opened) com->close();
    com->deleteLater();
}

bool SgComPort::isOpened()
{
    return opened;
}

void SgComPort::close()
{
    com->close();
    opened = false;
    com_name = "";
    mode = "Closed";
}

QString SgComPort::errorString()
{
    return com->errorString();
}

bool SgComPort::open(int idx, qint32 baud)
{
    com_name = getComName(idx);
    mode = "Closed";
    bool res = false;
    if (opened) com->close();
    com->setPortName(com_name);
    com->setBaudRate(baud);
    com->setDataBits(QSerialPort::Data8);
    com->setStopBits(QSerialPort::OneStop);
    com->setParity(QSerialPort::NoParity);
    // com->setBreakEnabled(false);
    //com->setFlowControl(QSerialPort::NoFlowControl);
    try {
        res = com->open(QIODevice::ReadWrite);
        if (!res) {
            res = com->open(QIODevice::ReadOnly);
            if(res) {
                mode = "ReadOnly";
            } else {
                mode = com->errorString();
            }
        } else {
            mode = "ReadWrite";
        }
    } catch (QException e) {
        throw QException(e);
    }
    opened = res;
    return res;
}

bool SgComPort::open(QString comName, qint32 baud)
{
    com_name = comName;
    mode = "Closed";
    bool res = false;
    if (opened) com->close();
    com->setPortName(com_name);
    com->setBaudRate(baud);
    com->setDataBits(QSerialPort::Data8);
    com->setStopBits(QSerialPort::OneStop);
    com->setParity(QSerialPort::NoParity);
    // com->setBreakEnabled(false);
    //com->setFlowControl(QSerialPort::NoFlowControl);
    try {
        res = com->open(QIODevice::ReadWrite);
        if (!res) {
            res = com->open(QIODevice::ReadOnly);
            if(res) {
                mode = "ReadOnly";
            } else {
                mode = com->errorString();
            }
        } else {
            mode = "ReadWrite";
        }
    } catch (QException e) {
        throw QException(e);
    }
    opened = res;
    return res;
}

QString SgComPort::getComName(int portIdx)
{
    return QString("%1%2").arg(com_name_prefix).arg(com_start_index + portIdx);
}

void SgComPort::read()
{
    onePack = com->readAll();
    recievedPack.append(onePack);
//    packComplete.start(1);         // недостаточно 1 мсек
    emit packRecieved(recievedPack);
    recievedPack.clear();
}

void SgComPort::com_error(QSerialPort::SerialPortError err)
{
    QString st;// = err.errorString();// всегда пусто, по крайней мере, в АстраЛинуксе
    switch (err) {
    case QSerialPort::NoError:
        st = "NoError";
        break;
    case QSerialPort::DeviceNotFoundError:
        st = "DeviceNotFoundError";
        break;
    case QSerialPort::PermissionError:
        st = "PermissionError";
        break;
    case QSerialPort::OpenError:
        st = "OpenError";
        break;
    case QSerialPort::ParityError:
        st = "ParityError";
        break;
    case QSerialPort::FramingError:
        st = "FramingError";
        break;
    case QSerialPort::BreakConditionError:
        st = "BreakConditionError";
        break;
    case QSerialPort::WriteError:
        st = "WriteError";
        break;
    case QSerialPort::ReadError:
        st = "ReadError";
        break;
    case QSerialPort::ResourceError:
        st = "ResourceError";
        break;
    case QSerialPort::UnsupportedOperationError:
        st = "UnsupportedOperationError";
        break;
    case QSerialPort::UnknownError:
        st = "UnknownError";
        break;
    case QSerialPort::TimeoutError:
        st = "TimeoutError";
        break;
    case QSerialPort::NotOpenError:
        st = "NotOpenError";
        break;
    default:
        st = "NoError";
        break;
    }
    st += ":\n " + com->errorString();
    emit error(st);
}

/*
void SgComPort::on_pack_complete()
{
    packComplete.stop();
    emit packRecieved(recievedPack);
    recievedPack.clear();
}
*/

void SgComPort::write(QByteArray pack)
{
    com->write(pack, pack.size());
    //com->flush(); // не нужно, делается автоматом
}
