#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile temp("E:\\workspace\\qt\\demo01\\serialread\\temp.txt");
    QTextStream in(&temp);
    if(temp.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        in<<"";
    }
    temp.close();//格式化temp.txt

    QStringList SerialNamePort;
    serialPort = new QSerialPort(this);

    connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialPort_readyread_Slot()));
//connect the signal to the slot

    foreach (const QSerialPortInfo &info ,QSerialPortInfo::availablePorts()) {
        SerialNamePort<<info.portName();
    }
    ui->serialCB->addItems(SerialNamePort);
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-7500,7500);
//range -32768, 32767 -7500,7500
//search the available serialport and show
}

Widget::~Widget()
{
    delete ui;
}

void Widget::serialPort_readyread_Slot()
{

    buf = serialPort->readAll();
    hex.append(buf);

//    qDebug()<<hex.size()<<' '<<p;

    ui->serialportPT->appendPlainText(buf.toHex(' ').toUpper());
    ui->serialportPT->moveCursor(QTextCursor::End);
    //receive the data from serialport

{
    if(hex.size() >= 3000 && p > 2500)
    {
        hex.remove(0,2500);
        p -= 2500;//restrict the size of hex
    }
// !!! bug here  finished
/*在清除前面的数据的时候hexsize在2504的时候出了问题，
  然后就读取不了了
  有可能是p远落后于hexsize，然后-2500的时候减成了负数，然后就爆了
  但是用整型数好像也有问题
  正确的，改好了，就是把p减成负数然后出了问题，减之前加个限制就行
*/

    while(p+3 < hex.size())
    {
        c = hex.at(p);
        if(c != SYNC){ p++; continue;}

        c = hex.at(p+1);
        if(c != SYNC) { p++; continue;}//make sure p points at start byte

        while(1)
        {
            plength=hex.at(p+2);
            if( plength != 170 ) { break;}
            p++;//if ==AA,means last checksum is AA,and this byte is the second SYNC, just repeat this step and correct the p.
        }//优化空间：不用while，写两个if

        if( p + (uint)plength + 4 >= hex.size()) break;

        if( (uint)plength > 169 ) continue;

        payload = hex.mid(p+3, (uint)plength);//read the payload

//        qDebug()<<static_cast<quint8>(payload.at(0));
        checksum = 0;
        p = p + (uint)plength + 3;//p point at the start of next datapacket
        for(int i=0; i<(uint)plength; i++ ) checksum += static_cast<quint8>(payload.at(i));
        checksum &= 0xFF;
        checksum = ~checksum & 0xFF;

        if(checksum != static_cast<quint8>(hex.at(p))) continue;
        p++;
//        qDebug()<<p<<" Parse successed ";
        parsepayload(payload,plength);

    }
}//pick up the data row

}//when the serialport ready to read, this func will be called

void Widget::parsepayload(QByteArray packet, char length)
{
    int i = 0;
    unsigned int temp = 0;
    static QTime timenow = QTime::currentTime();
    double record = timenow.msecsTo(QTime::currentTime())/1200.0;
    while(i < (uint)length)
    {
        switch (static_cast<quint8>(packet.at(i))) {
        case PSQ:
//            ui->featurePT->appendPlainText(packet.mid(i+1,1).toHex().toUpper());
            i += 2;
            break;
        case HRV:
            ui->featurePT->appendPlainText(packet.mid(i+1,1).toHex().toUpper());

            i += 20;
            break;
        case RWV:
            temp = static_cast<uchar>(packet.at(i+3));
//            temp = temp << 8;
            temp = temp | static_cast<uchar>(packet.at(i+2))<<8;
//            if (temp < 65280)//unknown too large data
//            {
                rawwave.append(temp);
                time.append(record);
//            }
//            qDebug()<<packet.mid(i+2,2).toHex().toUpper()<<' '<<(int)temp;
            i += 4;
            break;
        case CON:
//            serialPort->write(packet.mid(i+1,1));
            i += 2;
            break;
        case DEBA:
            i += 7;
            break;
        case DEBB:
            i += 5;
            break;
        default:
            i ++;
            break;
        }
    }

/*{
    if(plotflag == 1 && time < rawwave.size()+a*2000)
    {
      // add data to lines:
        ui->customPlot->graph(0)->addData(time, (int)(rawwave.at(time-a*2000)));

      // make key axis range scroll with the data (at a constant range size of 8):+rawwave.at(time +1 - a*4000)+rawwave.at(time+2-a*4000)
        ui->customPlot->xAxis->setRange(time, 1500, Qt::AlignRight);
        ui->customPlot->replot();
        time++;
    }
//    else
//    {
//        qDebug()<<p<<hex.size()<<rawwave.size()<<"end";
//    }

}//plot*/


    if(rawwave.size()>=30000)
    {
        QString fileName = "E:\\workspace\\qt\\demo01\\serialread\\temp.txt";

        QFile file(fileName);

        //以文本方式打开
        if(file.open(QIODevice::Append | QIODevice::Text) )
        {
            QTextStream out(&file); //IO设备对象的地址对其进行初始化

            for (int i=0; i <= edge-1 ;i++)
                out<<QString::number(time.at(i))<<": "<<QString::number(rawwave.at(i))<<"\n";
            file.close();
        }
        qDebug()<<"saved";
        rawwave.remove(0,edge);
        time.remove(0,edge);
        a++;
    }
}

