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


    void on_pushButton_ajouter_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_details_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_recherche_clicked();

    void on_pushButton_notifier_clicked();

    void on_pushButton_stats_clicked();

    void on_pushButton_envoyer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;


    invite tmpinvite;
    table tmptable;
    QRegExp mail_regex;
    QRegExp cin_regex;
    QRegExp chaine_regex;
    QRegExp telephone_regex;
    QPropertyAnimation *contract_animation;
    QPropertyAnimation *expand_animation;
    QPropertyAnimation *contract_animation_2;
    QPropertyAnimation *expand_animation_2;
};
#endif // MAINWINDOW_H
