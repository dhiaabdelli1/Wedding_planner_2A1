#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QSound>
#include <QMainWindow>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QItemSelectionModel>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlTableModel>
#include <QDialog>
#include <QWidget>
#include "produits.h"
#include"fournisseurs.h"
#include <QSqlTableModel>




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

    void on_pushButton_val_clicked();

    void on_pushButton_Supp_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_Recherche_clicked();

    void on_pushButton_afficher_clicked();

    void on_pushButton_val_2_clicked();

    void on_pushButton_supp_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_afficher_2_clicked();

    void on_actionSound_clicked();

    void on_muteSound_clicked();

    void on_pushButton_rechercher_2_clicked();

    void on_pushButton_Exporter_clicked();

private:
    Ui::MainWindow *ui;
    produits tmpprod;
    fournisseurs tmpf;
    QSound *sound;
    enum column
    {
        REFERENCE,QUANTITE,TYPE,DATE
    };
};
#endif // MAINWINDOW_H




