#ifndef STAT_H
#define STAT_H

#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

#include <QWidget>

namespace Ui {
class Stat;
}

class Stat : public QWidget
{
    Q_OBJECT

public:
    explicit Stat(QWidget *parent = nullptr);
    void make();
    ~Stat();

private:
    Ui::Stat *ui;
};

#endif // STAT_H


