#include "mywidget.h"
#include "ui_mywidget.h"
#include "pythreadstatelock.h"
/*
 * ***************************************************************************************
 * 运行平台：正点原子家的i.mx6ull开发板、树莓派4B、windows10、11系统的电脑,实测可行
 * @log
 * 电感通道1：1、2、3、 4、 5、 6
 * 电感通道2：7、8、13、14、15、0
 * 霍尔通道1：10
 * 霍尔通道2：11
 * 距离通道 ：9、12
 * *************************************************************************************
**/
/*
 * @brief 主窗口类构造函数，启动时先执行
 * @param 父类QWidget
 * @retval 无
*/
int maxYother;
int minYother;
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->resize(QSize(1280,720));//大小
    maxSize = 4000;
    maxX = graph_x_axis_Count;
    maxY = 6000;
    maxYother=maxY;
    minYother=minY;
    QCustomPlot* QChart_hall = ui->widget_hall;
    QChart_hall->addGraph();
    QChart_hall->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
    QChart_hall->addGraph();
    QChart_hall->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 300);
    plotGradient.setColorAt(0, QColor(208, 255, 232));
    plotGradient.setColorAt(1, QColor(208, 255, 232));
    ui->widget_hall->setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(255, 255, 227));
    axisRectGradient.setColorAt(1, QColor(255, 255, 227));
    ui->widget_hall->axisRect()->setBackground(axisRectGradient);   // 设置QCPAxisRect背景颜色

    ui->widget_hall->setBackground(plotGradient);
    QChart_hall->xAxis->setTickLabels(false);//显示刻度值
    QChart_hall->yAxis->setLabel("信号幅值Y2");//轴标签
    ui->widget_hall->yAxis->setLabelColor("black");
    ui->widget_hall->xAxis->setTickLabelColor("black");
    ui->widget_hall->yAxis->setTickLabelColor("black");
    ui->widget_hall->xAxis->setBasePen(QPen("black"));
    ui->widget_hall->yAxis->setBasePen(QPen("black"));
    ui->widget_hall->xAxis->setTickPen(QPen("black"));
    ui->widget_hall->yAxis->setTickPen(QPen("black"));
    ui->widget_hall->xAxis->setSubTickPen(QPen("black"));
    ui->widget_hall->yAxis->setSubTickPen(QPen("black"));
//    ui->widget_hall->setVisible(0);//设置不可见
//    ui->widget_hall->graph(0)->setSmooth(true);//添加平滑曲线
//    ui->widget_hall->graph(1)->setSmooth(true);//添加平滑曲线
//    QSplineSeries_hall = new QLineSeries();
//    QSplineSeries_hall2 = new QLineSeries();
//    QSplineSeries_hall->setUseOpenGL(true);
//    QSplineSeries_hall2->setUseOpenGL(true);
    QChart_hall->axisRect()->setupFullAxesBox();
    QChart_hall->xAxis->setRange(0, maxX);
    QChart_hall->xAxis->grid()->setVisible(false);
    QChart_hall->yAxis->setRange(-3000, 7000);
//    QChart_hall->setTheme(QtCharts::QChart::ChartThemeDark);


    QCustomPlot* QChart_coil = ui->widget_coil;
    QChart_coil->addGraph();
    QChart_coil->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
    QChart_coil->addGraph();
    QChart_coil->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
    QLinearGradient plotGradient2;
    plotGradient2.setStart(0, 0);
    plotGradient2.setFinalStop(0, 350);
    plotGradient2.setColorAt(0, QColor(208, 255, 232));
    plotGradient2.setColorAt(1, QColor(208, 255, 232));
    ui->widget_coil->setBackground(plotGradient2);

    QLinearGradient axisRectGradient2;
    axisRectGradient2.setStart(0, 0);
    axisRectGradient2.setFinalStop(0, 350);
    axisRectGradient2.setColorAt(0, QColor(255, 255, 227));
    axisRectGradient2.setColorAt(1, QColor(255, 255, 227));
    ui->widget_coil->axisRect()->setBackground(axisRectGradient2);   // 设置QCPAxisRect背景颜色

    QChart_coil->xAxis->setTickLabels(false);//显示刻度值
    QChart_coil->yAxis->setLabel("信号幅值Y1");//轴标签
    ui->widget_coil->yAxis->setLabelColor("black");
    ui->widget_coil->xAxis->setTickLabelColor("black");
    ui->widget_coil->yAxis->setTickLabelColor("black");
    ui->widget_coil->xAxis->setBasePen(QPen("black"));
    ui->widget_coil->yAxis->setBasePen(QPen("black"));
    ui->widget_coil->xAxis->setTickPen(QPen("black"));
    ui->widget_coil->yAxis->setTickPen(QPen("black"));
    ui->widget_coil->xAxis->setSubTickPen(QPen("black"));
    ui->widget_coil->yAxis->setSubTickPen(QPen("black"));
//    ui->widget_coil->graph(0)->setSmooth(true);//添加平滑曲线
//    ui->widget_coil->graph(1)->setSmooth(true);//添加平滑曲线

