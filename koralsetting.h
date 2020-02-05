#ifndef KORALSETTING_H
#define KORALSETTING_H

#include <QWidget>
#include <QtWidgets>
#include "koral.h"  // добавлена лишь для типа koralChannel для перевода float в hex текст

class cKoralSetting : public QWidget
{
    Q_OBJECT
public:
    explicit cKoralSetting(QWidget *parent = 0);
    cKoralSetting(const quint32 num, tSensorType type, const quint8 adr) : cKoralSetting(0)
    {
        lNum->setText(QString::number(num) + ":");
        setType(type); setAddr(adr);
        // если сенсор чётный. Для равен массметра наоборот
        if((  (num%2) && (type != PlusMassType))
          ||(!(num%2) && (type == PlusMassType))) {
            QPalette pal = backwidget->palette();
            // изменить цвет, сделать его на 5% ярче
            pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).lighter(105)));
            backwidget->setPalette(pal);
            backwidget->setAutoFillBackground(true);    // автоматически залить фон цветом
        }
        else
        {
                    QPalette pal = backwidget->palette();
                    // изменить цвет, сделать его на 5% темнее
                    pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).darker(105)));
                    backwidget->setPalette(pal);
                    backwidget->setAutoFillBackground(true);    // автоматически залить фон цветом
                }
    }
    quint8 getAddr() const {return _addr;}
    tSensorType getType() const {return _type;}
    QString getName() const {return SensorsName[_type];}
    float getValue1() const {return _value1;}
    float getValue2() const {return _value2;}
    float getInc1() const {return _inc1;}
    float getInc2() const {return _inc2;}
    quint8 getErr() const {return _err;}
    quint8 getStat() const {return _stat;}
    bool getRnd1() const {return _rnd1;}
    bool getRnd2() const {return _rnd2;}
    void step()
    {
        if(_rnd1) randValue1();
        else incValue1();
        if(_rnd2) randValue2();
        else incValue2();
    }

    void blink(int interval, QColor col);

private:
    quint8 _addr = 0;       // адрес датчика в системе
    tSensorType _type = KorallType;       // тип датчика
    float _value1 = 0.0;    // первое значение
    float _value2 = 0.0;    // второе значение
    float _inc1 = 0.0;      // шаг изменения первого значения
    float _inc2 = 0.0;      // шаг изменения второго значения
    bool _rnd1 = false;     // флаг случайного изменения параметра 1
    bool _rnd2 = false;     // флаг случайного изменения параметра 2
    quint8 _err = 0;        // байт ошибки
    quint8 _stat = 0;       // байт статуса

    QWidget * backwidget;
    QVBoxLayout * verLayout;
    QHBoxLayout * horLayout;
    QLabel * lNum;
    QLabel * lAddress;
    QLabel * lValue1;
    QLabel * lValue2;
    QLabel * lFlags;
    QSpacerItem * horSpacer;

    QComboBox * comboBoxType;
    QSpinBox * spinBoxAddress;
    QSpinBox * spinBoxErr;
    QSpinBox * spinBoxStat;
    QCheckBox * checkBoxRnd1;
    QCheckBox * checkBoxRnd2;
    QDoubleSpinBox * dSpinBoxValue1;
    QDoubleSpinBox * dSpinBoxInc1;
    QDoubleSpinBox * dSpinBoxValue2;
    QDoubleSpinBox * dSpinBoxInc2;

    static const int ErrorCount = 9;
    static const int StatusCount = 8;
    static const int SensorsCount = NumOfTypes;
    const QString SensorsName[SensorsCount] = {
        tr("Коралл-8"),
        tr("Вибро-1"),
        tr("КРУ-1"),
        tr("Коралл+"),
        tr("+массметр"),
        tr("+Вибро")
    };
// максимальное значение байта ошибки и байта статуса
    const quint8 errStatMaxValues[SensorsCount][2] =
    {{6, 7}, {7, 1}, {0, 0x7F}, {8, 7}, {0, 0}, {0, 0}};
