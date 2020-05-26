#include "koralsetting.h"

cKoralSetting::cKoralSetting(QWidget *parent) : QWidget(parent)
{
    verLayout = new QVBoxLayout(this);
    verLayout->setSpacing(0);
    verLayout->setObjectName(QStringLiteral("verLayout"));
    verLayout->setContentsMargins(0, 0, 0, 0);

    backwidget = new QWidget();
    backwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    backwidget->setContentsMargins(0,2,0,2);

    horLayout = new QHBoxLayout(backwidget);
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setSpacing(6);
    lNum = new QLabel(this);
    lNum->setFixedSize(QSize(15, 20));
    lNum->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    horLayout->addWidget(lNum);

    comboBoxType = new QComboBox(backwidget);
    comboBoxType->setFixedSize(80, 20);
    comboBoxType->setMaxCount(SensorsCount);
    for (int i = 0; i < tSensorType::NumOfTypes; ++i)
        comboBoxType->addItem(SensorsName[i]);
    QStandardItemModel* model = (QStandardItemModel*) comboBoxType->model();
    model->item(tSensorType::PlusMassType)->setEnabled(false);
    model->item(tSensorType::PlusVibroType)->setEnabled(false);
    comboBoxType->setCurrentIndex(tSensorType::KorallType);
    horLayout->addWidget(comboBoxType);

    lAddress = new QLabel(backwidget);
    lAddress->setMaximumSize(QSize(50, 20));
    lAddress->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    horLayout->addWidget(lAddress);

    spinBoxAddress = new QSpinBox(backwidget);
    spinBoxAddress->setFixedSize(QSize(40, 20));
    spinBoxAddress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    spinBoxAddress->setMaximum(63);
    horLayout->addWidget(spinBoxAddress);

    lValue1 = new QLabel(backwidget);
    lValue1->setMinimumSize(QSize(80, 20));
    lValue1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    horLayout->addWidget(lValue1);

    dSpinBoxValue1 = new QDoubleSpinBox(backwidget);
    dSpinBoxValue1->setFixedSize(QSize(70, 20));
    dSpinBoxValue1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    dSpinBoxValue1->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
    dSpinBoxValue1->setDecimals(3);
    dSpinBoxValue1->setMinimum(-9999.999);
    dSpinBoxValue1->setMaximum(9999.999);
    dSpinBoxValue1->setSingleStep(0.100);
    horLayout->addWidget(dSpinBoxValue1);

    dSpinBoxInc1 = new QDoubleSpinBox(backwidget);
    dSpinBoxInc1->setFixedSize(QSize(65, 20));
    dSpinBoxInc1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    dSpinBoxInc1->setDecimals(3);
    dSpinBoxInc1->setMinimum(-99.999);
    dSpinBoxInc1->setMaximum(99.999);
    dSpinBoxInc1->setSingleStep(0.100);
    horLayout->addWidget(dSpinBoxInc1);

    checkBoxRnd1 = new QCheckBox(backwidget);
    checkBoxRnd1->setFixedSize(QSize(20, 20));
    checkBoxRnd1->setCheckState(Qt::Unchecked);
    checkBoxRnd1->setText("");
    horLayout->addWidget(checkBoxRnd1);

    lValue2 = new QLabel(backwidget);
    lValue2->setMinimumSize(QSize(60, 20));
    lValue2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    horLayout->addWidget(lValue2);

    dSpinBoxValue2 = new QDoubleSpinBox(backwidget);
    dSpinBoxValue2->setFixedSize(QSize(70, 20));
    dSpinBoxValue2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    dSpinBoxValue2->setDecimals(3);
    dSpinBoxValue2->setMinimum(-9999.999);
    dSpinBoxValue2->setMaximum(9999.999);
    dSpinBoxValue2->setSingleStep(0.100);
    horLayout->addWidget(dSpinBoxValue2);

    dSpinBoxInc2 = new QDoubleSpinBox(backwidget);
    dSpinBoxInc2->setFixedSize(QSize(65, 20));
    dSpinBoxInc2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    dSpinBoxInc2->setDecimals(3);
    dSpinBoxInc2->setMinimum(-99.999);
    dSpinBoxInc2->setMaximum(99.999);
    dSpinBoxInc2->setSingleStep(0.100);
    horLayout->addWidget(dSpinBoxInc2);

    checkBoxRnd2 = new QCheckBox(backwidget);
    checkBoxRnd2->setFixedSize(QSize(20, 20));
    checkBoxRnd2->setCheckState(Qt::Unchecked);
    checkBoxRnd2->setText("");
    horLayout->addWidget(checkBoxRnd2);

    horSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horLayout->addItem(horSpacer);

    lFlags = new QLabel(backwidget);
    lFlags->setMinimumSize(QSize(70, 20));
    lFlags->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    horLayout->addWidget(lFlags);

    spinBoxErr = new QSpinBox(backwidget);
    spinBoxErr->setFixedSize(QSize(40, 20));
    spinBoxErr->setAlignment(Qt::AlignCenter);
    horLayout->addWidget(spinBoxErr);

    spinBoxStat = new QSpinBox(backwidget);
    spinBoxStat->setFixedSize(QSize(40, 20));
    spinBoxStat->setAlignment(Qt::AlignCenter);
    horLayout->addWidget(spinBoxStat);

//    verLayout->addLayout(horLayout);
    verLayout->addWidget(backwidget);

    lNum->setText(tr("1:"));
    lAddress->setText(tr("Адрес"));
    lValue1->setText(tr("Параметр 1"));
    lValue2->setText(tr("Параметр 2"));
    lFlags->setText(tr("Состояние:"));

    comboBoxType->setStatusTip("Тип датчика. Для 'Коралла-8' с поключённым 'Вибро-1' использовать тип 'Коралл+', '+ массметр', '+ Вибро' с одинаковыми адресами" );
    spinBoxAddress->setStatusTip("Адрес датчика (0..31)");
    checkBoxRnd1->setStatusTip("Флаг режима случайного изменения параметра 1 { -приращение | 0 | +приращение }");
    checkBoxRnd2->setStatusTip("Флаг режима случайного изменения параметра 2 { -приращение | 0 | +приращение }");
    dSpinBoxValue1->setStatusTip(SensorHint[0][0]);
    dSpinBoxValue2->setStatusTip(SensorHint[0][1]);
//    dSpinBoxValue3->setStatusTip(tr("Значение третьего параметра (измеренное значение массового расхода)"));
//    dSpinBoxValue4->setStatusTip(tr("Значение четвёртого параметра (измеренное значение массы)"));
//    dSpinBoxValue5->setStatusTip(tr("Значение пятого параметра (измеренное значение плотности)"));
//    dSpinBoxValue6->setStatusTip(tr("Значение шестого параметра (измеренное значение температуры)"));
    dSpinBoxInc1->setStatusTip(tr("Приращение первого параметра"));
    dSpinBoxInc2->setStatusTip(tr("Приращение второго параметра"));
    spinBoxErr->setStatusTip(tr("Байт номера ошибки"));
    spinBoxStat->setStatusTip(tr("Байт статуса"));


    connect(comboBoxType, SIGNAL(currentIndexChanged(int)), this, SLOT(setType(int)));
    connect(spinBoxAddress, SIGNAL(valueChanged(int)),this, SLOT(setAddr(int)));
    connect(spinBoxErr, SIGNAL(valueChanged(int)),this, SLOT(setErr(int)));
    connect(spinBoxStat, SIGNAL(valueChanged(int)),this, SLOT(setStat(int)));
    connect(checkBoxRnd1, SIGNAL(toggled(bool)),this, SLOT(setRnd1(bool)));
    connect(checkBoxRnd2, SIGNAL(toggled(bool)),this, SLOT(setRnd2(bool)));
    connect(dSpinBoxValue1, SIGNAL(valueChanged(double)), this, SLOT(setValue1(double)));
    connect(dSpinBoxValue2, SIGNAL(valueChanged(double)), this, SLOT(setValue2(double)));
    connect(dSpinBoxInc1, SIGNAL(valueChanged(double)), this, SLOT(setInc1(double)));
    connect(dSpinBoxInc2, SIGNAL(valueChanged(double)), this, SLOT(setInc2(double)));

//    vLayout->addWidget(widget);
    this->setMouseTracking(true);
}

void cKoralSetting::setType(int type)
{
    _type = static_cast<tSensorType>(type);
    comboBoxType->setCurrentIndex(static_cast<int>(_type));
    dSpinBoxValue1->setStatusTip(SensorHint[_type][0]);
    dSpinBoxValue2->setStatusTip(SensorHint[_type][1]);
    spinBoxErr->setToolTip(SensorHint[_type][2]);
    spinBoxStat->setToolTip(SensorHint[_type][3]);
    spinBoxErr->setMaximum(errStatMaxValues[_type][0]);
    spinBoxStat->setMaximum(errStatMaxValues[_type][1]);
}

void cKoralSetting::blink(int interval, QColor col)
{
    QPalette pal = spinBoxAddress->palette();
    pal.setColor(QPalette::Base, col);
    spinBoxAddress->setPalette(pal);
    QTimer::singleShot(interval, this, SLOT(restoreFromBlink()));
}

void cKoralSetting::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
//    QPalette pal = spinBoxStat->palette();
//    if((event->pos().y() > (this->size().height() - 20) / 2) && (event->pos().y() < (this->size().height() + 20) / 2))
//        pal.setColor(QPalette::Base, QColor(255,0,0));
//    spinBoxErr->setPalette(pal);
}
