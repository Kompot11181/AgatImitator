#include "avrorasensor.h"

AvroraSensor::AvroraSensor()
{

}

// clear pack; pack = 0
void AvroraSensor::clear()
{
    _pack.startByte = 0; _packCMD.startByte = 0;
    _pack.srcByte = 0;   _packCMD.srcByte = 0;
    _pack.dstByte = 0;   _packCMD.dstByte = 0;
    _pack.spaceByte = 0; _packCMD.spaceByte = 0;
    _pack.cmdByte = 0;   _packCMD.cmdByte = 0;
    for(int i = 0; i < AvroraConst::maxChnls; ++i) {
        _pack.chnl[i].idata = 0;
        _pack.statusArr[i] = 0;
    }
    _pack.errorByte = 0; _pack.errArr.idata = 0;
    _pack.statusByte = 0;
    _pack.emptyByte = 0;
    _pack.crc = 0;       _packCMD.crc = 0;
    _pack.endByte = 0;   _packCMD.endByte = 0;
    _pack.stopByte = 0;  _packCMD.stopByte = 0;
    _errorCode = ERR_CODE::ERR_NO_ERROR;
}


bool AvroraSensor::updateCMDPack(QByteArray pck)
{
    using namespace AvroraConst;
    clear();
    // режет возможные артефакты в начале пакета до первого байта полезных данных
    pck = pck.mid(pck.indexOf(AvroraConst::SOT));
    // заменить задвоенные символы признака начала пакета на одинарные
    pck.replace(QByteArray(2, AvroraConst::SOT), QByteArray(1, AvroraConst::SOT));
    // заменить задвоенные символы признака конца пакета на одинарные
    pck.replace(QByteArray(2, AvroraConst::EOT), QByteArray(1, AvroraConst::EOT));
    int endptr = pck.length()-1;    // указатель на последний элемент массива

    // look for start of transaction
    if(pck[0] != SOT)
    {
        _errorCode = ERR_CODE::ERR_WRONG_SOT;
        return false;
    }
    _packCMD.startByte = pck[0];

    // look for space char
    if(pck[3] != SCT)
    {
        _errorCode = ERR_CODE::ERR_WRONG_SCT;
        return false;
    }
    _packCMD.spaceByte = pck[3];

    // look for end of transaction
    if(pck[endptr-1] != EOT)
    {
        _errorCode = ERR_CODE::ERR_WRONG_EOT;
        return false;
    }
    _packCMD.endByte = pck[endptr + posEndEOT];

    // look for stop of transaction
    if(pck[endptr] != STT)
    {
        _errorCode = ERR_CODE::ERR_WRONG_STT;
        return false;
    }
    _packCMD.stopByte = pck[endptr + posEndSTT];

    // look for crc-code
    uint16_t pack_crc = ((pck[endptr + posEndCRCH] << 8) & 0xFF00) | (pck[endptr + posEndCRCL] & 0x00FF);
    // calculate crc
    uint16_t crc = crc16(pck, posDST, endptr + posEndDat);
    if( crc !=  pack_crc)
    {
        _errorCode = ERR_CODE::ERR_WRONG_CRC;
        _pack.crc = crc;
        qDebug() << "Calculated CRC = " << hex << showbase << uppercasedigits << crc << getErrorMsg(getErrorCode());
        qDebug() << " CRC from pack = " << hex << showbase << uppercasedigits << pack_crc;
#ifndef NO_CRC
        return false;
#endif
    }
    _packCMD.dstByte = pck[posDST];
    _packCMD.srcByte = pck[posSRC];
    _packCMD.cmdByte = pck[posCMD];
    return true;
}

