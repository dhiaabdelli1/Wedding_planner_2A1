#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "collaborateur.h"
#include "service.h"
#include <QMainWindow>
#include <QRegularExpression>

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
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_pushButton_ajouterS_clicked();

    void on_pushButton_supprimerS_clicked();

    void on_modifier_clicked();

    void on_pushButton_modifierS_clicked();


    void on_reset_clicked();

    void on_resetS_clicked();




    void on_checkBox_7_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_5_clicked();




    void on_rechercher_colab_clicked();

    void on_reafficher_colab_clicked();



    //void on_envoyer_clicked();

    void on_exporter_clicked();

    void on_envoyer_clicked();



    void on_radioButton_triType_clicked();

    void on_radioButton_triPrix_clicked();

    void on_radioButton_triDate_clicked();

private:
    Ui::MainWindow *ui;
    QRegExp MRE;
    collaborateur tmpCollaborateur;
    collaborateur tmpr;
    service tmpservice;

};
#endif // MAINWINDOW_H
