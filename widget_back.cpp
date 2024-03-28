#include "widget_back.h"
#include "ui_widget_back.h"
/*
 * ***************************************************************************************
 * **************************************
 * @attention
 *
 * 运行平台：正点原子家的i.mx6ull开发板、树莓派4B、windows10、11系统的电脑,实测可行
 * *************************************************************************************
**/
widget_back::widget_back(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_back)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框

    //动态式
        extern int maxYother;
        extern int minYother;
        maxSize = 4000;
        maxX = graph_x_axis_Count;
        maxY = 7000;
        minY = minYother;
        qDebug()<<maxYother;

        QCustomPlot* QChart_hall = ui->widget_hall;
        QChart_hall->addGraph();
        QChart_hall->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
        QChart_hall->addGraph();
        QChart_hall->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 300);
        plotGradient.setColorAt(0, QColor(30, 30, 30));
        plotGradient.setColorAt(1, QColor(10, 10, 10));
        ui->widget_hall->setBackground(plotGradient);

        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(15, 15, 15));
        axisRectGradient.setColorAt(1, QColor(50, 50, 50));
        ui->widget_hall->axisRect()->setBackground(axisRectGradient);   // 设置QCPAxisRect背景颜色

        QChart_hall->xAxis->setTickLabels(false);//显示刻度值
        QChart_hall->xAxis->setLabel("this is x Axis Label");//轴标签
        ui->widget_hall->yAxis->setLabelColor("white");
        ui->widget_hall->xAxis->setTickLabelColor("white");
        ui->widget_hall->yAxis->setTickLabelColor("white");
        ui->widget_hall->xAxis->setBasePen(QPen("white"));
        ui->widget_hall->yAxis->setBasePen(QPen("white"));
        ui->widget_hall->xAxis->setTickPen(QPen("white"));
        ui->widget_hall->yAxis->setTickPen(QPen("white"));
        ui->widget_hall->xAxis->setSubTickPen(QPen("white"));
        ui->widget_hall->yAxis->setSubTickPen(QPen("white"));
        QChart_hall->axisRect()->setupFullAxesBox();
        QChart_hall->xAxis->setRange(0, maxX);
        QChart_hall->xAxis->grid()->setVisible(false);
        QChart_hall->yAxis->setRange(-3000, maxY);


        QCustomPlot* QChart_coil = ui->widget_coil;
        QChart_coil->addGraph();
        QChart_coil->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
        QChart_coil->addGraph();
        QChart_coil->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
        QLinearGradient plotGradient2;
        plotGradient2.setStart(0, 0);
        plotGradient2.setFinalStop(0, 300);
        plotGradient2.setColorAt(0, QColor(30, 30, 30));
        plotGradient2.setColorAt(1, QColor(10, 10, 10));
        ui->widget_coil->setBackground(plotGradient2);

        QLinearGradient axisRectGradient2;
        axisRectGradient2.setStart(0, 0);
        axisRectGradient2.setFinalStop(0, 350);
        axisRectGradient2.setColorAt(0, QColor(15, 15, 15));
        axisRectGradient2.setColorAt(1, QColor(50, 50, 50));
        ui->widget_hall->axisRect()->setBackground(axisRectGradient2);   // 设置QCPAxisRect背景颜色

        QChart_coil->xAxis->setTickLabels(false);//显示刻度值
        QChart_coil->xAxis->setLabel("this is x Axis Label");//轴标签
        ui->widget_coil->yAxis->setLabelColor("white");
        ui->widget_coil->xAxis->setTickLabelColor("white");
        ui->widget_coil->yAxis->setTickLabelColor("white");
        ui->widget_coil->xAxis->setBasePen(QPen("white"));
        ui->widget_coil->yAxis->setBasePen(QPen("white"));
        ui->widget_coil->xAxis->setTickPen(QPen("white"));
        ui->widget_coil->yAxis->setTickPen(QPen("white"));
        ui->widget_coil->xAxis->setSubTickPen(QPen("white"));
        ui->widget_coil->yAxis->setSubTickPen(QPen("white"));
        QChart_coil->axisRect()->setupFullAxesBox();
        QChart_coil->xAxis->setRange(0, maxX);
        QChart_coil->xAxis->grid()->setVisible(false);
        QChart_coil->yAxis->setRange(-3000, maxY);
        if (QVector_QPointF_coil_graph_data1.isEmpty())//开辟空间
        {
            QVector_QPointF_hall_graph_data1.reserve(graph_x_axis_Count);
            QVector_QPointF_hall_graph_data2.reserve(graph_x_axis_Count);
            QVector_QPointF_coil_graph_data1.reserve(graph_x_axis_Count);
            QVector_QPointF_coil_graph_data2.reserve(graph_x_axis_Count);
            for (int i = 0; i < graph_x_axis_Count; ++i)
            {

                QVector_QPointF_hall_graph_data1.append(QPointF(i, 0));
                QVector_QPointF_hall_graph_data2.append(QPointF(i, 0));
                QVector_QPointF_coil_graph_data1.append(QPointF(i, 0));
                QVector_QPointF_coil_graph_data2.append(QPointF(i, 0));
            }
        }

    //the page way
