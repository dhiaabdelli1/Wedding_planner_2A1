#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QItemSelectionModel>
#include <QDebug>
#include <QSqlTableModel>
#include <QDialog>
#include <QPrinter>
#include <QPrintDialog>
#include "qtmaterialraisedbutton.h"
#include <qtextbrowser.h>

#include <QPropertyAnimation>
#include <QSound>
#include <QInputDialog>

#include "invite.h"
#include "table.h"
#include "stats.h"




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


    void on_ajouter_invite_clicked();

    void on_reset_invite_clicked();

    void on_exporter_invite_clicked();

    void on_modifier_invite_clicked();

    void on_supprimer_invite_clicked();

    void on_recherche_invite_clicked();

    void on_imrprimer_clicked();

    void on_affichier_tout_invite_clicked();

    void on_envoyer_clicked();

    void on_trier_invite_clicked();

    void on_stats_clicked();

    void on_contract_invite_clicked();

    void on_lineEdit_recherche_invite_textChanged(const QString &arg1);

    void on_ajouter_table_clicked();

    void on_modifier_table_clicked();

    void on_supprimer_table_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_trier_table_clicked();

    void on_affecter_table_clicked();

    void on_contract_table_clicked();

    void on_imprimer_clicked();

    void on_afficher_tout_invite_clicked();

    void on_reset_table_clicked();

    void on_aucun_clicked();

    void on_aucun_table_clicked();

private:
    Ui::MainWindow *ui;


    invite tmpinvite;
    table tmptable;
    //Regex
    QRegExp mail_regex;
    QRegExp cin_regex;
    QRegExp chaine_regex;
    QRegExp telephone_regex;
    //Animation
    QPropertyAnimation *contract_animation;
    QPropertyAnimation *expand_animation;
    QPropertyAnimation *contract_animation_2;
    QPropertyAnimation *expand_animation_2;
};
#endif // MAINWINDOW_H
