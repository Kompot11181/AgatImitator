#ifndef SENSORSETTINGS_H
#define SENSORSETTINGS_H

#include <QWidget>
#include <QtWidgets>
#include "avrorasensor.h"  // добавлена лишь для типа AvroraChannel для перевода float в hex текст

class SensorSettings : public QWidget
{
    Q_OBJECT
public:
    explicit SensorSettings(QWidget *parent = 0);
    SensorSettings(const quint32 num, tSensorSettingsType type, const quint8 adr) : SensorSettings(0)
    {
        lNum->setText(QString::number(num) + ":");
        setType(type); setAddr(adr);
        QPalette pal = backwidget->palette();
        // если сенсор чётный. Для равен массметра наоборот
        if((  (num%2) && ((type != KorallPlusType1) && (type != BKS16Type1) && (type != BKS16Type3) && (type != BKS14Type1))) ||
           ( !(num%2) && ((type == KorallPlusType1) || (type == BKS16Type1) || (type == BKS16Type3) || (type == BKS14Type1)))) {
            // изменить цвет, сделать его на 5% ярче
            pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).lighter(105)));
            pal.setColor(QPalette::Base, QColor(pal.color(QPalette::Window)));
        }
        else
        {

                    // изменить цвет, сделать его на 5% темнее
                    pal.setColor(QPalette::Window, QColor(pal.color(QPalette::Window).darker(105)));
                    pal.setColor(QPalette::Base, QColor(pal.color(QPalette::Window)));
        }
        backwidget->setPalette(pal);
        leAddress->setPalette(pal);
        leValue1->setPalette(pal);
        leValue2->setPalette(pal);
        leFlags->setPalette(pal);
        backwidget->setAutoFillBackground(true);    // автоматически залить фон цветом
    }

    quint8 getAddr() const {return _addr;}
    tSensorSettingsType getType() const {return _type;}
    QString getName() const {return sensorsList[_type].name;}
    QString getAddrName() const {return leAddress->text();}
    QString getValue1Name() const {return leValue1->text();}
    QString getValue2Name() const {return leValue2->text();}
    QString getFlagsName() const {return leFlags->text();}
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
    tSensorSettingsType _type = KRUType;       // тип датчика
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
    QLineEdit * leAddress;
    QLineEdit * leValue1;
    QLineEdit * leValue2;
    QLineEdit * leFlags;
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

    static const int SensorsCount = NumOfTypes;

    typedef struct {
        QString image;
        QString name;
        bool enabled;
    } SensorList;

    const SensorList sensorsList[SensorsCount] = {
        { ":/images/sensor_2.png", tr(" Коралл-8"),  true  },
        { ":/images/sensor_4.png", tr(" Гиацинт-У"), true  },
        { ":/images/sensor_1.png", tr(" Вибро-1"),   true  },
        { ":/images/sensor_3.png", tr(" КРУ-1"),     true  },
        { ":/images/sensor_7.png", tr(" Коралл+"),   true  },
        { "",                      tr("+ массметр+"),false },
        { "",                      tr("+ Вибро"),    false },
        { ":/images/sensor_8.png", tr("  БКС14 +"),  true  },
        { "",                      tr("+ БКС14 +"),  false },
        { "",                      tr("+ БКС14  "),  false },
        { ":/images/sensor_8.png", tr("  БКС16 +"),  true  },
        { "",                      tr("+ БКС16 +"),  false },
        { "",                      tr("+ БКС16 +"),  false },
        { "",                      tr("+ БКС16 +"),  false },
        { "",                      tr("+ БКС16  "),  false }
    };


// максимальное значение байта ошибки и байта статуса
    const quint8 errStatMaxValues[SensorsCount][2] =
//   Коралл        Гиацинт, Вибро   КРУ-1      Коралл+                       БКС14                                     БКС16
    {{0x7F, 0xFF}, {9, 0},  {7, 1}, {0x7F, 0}, {0x7F, 0xFF}, {0, 0}, {0, 0}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0x00}, {0xF, 0xF}, {0xF, 0xF}, {0xF, 0xF}, {0, 0}};
