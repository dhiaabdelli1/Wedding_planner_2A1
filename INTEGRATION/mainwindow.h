#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
#include <qtextbrowser.h>

#include <QPropertyAnimation>
#include <QSound>
#include <QInputDialog>

#include "invite.h"
#include "table.h"
#include "client.h"
#include "reservation.h"
#include "login.h"

#include "arduino.h"
//#include "stats.h"
//#include "arduino.h"

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
    void on_Dhia_clicked();

    void on_Sara_clicked();

    void on_Iheb_clicked();

    void on_Elaa_clicked();

    void on_Barkia_clicked();

    void on_login_button_clicked();

    void on_sign_up_button_clicked();

    void on_ajouter_invite_clicked();

    void on_reset_invite_clicked();

    void on_exporter_invite_clicked();

    void on_modifier_invite_clicked();

    void on_supprimer_invite_clicked();

    void on_recherche_invite_clicked();

    void on_imprimer_invite_clicked();

    void on_afficher_tout_invite_clicked();

    void on_envoyer_clicked();

    void on_trier_invite_clicked();

    void on_stats_invite_clicked();

    void on_contract_invite_clicked();

    void on_lineEdit_recherche_invite_textChanged(const QString &arg1);

    void on_ajouter_table_clicked();

    void on_modifier_table_clicked();

    void on_supprimer_table_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_trier_table_clicked();

    void on_affecter_table_clicked();

    void on_contract_table_clicked();

    void on_reset_table_clicked();

    void on_aucun_clicked();

    void on_aucun_table_clicked();

    void on_logout_button_clicked();

    void on_ajouter_client_clicked();

    void on_modifier_client_clicked();

    void on_supprimer_client_clicked();

    void on_recherche_client_textChanged(const QString &arg1);

    void on_exporter_client_clicked();

    void on_imprimer_client_clicked();

    void on_trier_client_clicked();

    void on_ajouter_reservation_clicked();

    void on_modifier_reservation_clicked();

    void on_supprimer_reservation_clicked();

    void on_trier_reservation_clicked();

    void on_recherche_reservation_textChanged(const QString &arg1);





    void update_label();

    void on_refuser_clicked();



    void on_accepter_clicked();

    void on_enter_clicked();

private:
    Ui::MainWindow *ui;

    invite tmpinvite;
    table tmptable;
    client tempclient;
    reservation tempreservation;
    //Regex
    QRegExp mail_regex;
    QRegExp cin_regex;
    QRegExp chaine_regex;
    QRegExp telephone_regex;
    QRegExp nom_regex,prenom_regex,tel_regex,budget_regex; //IHEB
    //Animation
    QPropertyAnimation *contract_animation;
    QPropertyAnimation *expand_animation;
    QPropertyAnimation *contract_animation_2;
    QPropertyAnimation *expand_animation_2;

    //Arduino
    QByteArray data; //contient les données reçus
    Arduino A; //Tmp
};
#endif // MAINWINDOW_H
