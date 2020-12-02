#include "statistique.h"
#include "ui_statistique.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

Statistique::Statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistique)
{
    ui->setupUi(this);
    QSqlQuery query,query1,query2;

        int i =0;
          // set dark background gradient:
          QLinearGradient gradient(0, 0, 0, 400);
          gradient.setColorAt(0, QColor(255,255,255));
          gradient.setColorAt(0.38, QColor(255,255,255));
          gradient.setColorAt(1, QColor(255,255,255));
          ui->widget->setBackground(QBrush(gradient));
        QCPBars *fossil = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
         QCPBars *nuclear = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        fossil->setName("prix_achat");
        fossil->setPen(QPen(QColor(0, 0, 255).lighter(190)));
        fossil->setBrush(QColor(255, 0, 0));
        nuclear->setName("quantite");
        nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
        nuclear->setBrush(QColor(250, 170, 20));
        nuclear->moveAbove(fossil);

          // prepare x axis with country labels:
          QVector<double> ticks,ticks2;
          QVector<QString> labels;
            QVector<double> fossilData,nuclearData;
          query.prepare("SELECT nom_categorie FROM categorie");
          query.exec();


          while(query.next())
          {
           labels.append(query.value(0).toString());
           i++;
           ticks.append(i);

           query1.prepare("SELECT count(*) FROM produit where id_categorie = '"+query.value(0).toString()+"' ");
           query1.exec();
           while (query1.next()) {
             fossilData.append(query1.value(0).toDouble());
           }


          }



          //ticks << 1 << 2 << 3 ;
        //  labels << "5000" << "10000" << "15000" ;
          QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
          textTicker->addTicks(ticks, labels);
          ui->widget->xAxis->setTicker(textTicker);
          ui->widget->xAxis->setTickLabelRotation(60);
          ui->widget->xAxis->setSubTicks(false);
          ui->widget->xAxis->setTickLength(0, 4);
          ui->widget->xAxis->setRange(0, 8);
          ui->widget->xAxis->setBasePen(QPen(Qt::black));
          ui->widget->xAxis->setTickPen(QPen(Qt::black));
          ui->widget->xAxis->grid()->setVisible(true);
          ui->widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
          ui->widget->xAxis->setTickLabelColor(Qt::black);
          ui->widget->xAxis->setLabelColor(Qt::black);

          // prepare y axis:
          ui->widget->yAxis->setRange(0, 10);
          ui->widget->yAxis->setPadding(5); // a bit more space to the left border
          ui->widget->yAxis->setLabel("Bénefice des publicités en 2019");
          ui->widget->yAxis->setBasePen(QPen(Qt::black));
          ui->widget->yAxis->setTickPen(QPen(Qt::black));
          ui->widget->yAxis->setSubTickPen(QPen(Qt::black));
          ui->widget->yAxis->grid()->setSubGridVisible(true);
          ui->widget->yAxis->setTickLabelColor(Qt::black);
          ui->widget->yAxis->setLabelColor(Qt::black);
          ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
          ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

          // Add data:



         fossil->setData(ticks, fossilData);

         nuclear->setData(ticks, nuclearData);


          // setup legend:
          ui->widget->legend->setVisible(true);
          ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
          ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
          ui->widget->legend->setBorderPen(Qt::NoPen);
          QFont legendFont = font();
          legendFont.setPointSize(10);
          ui->widget->legend->setFont(legendFont);
          ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

Statistique::~Statistique()
{
    delete ui;
}
