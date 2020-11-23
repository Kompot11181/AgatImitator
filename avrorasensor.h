/***************************************************
 *  класс пакета протокола Аврора
 * –	скорость передачи, бит/сек	57600;
 * –	количество бит данных	8;
 * –	стоп-бит 	1
 *
 ***************************************************/

#ifndef AVRORASENSOR_H
#define AVRORASENSOR_H
#include <QObject>
#include <QDebug>

//#define NO_CRC                          // если определено, игнорировать ошибку CRC

namespace AvroraConst{
    constexpr int maxChnls = 10;        // максимальное кол-во каналов в ответе
    constexpr int bytesPerChnl = 4;     // кол-во байт на канал (float)

    constexpr char SOT = '\x1F';        // Start Of Transaction
    constexpr char SCT = '\x24';        // Space Char of Transaction
    constexpr char RES = '\x00';        // Reserve byte
    constexpr char EOT = '\x2F';        // End Of Transaction
    constexpr char STT = '\x55';        // STop Transaction

    constexpr int posSOT = 0;           // адрес символа начала пакета
    constexpr int posDST = 1;           // адрес байта номера инициатора
    constexpr int posSRC = 2;           // адрес байта номера источника
    constexpr int posSCT = 3;           // адрес байта-разделителя
    constexpr int posCMD = 4;           // адрес номера команды
    constexpr int posDAT = 5;           // адрес начала данных
    constexpr int posDAT0 = 5;          // адрес начала 0-го значения данных
    constexpr int posDAT1 = 9;          // адрес начала 1-го значения данных
    constexpr int posDAT2 = 13;         // адрес начала 2-го значения данных (резерв; =0)
    constexpr int posERR = 17;          // адрес байта состояния
    constexpr int posSTAT = 18;         // адрес байта кода режима работы
    constexpr int posRES = 19;          // адрес резервного байта
    constexpr int posEndSTT = 0;        // адрес стоп-байта относительно конца пакета
    constexpr int posEndEOT = -1;       // адрес байта EOT относительно конца пакета
    constexpr int posEndCRCH = -2;      // адрес старшего байта CRC относительно конца пакета
    constexpr int posEndCRCL = -3;      // адрес младшего байта CRC относительно конца пакета (младший первый)
    constexpr int posEndCRC = -3;       // адрес CRC относительно конца пакета
    constexpr int posEndDat = -4;       // адрес последнего байта поля данных относительно конца пакета
}

namespace koralCmdConst{
    constexpr char MeasureVolume = 0x01;   // измерение объемного расхода без счёта объёма
    constexpr char StartVolumeCnt = 0x02;  // запуск счёта объема
    constexpr char StopVolumeCnt = 0x03;   // стоп счёта объёма
    constexpr char ClearVolumeCnt = 0x04;  // сброс счёта объёма. Значение приравнивается к нулю
    constexpr char SetControl = 0x05;      // включение режима "Контроль"
    constexpr char MeasureDensity = 0x06;  // измерение плотности (режим плотномера)
    constexpr char StartMassCnt = 0x07;    // запуск измерения массы
    constexpr char StopMassCnt = 0x08;     // стоп измерения массы
    constexpr char ClearMassCnt = 0x09;    // сброс значения измеренной массы
    constexpr char DiagDevice = 0x10;      // запрос диагностических данных (не доступно)
    constexpr char IdentDevice = 0x11;     // запрос идентификационных данных
    constexpr char DiagDevice1 = 0x12;     // запрос диагностических данных (не доступно)
    constexpr char DiagDevice2 = 0x13;     // запрос диагностических данных (не доступно)
    constexpr char DiagDevice3 = 0x14;     // запрос диагностических данных (не доступно)
    constexpr char DiagDevice4 = 0x15;     // запрос диагностических данных (не доступно)
    constexpr char DiagDevice5 = 0x16;     // запрос диагностических данных (не доступно)
    constexpr char DiagDevice6 = 0x17;     // запрос диагностических данных (не доступно)
    constexpr char MaxNumOfCommands = 0x18;// для проверки на корректность номера команды
}

namespace koralErrorConst{
    constexpr char NoErr = 0x00;    // нет ошибок
    constexpr char Cntrl = 0x01;    // режим "контроль"
    constexpr char Res = 0x02;      // резерв
    constexpr char Empty = 0x03;    // отсутствие измеряемой среды
    constexpr char Acust = 0x04;    // ошибка части акустических каналов
    constexpr char Second = 0x05;   // ошибка вторичного преобразователя
    constexpr char First = 0x06;    // нет первичного преобразователя
    constexpr char NoDencity = 0x07;// отсутствие плотномера (для команд 0x06-0x09)
    constexpr char ErDencity = 0x08;// неисправность плотномера (для команд 0x06-0x09)
    constexpr char Any = 0x0F;      // любая из ошибок Коралла (маска)
}

