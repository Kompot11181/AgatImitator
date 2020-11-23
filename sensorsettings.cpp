#include "sensorsettings.h"

SensorSettings::SensorSettings(QWidget *parent) : QWidget(parent)
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
    horLayout->setSpacing(5);
    lNum = new QLabel(this);
    lNum->setFixedSize(QSize(15, 20));
    lNum->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    horLayout->addWidget(lNum);

    leAddress = new QLineEdit(backwidget);
    leAddress->setMaximumSize(QSize(50, 20));
    leAddress->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    leAddress->setFrame(false);
    horLayout->addWidget(leAddress);

    spinBoxAddress = new QSpinBox(backwidget);
    spinBoxAddress->setFixedSize(QSize(40, 20));
    spinBoxAddress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    spinBoxAddress->setMaximum(255);
    horLayout->addWidget(spinBoxAddress);

    comboBoxType = new QComboBox(backwidget);
    comboBoxType->setFixedSize(100, 20);
    comboBoxType->setMaxCount(SensorsCount);
    for (int i = 0; i < tSensorType::NumOfTypes; ++i)
        comboBoxType->addItem(QIcon(SensorsImage[i]), SensorsName[i]);
    QStandardItemModel* model = (QStandardItemModel*) comboBoxType->model();
    model->item(tSensorType::KorallPlusType1)->setEnabled(false);
    model->item(tSensorType::KorallPlusType2)->setEnabled(false);
    model->item(tSensorType::BKS14Type1)->setEnabled(false);
    model->item(tSensorType::BKS14Type2)->setEnabled(false);
    model->item(tSensorType::BKS16Type1)->setEnabled(false);
    model->item(tSensorType::BKS16Type2)->setEnabled(false);
    model->item(tSensorType::BKS16Type3)->setEnabled(false);
    model->item(tSensorType::BKS16Type4)->setEnabled(false);
    comboBoxType->setCurrentIndex(tSensorType::KorallType);
    horLayout->addWidget(comboBoxType);

    leValue1 = new QLineEdit(backwidget);
    leValue1->setMinimumSize(QSize(80, 20));
    leValue1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    leValue1->setFrame(false);
    horLayout->addWidget(leValue1);

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

    leValue2 = new QLineEdit(backwidget);
    leValue2->setMinimumSize(QSize(60, 20));
    leValue2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    leValue2->setFrame(false);
    horLayout->addWidget(leValue2);

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

    horSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horLayout->addItem(horSpacer);

    leFlags = new QLineEdit(backwidget);
    leFlags->setBaseSize(QSize(70, 20));
    leFlags->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    leFlags->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    leFlags->setFrame(false);
    horLayout->addWidget(leFlags);

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
    leAddress->setText(tr("Адрес"));
    comboBoxType->setStatusTip("Тип датчика." );
    spinBoxAddress->setStatusTip("Адрес датчика");
    checkBoxRnd1->setStatusTip("Флаг режима случайного изменения параметра 1 { -приращение | 0 | +приращение }");
    checkBoxRnd2->setStatusTip("Флаг режима случайного изменения параметра 2 { -приращение | 0 | +приращение }");
    comboBoxType->setStatusTip(SensorHint[0][0]);
    leValue1->setText(SensorHint[0][1]);
    dSpinBoxValue1->setStatusTip(SensorHint[0][2]);
    leValue1->setText(SensorHint[0][3]);
    dSpinBoxValue2->setStatusTip(SensorHint[0][4]);
    leFlags->setText(SensorHint[0][5]);
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

void SensorSettings::setType(int type)
{
    _type = static_cast<tSensorType>(type);
    comboBoxType->setCurrentIndex(static_cast<int>(_type));
    comboBoxType->setStatusTip(SensorHint[_type][0]);
    leValue1->setText(SensorHint[_type][1]);
    dSpinBoxValue1->setStatusTip(SensorHint[_type][2]);
    leValue2->setText(SensorHint[_type][3]);
    dSpinBoxValue2->setStatusTip(SensorHint[_type][4]);
    leFlags->setText(SensorHint[_type][5]);
    spinBoxErr->setStatusTip(SensorHint[_type][6]);
    spinBoxStat->setStatusTip(SensorHint[_type][7]);
    spinBoxErr->setToolTip(SensorHint[_type][6]);
    spinBoxStat->setToolTip(SensorHint[_type][7]);
    spinBoxErr->setMaximum(errStatMaxValues[_type][0]);
    spinBoxStat->setMaximum(errStatMaxValues[_type][1]);
}

void SensorSettings::blink(int interval, QColor col)
{
    QPalette pal = spinBoxAddress->palette();
    pal.setColor(QPalette::Base, col);
    spinBoxAddress->setPalette(pal);
    QTimer::singleShot(interval, this, SLOT(restoreFromBlink()));
}

void SensorSettings::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
//    QPalette pal = spinBoxStat->palette();
//    if((event->pos().y() > (this->size().height() - 20) / 2) && (event->pos().y() < (this->size().height() + 20) / 2))
//        pal.setColor(QPalette::Base, QColor(255,0,0));
//    spinBoxErr->setPalette(pal);
}
