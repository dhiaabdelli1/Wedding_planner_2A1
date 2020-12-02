#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mail_regex=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    ui->setupUi(this);

    this->setStyleSheet("background-color: rgb(97, 97, 97);");

    ui->groupBox->setMaximumWidth(100);


    ui->cINLineEdit->setMaxLength(8);

    ui->cINLineEdit->setPlaceholderText("CIN ...");
    ui->nomLineEdit->setPlaceholderText("Nom ...");
    ui->prNomLineEdit->setPlaceholderText("Prénom ...");
    ui->eMailLineEdit->setPlaceholderText("E-mail ...");


    ui->tableView->setModel(tmpinvite.afficher());


    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


    contract_animation = new QPropertyAnimation(ui->groupBox,"maximumWidth");
    contract_animation->setDuration(400);
    contract_animation->setStartValue(300); //find how to get get default value
    contract_animation->setEndValue(100);

    expand_animation = new QPropertyAnimation(ui->groupBox,"maximumWidth");
    expand_animation->setDuration(400);
    expand_animation->setStartValue(100); //find how to get get default value
    expand_animation->setEndValue(300);

    ui->pushButton_3->setText("Contract");

    expand_animation->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouter_clicked()
{
    bool mail_verif = mail_regex.exactMatch(ui->eMailLineEdit->text());

    if ( ui->cINLineEdit->text()!= "" &&
         ui->nomLineEdit->text()!="" &&
         ui->prNomLineEdit->text() != "" &&
         ui->eMailLineEdit->text()!= "")
    {
        if (!mail_verif)
        {
            QMessageBox::warning(this,"Erreur lors de l'ajout","E-mail invalid");
        }
        else
        {

            QString cin=ui->cINLineEdit->text();
            QString nom= ui->nomLineEdit->text();
            QString prenom= ui->prNomLineEdit->text();
            QString mail= ui->eMailLineEdit->text();
            QString sexe = ui->sexeComboBox->currentText();
            QDate date_naissance = ui->dateDeNaissanceDateEdit->date();


            invite inv(cin,nom,prenom,date_naissance,mail,sexe);

            bool test=inv.ajouter();

            if (test)
                ui->tableView->setModel(tmpinvite.afficher());



            ui->cINLineEdit->setText("");
            ui->nomLineEdit->setText("");
            ui->prNomLineEdit->setText("");
            ui->eMailLineEdit->setText("");
        }


    }
    else
    {
        QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez compléter tous les champs");
    }


}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->cINLineEdit->setText("");
    ui->nomLineEdit->setText("");
    ui->prNomLineEdit->setText("");
    ui->eMailLineEdit->setText("");
}

