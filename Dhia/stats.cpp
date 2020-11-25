#include "stats.h"
#include "ui_stats.h"

stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);



//    QBarSet *set0=new QBarSet("Dhia");
//    QBarSet *set1=new QBarSet("Nour");
//    QBarSet *set2=new QBarSet("Mouna");
//    QBarSet *set3=new QBarSet("Mosbah");

//    *set0 << 283 << 341 << 313 << 334 << 346 <<335;
//    *set1 << 253 << 241 << 313 << 352 << 346 <<335;
//    *set2 << 263 << 141 << 313 << 238 << 346 <<325;
//    *set3 << 283 << 341 << 313 << 118 << 146 <<335;

//    QBarSeries *series= new QBarSeries();
//    series->append(set0);
//    series->append(set1);
//    series->append(set2);
//    series->append(set3);

//    QChart *chart=new QChart();
//    chart->addSeries(series);
//    chart->setTitle("hello");

//    chart->setAnimationOptions(QChart::AllAnimations);

//    QStringList categories;
//    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";
//    QBarCategoryAxis *axis= new QBarCategoryAxis();
//    axis->append(categories);
//    chart->createDefaultAxes();
//    chart->setAxisX(axis,series);
//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignBottom);

//    QChartView *chartView= new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);


    /*QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window,QRgb(0xffffff));
    pal.setColor(QPalette::WindowText,QRgb(0x404040));

    qApp->setPalette(pal);*/

    QPieSeries *series = new QPieSeries();

            series->append("C++", 80);
            series->append("Python", 70);
            series->append("Java", 50);
            series->append("C#", 40);
            series->append("PHP", 30);


            QPieSlice *slice = series->slices().at(1);
            slice->setExploded(true);
            slice->setLabelVisible(true);
            slice->setPen(QPen(Qt::darkGreen, 2));
            slice->setBrush(Qt::green);


            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Qt5 Pie Chart Example");


            QChartView *chartview = new QChartView(chart);
            chartview->setParent(ui->testPie);



}

stats::~stats()
{
    delete ui;
}
