#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PROGRAM_NAME "AGAT-Imitator"
#define VERSION_NAME "v.0.98"
#define PROG_DATE __DATE__
#define PROG_TIME  __TIME__

QVector<SensorSettings *> sensorList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap imageAgat(":/images/Agat_big_grey.png");
    imageAgat.setMask(imageAgat.createMaskFromColor(QColor(128,128,128),Qt::MaskInColor));
    ui->label->setPixmap(imageAgat.scaled(ui->label->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QLabel * L = new QLabel();
    L->setFixedSize(25,10);
    L->setStatusTip("mailto: chosen_i@inbox.ru");
    QPixmap imageJK(":/images/jk.png");
    setWindowTitle(windowTitle() + " " + VERSION_NAME);
    imageJK.setMask(imageJK.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor));
    L->setPixmap(imageJK.scaled(L->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    ui->statusBar->insertPermanentWidget(0, L);

    ui->teInputData->document()->setMaximumBlockCount(100); // максимальное кол-во строк в логе

// сформировать контейнер для списка расходомеров
    QWidget * tempContainer = new QWidget();    // требуется дополнительная обёртка, иначе
    tempContainer->setLayout(ui->vLayout);
    ui->scrollArea->setWidget(tempContainer);   // иначе слой в scrollArea не добавляется

// добавить полосу сплиттера на форму
    QSplitter* sp = new QSplitter(Qt::Vertical, this);
//    sp->setGeometry(this->rect());
    sp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sp->addWidget(ui->groupBoxSensors);
    sp->addWidget(ui->groupBox);
    ui->vCentralLayout->addWidget(sp);

    ui->pbClear->setParent(ui->teInputData);
    QHBoxLayout *hblInputData = new QHBoxLayout();  //ui->teInputData);
    QVBoxLayout *vblInputData = new QVBoxLayout();  //ui->teInputData);
    QSpacerItem * spacerh = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem * spacerv = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    hblInputData->setMargin(0); vblInputData->setMargin(0);
    ui->teInputData->setLayout(hblInputData->layout());
    hblInputData->addItem(spacerh); hblInputData->addItem(vblInputData);
    vblInputData->addWidget(ui->pbClear); vblInputData->addItem(spacerv);


    ui->statusBar->showMessage("Начало программы", 2000);       // вывод сообещения
    ui->cbPort->addItems(SgComPort::getComList());              // получить список доступных COM-портов
    ui->cbBitRate->addItems(SgComPort::getBitRateList());       // получить список стандартных скоростей
    ui->pbCalcCRC->setEnabled(false);
    ui->pbSend->setEnabled(false);

    // создать подключение (но не подключиться)
    this->initSerial();
    // если посылку поменяли (нажатие Enter), пересчитать индексы
    connect(ui->leOutputData, SIGNAL(returnPressed()),this, SLOT(on_pbCalcCRC_clicked()));
    // вызов контекстного меню
    connect(ui->leOutputData, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(QApplication::keyboardModifiers() != Qt::ControlModifier) return;
    int key = event->key();
    switch (key) {
    case Qt::Key_C:
        this->copyFromOutputData();
//        QApplication::processEvents();
        break;
    default:
        break;
    }
}

void MainWindow::initSerial()
{
    com = new SgComPort();
}

//
// Example: pack from KORAL
// 1F 1A 33 24 01 FA 35 2F 55
// 1F 33 1A 24 01 41 9F 99 9A 00 00 00 00 00 00 00 00 00 00 00 15 E5 2F 55
// start: 0x1F
// dst: 0x33 // server
// src: 0x1A // koral
// space: 0x24
// cmd: 0x01
// data0 (19.95): 41 9F 99 9A
// data1 (0.0): 00 00 00 00
// data2 (0.0): 00 00 00 00 00
// error: 0x00
// status: 0x00
// emty byte: 0x00
// crc: 15 E5
// eof: 2F
// stop: 55

// это слот для сигнала от потока приходящих даннных, где пакет уже парсится и передаёт готовые данные
void MainWindow::serialReceive(QByteArray pck)
{
    static QByteArray pack;
    QString logOutStr;
// добавить данные в буфер пришёдших байт
    pack += pck;
//    qDebug() << "receive:" << pack.toHex();
// если нашли символ конца сообщения, тогда продолжить
    if(pack.contains(AvroraConst::STT))
    {
        // вывод в окно, если разрешён
        if(ui->groupBox->isChecked())
        {
            logOutStr = QString("%1 - %2 ").arg(QTime::currentTime().toString("HH:mm:ss.zzz ")).arg(static_cast<QString>(pack.toHex()).toUpper());
        }
        // получить первую команду из буфера (возможны в буфере несколько команд подряд), вырезав до символа конца сообщения
        QByteArray onePack = pack.left(pack.indexOf(AvroraConst::STT) + 1);
        // уменьшить буфер
        pack = pack.right(pack.length() - pack.indexOf(AvroraConst::STT) - 1);
        // попытаться расшифровать
        AvroraSensor avroraSensor;
        // до тех пор пока не получится расшифровать правильно
        while(!avroraSensor.updateCMDPack(onePack)){
            // добавить ещё хвост пакета до символа конца (вдруг STT попался в середине пакета)
            if(pack.contains(AvroraConst::STT))
            {
                onePack.append(pack.left(pack.indexOf(AvroraConst::STT) + 1));
                pack = pack.right(pack.length() - pack.indexOf(AvroraConst::STT) - 1);
            }
            else
            {
             // если добавлять нечего, это ошибка (или пакет пришёл не полностью, но с байтом STT в середине)
                if(ui->groupBox->isChecked())
                {
                    logOutStr += QString("- <font color = ""red"">Error #<b>%1</b>: %2</font>").arg(avroraSensor.getErrorCode()).arg(QString(avroraSensor.getErrorMsg(avroraSensor.getErrorCode())));
                    if(avroraSensor.getErrorCode() == (int)ERR_CODE::ERR_WRONG_CRC)
                        logOutStr += QString("<font color = ""red"">. Calculated: <b>%1</b></font>").arg(QString::number(((avroraSensor.getCRC()&0xFF)<<8) | (avroraSensor.getCRC()>>8), 16).toUpper());
                    ui->teInputData->append(logOutStr);
                }
                return;
            }
        };
        pack = "";  // очисить буфер (включая возможные неразоранные пакеты)
        ui->statusBar->showMessage(onePack.toHex().toUpper(), 1000);

        // проверка на опрашиваемые датчики
        quint8 dst = avroraSensor.getDst();
        int sensor_in_list = -1; // номер датчика в списке заданных
        for(int i = 0; i < sensorList.length(); ++i)
            if(sensorList.at(i)->getAddr() == dst) {
                sensor_in_list = i;
                break;
            }
        if (sensor_in_list == -1)
        {
            logOutStr += QString(" - <font color = ""green"">[%1: ??? ] <b> не удалось распознать команду запроса</b></font>").arg(QString::number(dst));
            if(ui->groupBox->isChecked()) ui->teInputData->append(logOutStr);
            return;
        }

/*
        // проверка на команду датчику
        if ((avroraSensor.getCmd() <= 0) &&(avroraSensor.getCmd() >= koralCmdConst::MaxNumOfCommands))
        {
            logOutStr += QString(" - <font color = ""green"">[%1: %2 ] неизвестная команда: <b>%3</b></font>")
                    .arg(QString::number(dst))
                    .arg(sensorList.at(sensor_in_list)->getName())
                    .arg(QString::number(avroraSensor.getCmd()));
            if(ui->groupBox->isChecked()) ui->teInputData->append(logOutStr);
            return;
        }
*/
        // индикация посылки (светло-зелёный цвет)
        sensorList.at(sensor_in_list)->blink(100, QColor(230, 255, 240));

        // сформировать пакет ответа
        avroraSensor.setDst(avroraSensor.getSrc());
        avroraSensor.setSrc(avroraSensor.getDst());
        avroraSensor.setCmd(avroraSensor.getCmd());
        avroraSensor.setErr(sensorList.at(sensor_in_list)->getErr());
        avroraSensor.setStat(sensorList.at(sensor_in_list)->getStat());
        // изменить значение датчика
        sensorList.at(sensor_in_list)->step();
        avroraSensor.setData(0, sensorList.at(sensor_in_list)->getValue1());
        avroraSensor.setData(1, sensorList.at(sensor_in_list)->getValue2());
        bool ok = false;
        // проверить, вдруг обращение идёт к связке датчиков Коралл+Вибро
        if((sensorList.at(sensor_in_list)->getType() != KorallPlusType) &&
           (sensorList.at(sensor_in_list)->getType() != BKS16Type)  &&
           (sensorList.at(sensor_in_list)->getType() != BKS14Type)) {
            // сформировать пакет для датчиков
            avroraSensor.setData(2, 0.0);
            ok = avroraSensor.makeAnswer(sensorList.at(sensor_in_list)->getType());
        }
        else
        {
            // для Коралл+Вибро взять и изменить значения для виртуальных датчиков
            if (sensorList.at(sensor_in_list)->getType() == KorallPlusType) {
                SensorSettings *k2, *k3;
                if((sensorList.count() > (sensor_in_list+1)) && (sensorList.at(sensor_in_list+1)->getType() == KorallPlusType1)) {
                    k2 = sensorList.at(sensor_in_list+1);
                    k2->step();
                    avroraSensor.setData(2,k2->getValue1());
                    avroraSensor.setData(3,k2->getValue2());
                    if((sensorList.count() > (sensor_in_list+2)) && (sensorList.at(sensor_in_list+2)->getType() == KorallPlusType2)) {
                        k3 = sensorList.at(sensor_in_list+2);
                        k3->step();
                        avroraSensor.setData(4,k3->getValue1());
                        avroraSensor.setData(5,k3->getValue2());
                    }
                }
                ok = avroraSensor.makeAnswer(KorallPlusType);
            }
            // для БКС14 взять и изменить значения для виртуальных датчиков
            if (sensorList.at(sensor_in_list)->getType() == BKS14Type) {
                SensorSettings *k2, *k3;
                avroraSensor.setStatArray(0, sensorList.at(sensor_in_list)->getErr());
                avroraSensor.setStatArray(1, sensorList.at(sensor_in_list)->getStat());
                if((sensorList.count() > (sensor_in_list+1)) && (sensorList.at(sensor_in_list+1)->getType() == BKS14Type1)) {
                    k2 = sensorList.at(sensor_in_list+1);
                    k2->step();
                    avroraSensor.setData(2,k2->getValue1());
                    avroraSensor.setStatArray(2, k2->getErr());
                    avroraSensor.setData(3,k2->getValue2());
                    avroraSensor.setStatArray(3, k2->getStat());
                    if((sensorList.count() > (sensor_in_list+2)) && (sensorList.at(sensor_in_list+2)->getType() == BKS14Type2)) {
                        k3 = sensorList.at(sensor_in_list+2);
                        k3->step();
                        avroraSensor.setData(4,k3->getValue1());
                        avroraSensor.setStatArray(4, k3->getErr());
                        avroraSensor.setData(5,k3->getValue2());
                        avroraSensor.setStatArray(5, k3->getStat());
                    }
                }
                //avroraSensor.setErrArray(err.idata);
                ok = avroraSensor.makeAnswer(BKS14Type);
            }
            // для БКС16 взять и изменить значения для виртуальных датчиков
            if (sensorList.at(sensor_in_list)->getType() == BKS16Type) {
                SensorSettings *k2, *k3, *k4, *k5;
                AvroraChannel err; err.idata = 0;
                err.array[3] = sensorList.at(sensor_in_list)->getErr();
                if((sensorList.count() > (sensor_in_list+1)) && (sensorList.at(sensor_in_list+1)->getType() == BKS16Type1)) {
                    k2 = sensorList.at(sensor_in_list+1);
                    k2->step();
                    err.array[2] = ((k2->getErr() & 0x0F) << 4) | (k2->getStat() & 0x0F);
                    avroraSensor.setData(2,k2->getValue1());
                    avroraSensor.setData(3,k2->getValue2());
                    if((sensorList.count() > (sensor_in_list+2)) && (sensorList.at(sensor_in_list+2)->getType() == BKS16Type2)) {
                        k3 = sensorList.at(sensor_in_list+2);
                        k3->step();
                        err.array[1] = ((k3->getErr() & 0x0F) << 4) | (k3->getStat() & 0x0F);
                        avroraSensor.setData(4,k3->getValue1());
                        avroraSensor.setData(5,k3->getValue2());
                        if((sensorList.count() > (sensor_in_list+3)) && (sensorList.at(sensor_in_list+3)->getType() == BKS16Type3)) {
                            k4 = sensorList.at(sensor_in_list+3);
                            k4->step();
                            err.array[0] = ((k4->getErr() & 0x0F) << 4) | (k4->getStat() & 0x0F);
                            avroraSensor.setData(6,k4->getValue1());
                            avroraSensor.setData(7,k4->getValue2());
                            if((sensorList.count() > (sensor_in_list+4)) && (sensorList.at(sensor_in_list+4)->getType() == BKS16Type4)) {
                                k5 = sensorList.at(sensor_in_list+4);
                                k5->step();
                                avroraSensor.setData(8,k5->getValue1());
                                avroraSensor.setData(9,k5->getValue2());
                            }
                        }
                    }
                }
                avroraSensor.setErr32(err.idata);
                ok = avroraSensor.makeAnswer(BKS16Type);
            }
        }
        // проверка на корректно сформированный пакет ответа
        if(!ok)
        {
            if(ui->groupBox->isChecked())
            {
                logOutStr += QString(" - <font color = ""red""><b>Error to make answer!</b></font>");
                ui->teInputData->append(logOutStr);
            }
            return;
        };
        // передать пакет на посылку
        MainWindow::serialSend(avroraSensor.getPack());
        QString pckStr = static_cast<QString>(avroraSensor.getPack().toHex()).toUpper();
        if(ui->groupBox->isChecked())
        {                                  //ui->teInputData->insertHtml(QString(" - <font color = ""green"">[%1: %2] %3 <b>%4</b> %5</font>\n")
            logOutStr += QString(" - <font color = ""green"">[%1: %2] %3 <b>%4</b> %5</font>")
                                    .arg(QString::number(sensor_in_list+1))
                                    .arg(sensorList.at(sensor_in_list)->getName())
                                    .arg(pckStr.left(10))
                                    .arg(pckStr.mid(10, pckStr.length() - 18))
                                    .arg(pckStr.right(8));
            ui->teInputData->append(logOutStr);
        }
    };
}

void MainWindow::on_pbOpen_clicked()
{
#if defined(Q_OS_WIN)
    int	com_index = ui->cbPort->currentText().remove(QRegExp("\\D")).toInt()-1;
#elif defined(Q_OS_UNIX)
    int com_index = ui->cbPort->currentText().remove(QRegExp("\\D")).toInt();
#endif

    if(com->isOpened())
    {
        com->close();
        ui->pbOpen->setText("Открыть");
        if(ui->groupBox->isChecked()) ui->teInputData->append("Порт закрыт");
        ui->statusBar->showMessage("Порт закрыт", 2000);
        qDebug() << "Close port";
        ui->pbSend->setEnabled(false);
        disconnect(com, &SgComPort::packRecieved, this, &MainWindow::serialReceive);
        disconnect(com, &SgComPort::packRecieved, this, &MainWindow::serialReceive);
    }
    else
    {
        if(com->open(com_index, ui->cbBitRate->currentText().toInt()))           //,(qint32)ui->cbBitRate->currentData().toUInt());
        {
            qDebug() << "Open port #"<< com_index << com->com_name;
            if(ui->groupBox->isChecked()) ui->teInputData->append("Открыт порт: " + com->com_name + "; скорость: " + QString("%1").arg(ui->cbBitRate->currentText().toInt()) +" bps");
            ui->statusBar->showMessage("Открыт порт: " + com->com_name + "; скорость: " + ui->cbBitRate->currentText() + " bps.", 2000);
            ui->pbOpen->setText("Закрыть");
            ui->pbSend->setEnabled(true);
            connect(com, &SgComPort::packRecieved, this, &MainWindow::serialReceive);       // если данные получены, обработать
        }
        else
        {
            qDebug() << "Error to open port!";
            ui->pbSend->setEnabled(false);
            if(ui->groupBox->isChecked()) ui->teInputData->append("Ошибка открытия порта");    //ui->teInputData->insertPlainText("\nОшибка открытия порта\n");
            ui->statusBar->showMessage("Ошибка открытия порта", 2000);
        }
    }
}

void MainWindow::on_pbSend_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QByteArray str = codec->fromUnicode(ui->leOutputData->placeholderText());
    if (str.length() == 0)
        str = codec->fromUnicode(ui->leOutputData->text());
// для БСК/Коралла/Кру работает на скорости 57600, 8N1.
    if(com->isOpened())
    {
        QByteArray hex = QByteArray::fromHex(str);
        QString logOutStr =  hex.toHex().toUpper();
        ui->statusBar->showMessage("Отправка пакета: " + logOutStr, 1000);
        if(ui->groupBox->isChecked()) {
            if(logOutStr.length() >= 10) {
                logOutStr = QString("%1 - <font color = ""green"">Отправка: %2 <b>%3</b> %4</font>")
                                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz "))
                                        .arg(logOutStr.left(2))
                                        .arg(logOutStr.mid(2, logOutStr.length() - 10))
                                        .arg(logOutStr.right(8));

            } else {
                logOutStr = QString("%1 - <font color = ""green"">Отправка: %2 </font>")
                                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz "))
                                        .arg(logOutStr);
            }
            ui->teInputData->append(logOutStr);
        }
        MainWindow::serialSend(hex);
    }
    else
    {
    // если порт закрыт
        ui->statusBar->showMessage("Сначала откройте COM-порт", 2000);
    };
}

void MainWindow::serialSend(QByteArray snd)
{
    com->write(snd);        // посылка готового пакета
}

void MainWindow::on_pbClear_clicked()
{
    ui->teInputData->clear();
}

void MainWindow::on_pbCalcCRC_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QByteArray pck = codec->fromUnicode(ui->leOutputData->text());
    pck = QByteArray::fromHex(pck);

//    QString strtext = pck.toHex().toUpper();

    AvroraSensor::combineAnswer(pck);

    QString strholder = pck.toHex().toUpper();
    for (int i = strholder.length()-2; i > 1; i-=2)
        strholder.insert(i, ' ');
    ui->leOutputData->setPlaceholderText(strholder);
//    for (int i = strtext.length()-2; i > 1; i-=2)
//        strtext.insert(i, ' ');
//    strtext.insert(1, "   ");
    ui->leOutputData->setText("");
    ui->pbCalcCRC->setEnabled(false);
}

void MainWindow::on_pbPlus_clicked()
{
    if(sensorList.length() == 0)
    {
        ui->lFirstSet->deleteLater();
        sensorList.append(new SensorSettings(1, tSensorSettingsType::KRUType, 1));
    }
     else
        switch(sensorList.at(sensorList.length()-1)->getType()){
        case KorallPlusType:
            sensorList.append(new SensorSettings(sensorList.length()+1, KorallPlusType1, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            sensorList.at(sensorList.length()-1)->setFixedState();
            ui->vLayout->addWidget(sensorList.last());
            sensorList.append(new SensorSettings(sensorList.length()+1, KorallPlusType2, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            sensorList.at(sensorList.length()-1)->setFixedState();
            break;
        case KorallPlusType2:
            sensorList.append(new SensorSettings(sensorList.length()+1, KorallPlusType, sensorList.at(sensorList.length()-1)->getAddr() + 1)); break;
        case BKS14Type:
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS14Type1, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            ui->vLayout->addWidget(sensorList.last());
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS14Type2, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            break;
        case BKS14Type2:
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS14Type, sensorList.at(sensorList.length()-1)->getAddr() + 1)); break;
        case BKS16Type:
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS16Type1, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            ui->vLayout->addWidget(sensorList.last());
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS16Type2, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            ui->vLayout->addWidget(sensorList.last());
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS16Type3, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            ui->vLayout->addWidget(sensorList.last());
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS16Type4, sensorList.at(sensorList.length()-1)->getAddr()));
            sensorList.at(sensorList.length()-1)->setFixedType();
            sensorList.at(sensorList.length()-1)->setFixedState();
            break;
        case BKS16Type4:
            sensorList.append(new SensorSettings(sensorList.length()+1, BKS16Type, sensorList.at(sensorList.length()-1)->getAddr() + 1)); break;
        default:
            sensorList.append(new SensorSettings(sensorList.length()+1, sensorList.at(sensorList.length()-1)->getType(), sensorList.at(sensorList.length()-1)->getAddr() + 1));
        }
    ui->vLayout->addWidget(sensorList.last());
}

void MainWindow::on_pbMinus_clicked()
{
    if(sensorList.length() > 1)
    {
//// !!! здесь сквозной CASE. Выполнение операций последовательно начиная с совпадения!!!
        switch(sensorList.last()->getType()){
        case BKS16Type4:
            delete sensorList.last();
            sensorList.pop_back();
            delete sensorList.last();
            sensorList.pop_back();
        case BKS14Type2:
        case KorallPlusType2:
            delete sensorList.last();
            sensorList.pop_back();
        default:
            delete sensorList.last();
            sensorList.pop_back();
        }
    }
}


void MainWindow::on_leOutputData_textEdited(const QString &arg1)
{
    ui->leOutputData->setPlaceholderText("");
    if(arg1 == "")
    {
        ui->pbCalcCRC->setEnabled(false);
    }
    else
    {
        ui->pbCalcCRC->setEnabled(true);
    }
}

void MainWindow::contextMenuRequested(QPoint point)
{
    // объявление и инициализация конеткстного меню
    QMenu * menu = ui->leOutputData->createStandardContextMenu(); //new QMenu(ui->leOutputData->window());
    // создание нового действия
    QAction * act_copy = new QAction(QIcon(":/images/copy.png"), tr("Копировать"), menu->parent());
    // описание сочетания клавиш (только лишь?)
    act_copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    // соединение действия с функцией копирования в буфер обмена
    connect (act_copy, SIGNAL(triggered()), this, SLOT(copyFromOutputData()));
    // удалить "Cut"
    menu->removeAction(menu->actions().at(3));
    // удалить "Copy"
    menu->removeAction(menu->actions().at(3));
    // добавить действие в меню
    menu->insertAction(menu->actions().at(3), act_copy);
    // с учётом того, есть ли данные для копирования или нет
    if((ui->leOutputData->text() == "") && (ui->leOutputData->placeholderText() == ""))
    {
        act_copy->setEnabled(false);
    }
    else
    {
        act_copy->setEnabled(true);
    }
    // вывести контекстное меню
    menu->popup(ui->leOutputData->mapToGlobal(point));
}

void MainWindow::copyFromOutputData()
{
    QClipboard * clipboard = QApplication::clipboard();
    if(ui->leOutputData->text() == "")
    {
        if(ui->leOutputData->placeholderText() != "")
        {
            clipboard->setText(ui->leOutputData->placeholderText());
            ui->statusBar->showMessage("Скопировано в буфер обмена: " + clipboard->text(), 1000);
        }
    }
    else
    {
        clipboard->setText(ui->leOutputData->text());
            ui->statusBar->showMessage("Скопировано в буфер обмена: " + clipboard->text(), 1000);
    }
}

void MainWindow::on_pbSave_clicked()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Сохранить установки в файле"), QCoreApplication::applicationDirPath(), "*.ini Файл настройки");
    if (str == "") return;
    if (!sensorList.length())
    {
        QMessageBox::information(this, "Отмена сохранения", "Необходимо настроить хотя бы один датчик", QDialogButtonBox::StandardButton::Ok);
    }
    if (str.right(4) != ".ini") str += ".ini";
    QSettings settings(str, QSettings::IniFormat);
    settings.setIniCodec("Windows-1251");
// сведения о программе и настройке (при загрузке не используется)
    settings.setValue("About/Program", PROGRAM_NAME);
    settings.setValue("About/Version", VERSION_NAME);
    settings.setValue("About/DateOfProg", PROG_DATE);
    settings.setValue("About/ProgramPath", QCoreApplication::applicationDirPath());
    settings.setValue("About/TimeOfSavingINI", QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
// основные настройи главного окна
    settings.setValue("General/COM", ui->cbPort->currentText());
    settings.setValue("General/Bitrate", ui->cbBitRate->currentText());
    settings.setValue("General/Print", ui->groupBox->isChecked());
    settings.setValue("General/MaxLogLines", ui->teInputData->document()->maximumBlockCount());
    settings.setValue("General/OutputData", ui->leOutputData->text());
    settings.setValue("General/OutputMess", ui->leOutputData->placeholderText());
// запись параметров для каждого из датчиков
    quint8 i = 0;
    foreach(SensorSettings * sensor, sensorList)
    {
        ++i;
        settings.beginGroup("Sensor" + QString::number(i));
        settings.setValue("Type", static_cast<int>(sensor->getType()));
        settings.setValue("Address", sensor->getAddr());
        settings.setValue("AddressName", sensor->getAddrName().replace("³", "^3").replace("²", "^2"));
        settings.setValue("Value1", QString::number(sensor->getValue1(),'f', 3));
        settings.setValue("Value1Name", sensor->getValue1Name().replace("³", "^3").replace("²", "^2"));
        settings.setValue("Value2", QString::number(sensor->getValue2(),'f', 3));
        settings.setValue("Value2Name", sensor->getValue2Name().replace("³", "^3").replace("²", "^2"));
        settings.setValue("Increment1", QString::number(sensor->getInc1(),'f', 3));
        settings.setValue("Increment2", QString::number(sensor->getInc2(),'f', 3));
        settings.setValue("RandomFlag1", sensor->getRnd1());
        settings.setValue("RandomFlag2", sensor->getRnd2());
        settings.setValue("FlagsName", sensor->getFlagsName().replace("³", "^3").replace("²", "^2"));
        settings.setValue("Status", sensor->getStat());
        settings.setValue("Error", sensor->getErr());
        settings.endGroup();
    }
    ui->statusBar->showMessage("Установок успешно сохранены", 2000);
}

void MainWindow::on_pbLoad_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, tr("Загрузить файл установок"), QCoreApplication::applicationDirPath(), "*.ini Файл настройки;;*.* Все файлы");
    if (str == "") return;
    QSettings settings(str, QSettings::IniFormat);
    settings.setIniCodec("Windows-1251");