//    maxSize = 4000;
//    maxX = graph_x_axis_Count;
//    maxY = 7000;
//    QChart_hall->addSeries(QSplineSeries_hall);
//    QChart_hall->addSeries(QSplineSeries_hall2);
//    QChart_hall->legend()->hide();
//    QChart_hall->createDefaultAxes();
//    QChart_hall->axisX()->setRange(0, maxX);
//    QChart_hall->axisX()->hide();
//    QChart_hall->axisY()->setRange(0, 7000);
//    QChart_hall->setTheme(QtCharts::QChart::ChartThemeDark);

//    ui->widget_hall->setChart(QChart_hall);
//    ui->widget_hall->setRenderHint(QPainter::Antialiasing,true);
//    QChart_coil->addSeries(QSplineSeries_coil);
//    QChart_coil->addSeries(QSplineSeries_coil2);
//    QChart_coil->legend()->hide();
//    QChart_coil->createDefaultAxes();
//    QChart_coil->axisX()->setRange(0, maxX);
//    QChart_coil->axisX()->hide();
//    QChart_coil->axisY()->setRange(-2000, maxY);
//    QChart_coil->setTheme(QtCharts::QChart::ChartThemeDark);

//    ui->widget_coil->setChart(QChart_coil);
//    ui->widget_coil->setRenderHint(QPainter::Antialiasing,true);
//    if (QVector_QPointF_coil_graph_data1.isEmpty())//开辟空间
//    {
//        QVector_QPointF_hall_graph_data1.reserve(graph_x_axis_Count);
//        QVector_QPointF_hall_graph_data2.reserve(graph_x_axis_Count);
//        QVector_QPointF_coil_graph_data1.reserve(graph_x_axis_Count);
//        QVector_QPointF_coil_graph_data2.reserve(graph_x_axis_Count);
//        for (int i = 0; i < graph_x_axis_Count; ++i)
//        {

//            QVector_QPointF_hall_graph_data1.append(QPointF(i, 0));
//            QVector_QPointF_hall_graph_data2.append(QPointF(i, 0));
//            QVector_QPointF_coil_graph_data1.append(QPointF(i, 0));
//            QVector_QPointF_coil_graph_data2.append(QPointF(i, 0));
//        }
//        /*
//        QSplineSeries_coil->replace(QVector_QPointF_coil_graph_data1);
//        QSplineSeries_coil2->replace(QVector_QPointF_coil_graph_data2);
//        QSplineSeries_hall->replace(QVector_QPointF_hall_graph_data1);
//        QSplineSeries_hall2->replace(QVector_QPointF_hall_graph_data2);
//        */
//    }

}

widget_back::~widget_back()
{
    delete QSplineSeries_hall;
    delete QSplineSeries_hall2;
    delete QSplineSeries_coil;
    delete QSplineSeries_coil2;
    delete QChart_coil;
    delete QChart_hall;
    delete ui;
}

void widget_back::on_pushButton_quit_clicked()
{
    this->hide();
}

void widget_back::on_pushButton_alldata_clicked()
{
    alldata_flag=1;
}