namespace koralStatConst{
    constexpr char Volume = 0x00;          // режима измерения объемного расхода без счёта объёма
    constexpr char VolumeAndCount = 0x01;  // режима измерения объемного расхода и счёт объёма
    constexpr char Mass = 0x02;            // режима измерения массового расхода без счёта массы
    constexpr char MassAndCount = 0x03;    // режима измерения массового расхода и счёт массы
    constexpr char ACalibration = 0x04;    // режима калибровки аналогового выходного сигнала
    constexpr char Imitation = 0x05;       // режима имитации расхода (при поверке)
    constexpr char Calibration = 0x06;     // режима калибровки
    constexpr char ROMreadWrite = 0x07;    // режима работы с ПЗУ при записи и чтении
}

typedef union{
    char	array[sizeof(float)];
    float   fdata;
    qint32  idata;
}AvroraChannel;

// Запрос значений для датчиков
struct AvroraPackCMD{
    char startByte;     // стартовый байт 0x1F
    char dstByte;       // адрес расходомера
    char srcByte;       // адрес источника запроса
    char spaceByte;     // байт-разделитель 0x24
    char cmdByte;       // байт кода команды
//    koralChannel chnl[koralConst::maxChnls];  // данные заполняются 0, длина неважна?
    uint16_t crc;       // контрольная сумма
    char endByte;       // байт конца посылки
    char stopByte;      // стоп-байт транзакции
};

// ответ, сформиованный датчиком (концентратором)
struct AvroraPack{
    char startByte;     // стартовый байт 0x1F
    char dstByte;       // адрес источника запроса
    char srcByte;       // адрес расходомера
    char spaceByte;     // байт-разделитель 0x24
    char cmdByte;       // байт команды
    AvroraChannel chnl[AvroraConst::maxChnls];  // данные
    char errorByte;     // байт состояния (см. koralErrorConst)
    AvroraChannel errArr;// поле ошибок (только для БКС)
    char statusByte;    // байт кода режима работы
    char statusArr[AvroraConst::maxChnls];  // массив статусов для каждого канала (для БКС14)
    char emptyByte;     // пустой байт (=0)
    uint16_t crc;       // контрольная сумма
    char endByte;       // байт конца посылки
    char stopByte;      // стоп-байт транзакции
};

enum tSensorType
{
    KorallType = 0,
    VibroType,
    KRUType,
    KorallPlusType,
    KorallPlusType1,
    KorallPlusType2,
    BKS14Type,
    BKS14Type1,
    BKS14Type2,
    BKS16Type,
    BKS16Type1,
    BKS16Type2,
    BKS16Type3,
    BKS16Type4,
    NumOfTypes
};

enum class ERR_CODE
{
    ERR_NO_ERROR = 0,
    ERR_WRONG_SOT,
    ERR_WRONG_SCT,
    ERR_WRONG_CRC,
    ERR_WRONG_EOT,
    ERR_WRONG_STT,
    ERR_UNKNOWN,
    ERR_MAX_ERROR
};

