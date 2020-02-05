#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QStyle>
#include <QTextCodec>
#include <QTime>
#include <QProcess>
#include <QDebug>
#include "sg_comport.h"
#include "koral.h"
#include "koralsetting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbOpen_clicked();
    void on_pbSend_clicked();
    void serialReceive(QByteArray pack);
    void serialSend(QByteArray snd);
    void on_pbClear_clicked();

    void on_pbCalcCRC_clicked();

    void on_pbPlus_clicked();

    void on_pbMinus_clicked();

    void on_leOutputData_textEdited(const QString &arg1);

    void contextMenuRequested(QPoint);

    void copyFromOutputData();

    void on_pbSave_clicked();

    void on_pbLoad_clicked();

protected slots:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    SgComPort *com;
    void initSerial();
};
#endif // MAINWINDOW_H
