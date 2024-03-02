

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // 创建 QCustomPlot 控件
    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    // 创建数据层
    dataLayer = new QCPLayer(customPlot, "Data");

    // 创建图表对象
    graph = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(graph);
    graph->setPen(QPen(Qt::blue));  // 设置曲线颜色
    graph->setLayer(dataLayer);  // 设置使用的层

    // 设置坐标轴标签
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Payload");

    // 设置坐标轴范围
    customPlot->xAxis->setRange(0, 10);  // 根据需求自行调整范围
    customPlot->yAxis->setRange(0, 100); // 根据需求自行调整范围

    // 创建定时器，每隔一段时间更新曲线图
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
    timer->start(1000);  // 根据需求自行调整更新间隔
}

MainWindow::~MainWindow()
{
    delete customPlot;
    delete timer;
}

void MainWindow::updatePlot()
{
    // 清空数据
    graph->clearData();

    // 获取当前时间作为横坐标
    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;

    // 添加新的数据点
    timeData.append(currentTime);
    payloadData.append(payload.toDouble());

    // 设置数据
    graph->setData(timeData, payloadData);

    // 重新绘制曲线图
    customPlot->replot();
}