// подсказки
    const QString SensorHint[SensorsCount][4] = {
//Коралл
        {tr("Значение первого параметра (измеренное значение объёмного расхода)"),
         tr("Значение второго параметра (измеренное значение объёма)"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок\n"
             "1 - режим «Контроль»\n"
             "2 - резерв\n"
             "3 - отсутствие измеряемой среды\n"
             "4 - ошибка акустических каналов\n"
             "5 - ошибка вторичного преобразователя\n"
             "6 - нет первичного преобразователя"),
         tr("Байт статуса:\n"
             "0 - измерение объёмного расхода без счёта объёма\n"
             "1 - измерение объёмного расхода и счёт объёма\n"
             "2 - измерение массового расхода без счёта массы\n"
             "3 - измерение массового расхода и счёт массы\n"
             "4 - калибровка аналогового выходного сигнала\n"
             "5 - режим имитации расхода\n"
             "6 - режим калибровки\n"
             "7 - режим работы ПЗУ при записи и чтении")
        },         //Коралл
//Вибро-1
        {tr("Значение первого параметра (измеренное значение плотности)"),
         tr("Значение шестого параметра (измеренное значение температуры)"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок\n"
             "1 - отсутствие измеряемой среды\n"
             "2 - чувствительный элемент загрязнен\n"
             "3 - неисправность канала измерений температуры\n"
             "4 - неисправность канала измерений плотности электронного блока\n"
             "5 - ошибка электронного блока\n"
             "6 - нет первичного преобразователя\n"
             "7 - плотномер в режиме «Диагностика»"),
         tr("Байт статуса:\n"
             "0 - режим измерения плотности и температуры\n"
             "1 - режим «Диагностика»")
        },    //Вибро-1
//КРУ-1В
        {tr("Значение первого параметра (измеренное значение уровня жидкости)"),
         tr("Значение второго параметра (не используется)"),
         tr("не используется"),
         tr("Байт статуса:\n"
             "0 - рабочий режим\n"
             "1 - нет ПП\n"
             "2 - плохая связь с ПП\n"
             "4 - ошибка по питанию ПП\n"
             "8 - ошибка по питанию ВП\n"
             "16 - ошибка поиска импульсов или измерения\n"
             "32 - не соответствия з/н ПП и ВП\n"
             "64 - прочие ошибки"),
        },                    //КРУ-1В
//Коралл+
        {tr("Значение первого параметра (измеренное значение объёмного расхода)"),
         tr("Значение второго параметра (измеренное значение объёма)"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок\n"
             "1 - режим «Контроль»\n"
             "2 - резерв\n"
             "3 - отсутствие измеряемой среды\n"
             "4 - ошибка акустических каналов\n"
             "5 - ошибка вторичного преобразователя\n"
             "6 - нет первичного преобразователя\n"
             "7 - отсутствие плотномера\n"
             "8 - неисправность плотномера"),
          tr("Байт статуса:\n"
              "0 - измерение объёмного расхода без счёта объёма\n"
              "1 - измерение объёмного расхода и счёт объёма\n"
              "2 - измерение массового расхода без счёта массы\n"
              "3 - измерение массового расхода и счёт массы\n"
              "4 - калибровка аналогового выходного сигнала\n"
              "5 - режим имитации расхода\n"
              "6 - режим калибровки\n"
              "7 - режим работы ПЗУ при записи и чтении")
        },         //Коралл+
        {tr("Значение первого параметра (измеренное значение массового расхода)"),
         tr("Значение второго параметра (измеренное значение массы)"),
         tr(""), tr("")
        },          //+массметр
        {tr("Значение первого параметра (измеренное значение плотности)"),
         tr("Значение второго параметра (измеренное значение температуры)"),
         tr(""), tr("")
        }          //+Вибро
    };

signals:

public slots:
    void setAddr(int adr) {_addr = static_cast<quint8>(adr); spinBoxAddress->setValue(_addr); spinBoxAddress->setToolTip("0x" + QString::number(_addr, 16).toUpper());}
    void setType(int type);
    void setFixedType () {comboBoxType->setEnabled(false); spinBoxAddress->setEnabled(false); spinBoxErr->setVisible(false); spinBoxStat->setVisible(false); lFlags->setVisible(false);}
    void setErr(int er) {spinBoxErr->setValue(er); _err = static_cast<quint8>(spinBoxErr->value());}
    void setStat(int st) {spinBoxStat->setValue(st); _stat = static_cast<quint8>(spinBoxStat->value());}
    void setRnd1(bool rnd) {_rnd1 = rnd; checkBoxRnd1->setChecked(_rnd1);}
    void setRnd2(bool rnd) {_rnd2 = rnd; checkBoxRnd2->setChecked(_rnd2);}
    void setValue1(double v) {_value1 = static_cast<float>(v); dSpinBoxValue1->setValue(static_cast<double>(_value1)); koralChannel ch; ch.fdata = _value1; dSpinBoxValue1->setToolTip("0x" + QString::number(ch.idata & 0xFFFFFFFF, 16).toUpper());}
    void setValue2(double v) {_value2 = static_cast<float>(v); dSpinBoxValue2->setValue(static_cast<double>(_value2)); koralChannel ch; ch.fdata = _value2; dSpinBoxValue2->setToolTip("0x" + QString::number(ch.idata & 0xFFFFFFFF, 16).toUpper());}
    void setInc1(double i) {_inc1 = static_cast<float>(i); dSpinBoxInc1->setValue(static_cast<double>(_inc1)); dSpinBoxInc1->setToolTip(QString::number(_inc1).toUpper());}
    void setInc2(double i) {_inc2 = static_cast<float>(i); dSpinBoxInc2->setValue(static_cast<double>(_inc2)); dSpinBoxInc2->setToolTip(QString::number(_inc2).toUpper());}
    void incValue1() {setValue1(_value1 + _inc1); dSpinBoxValue1->setValue(static_cast<double>(_value1)); _value1 = static_cast<float>(dSpinBoxValue1->value());}
    void incValue2() {setValue2(_value2 + _inc2); dSpinBoxValue2->setValue(static_cast<double>(_value2)); _value2 = static_cast<float>(dSpinBoxValue2->value());}
    void randValue1() {setValue1(_value1 + ((qrand()%3)-1) * _inc1); _value1 = static_cast<float>(dSpinBoxValue1->value());}
    void randValue2() {setValue2(_value2 + ((qrand()%3)-1) * _inc2); _value2 = static_cast<float>(dSpinBoxValue2->value());}
    void restoreFromBlink() {spinBoxAddress->setPalette(spinBoxStat->palette());}
protected:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // KORALSETTING_H