// подсказки
    const QString SensorHint[SensorsCount][8] = {
//Коралл
        {tr("Расходомер жидких сред «Коралл-8» АГТС.407251.002"),
         tr("Объёмный расход:"), tr("Значение первого параметра (измеренное значение объёмного расхода, м³/ч)"),
         tr("Объём:"), tr("Значение второго параметра (измеренное значение объёма, м³)"),
         tr("Ошибка/статус:"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок;\n"
             "1 - расходомер после запуска до получения расчётов;\n"
             "2 - отсутствие измеряемой среды;\n"
             "4 - ошибка акустических каналов;\n"
             "8 - ошибка вторичного преобразователя;\n"
             "16 - нет первичного преобразователя;\n"
             "32 - отсутствие плотномера;\n"
             "64 - неисправность плотномера (ошибка плотномера)."),
         tr("Байт статуса:\n"
             "0 - измерение объёмного расхода без счёта объёма;\n"
             "1 - режим «Контроль»;\n"
             "2 - измерение объёма / массы (режим накопления);\n"
             "4 - режим калибровки;\n"
             "8 - режим имитации расхода;\n"
             "16 - режим синхронизации (настройка прибора);\n"
             "32 - новый шаг в режиме синхронизации (настройка прибора);\n"
             "64 - запрет на автоматическую регулироваку усилителя сигналов;\n"
             "128 - режим отладки (перемыка установлена).")
        },         //Коралл
//Гиацинт
        {tr("Расходомер питательной воды «Гиацинт-У» АГТС.407259.001"),
         tr("Объёмный расход:"), tr("Значение первого параметра (измеренное значение объёмного расхода, м³/ч)"),
         tr(""), tr("Значение второго параметра (не используется)"),
         tr("Ошибка/статус:"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок;\n"
             "1 - режим «Контроль»;\n"
             "2 - резерв;\n"
             "3 - отсутствие измеряемой среды;\n"
             "4 - не подключён кабель к ПЭП 1;\n"
             "5 - не подключён кабель к ПЭП 2;\n"
             "7 - нет первичного преобразователя;\n"
             "8 - нет промежуточного преобразователя;\n"
             "9 - режим имитации расхода."),
         tr("не используется")
        },         //Коралл
//Вибро-1
        {tr("Плотномер вибрационный «Вибро-1» АГТС.414152.001"),
         tr("Плотность:"), tr("Значение первого параметра (измеренное значение плотности, кг/м³)"),
         tr("Температура:"), tr("Значение шестого параметра (измеренное значение температуры, ºC)"),
         tr("Ошибка/статус:"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок;\n"
             "1 - отсутствие измеряемой среды;\n"
             "2 - чувствительный элемент загрязнен;\n"
             "3 - неисправность канала измерений температуры;\n"
             "4 - неисправность канала измерений плотности электронного блока;\n"
             "5 - ошибка электронного блока;\n"
             "6 - нет первичного преобразователя;\n"
             "7 - плотномер в режиме «Диагностика»."),
         tr("Байт статуса:\n"
             "0 - режим измерения плотности и температуры;\n"
             "1 - режим «Диагностика».")
        },    //Вибро-1
//КРУ-1В
        {tr("Уровнемер корабельный рефлектометрический «КРУ-1Р» АГТС.407629.002"),
         tr("Уровень:"), tr("Значение первого параметра (измеренное значение уровня жидкости, мм)"),
         tr("Объём:"), tr("Значение второго параметра (измеренное значение уровня объёма, м³)"),
         tr("Байт ошибки:"),
         tr("Байт статуса (ошибки):\n"
             "0 - рабочий режим;\n"
             "1 - нет ПП;\n"
             "2 - плохая связь с ПП;\n"
             "4 - ошибка по питанию ПП;\n"
             "8 - ошибка по питанию ВП;\n"
             "16 - ошибка поиска импульсов или измерения;\n"
             "32 - не соответствия з/н ПП и ВП;\n"
             "64 - прочие ошибки."),
         tr("не используется"),
        },                    //КРУ-1В
//Коралл+
        {tr("Расходомер жидких сред «Коралл-8» АГТС.407251.002 с плотномером вибрационным «Вибро-1» АГТС.414152.001"),
         tr("Объёмный расход:"), tr("Значение первого параметра (измеренное значение объёмного расхода, м³/ч)"),
         tr("Объём:"), tr("Значение второго параметра (измеренное значение объёма, м³)"),
         tr("Ошибка/статус:"),
         tr("Байт ошибки:\n"
             "0 - нет ошибок;\n"
             "1 - расходомер после запуска до получения расчётов;\n"
             "2 - отсутствие измеряемой среды;\n"
             "4 - ошибка акустических каналов;\n"
             "8 - ошибка вторичного преобразователя;\n"
             "16 - нет первичного преобразователя;\n"
             "32 - отсутствие плотномера;\n"
             "64 - неисправность плотномера (ошибка плотномера)."),
         tr("Байт статуса:\n"
             "0 - измерение объёмного расхода без счёта объёма;\n"
             "1 - режим «Контроль»;\n"
             "2 - измерение объёма / массы (режим накопления);\n"
             "4 - режим калибровки;\n"
             "8 - режим имитации расхода;\n"
             "16 - режим синхронизации (настройка прибора);\n"
             "32 - новый шаг в режиме синхронизации (настройка прибора);\n"
             "64 - запрет на автоматическую регулироваку усилителя сигналов;\n"
             "128 - режим отладки (перемыка установлена).")
        },         //Коралл+
//+массметр
        {tr("Расходомер жидких сред «Коралл-8» АГТС.407251.002 с плотномером вибрационным «Вибро-1» АГТС.414152.001"),
         tr("Массовый расход:"), tr("Значение первого параметра (измеренное значение массового расхода, кг/ч)"),
         tr("Масса:"), tr("Значение второго параметра (измеренное значение массы, кг)"),
         tr(""), tr(""), tr("")
        },          //+массметр
//+вибро
        {tr("Расходомер жидких сред «Коралл-8» АГТС.407251.002 с плотномером вибрационным «Вибро-1» АГТС.414152.001"),
         tr("Плотность:"), tr("Значение первого параметра (измеренное значение плотности, кг/м³)"),
         tr("Температура:"), tr("Значение шестого параметра (измеренное значение температуры, ºC)"),
         tr(""), tr(""), tr("")
        },          //+dибро
// БКС14 01+
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава многофункциональной системы контроля МСК ПДСК.411712.001-014"),
         tr("Канал №1:"), tr("Значение 1-го канала"),
         tr("Канал №2:"), tr("Значение 2-го канала"),
         tr("Статус канала 1, 2:"),
         tr("Статус 1-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован."),
         tr("Статус 2-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован.")
        },          // БКС16 01+
