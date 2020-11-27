#include "stats.h"
#include "ui_stats.h"

stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);



    QBarSet *set0=new QBarSet("Dhia");
    QBarSet *set1=new QBarSet("Nour");
    QBarSet *set2=new QBarSet("Mouna");
    QBarSet *set3=new QBarSet("Mosbah");

    *set0 << 283 << 341 << 313 << 334 << 346 <<335;
    *set1 << 253 << 241 << 313 << 352 << 346 <<335;
    *set2 << 263 << 141 << 313 << 238 << 346 <<325;
    *set3 << 283 << 341 << 313 << 118 << 146 <<335;

    QBarSeries *series= new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Stats invités");

    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";
    QBarCategoryAxis *axis= new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView= new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //PIE

    QPieSeries *series_pie = new QPieSeries();

    series_pie->append("C++", 80);
    series_pie->append("Python", 70);
    series_pie->append("Java", 50);
    series_pie->append("C#", 40);
    series_pie->append("PHP", 30);


    QPieSlice *slice = series_pie->slices().at(1);
    slice->setExploded(true);
    slice->setLabelVisible(true);
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);


    QChart *chart_pie = new QChart();
    chart_pie->addSeries(series_pie);
    chart_pie->setTitle("Qt5 Pie Chart Example");


    QChartView *chartview_pie = new QChartView(chart_pie);



    chartView->setParent(ui->horizontalFrame_sticks);
    chartview_pie->setParent(ui->horizontalFrame_pie);

}

stats::~stats()
{
    delete ui;
}