void Widget::plot()
{
    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:

//    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
//    static double lastPointKey = 0;
//    if (key-lastPointKey > 0.01 && rawwave.size()>0) // at most add point every 2 ms
//    {
//      // add data to lines:
//            qDebug()<<key<<rawwave.size()<<rawwave.back();
//      ui->customPlot->graph(0)->addData(key, (int)(rawwave.back()));
//      // rescale value (vertical) axis to fit the current data:
//      lastPointKey = key;
//    }
    static double key = 0, lastkey = 0;
    while (rawwave.size() + a*edge > key) {
       ui->customPlot->graph(0)->addData(key/512, (int)(rawwave.at(key- a*edge)));
       lastkey = key;
       key = key + 1;
    }

    ui->customPlot->xAxis->setRange(key/512, 5, Qt::AlignRight);
    ui->customPlot->replot();

}//plot, called in clicked()

void Widget::findpeak()
{
    /*
     * 时间要如何存储 在加点的时候把时间加上
     * 总共有 rawwave time interval
     * 计算指标 NN.mean NN50 SDNN PNN50 RMSSD
     * 对当前的rawwave处理，定位极大值的下标
     * 讲道理做这个不用滑动窗口吧
     * 自适应寻找波峰
     * 先滤波去毛刺，然后直接找两点间最大值
     * ！！有点问题，这样不太精准，找出来的峰值有较大偏差
     * 方向1，强力滤波
     * 方向2，当成最大值找，找到之后直接跳200个点
     * ！！！方向3，设定一个500个点大小的窗口，步长为200个点，直接找最值，连滤波都不用了
     * Q：极值刚好卡在边界怎么办？
     * A：1，卡在边界也能找到最值啊，没关系。2，个别点寻找错误对最后计算结果基本无影响
     */

/*    static unsigned int fliter_pointer = 0;//point at the lastest time
    QVector<double> fliter;

    fliter.append(rawwave.at(fliter_pointer - a * edge));
    fliter_pointer++;

    while(fliter_pointer - a * edge < rawwave.size() - 2)
    {
        fliter.append((rawwave.at(fliter_pointer - a * edge-1)+rawwave.at(fliter_pointer - a * edge)+rawwave.at(fliter_pointer - a * edge+1))/3);
        fliter_pointer++;
    }

    fliter.append(rawwave.back());
    fliter_pointer++;//fliter

    int i=1;
    while (i < fliter.size())
    {
        if(rawwave.at(fliter_pointer - a*edge - fliter.size() + i) > 1000)
            if(fliter.at(i) >= fliter.at(i-1) && fliter.at(i) >= fliter.at(i+1))
            {
                peak.append(time.at(fliter_pointer - fliter.size() + i));
                i+=140;
                qDebug()<<fliter_pointer - a*edge - fliter.size() + i<<peak.back();
            }
        i++;
    }//find the peak*/

    static unsigned int sp = 0, last_index = 0;
    int max_index, l;
    while(sp + 300 < rawwave.size() + a * edge)
    {
        l = sp;
        max_index = sp + 1;
        for( ; sp <= l+200 ; sp++)
        {
            if(rawwave.at(max_index - a * edge) < rawwave.at(sp - a * edge))
                max_index = sp;
        }
        if(max_index - last_index >= 150)
        {
            peak.append(time.at(max_index - a * edge));
            last_index = max_index;
        }
    }
//    direction 3

    feature_update();
}
void Widget::feature_update()
{
    /*
     * calculate the NN.mean HRV, NN50, SDNN, PNN50, RMSSD
     * frequent domain TP LF HF LF/RF
     * NNitv refers to NNinterval
     * !!！ bug here
     * 还没查清楚哪里有越界机会，先暂且是越界了吧。未解决
     * 现在的想法是没数据时rawwave出界了，有持续数据的时候出界是什么原因？
     * 实验证明是之前的滤波算法出了问题，这里反而没有毛病，峰值检测使用方向3之后就不用解决这个bug了
     */
    static int NNpointer = 0;
    int NNft = 0;
    static double sum = 0;
    double PNNft, SDNN = 0, RMSSD = 0;

    for(; NNpointer < peak.size()-1 ; NNpointer++)
    {
        NNitv.append(peak.at(NNpointer + 1) - peak.at(NNpointer));
        sum += NNitv.at(NNpointer);
    }

    for(int i=0;i<NNpointer-1;i++)
    {
        SDNN += pow(NNitv.at(i)- sum / NNpointer,2);
        RMSSD += pow(NNitv.at(i+1)-NNitv.at(i),2);

        if((NNitv.at(i+1) - NNitv.at(i)) * 1000 > 50)
            NNft++;//NN50
    }
    SDNN = sqrt(SDNN / NNpointer) * 1000;//SDNN
    RMSSD = sqrt(RMSSD / NNpointer) *1000 ;//RMSSD

    PNNft = NNft / (double)(NNpointer-1);//PNN50

    ui->NN50pt->appendPlainText(QString::number(NNft));
    ui->PNNftpt->appendPlainText(QString::number(PNNft,'g',3));
    ui->SDNNpt->appendPlainText(QString::number(SDNN,'g',3));
    ui->RMSSDpt->appendPlainText(QString::number(RMSSD,'g',3));
    qDebug()<<peak.size()<<peak.back();
}