//    QSplineSeries_hall = new QLineSeries();
//    QSplineSeries_hall2 = new QLineSeries();
//    QSplineSeries_hall->setUseOpenGL(true);
//    QSplineSeries_hall2->setUseOpenGL(true);
    QChart_coil->axisRect()->setupFullAxesBox();
    QChart_coil->xAxis->setRange(0, maxX);
    QChart_coil->xAxis->grid()->setVisible(false);
    QChart_coil->yAxis->setRange(-3000, 7000);
//    QChart_hall->setTheme(QtCharts::QChart::ChartThemeDark);
    // 使上下轴、左右轴范围同步
    connect(QChart_hall->xAxis, SIGNAL(rangeChanged(QCPRange)), QChart_hall->xAxis2, SLOT(setRange(QCPRange)));
    connect(QChart_hall->yAxis, SIGNAL(rangeChanged(QCPRange)), QChart_hall->yAxis2, SLOT(setRange(QCPRange)));
    connect(QChart_coil->xAxis, SIGNAL(rangeChanged(QCPRange)), QChart_coil->xAxis2, SLOT(setRange(QCPRange)));
    connect(QChart_coil->yAxis, SIGNAL(rangeChanged(QCPRange)), QChart_coil->yAxis2, SLOT(setRange(QCPRange)));


    connect(&QTimer_socket_connect_wait, &QTimer::timeout,this,&MyWidget::QTimer_socket_connect_wait_slots);
    connect(&QTimer_alarm_label,&QTimer::timeout,this,&MyWidget::QTimer_alarm_label_slots);
    connect(&QTcpSocket_DAQ, &QTcpSocket::connected,this,&MyWidget::QTcpSocket_DAQ_connected_slots);
    connect(&QTcpSocket_DAQ, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&MyWidget::QTcpSocket_DAQ_connected_error_slots);
    connect(&QTcpSocket_cloud, &QTcpSocket::connected,this,&MyWidget::QTcpSocket_cloud_connected_slots);
    connect(&QTcpSocket_cloud, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&MyWidget::QTcpSocket_cloud_connected_error_slots);
    connect(&Widget_set_win,&Widget_set::signals_bn_set_save,this,&MyWidget::slots_widget_set_handle);
    //connect(&thread_tcp_obj,&thread_tcp::sucessed_data_trans_togetner_socket,this,&MyWidget::thread_getdata_graph_plot,Qt::DirectConnection);

    QTimer_alarm_label.start(500);
    if (QVector_QPointF_coil_graph_data1.isEmpty())//开辟空间
    {
        QVector_QPointF_coil_graph_data1.reserve(graph_x_axis_Count);
        QVector_QPointF_coil_graph_data2.reserve(graph_x_axis_Count);
        QVector_QPointF_hall_graph_data1.reserve(graph_x_axis_Count);
        QVector_QPointF_hall_graph_data2.reserve(graph_x_axis_Count);
        for (int i = 0; i < graph_x_axis_Count; ++i)
        {
            QVector_QPointF_coil_graph_data1.append(QPointF(i, 0));
            QVector_QPointF_coil_graph_data2.append(QPointF(i, 0));
            QVector_QPointF_hall_graph_data1.append(QPointF(i, 0));
            QVector_QPointF_hall_graph_data2.append(QPointF(i, 0));
        }
    }
    qDebug()<<QDir_data_save_dir.currentPath();
    if(QDir_data_save_dir.exists("data_dir") == false)
    {
        QDir_data_save_dir.mkdir("data_dir");
    }
    //ui->pushButton_quit->hide();//回放功能未完成，隐藏按

}
/*
 * @brief 主窗口类析构函数，程序结束时最后执行
 * @param 无
 * @retval 无
*/
MyWidget::~MyWidget()
{
    delete QSplineSeries_coil;
    delete QSplineSeries_coil2;
    delete QSplineSeries_hall;
    delete QSplineSeries_hall2;
    delete QChart_coil;
    delete QChart_hall;
    delete ui;
}
/*
 * @brief 开始按钮的槽函数，点击开始按钮执行
 * @param 无
 * @retval 无
*/
int start_flag=0;
void MyWidget::on_pushButton_start_clicked()
{
    qDebug()<<"start";
    QDateTime current_date_time =QDateTime::currentDateTime();//获取当前系统时间
    QString current_date =current_date_time.toString("yyyyMMddhhmmsszzzddd");
    QString QString_fliename = "./data_dir/"+current_date+".txt";
    qDebug()<<QString_fliename;
    QFile_data_save_file.setFileName(QString_fliename);//文件创建与打开
    bool file_open_sucess = QFile_data_save_file.open(QIODevice::WriteOnly);
    if(file_open_sucess == true)
    {
        QDataStream_detec_data.setDevice(&QFile_data_save_file);
    }
    if(QTimer_socket_connect_wait.isActive() == false)//防止连接时间太长
    {
        QTimer_socket_connect_wait.start(1000);
    }
    QTcpSocket_DAQ.abort();
    QTcpSocket_DAQ.connectToHost("192.168.1.10",1000,QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
    if(this->flag_DAQ_error == 1){
        this->flag_DAQ_error = 0;
        QFile_data_save_file.close();
        return;
    }
    detec_count = 0;
    ui->label_axisX1->setText(QString("%1ms").arg(detec_count));
    ui->label_axisX2->setText(QString("%1ms").arg(detec_count+1600));
    ui->pushButton_start->hide();
    ui->pushButton_back->hide();
    ui->pushButton_report->hide();
    ui->pushButton_set->hide();
    ui->pushButton_quit->hide();
    ui->pushButton_stop->setFixedSize(120,50);
    start_flag=1;
    ui->widget_coil->graph(0)->data().data()->clear();
    ui->widget_coil->graph(1)->data().data()->clear();
    ui->widget_hall->graph(0)->data().data()->clear();
    ui->widget_hall->graph(1)->data().data()->clear();
    QChart_coil->replot();
    QChart_hall->replot();//删除之前的数据 避免重复绘制
}
/*
 * @brief 上传按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_upload_clicked()
{
    static int cnt = 0;
    qDebug()<<"upload";
    if(cnt%2 == 0){
        QTcpSocket_cloud.connectToHost("118.178.187.119",8889,QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
        if(this->flag_cloud_error == 1){
            this->flag_cloud_error = 0;
            QTcpSocket_cloud.disconnectFromHost();
            QTcpSocket_cloud.close();
            flag_cloud_uploading = 0;
            flag_cloud_realTime_upLoad = 0;
            cnt++;
            ui->pushButton_upload->setText("上传");
            return;
        }
        cnt++;
        ui->pushButton_upload->setText("停止");
    }
    else if(cnt%2 == 1){
        QTcpSocket_cloud.disconnectFromHost();
        QTcpSocket_cloud.close();
        flag_cloud_uploading = 0;
        flag_cloud_realTime_upLoad = 0;
        cnt++;
        ui->pushButton_upload->setText("上传");
    }

}
/*
 * @brief 停止按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_stop_clicked()
{
    qDebug()<<"stop";
    ui->pushButton_start->setText("检测");

    if(QTimer_socket_connect_wait.isActive() == true)
    {
        QTimer_socket_connect_wait.stop();
    }
    //主动和对方断开连接
    QTcpSocket_DAQ.disconnectFromHost();
    QTcpSocket_DAQ.close();
    int_defect_nubmer = 0;
    detec_count=0;
    ui->label_axisX1->setText(QString("%1ms").arg(detec_count));
    ui->label_axisX2->setText(QString("%1ms").arg(detec_count+1600));
    QFile_data_save_file.close();
    ui->pushButton_start->show();
    ui->pushButton_back->show();
    ui->pushButton_report->show();
    ui->pushButton_set->show();
    ui->pushButton_quit->show();
//    ui->pushButton_dema->show();
    //QChart_coil->clearGraphs();//清除所有graph
    //QChart_hall->clearGraphs();//清除所有graph
//    QChart_coil->clearPlottables();
//    QChart_hall->clearPlottables();

    ui->widget_coil->graph(0)->data().data()->clear();
    ui->widget_coil->graph(1)->data().data()->clear();
    ui->widget_hall->graph(0)->data().data()->clear();
    ui->widget_hall->graph(1)->data().data()->clear();
    QChart_coil->replot();
    QChart_hall->replot();//删除之前的数据 避免重复绘制
    start_flag=0;
}
/*
 * @brief 报告按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_report_clicked()
{
    qDebug()<<"report";
    widget_report_win.show();
}
/*
 * @brief 回放按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_back_clicked()
{
    qDebug()<<"back";
    widget_back_win.show();
}
/*
 * @brief 设置按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_set_clicked()
{
    qDebug()<<"set";
    Widget_set_win.show();
}
/*
 * @brief 退出按钮的槽函数，点击开始执行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_quit_clicked()
{
    qDebug()<<"quit";
    QTimer_alarm_label.stop();
    this->close();
}
/*
 * @brief 参数设置的槽函数，设置页面点击保存按钮会自动执行，即emit信号之后自动执行
 * @param show_up_limit, show_down_limit,alarm_up_limit,alarm_down_limit,float_distance_coefficient, base_name
 * @retval 无
*/
void MyWidget::slots_widget_set_handle(int show_up_limit,int show_down_limit,int alarm_up_limit,int alarm_down_limit,float float_distance_coefficient,QString base_name)
{
        extern int maxYother;
        extern int minYother;
        QChart_hall->clearGraphs();//清除所有graph
        QChart_coil->clearGraphs();//清除所有graph
        QChart_coil->plotLayout()->removeAt(0);
        QChart_hall->plotLayout()->removeAt(0);
        QChart_hall->replot();
        QChart_coil->replot();
        maxY=show_up_limit;
        minY=show_down_limit;
        //this->setWindowFlags(Qt::FramelessWindowHint);//无边框
        maxSize = 4000;
        maxX = graph_x_axis_Count;
        maxYother=maxY;
        minYother=minY;
        QCustomPlot* QChart_hall = ui->widget_hall;
//        QChart_hall->addGraph();
//        QChart_hall->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
//        QChart_hall->addGraph();
//        QChart_hall->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 300);
        plotGradient.setColorAt(0, QColor(208, 255, 232));
        plotGradient.setColorAt(1, QColor(208, 255, 232));
        ui->widget_hall->setBackground(plotGradient);

        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(255, 255, 227));
        axisRectGradient.setColorAt(1, QColor(255, 255, 227));
        ui->widget_hall->axisRect()->setBackground(axisRectGradient);   // 设置QCPAxisRect背景颜色

        QChart_hall->xAxis->setTickLabels(false);//显示刻度值
        QChart_hall->yAxis->setLabel("信号幅值Y2");//轴标签
        ui->widget_hall->yAxis->setLabelColor("black");
        ui->widget_hall->xAxis->setTickLabelColor("black");
        ui->widget_hall->yAxis->setTickLabelColor("black");
        ui->widget_hall->xAxis->setBasePen(QPen("black"));
        ui->widget_hall->yAxis->setBasePen(QPen("black"));
        ui->widget_hall->xAxis->setTickPen(QPen("black"));
        ui->widget_hall->yAxis->setTickPen(QPen("black"));
        ui->widget_hall->xAxis->setSubTickPen(QPen("black"));
        ui->widget_hall->yAxis->setSubTickPen(QPen("black"));
        QChart_hall->legend->setVisible(true);
        QChart_hall->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
        QChart_hall->legend->setBrush(QColor(255, 255, 255, 150));//设置图例背景
        QChart_hall->graph(0)->setName("霍尔1");//设置名称
        QChart_hall->graph(1)->setName("霍尔2");

        QChart_hall->axisRect()->setupFullAxesBox();
        QChart_hall->xAxis->setRange(0, maxX);
        QChart_hall->xAxis->grid()->setVisible(false);
        QChart_hall->yAxis->setRange(minY, maxY);


        QCustomPlot* QChart_coil = ui->widget_coil;
//        QChart_coil->addGraph();
//        QChart_coil->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
//        QChart_coil->addGraph();
//        QChart_coil->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
        QLinearGradient plotGradient2;
        plotGradient2.setStart(0, 0);
        plotGradient2.setFinalStop(0, 300);
        plotGradient2.setColorAt(0, QColor(208, 255, 232));
        plotGradient2.setColorAt(1, QColor(208, 255, 232));
        ui->widget_coil->setBackground(plotGradient2);

        QLinearGradient axisRectGradient2;
        axisRectGradient2.setStart(0, 0);
        axisRectGradient2.setFinalStop(0, 350);
        axisRectGradient2.setColorAt(0, QColor(255, 255, 227));
        axisRectGradient2.setColorAt(1, QColor(255, 255, 227));
        ui->widget_coil->axisRect()->setBackground(axisRectGradient2);   // 设置QCPAxisRect背景颜色

        QChart_coil->xAxis->setTickLabels(false);//显示刻度值
        QChart_coil->yAxis->setLabel("信号幅值Y1");//轴标签
        ui->widget_coil->yAxis->setLabelColor("black");
        ui->widget_coil->xAxis->setTickLabelColor("black");
        ui->widget_coil->yAxis->setTickLabelColor("black");
        ui->widget_coil->xAxis->setBasePen(QPen("black"));
        ui->widget_coil->yAxis->setBasePen(QPen("black"));
        ui->widget_coil->xAxis->setTickPen(QPen("black"));
        ui->widget_coil->yAxis->setTickPen(QPen("black"));
        ui->widget_coil->xAxis->setSubTickPen(QPen("black"));
        ui->widget_coil->yAxis->setSubTickPen(QPen("black"));
        QChart_coil->legend->setVisible(true);
        QChart_coil->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
        QChart_coil->legend->setBrush(QColor(255, 255, 255, 150));//设置图例背景
        QChart_coil->graph(0)->setName("电感1");//设置名称
        QChart_coil->graph(1)->setName("电感2");

        QChart_coil->axisRect()->setupFullAxesBox();
        QChart_coil->xAxis->setRange(0, maxX);
        QChart_coil->xAxis->grid()->setVisible(false);
        QChart_coil->yAxis->setRange(minY, maxY);


        QChart_coil->replot(QCustomPlot::rpQueuedReplot);
        QChart_coil->replot();
        QChart_hall->replot(QCustomPlot::rpQueuedReplot);
        QChart_hall->replot();
        qDebug()<<maxYother;
        connect(QChart_coil->yAxis, SIGNAL(rangeChanged(QCPRange)), QChart_coil->yAxis2, SLOT(setRange(QCPRange)));
        this->int_alarm_up_limit = alarm_up_limit;
        this->int_alarm_down_limit = alarm_down_limit;
        this->float_distance_coefficient = float_distance_coefficient;
        this->base_name = base_name;
        widget_report_win.int_alarm_up_limit = alarm_up_limit;
        widget_report_win.int_alarm_down_limit = alarm_down_limit;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //the other way
//    QChart_hall->xAxis->setRange(0, maxX);
//    QChart_hall->yAxis->setRange(0, 4000);
//    QChart_coil->yAxis->setRange(show_down_limit, show_up_limit);
//    this->int_alarm_up_limit = alarm_up_limit;
//    this->int_alarm_down_limit = alarm_down_limit;
//    this->float_distance_coefficient = float_distance_coefficient;
//    this->base_name = base_name;
//    widget_report_win.int_alarm_up_limit = alarm_up_limit;
//    widget_report_win.int_alarm_down_limit = alarm_down_limit;
//    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    qDebug()<<"handle setting data";
}
/*
 * @brief 采集卡网络对象的槽函数，套接字连接成功后自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_DAQ_connected_slots()//成功连接槽函数
{
    static bool flag_connect = false;
    qDebug()<<"sucess connecting";
    if(QTimer_socket_connect_wait.isActive() == true)
    {
        QTimer_socket_connect_wait.stop();
    }
    if(flag_connect == false)//只连接一次槽函数，否则报错
    {
        connect(&QTcpSocket_DAQ, &QTcpSocket::readyRead,this,&MyWidget::QTcpSocket_DAQ_readyRead_slots);
        flag_connect = true;
    }
    char char_buff = 'C';
    QTcpSocket_DAQ.write(&char_buff,1);
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    char_buff = 'L';
    QTcpSocket_DAQ.write(&char_buff,1);
}
/*
 * @brief 采集卡网络对象的槽函数，套接字连接失败后自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_DAQ_connected_error_slots()
{
    qDebug()<<"connecting error";
    QMessageBox::about(this,"温馨提示","采集卡连接失败，请检查采集卡后重试^o^");
    this->flag_DAQ_error = 1;
}
/*
 * @brief 上传到云端网络对象的槽函数，套接字连接成功后自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_cloud_connected_slots()//成功连接槽函数
{
    static bool flag_connect = false;
    qDebug()<<"sucess connecting";
    if(flag_connect == false)//只连接一次槽函数，否则报错
    {
        connect(&QTcpSocket_cloud, &QTcpSocket::readyRead,this,&MyWidget::QTcpSocket_cloud_readyRead_slots);
        flag_connect = true;
    }
    QString str ="send," + base_name;
    QByteArray sendMessage = str.toUtf8();
    //QThread::sleep(1);
    QTcpSocket_cloud.write(sendMessage);
}
/*
 * @brief 上传到云端网络对象的槽函数，套接字连接失败后自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_cloud_connected_error_slots()
{
    qDebug()<<"connecting error";
    QMessageBox::about(this,"温馨提示","服务器连接失败，请检查网络后重试^o^");
    this->flag_cloud_error = 1;
}
/*
 * @brief 上传到云端网络对象的槽函数，套接字有新数据时自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_cloud_readyRead_slots()//槽函数，自动调用，读取tcp数据
{
    QByteArray array = QTcpSocket_cloud.readAll();
    QString str = array;
    //qDebug()<<str;
    if(str == "GetDamageData"){
        flag_cloud_uploading = 1;
        flag_cloud_realTime_upLoad = 0;
    }else if(str == "GetRealTimeData"){
        flag_cloud_uploading = 0;
        flag_cloud_realTime_upLoad = 1;
    }

    else{
        QMessageBox::about(this,"温馨提示","地点命名重复，停止并修改后重试!");
    }
}

void MyWidget::QTimer_socket_connect_wait_slots()
{
    this->flag_DAQ_error = 1;
    QMessageBox::about(this,"温馨提示","连接超时，采集卡可能出现问题，请检查采集卡后重试^o^");
    if(QTimer_socket_connect_wait.isActive() == true)
    {
        QTimer_socket_connect_wait.stop();
    }
}
/*
 * @brief 采集卡网络对象的槽函数，套接字有新数据时自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::QTcpSocket_DAQ_readyRead_slots()//槽函数，自动调用，读取tcp数据
{
    static int flag_number = 0;
    switch (flag_number)
    {
    case 0:
        DAQ_socket_cmd = 'L';
        flag_number++;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        DAQ_socket_cmd = 'A';
        flag_number++;
        break;
    case 10:
        DAQ_socket_cmd = 'H';
        flag_number++;
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        DAQ_socket_cmd = 'A';
        flag_number++;
        break;
    case 19:
        DAQ_socket_cmd = 'A';
        flag_number = 0;
        break;
    }
    QByteArray array = QTcpSocket_DAQ.readAll();
    //QThread::msleep(12);
    QTcpSocket_DAQ.write(&DAQ_socket_cmd,1);
    tcp_data_trans_together_func(array);
    if(flag_cloud_realTime_upLoad == 1){
        QTcpSocket_cloud.write(array);//将数据上传到服务器
        qDebug()<<array.size();
    }
}
/*
 * @brief 采集卡数据解包函数
 * @param QByteArray data_in_array
 * @retval 无
*/
int data_return_1[160];
int data_return_2[160];
int data_return_3[160];
int data_return_4[160];
int tcp_data_flag=0;
void MyWidget::tcp_data_trans_together_func(QByteArray data_in_array)//高八位低八位数据整合
{
    int data_return[160];
    int data_return_python[320];
    int data_buff[640];
    int data_filter[320];
    int data_return_filter[640];
    int data_return_nofilter[640];
    int data_return_hall[320];
    int i = 0;
    for (i=0;i<640;i++)
    {
        data_buff[i] = data_in_array[2*i] + data_in_array[2*i+1]*256;
        //QDataStream_detec_data<<(qint32)data_buff[i];
    }
    //QDataStream_detec_data<<distance_buff;
    for (i=0;i<40;i++)
    {
        data_return[4*i] = data_buff[i*16+1]+data_buff[i*16+2]+data_buff[i*16+3]+data_buff[i*16+4]+data_buff[i*16+5]+data_buff[i*16+6];
        data_return[4*i+1] = data_buff[i*16+0]+data_buff[i*16+7]+data_buff[i*16+8]+data_buff[i*16+13]+data_buff[i*16+14]+data_buff[i*16+15];
        data_return[4*i+2] = data_buff[i*16+10];
        data_return[4*i+3] = data_buff[i*16+11];
        QDataStream_detec_data<<(qint32)data_return[4*i];
        QDataStream_detec_data<<(qint32)data_return[4*i+1];
        QDataStream_detec_data<<(qint32)data_return[4*i+2];
        QDataStream_detec_data<<(qint32)data_return[4*i+3];
        QDataStream_detec_data<<distance_buff;
        //qDebug()<<"orinaglldata:";
        //qDebug()<<data_return[4*i];
    }
    int_distance_calc = (uint8_t)data_in_array[18] + (uint8_t)data_in_array[19]*256+(uint8_t)data_in_array[24]*65536 ;//将位移信息写入变量



    tcp_data_flag++;
    if(tcp_data_flag=1)
    {
        for(i=0;i<160;i++)
        data_return_1[i]=data_return[i];
    }
    if(tcp_data_flag=2)
    {
        for(i=0;i<160;i++)
        data_return_2[i]=data_return[i];
    }
    if(tcp_data_flag=3)
    {
        for(i=0;i<160;i++)
        data_return_3[i]=data_return[i];
    }
    if(tcp_data_flag=4)
    {
        tcp_data_flag=0;
        for(i=0;i<160;i++)
        data_return_4[i]=data_return[i];

        for(i=0;i<40;i++)
        {
        data_filter[i]=data_return_1[4*i];
        data_return_hall[i]=data_return_1[4*i+2];
        }
        for(i=40;i<80;i++)
        {
        data_filter[i]=data_return_2[4*(i-40)];
        data_return_hall[i]=data_return_2[4*(i-40)+2];
        }
        for(i=80;i<120;i++)
        {
        data_filter[i]=data_return_3[4*(i-80)];
        data_return_hall[i]=data_return_3[4*(i-80)+2];
        }
        for(i=120;i<160;i++)
        {
        data_filter[i]=data_return_4[4*(i-120)];
        data_return_hall[i]=data_return_4[4*(i-120)+2];
        }
        for(i=160;i<200;i++)
        {
        data_filter[i]=data_return_1[4*(i-160)+1];
        data_return_hall[i]=data_return_1[4*(i-160)+3];
        }
        for(i=200;i<240;i++)
        {
        data_filter[i]=data_return_2[4*(i-200)+1];
        data_return_hall[i]=data_return_2[4*(i-200)+3];
        }
        for(i=240;i<280;i++)
        {
        data_filter[i]=data_return_3[4*(i-240)+1];
        data_return_hall[i]=data_return_3[4*(i-240)+3];
        }
        for(i=280;i<320;i++)
        {
        data_filter[i]=data_return_4[4*(i-280)+1];
        data_return_hall[i]=data_return_4[4*(i-280)+3];
        }

    for(i=0;i<160;i++)
    {
        data_return_filter[4*i]=data_return_python[i];
        data_return_filter[4*i+1]=data_return_python[i+160];
        data_return_filter[4*i+2]=data_return_hall[i];
        data_return_filter[4*i+3]=data_return_hall[i+160];
    }
    for(i=0;i<160;i++)
    {
        data_return_nofilter[4*i]=data_filter[i];
        data_return_nofilter[4*i+1]=data_filter[i+160];
        data_return_nofilter[4*i+2]=data_return_hall[i];
        data_return_nofilter[4*i+3]=data_return_hall[i+160];
    }
}



    for(int i = 0; i < 160; i++)
    {
    //printf("%d\n",data_return_python[i]);
        //data_return[i]=data_return[i]+1000;
    }
    if(start_flag==1)

    thread_getdata_graph_plot(data_return);
    else
    {
    }

//4次结束
//    Py_DECREF(PyList);
//    Py_DECREF(ArgList);
//    Py_DECREF(pReturn); //释放空间
//    Py_DECREF(pModule); //释放空间
//    Py_DECREF(pFunc); //释放空间
//    Py_DECREF(pDict); //释放空间

//    Py_Finalize();
}
/*
 * @brief 多线程更新数据，实际上没有采用多线程方案
 * @param int data_in[]
 * @retval 无
*/
void MyWidget::thread_getdata_graph_plot(int data_in[])//长度640 already to 160le
{
    static int i = 0;
    int a;
    int b;
    int data_in_python1[40];
    int data_in_python2[40];
    int data_inintopython_coil1[40];
    int data_inintopython_coil2[40];
    for(i=0;i<40;i++)
    {
        data_inintopython_coil1[i]=data_in[4*i];
        data_inintopython_coil2[i]=data_in[4*+1];
    }
    int flag_defect_detec = 1;//损伤判断标志位
    QCustomPlot* QChart_hall = ui->widget_hall;
    QCustomPlot* QChart_coil = ui->widget_coil;
    int detec_count_show;



    int data_before[160];
    for (i=0;i<40;i++)
    {
        data_before[4*i] = data_in[4*i];
        data_before[4*i+1] = data_in[4*i+1];
        data_before[4*i+2] = data_in[4*i+2];
        data_before[4*i+3] = data_in[4*i+3];
    }
    /*
    for(i=0;i<40;i++)
    {
        int_filter_data_buff[i] = int_filter_data_buff[i+40];
        int_filter_data_buff[i+40] = data_in[4*i];
    }
    */
    //data_filter_func(int_filter_data_buff);
    //调用脚本处理信号
    //data_filter_func(data_before);
    for(i=0;i<40;i++)
    {
    //qDebug()<<data_in[4*i];
    }
    //qDebug()<<"上面是原始数据，下面是处理结果";
    for(i=0;i<40;i++)
    {
    //qDebug()<<data_before[4*i];
    }

    QChart_hall->replot(QCustomPlot::rpQueuedReplot);
    QChart_coil->replot(QCustomPlot::rpQueuedReplot);
    a=0;b=0;
    for(i=0;i<40;i++)
    {
        a=a+data_in_python1[i];
        b=b+data_in_python2[i];
    }
    a=a/160;
    b=b/160;

    for(i=0;i<40;i++)
    {
        //qDebug()<<int_after_filter_data[40+i];
        //QVector_QPointF_coil_graph_data1[x_axis].setY(int_after_filter_data[40+i]);
        detec_count+=2;
        detec_count_show=detec_count/10;
        ui->label_axisX1->setText(QString("%1ms").arg(detec_count_show));
        ui->label_axisX2->setText(QString("%1ms").arg(detec_count_show+1600));
        double key = detec_count/1000.0; // 开始到现在的时间，单位秒

        // 添加数据到graph
        QChart_coil->graph(0)->addData(key, data_in[4*i]);
        QChart_coil->graph(1)->addData(key, data_in[4*i+1]);
        QChart_hall->graph(0)->addData(key, data_in[4*i+2]);
        QChart_hall->graph(1)->addData(key, data_in[4*i+3]);
        //qDebug()<<data_in_python[4*i+0]-a;
        //qDebug()<<data_in[4*i+3];
        //记录当前时刻
        //曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
        QChart_hall->xAxis->setRange(key, 30, Qt::AlignRight);
        QChart_coil->xAxis->setRange(key, 30, Qt::AlignRight);
        ui->widget_coil->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->widget_hall->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        //绘图
        //QChart_hall->replot();
        //QChart_coil->replot();



        //计算帧数
        static double lastFpsKey;
        static int frameCount;
        frameCount+=4;
        if (key-lastFpsKey > 2) // 每2秒求一次平均值
        {
            //状态栏显示帧数和数据总数
            ui->label_fps->setText(QString("%1 FPS").arg(frameCount/(key-lastFpsKey), 0, 'f', 0));
            lastFpsKey = key;
            frameCount = 0;

        }




        if(flag_defect_detec ==1)//损伤判断
        {
            if(data_in[4*i+0]>int_alarm_up_limit)
            {
                flag_defect_detec = 0;
                int_defect_nubmer++;
            }
            else if(data_in[4*i+0]<int_alarm_down_limit)
            {
                flag_defect_detec = 0;
                int_defect_nubmer++;
            }
            else if(data_in[4*i+1]>int_alarm_up_limit)
            {
                flag_defect_detec = 0;
                int_defect_nubmer++;
            }
            else if(data_in[4*i+1]<int_alarm_down_limit)
            {
                flag_defect_detec = 0;
                int_defect_nubmer++;
            }
        }
    }
}