// +БКС14 23
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава многофункциональной системы контроля МСК ПДСК.411712.001-014"),
         tr("Канал №3:"), tr("Значение 3-го канала"),
         tr("Канал №4:"), tr("Значение 4-го канала"),
         tr("Статус канала 3, 4:"),
         tr("Статус 3-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован."),
         tr("Статус 4-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован.")
        },          // +БКС16 23
// +БКС14 45
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава многофункциональной системы контроля МСК ПДСК.411712.001-014"),
         tr("Канал №5:"), tr("Значение 5-го канала"),
         tr("Канал №6:"), tr("Значение 6-го канала"),
         tr("Статус канала 5, 6:"),
         tr("Статус 5-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован."),
         tr("Статус 6-го канала:\n"
             "1 - сработала уставка по минимуму;\n"
             "2 - сработал триггер по миимуму;\n"
             "4 - превышение показаний АЦП;\n"
             "8 - сработала уставка по максимуму;\n"
             "16 - включён режим «Контроль»;\n"
             "32 - тест в режиме «Контроль» провален;\n"
             "64 - сработал триггер по максмуму;\n"
             "128 - канал не задействован.")
        },
// БКС16 01+
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава универсальной системы контроля топлива УСКТ «Опричник» АГТС.421411.010"),
         tr("Параметр 1:"), tr("Значение 1-го параметра"),
         tr("Параметр 2:"), tr("Значение 2-го параметра"),
         tr("Общий байт ошибки:"),
         tr("Общая ошибка БКС"), tr("не используется")
        },          // БКС16 01+
// +БКС16 23
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава универсальной системы контроля топлива УСКТ «Опричник» АГТС.421411.010"),
         tr("Параметр 3:"), tr("Значение 3-го параметра"),
         tr("Параметр 4:"), tr("Значение 4-го параметра"),
         tr("Ошибка канала 1, 2:"),
         tr("Ошибка 1-го канала"), tr("Ошибка 2-го канала")
        },          // +БКС16 23
// +БКС16 45
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава универсальной системы контроля топлива УСКТ «Опричник» АГТС.421411.010"),
         tr("Параметр 5:"), tr("Значение 5-го параметра"),
         tr("Параметр 6:"), tr("Значение 6-го параметра"),
         tr("Ошибка канала 3, 4:"),
         tr("Ошибка 3-го канала"), tr("Ошибка 4-го канала")
        },          // +БКС16 45