void Widget::on_startbt_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checBits;

    baudRate = QSerialPort::Baud57600;
    dataBits = QSerialPort::Data8;
    stopBits = QSerialPort::OneStop;
    checBits = QSerialPort::NoParity;
//define the configuration
    serialPort->setPortName(ui->serialCB->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setParity(checBits);
    serialPort->setStopBits(stopBits);
//setup the configuration
    serialPort->open(QIODevice::ReadWrite);
//    plotflag = 1;
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(plot()));
    dataTimer.start(10);// !!调整速度
    connect(&anaTimer, SIGNAL(timeout()), this, SLOT(findpeak()));
    anaTimer.start(2000);

//{
//    if(serialPort->open(QIODevice::ReadWrite) == true)
//        QMessageBox::information(this,"suggestion","success");
//    else
//        QMessageBox::critical(this,"suggestion","fail");
//}
//enable to check out whether the serialport has already opened or not

}
//Start button clicked

void Widget::on_stopbt_clicked()
{
    serialPort->close();
//    qDebug()<<rawwave;
//    plotflag = 0;
    dataTimer.stop();
    anaTimer.stop();
}
//stop button clicked

void Widget::on_clearbt_clicked()
{
    ui->serialportPT->clear();
    ui->featurePT->clear();

}


void Widget::on_savebt_clicked()
{
    /*
     * 保存数据，并不是把完整的全部数据记录下来，只保存波峰位置
     * 还得是完全保留，你得算频谱
     *
     * 保存格式
     * time: rawwave
     *
     * bug here!!! finished
     * 描述：两次保存在temp.txt之后保存就会出bug，bug表现为保存前2万多个数据点，时间和值都对的上
     * 但是一次保存，即数据点小于55000个时保存没有问题
     * 现在有一个解决方法，就是把time也保存进temp.txt里面，这样就可以排除vector time爆炸的可能
     * 但这样的成本太大了，要改好多地方。
     * 还是觉得这个方法吧，这样才能长时间记录。
     * 要改的地方主要是峰值查找，temp保存，还有datasave保存
     * 改好了，原因是buffer存太多东西爆了，现在直接把time也存进temp里面，buffer改成单个QString变量
    */

    QFileDialog dlg(this);

        //获取内容的保存路径
        QString fileName = dlg.getSaveFileName(this, tr("Save As"), "./", tr("Text File(*.txt)"));

        if( fileName == "" )
        {
            return;
        }

        //内容保存到路径文件
        QFile file(fileName);
        QFile temp("E:\\workspace\\qt\\demo01\\serialread\\temp.txt");
        QTextStream in(&temp);
        QString buffer/*buffer[25001]*/;
        //以文本方式打开
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&file); //IO设备对象的地址对其进行初始化

//            for(int i=0;i<a;i++)
//            {
//                if(temp.open(QIODevice::ReadOnly))
//                for(int j=i*edge ; j< (i+1) * edge ; j++)
//                {
//                    buffer = in.readLine();

//                }
//                temp.close();
//                for(int j=0;j<edge;j++)
//                {
//                    out<<buffer[j]<<"\n";
//                }
//            }
            if(temp.open(QIODevice::ReadOnly))
                for(int j =0;j<a*edge;j++)
                    out<<in.readLine()<<"\n";
            for (int i=0; i < rawwave.size() ;i++)
                out<<QString::number(time.at(i))<<": "<<QString::number(rawwave.at(i))<<"\n";

//            out<<QString::number();//feature output
            QMessageBox::warning(this, tr("Finish"), tr("Successfully save the file!"));

            file.close();

//            if(temp.open(QIODevice::WriteOnly | QIODevice::Text))
//            {

//                in<<"";
//            }
//            temp.close();//格式化temp.txt

        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("File to open file!"));
        }
}

void Widget::on_clear_temp_bt_clicked()
{
    QFile temp("E:\\workspace\\qt\\demo01\\serialread\\temp.txt");
    QTextStream in(&temp);
    if(temp.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        in<<"";
    }
    temp.close();//格式化temp.txt
    QMessageBox::warning(this, tr("Finish"), tr("temp.txt already initial"));
}