void MainWindow::on_pushButton_details_clicked()
{

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_invites.pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM invites ");
    q.exec();
    QString pdf="<br> <img src='D:/Users/dhiaa/Desktop/gestion_invités/logo.png' height='42' width='144'/> <h1  style='color:red'>       LISTE DES INVITES  <br></h1>\n <br> <table>  <tr>  <th> CIN </th> <th> NOM </th> <th> PRENOM </th> <th> DATE NAISSANCE  </th> <th>E-MAIL </th>  </tr>" ;


    while ( q.next()) {

        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>" ;

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}

void MainWindow::on_pushButton_modifier_clicked()
{
    if (ui->pushButton_modifier->isChecked())
    {

        ui->pushButton_modifier->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("INVITES");
        tableModel->select();
        ui->tableView->setModel(tableModel);
    }
    else
    {
        ui->pushButton_modifier->setText("Modifier");
        ui->tableView->setModel(tmpinvite.afficher());

    }

}

void MainWindow::on_pushButton_supprimer_clicked()
{


    QItemSelectionModel *select = ui->tableView->selectionModel();

    QString cin =select->selectedRows(0).value(0).data().toString();

    if(tmpinvite.supprimer(cin))
    {
        ui->tableView->setModel(tmpinvite.afficher());
        ui->statusbar->showMessage("Invité supprimé");
    }


}

void MainWindow::on_pushButton_recherche_clicked()
{

    QString nom=ui->lineEdit_recherche->text();
    QDate date=ui->dateEdit->date();
    QString sexe;
    QString email=ui->lineEdit_recherche->text();
    if (ui->radioButton->isChecked())
        sexe=ui->radioButton->text();
    else if (ui->radioButton_2->isChecked())
        sexe=ui->radioButton_2->text();




    if (ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
    {

        QSqlQueryModel *verif_combinaison=tmpinvite.rechercher_combinaison_all(nom,sexe,date);
        if (verif_combinaison!=nullptr)
        {
            ui->tableView->setModel(verif_combinaison);
        }

    }
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_sexe=tmpinvite.rechercher_sexe(sexe);
        if (verif_sexe!=nullptr)
        {
            ui->tableView->setModel(verif_sexe);
        }
    }
    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_date=tmpinvite.rechercher_date(date);
        if (verif_date!=nullptr)
        {
            ui->tableView->setModel(verif_date);
        }
    }
    else if (ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_nom=tmpinvite.rechercher_nom(nom);
        if (verif_nom!=nullptr)
        {
            ui->tableView->setModel(verif_nom);
        }
    }
    else if (ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_nom_sexe=tmpinvite.rechercher_combinaison_nom_sexe(nom,sexe);
        if (verif_nom_sexe!=nullptr)
        {
            ui->tableView->setModel(verif_nom_sexe);
        }
    }
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_sexe_date=tmpinvite.rechercher_combinaison_sexe_date(sexe,date);
        if (verif_sexe_date!=nullptr)
        {
            ui->tableView->setModel(verif_sexe_date);
        }
    }
    else if (ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
    {
        QSqlQueryModel *verif_nom_date=tmpinvite.rechercher_combinaison_nom_date(nom,date);
        if (verif_nom_date!=nullptr)
        {
            ui->tableView->setModel(verif_nom_date);
        }
    }

    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked() && ui->checkBox_mail)
    {
        QSqlQueryModel *verif_mail=tmpinvite.rechercher_email(email);
        if (verif_mail!=nullptr)
        {
            ui->tableView->setModel(verif_mail);
        }
    }

}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_notifier_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("Title")
          <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void MainWindow::on_pushButton_stats_clicked()
{
    ui->tableView->setModel(tmpinvite.afficher());
}

void MainWindow::on_pushButton_envoyer_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();

    QString email_recipient =select->selectedRows(4).value(0).data().toString();
    QString nom_recipient =select->selectedRows(1).value(0).data().toString();
    QString sexe_recipient =select->selectedRows(5).value(0).data().toString();


    QDialog *d=new Dialog(email_recipient,nom_recipient,sexe_recipient,this);
    d->show();
    d->exec();
}



void MainWindow::on_pushButton_clicked()
{
    if (ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("nom",ui->comboBox_2->currentText()));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("sexe",ui->comboBox_2->currentText()));
    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("date_naissance",ui->comboBox_2->currentText()));
    else if (ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("nom, sexe",ui->comboBox_2->currentText()));
    else if (ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("nom, date_naissance",ui->comboBox_2->currentText()));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("sexe, date_naissance",ui->comboBox_2->currentText()));
    else if (ui->checkBox_nom->isChecked() && ui->checkBox_sexe->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpinvite.trier("nom, sexe, date_naissance",ui->comboBox_2->currentText()));

}

void MainWindow::on_pushButton_2_clicked()
{
    stats stats_window(this);
    stats_window.setModal(true);
    stats_window.show();
    stats_window.exec();
    QDialog d;
}

void MainWindow::on_pushButton_3_clicked()
{
    static int turn=1;

    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/wiou.wav");

    if (turn==1)
    {
        contract_animation->start();
        ui->pushButton_2->setText("Expand");
    }

    else
    {
        expand_animation->start();
        ui->pushButton_2->setText("Contract");
    }
    turn*=-1;
}

void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    if (!ui->checkBox_cin->isChecked() && ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked() && !ui->checkBox_mail->isChecked())
        ui->tableView->setModel(tmpinvite.rechercher_nom(arg1));
    else if (ui->checkBox_cin->isChecked() && !ui->checkBox_nom->isChecked() && !ui->checkBox_sexe->isChecked() && !ui->checkBox_date->isChecked() && !ui->checkBox_mail->isChecked())
        ui->tableView->setModel(tmpinvite.rechercher_cin(arg1));
}