void widget_back::on_pushButton_choose_clicked()
{
       alldata_flag=0;
       i=0;
       ui->widget_coil->graph(0)->data().data()->clear();
       ui->widget_coil->graph(1)->data().data()->clear();
       ui->widget_hall->graph(0)->data().data()->clear();
       ui->widget_hall->graph(1)->data().data()->clear();
       QChart_coil->replot();
       QChart_hall->replot();
       int detec_count_show=0;
       int detec_count=0;
       speed=15;
       extern int maxYother;
       extern int minYother;
       maxY = maxYother;
       minY = minYother;
       qDebug()<<maxYother;
       QChart_hall->clearGraphs();//清除所有graph
       QChart_coil->clearGraphs();//清除所有graph
       QChart_coil->plotLayout()->removeAt(0);
       QChart_hall->plotLayout()->removeAt(0);
       QChart_hall->replot();
       QChart_coil->replot();
       //this->setWindowFlags(Qt::FramelessWindowHint);//无边框
       maxSize = 4000;
       maxX = graph_x_axis_Count;
       QCustomPlot* QChart_hall = ui->widget_hall;
       QChart_hall->addGraph();
       QChart_hall->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
       QChart_hall->addGraph();
       QChart_hall->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
       QLinearGradient plotGradient;
       plotGradient.setStart(0, 0);
       plotGradient.setFinalStop(0, 300);
       plotGradient.setColorAt(0, QColor(30, 30, 30));
       plotGradient.setColorAt(1, QColor(10, 10, 10));
       ui->widget_hall->setBackground(plotGradient);

       QLinearGradient axisRectGradient;
       axisRectGradient.setStart(0, 0);
       axisRectGradient.setFinalStop(0, 350);
       axisRectGradient.setColorAt(0, QColor(15, 15, 15));
       axisRectGradient.setColorAt(1, QColor(50, 50, 50));
       ui->widget_hall->axisRect()->setBackground(axisRectGradient);   // 设置QCPAxisRect背景颜色

       QChart_hall->xAxis->setTickLabels(false);//显示刻度值
       QChart_hall->xAxis->setLabel("this is x Axis Label");//轴标签
       ui->widget_hall->yAxis->setLabelColor("white");
       ui->widget_hall->xAxis->setTickLabelColor("white");
       ui->widget_hall->yAxis->setTickLabelColor("white");
       ui->widget_hall->xAxis->setBasePen(QPen("white"));
       ui->widget_hall->yAxis->setBasePen(QPen("white"));
       ui->widget_hall->xAxis->setTickPen(QPen("white"));
       ui->widget_hall->yAxis->setTickPen(QPen("white"));
       ui->widget_hall->xAxis->setSubTickPen(QPen("white"));
       ui->widget_hall->yAxis->setSubTickPen(QPen("white"));
       QChart_hall->axisRect()->setupFullAxesBox();
       QChart_hall->xAxis->setRange(0, maxX);
       QChart_hall->xAxis->grid()->setVisible(false);
       QChart_hall->yAxis->setRange(minY, maxY);

       QCustomPlot* QChart_coil = ui->widget_coil;
       QChart_coil->addGraph();
       QChart_coil->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
       QChart_coil->addGraph();
       QChart_coil->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
       QLinearGradient plotGradient2;
       plotGradient2.setStart(0, 0);
       plotGradient2.setFinalStop(0, 300);
       plotGradient2.setColorAt(0, QColor(30, 30, 30));
       plotGradient2.setColorAt(1, QColor(10, 10, 10));
       ui->widget_coil->setBackground(plotGradient2);

       QLinearGradient axisRectGradient2;
       axisRectGradient2.setStart(0, 0);
       axisRectGradient2.setFinalStop(0, 350);
       axisRectGradient2.setColorAt(0, QColor(15, 15, 15));
       axisRectGradient2.setColorAt(1, QColor(50, 50, 50));
       ui->widget_hall->axisRect()->setBackground(axisRectGradient2);   // 设置QCPAxisRect背景颜色

       QChart_coil->xAxis->setTickLabels(false);//显示刻度值
       QChart_coil->xAxis->setLabel("this is x Axis Label");//轴标签
       ui->widget_coil->yAxis->setLabelColor("white");
       ui->widget_coil->xAxis->setTickLabelColor("white");
       ui->widget_coil->yAxis->setTickLabelColor("white");
       ui->widget_coil->xAxis->setBasePen(QPen("white"));
       ui->widget_coil->yAxis->setBasePen(QPen("white"));
       ui->widget_coil->xAxis->setTickPen(QPen("white"));
       ui->widget_coil->yAxis->setTickPen(QPen("white"));
       ui->widget_coil->xAxis->setSubTickPen(QPen("white"));
       ui->widget_coil->yAxis->setSubTickPen(QPen("white"));
       QChart_coil->axisRect()->setupFullAxesBox();
       QChart_coil->xAxis->setRange(0, maxX);
       QChart_coil->xAxis->grid()->setVisible(false);
       QChart_coil->yAxis->setRange(minY, maxY);
       QChart_coil->replot(QCustomPlot::rpQueuedReplot);
       QChart_coil->replot();
       QChart_hall->replot(QCustomPlot::rpQueuedReplot);
       QChart_hall->replot();
       ui->label_axis_X1->setText(QString("%1ms").arg(0));
       ui->label_axis_X2->setText(QString("%1ms").arg(0+1600));
       ui->pushButton_choose->show();
       ui->pushButton_nextpage->show();
       ui->pushButton_lastpage->show();
       ui->pushButton_quit->show();
       QVector_int_read_data1.clear();
       QVector_int_read_data2.clear();
       QVector_int_read_data3.clear();
       QVector_int_read_data4.clear();
       QVector_int_read_data5.clear();
       QVector_int_read_data6.clear();
       QVector_int_read_data7.clear();
       QVector_int_read_data8.clear();
       QVector_int_read_data9.clear();
       QVector_int_read_data10.clear();
       QVector_int_read_data11.clear();
       QVector_int_read_data12.clear();
       QVector_int_read_data13.clear();
       QVector_int_read_data14.clear();
       QVector_int_read_data15.clear();
       QVector_int_read_data16.clear();
       QVector_double_read_data17.clear();
       path = QFileDialog::getOpenFileName(this,"open","./data_dir");
       qDebug()<<path;

       if(path.isEmpty() == false)
           {
               QFile_file.setFileName(path);
               bool file_open_sucess = QFile_file.open(QIODevice::ReadOnly);
               if(file_open_sucess == true)
               {
                   //创建数据流，和file文件关联
                   //往数据流中读数据，相当于往文件里读数据
                   stream.setDevice(&QFile_file);
                   //读的时候，按写的顺序取数据
                   qint32 data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15,data16;
                   double data17;
                   QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                   while(stream.atEnd() == false)
                   {
                   i++;
                   stream>>data1;
                   stream>>data2;
                   stream>>data3;
                   stream>>data4;
                   stream>>data5;
                   stream>>data6;
//                   stream>>data17;
//                   stream>>data8;
//                   stream>>data9;
//                   stream>>data10;
//                   stream>>data11;
//                   stream>>data12;
//                   stream>>data13;
//                   stream>>data14;
//                   stream>>data15;
//                   stream>>data16;
//                   stream>>data17;
//                   qDebug()<<data1;
//                   qDebug()<<data2;
//                   qDebug()<<data3;
//                   qDebug()<<data4;
//                   qDebug()<<data5;
//                   qDebug()<<data6;
//                   qDebug()<<data7;
//                   qDebug()<<data8;
//                   qDebug()<<data9;
//                   qDebug()<<data10;
//                   qDebug()<<data11;
//                   qDebug()<<data12;
//                   qDebug()<<data13;
//                   qDebug()<<data14;
//                   qDebug()<<data15;
//                   qDebug()<<data16;
//                   qDebug()<<data17;
                   QVector_int_read_data1.append(data1);
                   QVector_int_read_data2.append(data2);
                   QVector_int_read_data3.append(data3);
                   QVector_int_read_data4.append(data4);
                   QVector_double_read_data17.append(data5);
                   int data_coil1;
                   int data_coil2;
                   int data_hall1;
                   int data_hall2;
                   data_coil1=data1;
                   data_coil2=data2;
                   data_hall1=data3;
                   data_hall2=data4;
                   detec_count+=2;
                   detec_count_show=detec_count/10;
                   ui->label_axis_X1->setText(QString("%1ms").arg(detec_count_show));
                   ui->label_axis_X2->setText(QString("%1ms").arg(detec_count_show+1600));
                   double key = detec_count/1000.0; // 开始到现在的时间，单位秒

                   // 添加数据到graph
                   QChart_coil->graph(0)->addData(key, data_coil1);
                   QChart_coil->graph(1)->addData(key, data_coil2);
                   QChart_hall->graph(0)->addData(key, data_hall1);
                   QChart_hall->graph(1)->addData(key, data_hall2);
                   //qDebug()<<data_coil1;
                   //记录当前时刻
                   //曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
                   QChart_hall->xAxis->setRange(key, 30, Qt::AlignRight);
                   QChart_coil->xAxis->setRange(key, 30, Qt::AlignRight);
                   QChart_coil->replot(QCustomPlot::rpQueuedReplot);
                   QChart_hall->replot(QCustomPlot::rpQueuedReplot);
                   ui->widget_coil->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
                   ui->widget_hall->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
                   if(speed>=1 && i==200 && alldata_flag==0)
                   {
                   Sleep(speed);
                   i=0;
                   }
                   else if(alldata_flag==1)
                   {

                   }

                   }
               }
                    QFile_file.close();
           }

    //the page way
//    ui->label_axis_X1->setText(QString("%1ms").arg(0));
//    ui->label_axis_X2->setText(QString("%1ms").arg(0+1600));
//    ui->pushButton_choose->show();
//    ui->pushButton_nextpage->show();
//    ui->pushButton_lastpage->show();
//    ui->pushButton_quit->show();
//    QVector_int_read_data1.clear();
//    QVector_int_read_data2.clear();
//    QVector_int_read_data3.clear();
//    QVector_int_read_data4.clear();
//    QVector_int_read_data5.clear();
//    QVector_int_read_data6.clear();
//    QVector_int_read_data7.clear();
//    QVector_int_read_data8.clear();
//    QVector_int_read_data9.clear();
//    QVector_int_read_data10.clear();
//    QVector_int_read_data11.clear();
//    QVector_int_read_data12.clear();
//    QVector_int_read_data13.clear();
//    QVector_int_read_data14.clear();
//    QVector_int_read_data15.clear();
//    QVector_int_read_data16.clear();
//    QVector_double_read_data17.clear();
//    path = QFileDialog::getOpenFileName(this,"open","./data_dir");
//    qDebug()<<path;
//    if(path.isEmpty() == false)
//    {
//        QFile_file.setFileName(path);
//        bool file_open_sucess = QFile_file.open(QIODevice::ReadOnly);
//        if(file_open_sucess == true)
//        {
//            //创建数据流，和file文件关联
//            //往数据流中读数据，相当于往文件里读数据
//            stream.setDevice(&QFile_file);
//            //读的时候，按写的顺序取数据
//            qint32 data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15,data16;
//            double data17;
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//            while(stream.atEnd() == false)
//            {
//                for(int i = 0 ; i < 640 ; i++){
//                    //stream>>data16;
//                    stream>>data1;
//                    stream>>data2;
//                    stream>>data3;
//                    stream>>data4;
//                    /*stream>>data5;
//                    stream>>data6;
//                    stream>>data7;
//                    stream>>data8;
//                    stream>>data9;
//                    stream>>data10;
//                    stream>>data11;
//                    stream>>data12;
//                    stream>>data13;
//                    stream>>data14;
//                    stream>>data15;*/
//                    stream>>data17;
//                    //qDebug()<<data1+data2+data3+data4+data5+data6-10000;
//                    QVector_int_read_data1.append(data1);
//                    QVector_int_read_data2.append(data2);
//                    QVector_int_read_data3.append(data3);
//                    QVector_int_read_data4.append(data4);
//                    QVector_double_read_data17.append(data17);
//                    /*QVector_int_read_data5.append(data5);
//                    QVector_int_read_data6.append(data6);
//                    QVector_int_read_data7.append(data7);
//                    QVector_int_read_data8.append(data8);
//                    QVector_int_read_data13.append(data13);
//                    QVector_int_read_data14.append(data14);
//                    QVector_int_read_data15.append(data15);
//                    QVector_int_read_data16.append(data16);*/
//                }
//                //stream>>data17;
//                //qDebug()<<data17;
//                //QVector_double_read_data17.append(data17);
//            }
//        }
//        data_length = QVector_int_read_data2.size();
//        qDebug()<<"datalength:"<<data_length;
//        if(data_length<=1600)//数据量较少
//        {
//            for(int i=0;i<data_length;i++)
//            {
//                 /*QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[i]+QVector_int_read_data2[i]+QVector_int_read_data3[i]
//                                                          +QVector_int_read_data4[i]+QVector_int_read_data5[i]+QVector_int_read_data6[i]
//                                                          -10000);
//                 QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data7[i]+QVector_int_read_data8[i]+QVector_int_read_data13[i]
//                                                          +QVector_int_read_data14[i]+QVector_int_read_data15[i]+QVector_int_read_data16[i]
//                                                          -10000);*/
//                QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[i]);
//                QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data2[i]);
//                QVector_QPointF_hall_graph_data1[i].setY(QVector_int_read_data3[i]);
//                QVector_QPointF_hall_graph_data2[i].setY(QVector_int_read_data4[i]);
//            }
//            QSplineSeries_coil->replace(QVector_QPointF_coil_graph_data1);
//            QSplineSeries_coil2->replace(QVector_QPointF_coil_graph_data2);
//            QSplineSeries_hall->replace(QVector_QPointF_hall_graph_data1);
//            QSplineSeries_hall2->replace(QVector_QPointF_hall_graph_data2);
//            data_plot_pos = data_length;
//            ui->pushButton_lastpage->hide();
//            ui->pushButton_nextpage->hide();
//            qDebug()<<"数据量少！";
//        }
//        else//数据量足够
//        {
//            for(int i=0;i<1600;i++)
//            {
//                /*QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[i]+QVector_int_read_data2[i]+QVector_int_read_data3[i]
//                                                         +QVector_int_read_data4[i]+QVector_int_read_data5[i]+QVector_int_read_data6[i]
//                                                         -10000);
//                QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data7[i]+QVector_int_read_data8[i]+QVector_int_read_data13[i]
//                                                         +QVector_int_read_data14[i]+QVector_int_read_data15[i]+QVector_int_read_data16[i]
//                                                         -10000);*/
//                QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[i]);
//                QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data2[i]);
//                QVector_QPointF_hall_graph_data1[i].setY(QVector_int_read_data3[i]);
//                QVector_QPointF_hall_graph_data2[i].setY(QVector_int_read_data4[i]);
//            }
//            QSplineSeries_coil->replace(QVector_QPointF_coil_graph_data1);
//            QSplineSeries_coil2->replace(QVector_QPointF_coil_graph_data2);
//            QSplineSeries_hall->replace(QVector_QPointF_hall_graph_data1);
//            QSplineSeries_hall2->replace(QVector_QPointF_hall_graph_data2);
//            data_plot_pos = 1600;
//            qDebug()<<"显示第一屏！";
//            ui->pushButton_nextpage->show();
//            ui->pushButton_lastpage->hide();
//        }
//        QFile_file.close();
//    }
}
void widget_back::Sleep(double msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
void widget_back::on_pushButton_lastpage_clicked()
{
    speed+=5;

    //the page way
//    data_plot_pos = data_plot_pos - 1600;
//    ui->label_axis_X1->setText(QString("%1ms").arg(data_plot_pos));
//    ui->label_axis_X2->setText(QString("%1ms").arg(data_plot_pos+1600));
//    if(data_plot_pos<=data_length)
//    {
//        for(int i=0;i<1600;i++)
//        {
//            QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[data_plot_pos-1600+i]);
//            QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data2[data_plot_pos-1600+i]);
//            QVector_QPointF_hall_graph_data1[i].setY(QVector_int_read_data3[data_plot_pos-1600+i]);
//            QVector_QPointF_hall_graph_data2[i].setY(QVector_int_read_data4[data_plot_pos-1600+i]);
//            /*QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[data_plot_pos-1600+i]+QVector_int_read_data2[data_plot_pos-1600+i]+QVector_int_read_data3[data_plot_pos-1600+i]
//                                                     +QVector_int_read_data4[data_plot_pos-1600+i]+QVector_int_read_data5[data_plot_pos-1600+i]+QVector_int_read_data6[data_plot_pos-1600+i]
//                                                     -10000);
//            QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data7[data_plot_pos-1600+i]+QVector_int_read_data8[data_plot_pos-1600+i]+QVector_int_read_data13[data_plot_pos-1600+i]
//                                                     +QVector_int_read_data14[data_plot_pos-1600+i]+QVector_int_read_data15[data_plot_pos-1600+i]+QVector_int_read_data16[data_plot_pos-1600+i]
//                                                     -10000);*/
//        }
//        QSplineSeries_coil->replace(QVector_QPointF_coil_graph_data1);
//        QSplineSeries_coil2->replace(QVector_QPointF_coil_graph_data2);
//        QSplineSeries_hall->replace(QVector_QPointF_hall_graph_data1);
//        QSplineSeries_hall2->replace(QVector_QPointF_hall_graph_data2);
//    }

//    if(data_plot_pos>=3200)
//    {
//        ui->pushButton_lastpage->show();
//    }
//    else ui->pushButton_lastpage->hide();
//    if(data_plot_pos<data_length)
//    {
//        ui->pushButton_nextpage->show();
//    }
//    else ui->pushButton_nextpage->hide();
}
void widget_back::on_pushButton_nextpage_clicked()
{
  if(speed>1)
      speed-=1;
  else if(speed>0.1 && speed<=1)
  {
      speed=1;
      QMessageBox::about(this,"亲","已经是最快了！");
  }
  else
   {}
  qDebug()<<speed;

    //the page way
//    data_plot_pos = data_plot_pos + 1600;
//    ui->label_axis_X1->setText(QString("%1ms").arg(data_plot_pos));
//    ui->label_axis_X2->setText(QString("%1ms").arg(data_plot_pos+1600));
//    if(data_plot_pos<=data_length)
//    {
//        for(int i=0;i<1600;i++)
//        {
//            QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[data_plot_pos-1600+i]);
//            QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data2[data_plot_pos-1600+i]);
//            QVector_QPointF_hall_graph_data1[i].setY(QVector_int_read_data3[data_plot_pos-1600+i]);
//            QVector_QPointF_hall_graph_data2[i].setY(QVector_int_read_data4[data_plot_pos-1600+i]);
//            /*QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[data_plot_pos-1600+i]+QVector_int_read_data2[data_plot_pos-1600+i]+QVector_int_read_data3[data_plot_pos-1600+i]
//                                                     +QVector_int_read_data4[data_plot_pos-1600+i]+QVector_int_read_data5[data_plot_pos-1600+i]+QVector_int_read_data6[data_plot_pos-1600+i]
//                                                     -10000);
//            QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data7[data_plot_pos-1600+i]+QVector_int_read_data8[data_plot_pos-1600+i]+QVector_int_read_data13[data_plot_pos-1600+i]
//                                                     +QVector_int_read_data14[data_plot_pos-1600+i]+QVector_int_read_data15[data_plot_pos-1600+i]+QVector_int_read_data16[data_plot_pos-1600+i]
//                                                     -10000);
//            QVector_QPointF_coil_graph_data1[i].setY(QVector_int_read_data1[data_plot_pos-1600+i]);
//            QVector_QPointF_coil_graph_data2[i].setY(QVector_int_read_data2[data_plot_pos-1600+i]);*/
//        }
//        QSplineSeries_coil->replace(QVector_QPointF_coil_graph_data1);
//        QSplineSeries_coil2->replace(QVector_QPointF_coil_graph_data2);
//        QSplineSeries_hall->replace(QVector_QPointF_hall_graph_data1);
//        QSplineSeries_hall2->replace(QVector_QPointF_hall_graph_data2);
//    }


//    if(data_plot_pos>=3200)
//    {
//        ui->pushButton_lastpage->show();
//    }
//    else ui->pushButton_lastpage->hide();
//    if(data_plot_pos<data_length)
//    {
//        ui->pushButton_nextpage->show();
//    }
//    else ui->pushButton_nextpage->hide();
}




