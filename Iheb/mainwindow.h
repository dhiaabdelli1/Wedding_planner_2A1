#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tabWidget_2_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    client tempclient;
};
#endif // MAINWINDOW_H
