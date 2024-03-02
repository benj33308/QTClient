#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePlot();

private:
    QTimer *timer;
    QCustomPlot *customPlot;
    QCPLayer *dataLayer;
    QCPGraph *graph;
    QVector<double> timeData;
    QVector<double> payloadData;
};




#endif // MAINWINDOW_H