bool AvroraSensor::makeAnswer(tSensorType type)
{
    _packarray.clear();
    switch(type){
        case KorallType: {
            // формируем заголовок пакета:
            _packarray.append(_pack.dstByte)
                .append(_pack.srcByte)
                .append(AvroraConst::SCT)
                .append(_pack.cmdByte);
            // формируем поле данных
            for(int i = 0; i < 3; ++i)
                _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
                .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
            _packarray.append(_pack.errorByte)
                    .append(_pack.statusByte)
                    .append(_pack.emptyByte);
            break; }
        case VibroType: {
            // формируем заголовок пакета:
            _packarray.append(_pack.dstByte)
                .append(_pack.srcByte)
                .append(AvroraConst::SCT)
                .append(_pack.cmdByte);
            // формируем поле данных
            _packarray.append(_pack.errorByte)
                    .append(_pack.statusByte);
            for(int i = 0; i < 3; ++i)
                _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
                .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
            break; }
        case KRUType: {
            // формируем заголовок пакета:
            _packarray.append(_pack.dstByte)
                .append(_pack.srcByte)
                .append(AvroraConst::SCT)
                .append(_pack.cmdByte);
            // формируем поле данных
            _packarray.append(_pack.errorByte);
            _packarray.append(_pack.chnl[0].array[3]).append(_pack.chnl[0].array[2])
                      .append(_pack.chnl[0].array[1]).append(_pack.chnl[0].array[0]);
            break; }
        case KorallPlusType: {
            // формируем заголовок пакета:
            _packarray.append(_pack.dstByte)
                .append(_pack.srcByte)
                .append(AvroraConst::SCT)
                .append(_pack.cmdByte);
            // формируем поле данных
            if(_pack.cmdByte < koralCmdConst::MeasureDensity){
                for(int i = 0; i < 2; ++i)
                    _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
                    .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
                _packarray.append('\x0').append('\x0').append('\x0').append('\x0');
            }
            else if((_pack.cmdByte >= koralCmdConst::MeasureDensity) && (_pack.cmdByte <= koralCmdConst::ClearMassCnt)) {
                for(int i = 0; i < 6; ++i)
                    _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
                    .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
            }
            _packarray.append(_pack.errorByte)
                    .append(_pack.statusByte)
                    .append(_pack.emptyByte);
            break; }
        case BKS14Type: {
        // формируем заголовок пакета:
        _packarray.append(_pack.dstByte)
            .append(_pack.srcByte)
            .append(AvroraConst::SCT)
            .append(_pack.cmdByte);
        // формируем поле данных
        _packarray.append('\0').append('\0');                       // 2 байта статуса БКС
        for(int i = 0; i < 6; ++i) {
            _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
                      .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
            if (_pack.cmdByte == 0x06) {_packarray.append(_pack.statusArr[i] | 0x10);    // режим "Контроль" включён
            } else {                    _packarray.append(_pack.statusArr[i]);};
        }
        break;}

        case BKS16Type: {
        // формируем заголовок пакета:
        _packarray.append(_pack.dstByte)
            .append(_pack.srcByte)
            .append(AvroraConst::SCT)
            .append(_pack.cmdByte);
        // формируем поле данных
        _packarray.append(10)                        // 10 параметров
                .append(_pack.errArr.array[3])
                .append(_pack.errArr.array[2])
                .append(_pack.errArr.array[1])
                .append(_pack.errArr.array[0]);
        for(int i = 0; i < 10; ++i)
            _packarray.append(_pack.chnl[i].array[3]).append(_pack.chnl[i].array[2])
            .append(_pack.chnl[i].array[1]).append(_pack.chnl[i].array[0]);
        break;}
        default:
            return false;
    }
    combineAnswer(_packarray);
    return true;
}

void AvroraSensor::combineAnswer(QByteArray & pck)
{
    // расчёт контрольной суммы и формирование конца пакета
    uint16_t crc = AvroraSensor::crc16(pck, 0, pck.length()-1);
    pck.append(crc & 0x00FF)
        .append((crc >> 8) & 0x00FF);
    // заменить одинарные символы признака начала пакета на двойные
    pck.replace(QByteArray(1, AvroraConst::SOT), QByteArray(2, AvroraConst::SOT));
    // заменить одинырные символы признака конца пакета на двойные
    pck.replace(QByteArray(1, AvroraConst::EOT), QByteArray(2, AvroraConst::EOT));
    //добавить признак начала пакета
    pck.insert(0, AvroraConst::SOT);
    //добавить признак конца пакета
    pck.append(AvroraConst::EOT)
        .append(AvroraConst::STT);
}

// подсчёт контрольной суммы.
// входные данные - массив байт, стартовый номер байта, конечный номер байта
// для подсчёта.
// алгоритм основан на данных из сгенерированной таблицы tblcrc[256]
uint16_t AvroraSensor::crc16(QByteArray arr, int start, int end)
{
    uint16_t crc = 0;
    for(int i = start; i <= end; ++i)
    {
        crc = ((crc << 8) & 0xFF00) ^ tblcrc[ ((crc >> 8)^(arr[i])) & 0x00FF];
    }
    return crc;
}

// расчёт таблицы tblcrc[256]
/*
void initcrc16tab(void)
{
      int  b, v, i;
      const int P = 0x1021;
      for( b = 0; b < 256; ++b )
      {
            for( v = b << 8, i = 8; --i >= 0; )
                  v = v&0x8000 ? (v << 1)^P : v<<1;
            tblcrc[b] = v;
      }
}*/