/*
 * @brief 算法滤波函数，改到其他地方去了 全霍尔删去了
 * @param int input[80]
 * @retval 无
*/
double MyWidget::data_filter_func(double data_in[])
{
//    static const double dv[21] = { -1.8519480747177166E-18, -0.0064364156273118674,
//        -0.020344062613925358, -0.042715906243204434, -0.0642941075802573,
//        -0.0680503663752848, -0.03903518661005019, 0.024175976525245443,
//        0.10439338618338236, 0.17169615839553634, 0.19795049173952656,
//        0.17169615839553634, 0.10439338618338236, 0.024175976525245443,
//        -0.03903518661005019, -0.0680503663752848, -0.0642941075802573,
//        -0.042715906243204434, -0.020344062613925358, -0.0064364156273118674,
//        -1.8519480747177166E-18 };
//      memset(&int_after_filter_data[0], 0, 80U * sizeof(int));
//      for (int k = 0; k < 21; k++) {
//        int b_k;
//        b_k = k + 1;
//        for (int j = b_k; j < 81; j++) {
//          int_after_filter_data[j - 1] += dv[k] * input[(j - k) - 1];
//        }
//      }
    /*Pass by List: Transform an C Array to Python List*/
//    class PyThreadStateLock PyThreadLock;//获取全局锁
//    QTextStream cout(stdout,  QIODevice::WriteOnly);

//    PyObject * pModule = NULL;
//    PyObject * pFunc = NULL;
//    PyObject *pDict = NULL;
//    PyObject *pReturn = NULL;

//    pModule = PyImport_ImportModule("hello");
//    pDict = PyModule_GetDict(pModule);
//    pFunc = PyDict_GetItemString(pDict, "filter2");
//    printf("\n");
//    cout<<"C Array Pass Into The Python List:"<<endl;

//    PyObject *PyList  = PyList_New(160);//定义一个与数组等长的PyList对象数组
//    PyObject *ArgList = PyTuple_New(1);//定义一个Tuple对象，Tuple对象的长度与Python函数参数个数一直，上面Python参数个数为1，所以这里给的长度为1
//    for(int i = 0; i < PyList_Size(PyList); i++)
//    {
//        PyList_SetItem(PyList,i, PyFloat_FromDouble(data_in[i]));//给PyList对象的每个元素赋值
//    }
//    PyTuple_SetItem(ArgList, 0, PyList);//将PyList对象放入PyTuple对象中
//    pReturn=PyObject_CallObject(pFunc, ArgList);//调用函数，完成传递

//    if(PyList_Check(pReturn)){ //检查是否为List对象
//        printf("\n result: \n");
//        int SizeOfList = PyList_Size(pReturn);//List对象的大小，这里SizeOfList =
//        printf("%d\n",SizeOfList);
//        printf("%d\n",pReturn);
//        for(int i = 0; i < SizeOfList; i++){
//            PyObject *Item = PyList_GetItem(pReturn, i);//获取List对象中的每一个元素
//            int result;
//            PyArg_Parse(Item, "i", &result);//i表示转换成int型变量
//            printf("%d ",result);
//            //cout << PyInt_AsLong(Item) <<" "; //输出元素
//            Py_DECREF(Item); //释放空间
//         }
//        printf("\n");
//    }
//    else{
//        cout<<"Not a List"<<endl;
//    }

    //Py_Finalize();

}



