/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hCOMLayout;
    QPushButton *pbLoad;
    QPushButton *pbSave;
    QLabel *lComport;
    QComboBox *cbPort;
    QSpacerItem *hSpacerBitrate;
    QComboBox *cbBitRate;
    QLabel *lBirate;
    QPushButton *pbOpen;
    QSpacerItem *hSpacerAgat;
    QLabel *label;
    QVBoxLayout *vCentralLayout;
    QGroupBox *groupBoxKorals;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *vKoralLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *vLayout;
    QLabel *lFirstSet;
    QFrame *vLine;
    QVBoxLayout *vKoralBtnLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pbMinus;
    QPushButton *pbPlus;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *teInputData;
    QPushButton *pbClear;
    QFrame *line;
    QVBoxLayout *vSendLayout;
    QFrame *hLine;
    QHBoxLayout *hSendLayout;
    QLabel *lSendPack;
    QLineEdit *leOutputData;
    QPushButton *pbCalcCRC;
    QPushButton *pbSend;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(920, 550);
        MainWindow->setMinimumSize(QSize(920, 330));
        QIcon icon;
        icon.addFile(QStringLiteral(":/List.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, 0, 4, 0);
        hCOMLayout = new QHBoxLayout();
        hCOMLayout->setSpacing(6);
        hCOMLayout->setObjectName(QStringLiteral("hCOMLayout"));
        hCOMLayout->setContentsMargins(10, -1, -1, -1);
        pbLoad = new QPushButton(centralWidget);
        pbLoad->setObjectName(QStringLiteral("pbLoad"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbLoad->sizePolicy().hasHeightForWidth());
        pbLoad->setSizePolicy(sizePolicy);
        pbLoad->setMinimumSize(QSize(30, 30));
        pbLoad->setMaximumSize(QSize(30, 30));
        pbLoad->setIconSize(QSize(24, 20));
        pbLoad->setFlat(true);

        hCOMLayout->addWidget(pbLoad);

        pbSave = new QPushButton(centralWidget);
        pbSave->setObjectName(QStringLiteral("pbSave"));
        pbSave->setMinimumSize(QSize(30, 30));
        pbSave->setMaximumSize(QSize(30, 30));
        pbSave->setIconSize(QSize(24, 20));
        pbSave->setFlat(true);

        hCOMLayout->addWidget(pbSave);

        lComport = new QLabel(centralWidget);
        lComport->setObjectName(QStringLiteral("lComport"));
        lComport->setMinimumSize(QSize(100, 0));
        lComport->setLayoutDirection(Qt::LeftToRight);
        lComport->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hCOMLayout->addWidget(lComport);

        cbPort = new QComboBox(centralWidget);
        cbPort->setObjectName(QStringLiteral("cbPort"));
        cbPort->setMinimumSize(QSize(80, 0));
        cbPort->setFocusPolicy(Qt::TabFocus);

        hCOMLayout->addWidget(cbPort);

        hSpacerBitrate = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hCOMLayout->addItem(hSpacerBitrate);

        cbBitRate = new QComboBox(centralWidget);
        cbBitRate->setObjectName(QStringLiteral("cbBitRate"));
        cbBitRate->setMinimumSize(QSize(80, 0));
        cbBitRate->setFocusPolicy(Qt::TabFocus);

        hCOMLayout->addWidget(cbBitRate);

        lBirate = new QLabel(centralWidget);
        lBirate->setObjectName(QStringLiteral("lBirate"));
        lBirate->setMinimumSize(QSize(40, 0));

        hCOMLayout->addWidget(lBirate);

        pbOpen = new QPushButton(centralWidget);
        pbOpen->setObjectName(QStringLiteral("pbOpen"));
        pbOpen->setFocusPolicy(Qt::TabFocus);

        hCOMLayout->addWidget(pbOpen);

        hSpacerAgat = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        hCOMLayout->addItem(hSpacerAgat);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(50, 50));
        label->setMaximumSize(QSize(50, 50));

        hCOMLayout->addWidget(label);


        verticalLayout->addLayout(hCOMLayout);

        vCentralLayout = new QVBoxLayout();
        vCentralLayout->setSpacing(6);
        vCentralLayout->setObjectName(QStringLiteral("vCentralLayout"));
        groupBoxKorals = new QGroupBox(centralWidget);
        groupBoxKorals->setObjectName(QStringLiteral("groupBoxKorals"));
        groupBoxKorals->setAutoFillBackground(false);
        horizontalLayout_4 = new QHBoxLayout(groupBoxKorals);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 0, 0, 4);
        vKoralLayout = new QVBoxLayout();
        vKoralLayout->setSpacing(0);
        vKoralLayout->setObjectName(QStringLiteral("vKoralLayout"));
        vKoralLayout->setContentsMargins(0, 0, 8, 2);
        scrollArea = new QScrollArea(groupBoxKorals);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setLineWidth(0);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 864, 189));
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(370, 70, 61, 40));
        vLayout = new QVBoxLayout(verticalLayoutWidget_3);
        vLayout->setSpacing(0);
        vLayout->setContentsMargins(11, 11, 11, 11);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        vLayout->setContentsMargins(0, 18, 0, 16);
        scrollArea->setWidget(scrollAreaWidgetContents);

        vKoralLayout->addWidget(scrollArea);

        lFirstSet = new QLabel(groupBoxKorals);
        lFirstSet->setObjectName(QStringLiteral("lFirstSet"));
        QPalette palette;
        QBrush brush(QColor(128, 128, 128, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lFirstSet->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Batang"));
        font.setPointSize(12);
        lFirstSet->setFont(font);
        lFirstSet->setFrameShape(QFrame::NoFrame);
        lFirstSet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lFirstSet->setTextInteractionFlags(Qt::NoTextInteraction);

        vKoralLayout->addWidget(lFirstSet);


        horizontalLayout_4->addLayout(vKoralLayout);

        vLine = new QFrame(groupBoxKorals);
        vLine->setObjectName(QStringLiteral("vLine"));
        vLine->setLayoutDirection(Qt::LeftToRight);
        vLine->setFrameShadow(QFrame::Raised);
        vLine->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(vLine);

        vKoralBtnLayout = new QVBoxLayout();
        vKoralBtnLayout->setSpacing(0);
        vKoralBtnLayout->setObjectName(QStringLiteral("vKoralBtnLayout"));
        vKoralBtnLayout->setSizeConstraint(QLayout::SetMinimumSize);
        vKoralBtnLayout->setContentsMargins(0, -1, -1, -1);
        verticalSpacer = new QSpacerItem(20, 250, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vKoralBtnLayout->addItem(verticalSpacer);

        pbMinus = new QPushButton(groupBoxKorals);
        pbMinus->setObjectName(QStringLiteral("pbMinus"));
        sizePolicy.setHeightForWidth(pbMinus->sizePolicy().hasHeightForWidth());
        pbMinus->setSizePolicy(sizePolicy);
        pbMinus->setMaximumSize(QSize(25, 25));
        pbMinus->setFlat(true);

        vKoralBtnLayout->addWidget(pbMinus);

        pbPlus = new QPushButton(groupBoxKorals);
        pbPlus->setObjectName(QStringLiteral("pbPlus"));
        sizePolicy.setHeightForWidth(pbPlus->sizePolicy().hasHeightForWidth());
        pbPlus->setSizePolicy(sizePolicy);
        pbPlus->setMaximumSize(QSize(25, 25));
        pbPlus->setAutoFillBackground(false);
        pbPlus->setFlat(true);

        vKoralBtnLayout->addWidget(pbPlus);


        horizontalLayout_4->addLayout(vKoralBtnLayout);


        vCentralLayout->addWidget(groupBoxKorals);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(true);
        groupBox->setChecked(false);
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        teInputData = new QTextEdit(groupBox);
        teInputData->setObjectName(QStringLiteral("teInputData"));
        teInputData->setMinimumSize(QSize(100, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier New"));
        font1.setPointSize(10);
        teInputData->setFont(font1);
        teInputData->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        teInputData->setMouseTracking(false);
        teInputData->setFocusPolicy(Qt::WheelFocus);
        teInputData->setLayoutDirection(Qt::LeftToRight);
        teInputData->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        teInputData->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout_7->addWidget(teInputData);

        pbClear = new QPushButton(groupBox);
        pbClear->setObjectName(QStringLiteral("pbClear"));
        pbClear->setEnabled(true);
        sizePolicy1.setHeightForWidth(pbClear->sizePolicy().hasHeightForWidth());
        pbClear->setSizePolicy(sizePolicy1);
        pbClear->setMinimumSize(QSize(60, 20));
        pbClear->setMaximumSize(QSize(60, 20));
        pbClear->setBaseSize(QSize(60, 20));
        pbClear->setLayoutDirection(Qt::RightToLeft);
        pbClear->setAutoFillBackground(false);
        pbClear->setFlat(true);

        verticalLayout_7->addWidget(pbClear);


        vCentralLayout->addWidget(groupBox);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vCentralLayout->addWidget(line);


        verticalLayout->addLayout(vCentralLayout);

        vSendLayout = new QVBoxLayout();
        vSendLayout->setSpacing(6);
        vSendLayout->setObjectName(QStringLiteral("vSendLayout"));
        vSendLayout->setContentsMargins(4, -1, 4, -1);
        hLine = new QFrame(centralWidget);
        hLine->setObjectName(QStringLiteral("hLine"));
        hLine->setFrameShape(QFrame::HLine);
        hLine->setFrameShadow(QFrame::Sunken);

        vSendLayout->addWidget(hLine);

        hSendLayout = new QHBoxLayout();
        hSendLayout->setSpacing(6);
        hSendLayout->setObjectName(QStringLiteral("hSendLayout"));
        lSendPack = new QLabel(centralWidget);
        lSendPack->setObjectName(QStringLiteral("lSendPack"));
        lSendPack->setMinimumSize(QSize(50, 0));
        lSendPack->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hSendLayout->addWidget(lSendPack);

        leOutputData = new QLineEdit(centralWidget);
        leOutputData->setObjectName(QStringLiteral("leOutputData"));
        leOutputData->setMinimumSize(QSize(240, 0));
        leOutputData->setFont(font1);
        leOutputData->setContextMenuPolicy(Qt::CustomContextMenu);

        hSendLayout->addWidget(leOutputData);

        pbCalcCRC = new QPushButton(centralWidget);
        pbCalcCRC->setObjectName(QStringLiteral("pbCalcCRC"));
        pbCalcCRC->setMinimumSize(QSize(100, 0));

        hSendLayout->addWidget(pbCalcCRC);

        pbSend = new QPushButton(centralWidget);
        pbSend->setObjectName(QStringLiteral("pbSend"));
        pbSend->setFocusPolicy(Qt::WheelFocus);
        pbSend->setAutoDefault(true);

        hSendLayout->addWidget(pbSend);


        vSendLayout->addLayout(hSendLayout);


        verticalLayout->addLayout(vSendLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 920, 21));
        menuBar->setNativeMenuBar(false);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setMaximumSize(QSize(16777215, 20));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        lComport->setBuddy(cbPort);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cbPort, cbBitRate);
        QWidget::setTabOrder(cbBitRate, pbOpen);
        QWidget::setTabOrder(pbOpen, leOutputData);
        QWidget::setTabOrder(leOutputData, pbSend);

        retranslateUi(MainWindow);

        pbClear->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\220\320\223\320\220\320\242-\320\270\320\274\320\270\321\202\320\260\321\202\320\276\321\200", 0));
#ifndef QT_NO_STATUSTIP
        pbLoad->setStatusTip(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\272\320\271\320\270", 0));
#endif // QT_NO_STATUSTIP
        pbLoad->setText(QString());
#ifndef QT_NO_STATUSTIP
        pbSave->setStatusTip(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
#endif // QT_NO_STATUSTIP
        pbSave->setText(QString());
        lComport->setText(QApplication::translate("MainWindow", "COM-\320\277\320\276\321\200\321\202", 0));
#ifndef QT_NO_STATUSTIP
        cbPort->setStatusTip(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 COM-\320\277\320\276\321\200\321\202\320\260 (ttyS \320\264\320\273\321\217 Linux)", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        cbBitRate->setStatusTip(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270 \320\276\320\261\320\274\320\265\320\275\320\260 (\320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216 57600 bps)", 0));
#endif // QT_NO_STATUSTIP
        lBirate->setText(QApplication::translate("MainWindow", "bps", 0));
#ifndef QT_NO_STATUSTIP
        pbOpen->setStatusTip(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214/\320\267\320\260\320\272\321\200\321\213\321\202\321\214 COM-\320\277\320\276\321\200\321\202", 0));
#endif // QT_NO_STATUSTIP
        pbOpen->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("MainWindow", "\320\220\320\223\320\220\320\242-\320\232\320\230\320\237", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QApplication::translate("MainWindow", "\320\220\320\236 \320\234\320\276\321\200\320\270\320\275\321\204\320\276\321\200\320\274\321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\220\320\263\320\260\321\202-\320\232\320\230\320\237 \320\263.\320\240\321\217\320\267\320\260\320\275\321\214, \320\232\320\260\321\200\320\277\321\203\320\275\321\214\320\272\320\270\320\275 \320\257., 2019 \320\263.", 0));
#endif // QT_NO_STATUSTIP
        label->setText(QApplication::translate("MainWindow", "\320\220\320\263\320\260\321\202-\320\232\320\230\320\237", 0));
#ifndef QT_NO_STATUSTIP
        groupBoxKorals->setStatusTip(QApplication::translate("MainWindow", "\320\224\320\273\321\217 \320\264\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\275\320\276\320\262\320\276\320\263\320\276 \321\200\320\260\321\201\321\205\320\276\320\264\320\276\320\274\320\265\321\200\320\260 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 +", 0));
#endif // QT_NO_STATUSTIP
        groupBoxKorals->setTitle(QApplication::translate("MainWindow", "\320\224\320\260\321\202\321\207\320\270\320\272\320\270", 0));
        lFirstSet->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\275\320\260 \320\255\320\242\320\243 \320\272\320\275\320\276\320\277\320\272\321\203 \320\264\320\273\321\217 \320\264\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\264\320\260\321\202\321\207\320\270\320\272\320\260 \320\262 \321\201\320\277\320\270\321\201\320\276\320\272 \320\270\320\274\320\270\321\202\320\260\321\202\320\276\321\200\320\260 \342\206\222</p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        pbMinus->setToolTip(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pbMinus->setStatusTip(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\270\320\271 \321\200\320\260\321\201\321\205\320\276\320\264\320\276\320\274\320\265\321\200 \320\270\320\267 \321\201\320\277\320\270\321\201\320\272\320\260", 0));
#endif // QT_NO_STATUSTIP
        pbMinus->setText(QApplication::translate("MainWindow", "-", 0));
#ifndef QT_NO_TOOLTIP
        pbPlus->setToolTip(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pbPlus->setStatusTip(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\265\321\211\321\221 \320\276\320\264\320\270\320\275 \321\200\320\260\321\201\321\205\320\276\320\264\320\276\320\274\320\265\321\200 \320\262 \321\201\320\277\320\270\321\201\320\276\320\272", 0));
#endif // QT_NO_STATUSTIP
        pbPlus->setText(QApplication::translate("MainWindow", "+", 0));
#ifndef QT_NO_STATUSTIP
        groupBox->setStatusTip(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 / \320\262\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\273\320\276\320\263\320\263\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0));
#endif // QT_NO_STATUSTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#ifndef QT_NO_STATUSTIP
        teInputData->setStatusTip(QApplication::translate("MainWindow", "\320\236\320\272\320\275\320\276 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#endif // QT_NO_STATUSTIP
        teInputData->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
#ifndef QT_NO_STATUSTIP
        pbClear->setStatusTip(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\276\320\272\320\275\320\276 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", 0));
#endif // QT_NO_STATUSTIP
        pbClear->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", 0));
        lSendPack->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\213\320\273\320\272\320\260:", 0));
#ifndef QT_NO_STATUSTIP
        leOutputData->setStatusTip(QApplication::translate("MainWindow", "\320\224\320\273\321\217 \320\232\320\276\321\200\320\260\320\273\320\273\320\260: DST SRC 24 CMD float32 float32 float32 ERR STA", 0));
#endif // QT_NO_STATUSTIP
        leOutputData->setPlaceholderText(QString());
#ifndef QT_NO_STATUSTIP
        pbCalcCRC->setStatusTip(QApplication::translate("MainWindow", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\321\214 \320\277\320\276\321\201\321\213\320\273\320\272\321\203 \321\201\321\202\320\260\321\200\321\202\320\276\320\262\321\213\320\274, \321\201\321\202\320\276\320\277\320\276\320\262\321\213\320\274 \320\261\320\260\320\271\321\202\320\260\320\274\320\270, \320\272\320\276\320\275\321\202\321\200\320\276\320\273\321\214\320\275\320\276\320\271 \321\201\321\203\320\274\320\274\320\276\320\271", 0));
#endif // QT_NO_STATUSTIP
        pbCalcCRC->setText(QApplication::translate("MainWindow", "ST+{ }+CRC+EOT", 0));
#ifndef QT_NO_STATUSTIP
        pbSend->setStatusTip(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\321\201\321\213\320\273\320\272\321\203", 0));
#endif // QT_NO_STATUSTIP
        pbSend->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