// загрузка настроек для главного окна
    QString vers = settings.value("About/Version").toString();
    if (vers != VERSION_NAME) {QMessageBox::warning(this, tr("Загрузка конфигурации"), tr("ВНИМАНИЕ! Версия файла не совпадает с версией программы.\n\n Загруженная конфигурация может не совпадать с реальной!"));}
    ui->cbPort->setCurrentIndex(ui->cbPort->findText(settings.value("General/COM").toString()));
    ui->cbBitRate->setCurrentIndex(ui->cbBitRate->findText(settings.value("General/Bitrate").toString()));
    ui->groupBox->setChecked(settings.value("General/Print").toBool());
    ui->teInputData->document()->setMaximumBlockCount(settings.value("General/MaxLogLines").toInt());
    ui->leOutputData->setText(settings.value("General/OutputData").toString());
    ui->leOutputData->setPlaceholderText(settings.value("General/OutputMess").toString());
// удалить предыдущие датчики
    while(sensorList.length() > 1)
        MainWindow::on_pbMinus_clicked();
// загрузка настроек для каждого из датчиков
    quint8 i = 0;
    while(settings.contains("Sensor" + QString::number(++i) + "/Type"))
    {
        settings.beginGroup("Sensor" + QString::number(i));
        // если датчика ещё не существует в списке, создать
        if(sensorList.length() < i)
            MainWindow::on_pbPlus_clicked();
        sensorList.at(i-1)->setType(settings.value("Type").toInt());
        sensorList.at(i-1)->setAddr(settings.value("Address").toInt());
        sensorList.at(i-1)->setAddrName(settings.value("AddressName", "Адрес").toString().replace("^3", "³").replace("^2", "²"));
        sensorList.at(i-1)->setValue1(settings.value("Value1").toFloat());
        sensorList.at(i-1)->setValue1Name(settings.value("Value1Name", "Параметр 1").toString().replace("^3", "³").replace("^2", "²"));
        sensorList.at(i-1)->setValue2(settings.value("Value2").toFloat());
        sensorList.at(i-1)->setValue2Name(settings.value("Value2Name", "Параметр 2").toString().replace("^3", "³").replace("^2", "²"));
        sensorList.at(i-1)->setInc1(settings.value("Increment1").toFloat());
        sensorList.at(i-1)->setInc2(settings.value("Increment2").toFloat());
        sensorList.at(i-1)->setRnd1(settings.value("RandomFlag1", true).toBool());
        sensorList.at(i-1)->setRnd2(settings.value("RandomFlag2", true).toBool());
        sensorList.at(i-1)->setFlagsName(settings.value("FlagsName", "Состояние:").toString().replace("^3", "³").replace("^2", "²"));
        sensorList.at(i-1)->setStat(settings.value("Status").toInt());
        sensorList.at(i-1)->setErr(settings.value("Error").toInt());
        settings.endGroup();
    }
    str = "Загрузка установок из файла " + str + " прошла успешно";
    if(ui->groupBox->isChecked()) ui->teInputData->append(str);
    ui->statusBar->showMessage(str, 5000);
}
