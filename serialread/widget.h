#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QString>
#include <QTime>
#include <cmath>
#include "qcustomplot.h"
#define SYNC 0xAA
#define PSQ 0x02
#define HRV 0x03
#define RWV 0x80
#define CON 0x08
#define DEBA 0x84
#define DEBB 0x85
#define edge 25000

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void parsepayload(QByteArray payload, char plength);
    ~Widget();


private slots:
    void on_startbt_clicked();

    void on_stopbt_clicked();

    void serialPort_readyread_Slot();

    void on_clearbt_clicked();

    void plot();

    void findpeak();

    void feature_update();

//    void realtimeDataSlot();

    void on_savebt_clicked();

    void on_clear_temp_bt_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
    QByteArray hex, payload;
    QString poorsignal, heartrate;
    QVector<int16_t> rawwave;
    QVector<double> time, peak, NNitv;

    QByteArray buf;
    uint checksum;
    unsigned char c, plength;

    uint p=0, plotflag = 1, a=0;
    //parse packet
    //plotflag unused

    QTimer dataTimer, anaTimer;

//    QCPItemTracer *itemDemoPhaseTracer;
//    int currentDemoIndex;
    //plot

};


//void parsepayload(QByteArray payload, char plength);

#endif // WIDGET_H
