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
#ifndef SGCOMPORT_H
#define SGCOMPORT_H
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#if defined(Q_OS_WIN)
const QString com_name_prefix = "COM";
const int com_start_index = 1;
#elif defined(Q_OS_UNIX)
const QString com_name_prefix = "ttyS";
const int com_start_index = 0;
#else
const QString com_name_prefix = "COM";
const int com_start_index = 1;
#endif



class SgComPort : public QObject
{
    Q_OBJECT
public:
    explicit SgComPort(QObject *parent = 0);
    ~SgComPort();
    QString com_name;
    QSerialPort* com;
    QString mode;

    static QStringList getComList();
    static QStringList getBitRateList();
    bool isOpened();
    bool open(int portIdx, qint32 baud = 115200);
    bool open(QString comName, qint32 baud = 115200);
    void close();
    QString getComName(int portIdx);
    QString errorString();
private:
    QString errSt;
    quint8 portIndex;
    bool opened;
    QTimer packComplete;
    QByteArray onePack;
    QByteArray recievedPack;
signals:
    void packRecieved(QByteArray pack);
    void error(QString errorString);
private slots:
    void read();
    void com_error(QSerialPort::SerialPortError err);
//	void on_pack_complete();
public slots:
    void write(QByteArray pack);
};
#endif // SGCOMPORT_H
