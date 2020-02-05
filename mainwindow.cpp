#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PROGRAM_NAME "AGAT-Imitator"
#define VERSION_NAME "v.0.9"
#define PROG_DATE __DATE__
#define PROG_TIME  __TIME__

QVector<cKoralSetting *> koral_list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap imageAgat(":/Agat_big_grey.png");
    ui->pbLoad->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->pbSave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    imageAgat.setMask(imageAgat.createMaskFromColor(QColor(128,128,128),Qt::MaskInColor));
    ui->label->setPixmap(imageAgat.scaled(ui->label->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QLabel * L = new QLabel();
    L->setFixedSize(25,10);
    L->setStatusTip("mailto: chosen_i@inbox.ru");
    QPixmap imageJK(":/jk.png");
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
    sp->addWidget(ui->groupBoxKorals);
    sp->addWidget(ui->groupBox);
    ui->vCentralLayout->addWidget(sp);

    ui->pbClear->setIcon(style()->standardIcon(QStyle::SP_LineEditClearButton));
    ui->pbClear->setText("");
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
    if(pack.contains(koralConst::STT))
    {
        // вывод в окно, если разрешён
        if(ui->groupBox->isChecked())
        {
            logOutStr = QString("%1 - %2 ").arg(QTime::currentTime().toString("HH:mm:ss.zzz ")).arg(static_cast<QString>(pack.toHex()).toUpper());
        }
        // получить первую команду из буфера (возможны в буфере несколько команд подряд), вырезав до символа конца сообщения
        QByteArray onePack = pack.left(pack.indexOf(koralConst::STT) + 1);
        // уменьшить буфер
        pack = pack.right(pack.length() - pack.indexOf(koralConst::STT) - 1);
        // попытаться расшифровать
        cKoral koralpack;
        // до тех пор пока не получится расшифровать правильно
        while(!koralpack.updateCMDPack(onePack)){
            // добавить ещё хвост пакета до символа конца (вдруг STT попался в середине пакета)
            if(pack.contains(koralConst::STT))
            {
                onePack.append(pack.left(pack.indexOf(koralConst::STT) + 1));
                pack = pack.right(pack.length() - pack.indexOf(koralConst::STT) - 1);
            }
            else
            {
             // если добавлять нечего, это ошибка (или пакет пришёл не полностью, но с байтом STT в середине)
                if(ui->groupBox->isChecked())
                {
                    logOutStr += QString("- <font color = ""red"">Error #<b>%1</b>: %2</font>").arg(koralpack.getErrorCode()).arg(QString(koralpack.getErrorMsg(koralpack.getErrorCode())));
                    if(koralpack.getErrorCode() == (int)ERR_CODE::ERR_WRONG_CRC)
                        logOutStr += QString("<font color = ""red"">. Calculated: <b>%1</b></font>").arg(QString::number(((koralpack.getCRC()&0xFF)<<8) | (koralpack.getCRC()>>8), 16).toUpper());
                    ui->teInputData->append(logOutStr);
                }
                return;
            }
        };
        pack = "";  // очисить буфер (включая возможные неразоранные пакеты)
        ui->statusBar->showMessage(onePack.toHex().toUpper(), 1000);

        // проверка на опрашиваемые Кораллы
        quint8 dst = koralpack.getDst();
        int koral_in_list = -1; // номер Коралла в списке заданных
        for(int i = 0; i < koral_list.length(); ++i)
            if(koral_list.at(i)->getAddr() == dst) {
                koral_in_list = i;
                break;
            }
        if (koral_in_list == -1)
        {
            logOutStr += QString(" - <font color = ""green"">[%1: ??? ] <b>-</b></font>").arg(QString::number(dst));
            ui->teInputData->append(logOutStr);
            return;
        }
        // проверка на команду Кораллу
        if ((koralpack.getCmd() <= 0) &&(koralpack.getCmd() >= koralCmdConst::MaxNumOfCommands))
        {
            logOutStr += QString(" - <font color = ""green"">[%1: %2 ] неизвестная команда: <b>%3</b></font>")
                    .arg(QString::number(dst))
                    .arg(koral_list.at(koral_in_list)->getName())
                    .arg(QString::number(koralpack.getCmd()));
            ui->teInputData->append(logOutStr);
            return;
        }

        // индикация посылки (светло-зелёный цвет)
        koral_list.at(koral_in_list)->blink(100, QColor(230, 255, 240));

        // сформировать пакет ответа
        koralpack.setDst(koralpack.getSrc());
        koralpack.setSrc(koralpack.getDst());
        koralpack.setCmd(koralpack.getCmd());
        koralpack.setErr(koral_list.at(koral_in_list)->getErr());
        koralpack.setStat(koral_list.at(koral_in_list)->getStat());
        // изменить значение датчика
        koral_list.at(koral_in_list)->step();
        koralpack.setData(0, koral_list.at(koral_in_list)->getValue1());
        koralpack.setData(1, koral_list.at(koral_in_list)->getValue2());
        bool ok;
        // проверить, вдруг обращение идёт к связке датчиков Коралл+Вибро
        if(koral_list.at(koral_in_list)->getType() != KorallPlusType) {
            // сформировать пакет для датчиков
            koralpack.setData(2, 0.0);
            ok = koralpack.makeAnswer(koral_list.at(koral_in_list)->getType());
        }
        else
        {
            // для Коралл+вибро взять и изменить значения для виртуальных датчиков
            cKoralSetting *k2, *k3;
            if(koral_list.at(koral_in_list+1)->getType() == PlusMassType) {
                k2 = koral_list.at(koral_in_list+1);
                k2->step();
                koralpack.setData(2,k2->getValue1());
                koralpack.setData(3,k2->getValue2());
                if(koral_list.at(koral_in_list+2)->getType() == PlusVibroType) {
                    k3 = koral_list.at(koral_in_list+2);
                    k3->step();
                    koralpack.setData(4,k3->getValue1());
                    koralpack.setData(5,k3->getValue2());
                }
            }
            ok = koralpack.makeAnswer(KorallPlusType);
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
        MainWindow::serialSend(koralpack.getPack());
        QString pckStr = static_cast<QString>(koralpack.getPack().toHex()).toUpper();
        if(ui->groupBox->isChecked())
        {                                  //ui->teInputData->insertHtml(QString(" - <font color = ""green"">[%1: %2] %3 <b>%4</b> %5</font>\n")
            logOutStr += QString(" - <font color = ""green"">[%1: %2] %3 <b>%4</b> %5</font>")
                                    .arg(QString::number(koral_in_list+1))
                                    .arg(koral_list.at(koral_in_list)->getName())
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
        ui->statusBar->showMessage("Отправка: " + hex.toHex().toUpper(), 1000);
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

    cKoral::combineAnswer(pck);

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
    if(koral_list.length() == 0)
    {
        ui->lFirstSet->deleteLater();
        koral_list.append(new cKoralSetting(1, tSensorType::KorallType, 1));
    }
     else
        switch(koral_list.at(koral_list.length()-1)->getType()){
        case KorallPlusType:
            koral_list.append(new cKoralSetting(koral_list.length()+1, PlusMassType, koral_list.at(koral_list.length()-1)->getAddr()));
            koral_list.at(koral_list.length()-1)->setFixedType();
            ui->vLayout->addWidget(koral_list.last());
            koral_list.append(new cKoralSetting(koral_list.length()+1, PlusVibroType, koral_list.at(koral_list.length()-1)->getAddr()));
            koral_list.at(koral_list.length()-1)->setFixedType();
            break;
        case PlusVibroType:
            koral_list.append(new cKoralSetting(koral_list.length()+1, KorallType, koral_list.at(koral_list.length()-1)->getAddr() + 1)); break;
        default:
            koral_list.append(new cKoralSetting(koral_list.length()+1, koral_list.at(koral_list.length()-1)->getType(), koral_list.at(koral_list.length()-1)->getAddr() + 1));
        }
    ui->vLayout->addWidget(koral_list.last());
}

void MainWindow::on_pbMinus_clicked()
{
    if(koral_list.length() > 1)
    {
        switch(koral_list.last()->getType()){
        case PlusVibroType:
            delete koral_list.last();
            koral_list.pop_back();
        default:
            delete koral_list.last();
            koral_list.pop_back();
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
    QAction * act_copy = new QAction(style()->standardIcon(QStyle::SP_FileDialogDetailedView), tr("Копировать"), menu->parent());
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
    if (!koral_list.length())
    {
        QMessageBox::information(this, "Отмена сохранения", "Необходимо настроить хотя бы один датчик", QDialogButtonBox::StandardButton::Ok);
    }
    if (str.right(4) != ".ini") str += ".ini";
    QSettings settings(str, QSettings::IniFormat);
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
    foreach(cKoralSetting * sensor, koral_list)
    {
        ++i;
        settings.beginGroup("Sensor" + QString::number(i));
        settings.setValue("Type", static_cast<int>(sensor->getType()));
        settings.setValue("Address", sensor->getAddr());
        settings.setValue("Value1", QString::number(sensor->getValue1(),'f', 3));
        settings.setValue("Value2", QString::number(sensor->getValue2(),'f', 3));
        settings.setValue("Increment1", QString::number(sensor->getInc1(),'f', 3));
        settings.setValue("Increment2", QString::number(sensor->getInc2(),'f', 3));
        settings.setValue("RandomFlag1", sensor->getRnd1());
        settings.setValue("RandomFlag2", sensor->getRnd2());
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
// загрузка настроек для главного окна
    ui->cbPort->setCurrentIndex(ui->cbPort->findText(settings.value("General/COM").toString()));
    ui->cbBitRate->setCurrentIndex(ui->cbBitRate->findText(settings.value("General/Bitrate").toString()));
    ui->groupBox->setChecked(settings.value("General/Print").toBool());
    ui->teInputData->document()->setMaximumBlockCount(settings.value("General/MaxLogLines").toInt());
    ui->leOutputData->setText(settings.value("General/OutputData").toString());
    ui->leOutputData->setPlaceholderText(settings.value("General/OutputMess").toString());
// загрузка настроек для каждого из датчиков
    quint8 i = 0;
    while(settings.contains("Sensor" + QString::number(++i) + "/Type"))
    {
        settings.beginGroup("Sensor" + QString::number(i));
        // если датчика ещё не существует в списке, создать
        if(koral_list.length() < i)
            MainWindow::on_pbPlus_clicked();
        koral_list.at(i-1)->setType(settings.value("Type").toInt());
        koral_list.at(i-1)->setAddr(settings.value("Address").toInt());
        koral_list.at(i-1)->setValue1(settings.value("Value1").toFloat());
        koral_list.at(i-1)->setValue2(settings.value("Value2").toFloat());
        koral_list.at(i-1)->setInc1(settings.value("Increment1").toFloat());
        koral_list.at(i-1)->setInc2(settings.value("Increment2").toFloat());
        koral_list.at(i-1)->setRnd1(settings.value("RandomFlag1", true).toBool());
        koral_list.at(i-1)->setRnd2(settings.value("RandomFlag2", true).toBool());
        koral_list.at(i-1)->setStat(settings.value("Status").toInt());
        koral_list.at(i-1)->setErr(settings.value("Error").toInt());
        settings.endGroup();
    }
    // если датчиков больше, чем в файле настроек, то удалить лишние
    while(koral_list.length() >= i)
        MainWindow::on_pbMinus_clicked();
    ui->statusBar->showMessage("Загрузка установок прошла успешно", 2000);
}
