 #ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QSplineSeries>
#include <QScatterSeries>
#include<QTcpServer>
#include<QTcpSocket>
#include<QPushButton>
#include<QDebug>
#include<QMessageBox>
#include<QThread>
#include<QDir>
#include<QFileDialog>
#include<QDataStream>
#include<QTextEdit>
#include <QTimer> //定时器对象
#include <QTextCodec>
#include"widget_set.h"
#include"widget_report.h"
#include"thread_tcp.h"
#include "widget_back.h"
#include "qcustomplot.h"

/*

 *
 * 运行平台：正点原子家的i.mx6ull开发板、树莓派4B、windows10、11系统的电脑,实测可行
 * *************************************************************************************
**/
extern int maxYother;
extern int minYother;
using namespace QtCharts;
namespace Ui {
class MyWidget;
}
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget()override;
protected:
private slots:
    void on_pushButton_quit_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_report_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_set_clicked();
    void on_radioButton_distance_dir_toggled(bool checked);
    void on_pushButton_dema_clicked();
    void on_pushButton_upload_clicked();
public:////function
    void tcp_data_trans_together_func(QByteArray buff_array);
    double data_filter_func(double data_in[]);
    void PythonInit();
signals:
    void startThread_tcpcommunicate(); //启动子线程的信号
public:
    Ui::MyWidget *ui;
    QCustomPlot* QChart_coil = new QCustomPlot();
    QCustomPlot* QChart_hall = new QCustomPlot();

    QVector<QPointF> QVector_QPointF_data_buff; // 存储业务数据的 list
    QVector<QPointF> QVector_QPointF_coil_graph_data1; // 存储业务数据的 coil1
    QVector<QPointF> QVector_QPointF_coil_graph_data2; // 存储业务数据的 coil2
    QVector<QPointF> QVector_QPointF_hall_graph_data1; // 存储业务数据的 hall1
    QVector<QPointF> QVector_QPointF_hall_graph_data2; // 存储业务数据的 hall2

    QVector<int> QVector_int_filter_data_buff; // 滤波数据
    QVector<int> QVector_int_after_filter_data; // 滤波数据
    int int_filter_data_buff[80]; // 滤波数据
    int int_after_filter_data[80]; // 滤波数据

    QSplineSeries *QSplineSeries_hall;//平滑曲线点
    QSplineSeries *QSplineSeries_hall2;//平滑曲线点
    QSplineSeries *QSplineSeries_coil;//QLineSeries QXYSeries
    QSplineSeries *QSplineSeries_coil2;//QLineSeries QXYSeries

    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY;
    int minY;
//    class message     //新建一个类存放全局变量
//    {
//    public:
//         static int maxYother;
//    };
    long long detec_count = 0;
    int graph_x_axis_Count = 1600;//x-axis长度为4000  原1600
    char DAQ_socket_cmd = 'L';
    QTcpSocket QTcpSocket_DAQ; //采集卡通信套接字
    QTcpSocket QTcpSocket_cloud; //服务器通信套接字
    Widget_set Widget_set_win;
    widget_report widget_report_win;
    widget_back widget_back_win;
    //thread_tcp thread_tcp_obj;
    char flag_thread_run = 1;
    char flag_DAQ_error = 0;
    char flag_cloud_error = 0;
    char flag_cloud_uploading = 0;
    char flag_cloud_realTime_upLoad = 0;
    QTimer QTimer_socket_connect_wait; //定时器对象
    QTimer QTimer_alarm_label;//实时检测到损伤报警
    int int_alarm_up_limit = 4000;
    int int_alarm_down_limit = -2000;
    qint32 int_distance_calc = 8388608;
    int int_defect_nubmer = 0;
    float float_distance_coefficient = 1.00;
    double distance_buff = 0;
    int distance_dir = 1;
    QString base_name;
    QDir QDir_data_save_dir;
    QFile QFile_data_save_file;
    QDataStream QDataStream_detec_data;
    QTextCodec *tc = QTextCodec::codecForName("UTF-8");//
public slots:
    void QTimer_socket_connect_wait_slots();
    void QTimer_alarm_label_slots();
    void QTcpSocket_DAQ_connected_slots();
    void QTcpSocket_DAQ_readyRead_slots();
    void QTcpSocket_DAQ_connected_error_slots();
    void QTcpSocket_cloud_connected_slots();
    void QTcpSocket_cloud_readyRead_slots();
    void QTcpSocket_cloud_connected_error_slots();
    void thread_getdata_graph_plot(int data[]);
    void slots_widget_set_handle(int int_show_up_limit,int int_show_down_limit,int int_alarm_up_limit,int int_alarm_down_limit,float float_distance_coefficient,QString base_name);
};

#endif // MYWIDGET_H