/*
 * @brief 定时器槽函数，定时更新距离数据，自动执行
 * @param 无
 * @retval 无
*/
void MyWidget::QTimer_alarm_label_slots()
{
    if(int_defect_nubmer>0)
    {
        ui->label_defect->setText("有损伤");
        /*
         * 如果工作模式为上传模式，则需要上传损伤数据到服务器
        */
        if(flag_cloud_uploading == 1){
            QString str ="sendDamage," + base_name+"."+QString::number(int_defect_nubmer);
            QByteArray sendMessage = str.toUtf8();
            QTcpSocket_cloud.write(sendMessage);
        }
        int_defect_nubmer = 0;
    }
    else
    {
        ui->label_defect->setText("正常");
    }
    distance_buff = distance_dir*float_distance_coefficient*(int_distance_calc - 8388608)/1000;
    ui->label_distance->setText(QString("%1m").arg(distance_buff));
}

/*
 * @brief 方向控件，切换距离正负值以用来符合实际
 * @param bool checked
 * @retval 无
*/
void MyWidget::on_radioButton_distance_dir_toggled(bool checked)
{
    static double distance_buff = 0;
    if(checked)
    {
        distance_dir = 1;
        distance_buff = distance_dir*float_distance_coefficient*(int_distance_calc - 8388608)/1000;
        ui->label_distance->setText(QString("%1m").arg(distance_buff));
    }
    else
    {
        distance_dir = -1;
        distance_buff = distance_dir*float_distance_coefficient*(int_distance_calc - 8388608)/1000;
        ui->label_distance->setText(QString("%1m").arg(distance_buff));
    }
    qDebug()<<distance_dir;
}
/*
 * @brief 标定按钮的槽函数，点击按钮自动运行
 * @param 无
 * @retval 无
*/
void MyWidget::on_pushButton_dema_clicked()
{
//    bool ok;
//    double d = QInputDialog::getDouble(this, tr("距离系数标定"),tr("实际距离(m):"), 1.00, -10000, 10000, 2, &ok,Qt::MSWindowsFixedSizeDialogHint);
//    if (ok){
//        qDebug()<<(float)d;
//        if(distance_buff<0.001&&distance_buff>-0.001)distance_buff = 1;
//        qDebug()<<distance_buff;
//        this->float_distance_coefficient = (float)(d/distance_buff)*float_distance_coefficient;
//        Widget_set_win.float_distance_coefficient = this->float_distance_coefficient;
//        qDebug()<<this->float_distance_coefficient;
//    }//原标定

//    qDebug()<<"filter";
//    QDateTime current_date_time =QDateTime::currentDateTime();//获取当前系统时间
//    QString current_date =current_date_time.toString("yyyyMMddhhmmsszzzddd");
//    QString QString_fliename = "./data_dir/"+current_date+".txt";
//    qDebug()<<QString_fliename;
//    QFile_data_save_file.setFileName(QString_fliename);//文件创建与打开
//    bool file_open_sucess = QFile_data_save_file.open(QIODevice::WriteOnly);
//    if(file_open_sucess == true)
//    {
//        QDataStream_detec_data.setDevice(&QFile_data_save_file);
//    }
//    if(QTimer_socket_connect_wait.isActive() == false)//防止连接时间太长
//    {
//        QTimer_socket_connect_wait.start(1000);
//    }
//    QTcpSocket_DAQ.abort();
//    QTcpSocket_DAQ.connectToHost("192.168.1.15",1000,QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
//    if(this->flag_DAQ_error == 1){
//        this->flag_DAQ_error = 0;
//        QFile_data_save_file.close();
//        return;
//    }
//    detec_count = 0;
//    ui->label_axisX1->setText(QString("%1ms").arg(detec_count));
//    ui->label_axisX2->setText(QString("%1ms").arg(detec_count+1600));
//    ui->pushButton_start->hide();
//    ui->pushButton_back->hide();
//    ui->pushButton_report->hide();
//    //ui->pushButton_set->hide();
//    ui->pushButton_quit->hide();
//    ui->pushButton_dema->hide();
//    start_flag=1;

}


