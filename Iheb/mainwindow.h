#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPropertyAnimation>
#include <client.h>
#include <reservation.h>
#include "smtp.h"

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

    void on_pushButton_4_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);
    void on_actionplay_video_triggered();

 //   void on_actionstop_video_triggered();

    void sendMail();
    void mailSent(QString);
    void browse();



    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();



    void on_pushButton_6_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_stat_clicked();


    void on_comboBox_activated(int index);

    void on_pushButton_7_clicked();

    void on_tabWidget_3_currentChanged(int index);

    void on_pushButton_8_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    client tempclient;
    reservation tempreservation;
     QStringList files;
 QMediaPlayer* player;
 QVideoWidget* vw;
 QPropertyAnimation *anim,*anim2;
 QRegExp mail_regex;


};
#endif // MAINWINDOW_H
