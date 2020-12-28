#include "stats.h"
#include "ui_stats.h"
#include <QDebug>

stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);



    QBarSet *set0=new QBarSet("Homme");
    QBarSet *set1=new QBarSet("Femme");


    QDate date_1950(1950,01,01);
    QDate date_1960(1960,01,01);
    QDate date_1970(1970,01,01);
    QDate date_1980(1980,01,01);
    QDate date_1990(1990,01,01);
    QDate date_2000(2000,01,01);




    *set0 << tmpinvite.count_date(date_1950,date_1960,"Homme") << tmpinvite.count_date(date_1960,date_1970,"Homme") << tmpinvite.count_date(date_1970,date_1980,"Homme") << tmpinvite.count_date(date_1990,date_1990,"Homme") << tmpinvite.count_date(date_1990,date_2000,"Homme");
    *set1 << tmpinvite.count_date(date_1950,date_1960,"Femme") << tmpinvite.count_date(date_1960,date_1970,"Femme") << tmpinvite.count_date(date_1970,date_1980,"Femme") << tmpinvite.count_date(date_1980,date_1990,"Femme") << tmpinvite.count_date(date_1990,date_2000,"Femme");


    qDebug()<< tmpinvite.count_date(date_1950,date_2000,"Homme");
    qDebug()<< tmpinvite.count_date(date_1950,date_2000,"Femme");



    QBarSeries *series= new QBarSeries();
    series->append(set0);
    series->append(set1);


    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Stats sur l'âge");

    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    categories << "1950-1960" << "1960-1970" << "1970-1980" << "1980-1990" << "1990-2000";
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

    series_pie->append("Homme",tmpinvite.count("Homme"));
    series_pie->append("Femme", tmpinvite.count("Femme"));


    QPieSlice *slice = series_pie->slices().at(1);
    slice->setExploded(true);
    slice->setLabelVisible(true);
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);


    QChart *chart_pie = new QChart();
    chart_pie->addSeries(series_pie);
    chart_pie->setTitle("Stats sur le sexe");


    QChartView *chartview_pie = new QChartView(chart_pie);



    chartView->setParent(ui->horizontalFrame_sticks);
    chartview_pie->setParent(ui->horizontalFrame_pie);

}

stats::~stats()
{
    delete ui;
}
