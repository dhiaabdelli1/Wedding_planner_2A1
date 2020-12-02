#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnel.h"
#include "departement.h"
#include <QMainWindow>

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
    void on_pushButton_2_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();



    void on_ajouter2_clicked();

    void on_supprimer_departement_clicked();

    void on_modifier_departement_clicked();

   // void on_lineEdit_4_textChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_salaire_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();






 void on_pushButton_5_clicked();



 void on_checkBox_stateChanged(int arg1);

 void on_checkBox_2_stateChanged(int arg1);

 void on_checkBox_3_stateChanged(int arg1);

 void on_checkBox_4_stateChanged(int arg1);

 void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    personnel tmppersonnel;
    departement tmpdepartement;
};
#endif // MAINWINDOW_H