static constexpr uint16_t tblcrc[256] = {
        0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50a5,  0x60c6,  0x70e7,
        0x8108,  0x9129,  0xa14a,  0xb16b,  0xc18c,  0xd1ad,  0xe1ce,  0xf1ef,
        0x1231,  0x0210,  0x3273,  0x2252,  0x52b5,  0x4294,  0x72f7,  0x62d6,
        0x9339,  0x8318,  0xb37b,  0xa35a,  0xd3bd,  0xc39c,  0xf3ff,  0xe3de,
        0x2462,  0x3443,  0x0420,  0x1401,  0x64e6,  0x74c7,  0x44a4,  0x5485,
        0xa56a,  0xb54b,  0x8528,  0x9509,  0xe5ee,  0xf5cf,  0xc5ac,  0xd58d,
        0x3653,  0x2672,  0x1611,  0x0630,  0x76d7,  0x66f6,  0x5695,  0x46b4,
        0xb75b,  0xa77a,  0x9719,  0x8738,  0xf7df,  0xe7fe,  0xd79d,  0xc7bc,
        0x48c4,  0x58e5,  0x6886,  0x78a7,  0x0840,  0x1861,  0x2802,  0x3823,
        0xc9cc,  0xd9ed,  0xe98e,  0xf9af,  0x8948,  0x9969,  0xa90a,  0xb92b,
        0x5af5,  0x4ad4,  0x7ab7,  0x6a96,  0x1a71,  0x0a50,  0x3a33,  0x2a12,
        0xdbfd,  0xcbdc,  0xfbbf,  0xeb9e,  0x9b79,  0x8b58,  0xbb3b,  0xab1a,
        0x6ca6,  0x7c87,  0x4ce4,  0x5cc5,  0x2c22,  0x3c03,  0x0c60,  0x1c41,
        0xedae,  0xfd8f,  0xcdec,  0xddcd,  0xad2a,  0xbd0b,  0x8d68,  0x9d49,
        0x7e97,  0x6eb6,  0x5ed5,  0x4ef4,  0x3e13,  0x2e32,  0x1e51,  0x0e70,
        0xff9f,  0xefbe,  0xdfdd,  0xcffc,  0xbf1b,  0xaf3a,  0x9f59,  0x8f78,
        0x9188,  0x81a9,  0xb1ca,  0xa1eb,  0xd10c,  0xc12d,  0xf14e,  0xe16f,
        0x1080,  0x00a1,  0x30c2,  0x20e3,  0x5004,  0x4025,  0x7046,  0x6067,
        0x83b9,  0x9398,  0xa3fb,  0xb3da,  0xc33d,  0xd31c,  0xe37f,  0xf35e,
        0x02b1,  0x1290,  0x22f3,  0x32d2,  0x4235,  0x5214,  0x6277,  0x7256,
        0xb5ea,  0xa5cb,  0x95a8,  0x8589,  0xf56e,  0xe54f,  0xd52c,  0xc50d,
        0x34e2,  0x24c3,  0x14a0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
        0xa7db,  0xb7fa,  0x8799,  0x97b8,  0xe75f,  0xf77e,  0xc71d,  0xd73c,
        0x26d3,  0x36f2,  0x0691,  0x16b0,  0x6657,  0x7676,  0x4615,  0x5634,
        0xd94c,  0xc96d,  0xf90e,  0xe92f,  0x99c8,  0x89e9,  0xb98a,  0xa9ab,
        0x5844,  0x4865,  0x7806,  0x6827,  0x18c0,  0x08e1,  0x3882,  0x28a3,
        0xcb7d,  0xdb5c,  0xeb3f,  0xfb1e,  0x8bf9,  0x9bd8,  0xabbb,  0xbb9a,
        0x4a75,  0x5a54,  0x6a37,  0x7a16,  0x0af1,  0x1ad0,  0x2ab3,  0x3a92,
        0xfd2e,  0xed0f,  0xdd6c,  0xcd4d,  0xbdaa,  0xad8b,  0x9de8,  0x8dc9,
        0x7c26,  0x6c07,  0x5c64,  0x4c45,  0x3ca2,  0x2c83,  0x1ce0,  0x0cc1,
        0xef1f,  0xff3e,  0xcf5d,  0xdf7c,  0xaf9b,  0xbfba,  0x8fd9,  0x9ff8,
        0x6e17,  0x7e36,  0x4e55,  0x5e74,  0x2e93,  0x3eb2,  0x0ed1,  0x1ef0
};

class AvroraSensor
{
public:
    AvroraSensor();
    char getDst() const {return _packCMD.dstByte;}   // получить адрес запрашиваемого расходомера
    char getSrc() const {return _packCMD.srcByte;}   // получить адрес источника запроса
    char getCmd() const {return _packCMD.cmdByte;}   // получить код команды
    uint16_t getCRC() const {return _pack.crc;}      // получить вычисленную CRC
    QByteArray getPack() const {return _packarray;}  // получить сформированный пакет посылки QByteArray
    void setDst(const char dst) {_pack.dstByte = dst;}   // задать адрес истоника запроса
    void setSrc(const char src) {_pack.srcByte = src;}   // задать адрес расходомера
    void setCmd(const char cmd) {_pack.cmdByte = cmd;}   // задать номер команды
    void setErr(const char err) {_pack.errorByte = err;} // задать байт состояния
    void setErr32(const qint32 err) {_pack.errArr.idata = err;} // задать поле ошибок БКС
    void setStat(const char st) {_pack.statusByte = st;} // задать байт кода режима работы
    void setStatArray(const int num, const char st) {_pack.statusArr[num] = st;}  // массив статусов
    void setData(const int i, const float d)             // задать данные
    {
        if( (i >= 0) && (i < AvroraConst::maxChnls) )
            _pack.chnl[i].fdata = d;
    }

    int getErrorCode() const {return static_cast<int>(_errorCode);}  // содержит код ошибки, если преобразование неудачно
    QString getErrorMsg(int ec) const {return _errorMsg[ec];}        // содеражит описание кода ошибки

    void clear();                           // очистка данных packCMD, pack
    bool updateCMDPack(QByteArray);         // преобразует QByteArray в AvroraPackCMD, выдаёт true, если успешно
    bool makeAnswer(tSensorType type);           // формирует AvroraPack, выдаёт true, если успешно

    static void combineAnswer(QByteArray & pck);    // дописывает контрольную сумму, байты начала, конца (+ возможный дубляж)
    static uint16_t crc16(QByteArray arr, int start, int end);

private:
    AvroraPackCMD _packCMD;   // содержит последний пакет запроса (команды)
    AvroraPack _pack;         // содержит ответ на запрос
    QByteArray _packarray;   // содержит ответ в виде массива байтов
    ERR_CODE _errorCode;
    const QString _errorMsg[static_cast<int>(ERR_CODE::ERR_MAX_ERROR)] = {
        "",
        "Wrong start of transaction",
        "Wrong space char",
        "Wrong CRC",
        "Wrong end of transaction",
        "Wrong stop byte",
        "Unknown error of parsing"
    };
};


#endif // AVRORASENSOR_H