// +БКС16 67
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава универсальной системы контроля топлива УСКТ «Опричник» АГТС.421411.010"),
         tr("Параметр 7:"), tr("Значение 7-го параметра"),
         tr("Параметр 8:"), tr("Значение 8-го параметра"),
         tr("Ошибка канала 5, 6:"),
         tr("Ошибка 5-го канала"), tr("Ошибка 6-го канала")
        },          // +БКС16 67
// +БКС16 89
        {tr("Блок коммутации БКС ПДСК.426439.001-03 из состава универсальной системы контроля топлива УСКТ «Опричник» АГТС.421411.010"),
         tr("Параметр 9:"), tr("Значение 9-го параметра"),
         tr("Параметр 10:"), tr("Значение 10-го параметра"),
         tr(""), tr(""), tr("")
        }          // +БКС16 89
    };


signals:

public slots:
    void setAddr(int adr) {_addr = static_cast<quint8>(adr); spinBoxAddress->setValue(_addr); spinBoxAddress->setToolTip("0x" + QString::number(_addr, 16).toUpper());}
    void setType(int type);
    void setFixedType () {comboBoxType->setEnabled(false); spinBoxAddress->setEnabled(false);}
    void setFixedState() {spinBoxErr->setVisible(false); spinBoxStat->setVisible(false); leFlags->setText("...");
        horLayout->addItem(new QSpacerItem(spinBoxErr->width() + spinBoxStat->width() + 2*horLayout->spacing(), 20, QSizePolicy::Fixed, QSizePolicy::Minimum));}
    void setErr(int er) {spinBoxErr->setValue(er); _err = static_cast<quint8>(spinBoxErr->value());}
    void setStat(int st) {spinBoxStat->setValue(st); _stat = static_cast<quint8>(spinBoxStat->value());}
    void setRnd1(bool rnd) {_rnd1 = rnd; checkBoxRnd1->setChecked(_rnd1);}
    void setRnd2(bool rnd) {_rnd2 = rnd; checkBoxRnd2->setChecked(_rnd2);}
    void setValue1(double v) {_value1 = static_cast<float>(v); dSpinBoxValue1->setValue(static_cast<double>(_value1)); AvroraChannel ch; ch.fdata = _value1; dSpinBoxValue1->setToolTip("0x" + QString::number(ch.idata & 0xFFFFFFFF, 16).toUpper());}
    void setValue2(double v) {_value2 = static_cast<float>(v); dSpinBoxValue2->setValue(static_cast<double>(_value2)); AvroraChannel ch; ch.fdata = _value2; dSpinBoxValue2->setToolTip("0x" + QString::number(ch.idata & 0xFFFFFFFF, 16).toUpper());}
    void setInc1(double i) {_inc1 = static_cast<float>(i); dSpinBoxInc1->setValue(static_cast<double>(_inc1)); dSpinBoxInc1->setToolTip(QString::number(_inc1).toUpper());}
    void setInc2(double i) {_inc2 = static_cast<float>(i); dSpinBoxInc2->setValue(static_cast<double>(_inc2)); dSpinBoxInc2->setToolTip(QString::number(_inc2).toUpper());}
    void setAddrName(const QString &name) {leAddress->setText(name);}
    void setValue1Name(const QString &name) {leValue1->setText(name);}
    void setValue2Name(const QString &name) {leValue2->setText(name);}
    void setFlagsName(const QString &name) {leFlags->setText(name);}
    void incValue1() {setValue1(_value1 + _inc1); dSpinBoxValue1->setValue(static_cast<double>(_value1)); _value1 = static_cast<float>(dSpinBoxValue1->value());}
    void incValue2() {setValue2(_value2 + _inc2); dSpinBoxValue2->setValue(static_cast<double>(_value2)); _value2 = static_cast<float>(dSpinBoxValue2->value());}
    void randValue1() {setValue1(_value1 + ((qrand()%3)-1) * _inc1); _value1 = static_cast<float>(dSpinBoxValue1->value());}
    void randValue2() {setValue2(_value2 + ((qrand()%3)-1) * _inc2); _value2 = static_cast<float>(dSpinBoxValue2->value());}
    void restoreFromBlink() {spinBoxAddress->setPalette(spinBoxStat->palette());}
protected:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // SENSORSETTINGS_H
