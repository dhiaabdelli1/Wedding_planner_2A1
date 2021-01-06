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
#include <QMediaPlayer>
#include <QSystemTrayIcon>
#include <QtConcurrent>
#include <QFuture>

#include <QPropertyAnimation>
#include <QSound>
#include <QInputDialog>

#include <QTranslator>

#include "invite.h"
#include "table.h"
#include "client.h"
#include "reservation.h"
#include "personnel.h"
#include "departement.h"
#include "login.h"
#include "produits.h"
#include"excel.h"
#include "collaborateur.h"
#include "service.h"
#include "fournisseurs.h"

#include "arduino.h"
#include "dialog.h"
#include "smtp.h"
#include "stats.h"
#include "chat.h"
#include "windows.h"
#include <vector>
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
    //bool eventFilter(QObject *obj, QEvent *event);

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

    void on_envoyer_invite_clicked();

    void on_tabWidget_2_tabBarClicked(int index);

    void on_entrer_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_ajouter_departement_clicked();

    void on_reset_departement_clicked();

    void on_modifier_departement_clicked();

    void on_sypprimer_departement_clicked();

    void on_ajouter_personnel_clicked();

    void on_reset_personnel_clicked();

    void on_modifier_personnel_clicked();

    void on_supprimer_personnel_clicked();

    void on_pdf_personnel_clicked();

    void on_lineEdit_recherchepersonnel_textChanged(const QString &arg1);

    void on_stat_personnel_clicked();

    void on_tri_cin_personnel_clicked();

    void on_tri_salaire_personnel_clicked();

    void on_tri_nom_personnel_clicked();

    void on_configuration_clicked();

    void on_confirmer_chan_mdp_clicked();

    void on_pushButton_4_clicked();

    void on_confirmer_langue_clicked();

    void on_pushButton_val_p_clicked();

    void on_pushButton_Supp_p_clicked();

    void on_pushButton_Modifier_p_clicked();

    void on_pushButton_Recherche_p_clicked();

    void on_pushButton_afficher_p_clicked();

    void on_pushButton_val_f_clicked();

    void on_pushButton_supp_f_clicked();

    void on_pushButton_modifier_f_clicked();

    void on_pushButton_afficher_f_clicked();

    void on_pushButton_rechercher_f_clicked();

    void on_pushButton_Exporter_p_clicked();

    void on_pushButton_exporter_f_clicked();

    void on_ajouterC_2_clicked();

    void on_supprimerC_2_clicked();

    void on_pushButton_ajouterS_clicked();

    void on_pushButton_supprimerS_clicked();

    void on_modifierC_2_clicked();

    void on_pushButton_modifierS_clicked();


    void on_resetC_2_clicked();

    void on_resetS_clicked();




    void on_rechercher_colab_clicked();

    void on_reafficher_colab_clicked();





    void on_exporterC_clicked();

    void on_envoyerC_clicked();



    void on_radioButton_triType_clicked();

    void on_radioButton_triPrix_clicked();

    void on_radioButton_triDate_clicked();

    void on_chat_clicked();
    bool launch_chat(chat&);

    void on_signup_button_clicked();

    void on_image_clicked();

    void on_show_clicked();

    void on_mdp_oublie_label_linkActivated(const QString & link);

    void on_pushButton_3_clicked();

    void on_affecter_code_clicked();

    void on_enter_personnel_clicked();

    bool notifications_feed(QString);

    bool notifications_invite(QString);



    void on_test_clicked();

    void on_radioButton_nuit_toggled(bool checked);

    void on_radioButton_jour_toggled(bool checked);

    void on_cant_touch_this_pressed();


    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_email_clicked();

    void on_pushButton_7_clicked();

    void on_upload_image_clicked();

    void on_ajouter_image_clicked();

    void on_annuler_chan_mdp_clicked();

    void on_radioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    invite tmpinvite;
    table tmptable;
    client tempclient;
    reservation tempreservation;
    personnel tmppersonnel;
    departement tmpdepartement;
    produits tmpprod;
    fournisseurs tmpf;
    collaborateur tmpCollaborateur;
    collaborateur tmpr;
    service tmpservice;

    enum column
    {
        REFERENCE,QUANTITE,TYPE,DATE
    };
    //Regex
    QRegExp mail_regex;
    QRegExp cin_regex;
    QRegExp chaine_regex;
    QRegExp telephone_regex;
    QRegExp nom_regex,prenom_regex,tel_regex,budget_regex; //IHEB
    QRegExp M;
    QRegExp R;
    QRegExp T;
    QRegExp C;
    QRegExp ip_regex;
    //Animation
    QPropertyAnimation *contract_animation;
    QPropertyAnimation *expand_animation;
    QPropertyAnimation *contract_animation_2;
    QPropertyAnimation *expand_animation_2;

    //Arduino
    QByteArray data; //contient les données reçus
    Arduino A; //Tmp

    QString cin_recu="";
    QString tmp_recue="";
    bool tmp_verif=false;

    int num_entree=0;
    int num_entree_personnel=0;

    QTranslator *translator=new QTranslator;

    login *log;

    QString current_user;

    QString myid="";
    int counter=0;
    bool test=false;

    int initial_width;
    int initial_height;

    int login_width;
    int login_height;

    int center_main_x=0;
    int center_main_y=0;
    int center_login_x=0;
    int center_login_y=0;

    QMediaPlayer *player;

    QSystemTrayIcon *mSystemTrayIcon;
    QMediaPlayer *mMediaPlayer;
    QSound *son;

    QString tmp;

    QString id_entree;

};
#endif // MAINWINDOW_H
