#include "stat.h"
#include "ui_stat.h"
#include <QString>
#include"personnel.h"
#include<qsqlquery.h>


Stat::Stat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
}
Stat::~Stat()
{
    delete ui;
}


void Stat::make()
{
        int finance;
        int marketing;
        int total;
        QString Finance;
        QString Marketing;
        QSqlQuery q;

        q.prepare("SELECT COUNT(cin) FROM personnel where departement ='finance' ");
        q.exec();
        q.first() ;
        finance=(q.value(0).toInt());

        q.prepare("SELECT COUNT(cin) FROM personnel where departement ='marketing' ");
        q.exec();
        q.first() ;
        marketing=(q.value(0).toInt());
        q.prepare("SELECT COUNT(cin) FROM personnel  ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());

        marketing=((double)marketing/(double)total)*100;
        finance=100-marketing;

        Finance= QString::number(finance);
        Marketing=QString::number(marketing);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("FINANCE"+Finance+"%",finance);
         series->append("MARKETING"+Marketing+"%",marketing);
         QPieSlice *slice0 = series->slices().at(0);
          slice0->setLabelVisible();

          QPieSlice *slice1 = series->slices().at(1);
             slice1->setExploded();
             slice1->setLabelVisible();
             slice1->setPen(QPen(Qt::darkRed, 2));
             slice1->setBrush(Qt::black);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistiques sur les departements ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
