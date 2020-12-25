#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stat.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Regex (pour contrôle de saisie)
    mail_regex=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    cin_regex=QRegExp("[0-9]{8}$");
    chaine_regex=QRegExp("[a-zA-Z]{2,20}$");
    telephone_regex=cin_regex=QRegExp("[0-9]{8}$");

    nom_regex=QRegExp("[a-zA-Z]+$");
    prenom_regex=QRegExp("[a-zA-Z]+$");
    budget_regex=QRegExp("([0-9]+)*[.]*[0-9]+$");
    tel_regex=QRegExp("[0-9]+$");



    //Controle saisie avec LineEdit_invite/Qdate_recherche_invite
    ui->dateDeNaissanceDateEdit_invite->setMaximumDate(QDate::currentDate().addYears(-18));
    ui->date_recherche_invite->setMaximumDate(QDate::currentDate().addYears(-18));
    ui->cINLineEdit_invite->setMaxLength(8);
    ui->tLPhoneLineEdit_invite->setMaxLength(8);

    //Looks
    ui->groupBox_ajouter_table->setMaximumWidth(100);
    ui->groupBox_ajouter_invites->setMaximumWidth(400);
    QPixmap bkgnd("D:/Users/dhiaa/Desktop/gestion_invités/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    //palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->cINLineEdit_invite->setPlaceholderText("CIN ...");
    ui->nomLineEdit_invite->setPlaceholderText("Nom ...");
    ui->prNomLineEdit_invite->setPlaceholderText("Prénom ...");
    ui->eMailLineEdit_invite->setPlaceholderText("E-mail ...");
    ui->tLPhoneLineEdit_invite->setPlaceholderText("Téléphone ...");

    ui->nombrePlacesLineEdit_table->setPlaceholderText("Nombre places ...");
    ui->nomServeurLineEdit_table->setPlaceholderText("Nom serveur");

    ui->lineEdit_Ref_p->setPlaceholderText("Reference ...");
    ui->lineEdit_quantite_p->setPlaceholderText("Quantite ...");
    ui->lineEdit_Prix_p->setPlaceholderText("Prix ...");
    ui->lineEdit_CIN_f->setPlaceholderText("CIN...");
    ui->lineEdit_RIB_f->setPlaceholderText("RIB");
    ui->lineEdit_tel_f->setPlaceholderText("Numero de telephone");


    //Affichage des tableaux au lancement
    ui->tableView_invite->setModel(tmpinvite.afficher());
    ui->tableView_table->setModel(tmptable.afficher());
    ui->tableView_client->setModel(tempclient.afficher());
    ui->tableView_reservation->setModel(tempreservation.afficher());
    ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());
    ui->tableView_departement->setModel(tmpdepartement.afficher());
    ui->tableView_personnel->setModel(tmppersonnel.afficher());
    ui->tableView_Produits->setModel(tmpprod.afficher_p());
    ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());


    //Selection tableView_invite
    ui->tableView_invite->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_invite->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_client->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_reservation->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_reservation->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_notifications->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_notifications->setSelectionMode(QAbstractItemView::SingleSelection); 
    ui->tableView_personnel->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_personnel->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_departement->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_departement->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_Produits->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Produits->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_Fournisseurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Fournisseurs->setSelectionMode(QAbstractItemView::SingleSelection);

    //Animations
    contract_animation = new QPropertyAnimation(ui->groupBox_ajouter_invites,"maximumWidth");
    contract_animation->setDuration(400);
    contract_animation->setStartValue(300);
    contract_animation->setEndValue(80);
    expand_animation = new QPropertyAnimation(ui->groupBox_ajouter_invites,"maximumWidth");
    expand_animation->setDuration(400);
    expand_animation->setStartValue(80);
    expand_animation->setEndValue(300);
    ui->contract_invite->setText("Contract");


    contract_animation_2 = new QPropertyAnimation(ui->groupBox_ajouter_table,"maximumWidth");
    contract_animation_2->setDuration(400);
    contract_animation_2->setStartValue(300);
    contract_animation_2->setEndValue(80);
    expand_animation_2 = new QPropertyAnimation(ui->groupBox_ajouter_table,"maximumWidth");
    expand_animation_2->setDuration(400);
    expand_animation_2->setStartValue(80);
    expand_animation_2->setEndValue(300);
    ui->contract_table->setText("Contract");

    expand_animation->start();
    expand_animation_2->start();

    ui->passwordLineEdit_login->setEchoMode(QLineEdit::Password);
    ui->passwordLineEdit_signup->setEchoMode(QLineEdit::Password);

    int ret=A.connect_arduino();
    switch (ret)
    {
    case 0:
        qDebug() << "arduino is available and connected to:" << A.getarduino_port_name();
        break;
    case 1:
        qDebug() << "arduino is available but not connected to:" << A.getarduino_port_name();
        break;
    case -1:
        qDebug() << "arduino is not available";
        break;
    }

    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



    int nb=ui->tableView_table->model()->rowCount();

    for (int i=0;i<nb;i++)
    {
        QString num_table = ui->tableView_table->model()->index(i, 0).data().toString();
        ui->comboBox_tables->addItem(num_table);
    }

    QSqlQueryModel *model2=new QSqlQueryModel();
        QString id;
        model2->setQuery("select * from CLIENT");
    ui->comboBox_reservations->setModel(model2);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Dhia_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Iheb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Barkia_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Elaa_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Sara_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_login_button_clicked()
{


    if (log->sign_in(ui->usernameLineEdit_login->text(),ui->passwordLineEdit_login->text()))
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->usernameLineEdit_login->clear();
        ui->passwordLineEdit_login->clear();

    }
    else
        QMessageBox::warning(this,"Login","Erreur de login");
}

void MainWindow::on_sign_up_button_clicked()
{

    if (log->sign_up(ui->usernameLineEdit_signup->text(),ui->passwordLineEdit_signup->text()))
        ui->stackedWidget->setCurrentIndex(1);
    else
        QMessageBox::warning(this,"Sign-up","Erreur d'insciption");
}

void MainWindow::on_confirmer_chan_mdp_clicked()
{
    qDebug() << log->get_current_user();

    if (ui->confirmerNouveauMotDePasseLineEdit->text()==ui->nouveauMotDePasseLineEdit->text())
    {
        if (ui->ancienMotDePasseLineEdit->text()!="" && ui->confirmerNouveauMotDePasseLineEdit->text()!="")
        {
            qDebug() << log->get_current_user();
            bool test=log->modifier_mdp(log->get_current_user(),ui->ancienMotDePasseLineEdit->text(),ui->nouveauMotDePasseLineEdit->text());

            if (!test)
                QMessageBox::warning(this,"Changement du MDP","Erreur lors du changement du MDP");
            else
            {
                ui->ancienMotDePasseLineEdit->clear();
                ui->nouveauMotDePasseLineEdit->clear();
                ui->confirmerNouveauMotDePasseLineEdit->clear();
            }
        }
        else
            QMessageBox::warning(this,"Changement du MDP","Veuillez remplir tous les champs");
    }
    else
        QMessageBox::warning(this,"Changement du MDP","Les deux mots de passe ne sont pas identiques");
}


void MainWindow::on_logout_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ajouter_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");

    bool mail_verif = mail_regex.exactMatch(ui->eMailLineEdit_invite->text());
    bool cin_verif=cin_regex.exactMatch(ui->cINLineEdit_invite->text());
    bool nom_verif=chaine_regex.exactMatch(ui->nomLineEdit_invite->text());
    bool prenom_verif=chaine_regex.exactMatch(ui->prNomLineEdit_invite->text());
    bool telephone_verif=telephone_regex.exactMatch(ui->tLPhoneLineEdit_invite->text());
    bool telephone_verif_2=true;

    if (ui->tLPhoneLineEdit_invite->text().at(0)!='2' && ui->tLPhoneLineEdit_invite->text().at(0)!='5' && ui->tLPhoneLineEdit_invite->text().at(0)!='9' && ui->tLPhoneLineEdit_invite->text().at(0)!='7')
        telephone_verif_2=false;


    if ( ui->cINLineEdit_invite->text()!= "" &&
         ui->nomLineEdit_invite->text()!="" &&
         ui->prNomLineEdit_invite->text() != "" &&
         ui->eMailLineEdit_invite->text()!= "")
    {
        if(cin_verif && nom_verif && prenom_verif && telephone_verif && telephone_verif_2 && mail_verif)
        {
            QString cin=ui->cINLineEdit_invite->text();
            QString nom= ui->nomLineEdit_invite->text();
            QString prenom= ui->prNomLineEdit_invite->text();
            QString mail= ui->eMailLineEdit_invite->text();
            QString sexe = ui->sexeComboBox->currentText();
            QDate date_naissance = ui->dateDeNaissanceDateEdit_invite->date();
            QString telephone=ui->tLPhoneLineEdit_invite->text();


            invite inv(cin,nom,prenom,date_naissance,mail,sexe,telephone);

            bool test=inv.ajouter();

            if (test)
                ui->tableView_invite->setModel(tmpinvite.afficher());


            ui->cINLineEdit_invite->setText("");
            ui->nomLineEdit_invite->setText("");
            ui->prNomLineEdit_invite->setText("");
            ui->eMailLineEdit_invite->setText("");
            ui->tLPhoneLineEdit_invite->setText("");

            ui->cINLineEdit_invite->setStyleSheet("color: black");
            ui->nomLineEdit_invite->setStyleSheet("color: black");
            ui->prNomLineEdit_invite->setStyleSheet("color: black");
            ui->eMailLineEdit_invite->setStyleSheet("color: black");
            ui->tLPhoneLineEdit_invite->setStyleSheet("color: black");
        }

        else
        {

            if (!mail_verif)
            {
                //QMessageBox::warning(this,"Erreur lors de l'ajout","E-mail invalid");
                ui->eMailLineEdit_invite->setStyleSheet("color: red");
            }
            if (!cin_verif)
            {
                //QMessageBox::warning(this,"Erreur lors de l'ajout","CIN invalid");
                ui->cINLineEdit_invite->setStyleSheet("color: red");
            }
            if (!telephone_verif || !telephone_verif_2)
            {
                //QMessageBox::warning(this,"Erreur lors de l'ajout","Téléphone invalid");
                ui->tLPhoneLineEdit_invite->setStyleSheet("color: red");
            }
            if (!nom_verif)
            {
                //QMessageBox::warning(this,"Erreur lors de l'ajout","Nom invalid");
                ui->nomLineEdit_invite->setStyleSheet("color: red");
            }
            if (!prenom_verif)
            {
                //QMessageBox::warning(this,"Erreur lors de l'ajout","Prénom invalid");
                ui->prNomLineEdit_invite->setStyleSheet("color: red");
            }

        }


    }
    else
    {
        QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez compléter tous les champs");
    }


}

void MainWindow::on_reset_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    ui->cINLineEdit_invite->setText("");
    ui->nomLineEdit_invite->setText("");
    ui->prNomLineEdit_invite->setText("");
    ui->eMailLineEdit_invite->setText("");
}

void MainWindow::on_exporter_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
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
    QString pdf="<br> <img src='D:/Users/dhiaa/Desktop/gestion_invités/background.jpeg' height='84' width='288'/> <h1  style='color:red'>       LISTE DES INVITES  <br></h1>\n <br> <table>  <tr>  <th> CIN </th> <th> NOM </th> <th> PRENOM </th> <th> DATE NAISSANCE  </th> <th>E-MAIL </th>  </tr>" ;


    while ( q.next()) {

        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>" ;

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}

void MainWindow::on_modifier_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    if (ui->modifier_invite->isChecked())
    {

        ui->modifier_invite->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("INVITES");
        tableModel->select();
        ui->tableView_invite->setModel(tableModel);
    }
    else
    {
        ui->modifier_invite->setText("Modifier");
        ui->tableView_invite->setModel(tmpinvite.afficher());

    }

}

void MainWindow::on_supprimer_invite_clicked()
{

    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QItemSelectionModel *select = ui->tableView_invite->selectionModel();

    QString cin =select->selectedRows(0).value(0).data().toString();

    if(tmpinvite.supprimer(cin))
    {
        ui->tableView_invite->setModel(tmpinvite.afficher());
        ui->statusbar->showMessage("Invité supprimé");
    }


}

void MainWindow::on_recherche_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QString nom=ui->lineEdit_recherche_invite->text();
    QDate date=ui->date_recherche_invite->date();
    QString sexe;
    QString email=ui->lineEdit_recherche_invite->text();
    if (ui->radio_button_homme->isChecked())
        sexe=ui->radio_button_homme->text();
    else if (ui->radio_button_femme->isChecked())
        sexe=ui->radio_button_femme->text();

    if (ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
    {

        QSqlQueryModel *verif_combinaison=tmpinvite.rechercher_combinaison_all(nom,sexe,date);
        if (verif_combinaison!=nullptr)
        {
            ui->tableView_invite->setModel(verif_combinaison);
        }

    }
    else if (!ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_sexe=tmpinvite.rechercher_sexe(sexe);
        if (verif_sexe!=nullptr)
        {
            ui->tableView_invite->setModel(verif_sexe);
        }
    }
    else if (!ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_date=tmpinvite.rechercher_date(date);
        if (verif_date!=nullptr)
        {
            ui->tableView_invite->setModel(verif_date);
        }
    }
    else if (ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_nom=tmpinvite.rechercher_nom(nom);
        if (verif_nom!=nullptr)
        {
            ui->tableView_invite->setModel(verif_nom);
        }
    }
    else if (ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_nom_sexe=tmpinvite.rechercher_combinaison_nom_sexe(nom,sexe);
        if (verif_nom_sexe!=nullptr)
        {
            ui->tableView_invite->setModel(verif_nom_sexe);
        }
    }
    else if (!ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_sexe_date=tmpinvite.rechercher_combinaison_sexe_date(sexe,date);
        if (verif_sexe_date!=nullptr)
        {
            ui->tableView_invite->setModel(verif_sexe_date);
        }
    }
    else if (ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
    {
        QSqlQueryModel *verif_nom_date=tmpinvite.rechercher_combinaison_nom_date(nom,date);
        if (verif_nom_date!=nullptr)
        {
            ui->tableView_invite->setModel(verif_nom_date);
        }
    }

    else if (!ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked() && ui->checkBox_mail_invite)
    {
        QSqlQueryModel *verif_mail=tmpinvite.rechercher_email(email);
        if (verif_mail!=nullptr)
        {
            ui->tableView_invite->setModel(verif_mail);
        }
    }

}

void MainWindow::on_imprimer_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_invite->model()->rowCount();
    const int columnCount = ui->tableView_invite->model()->columnCount();

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
        if (!ui->tableView_invite->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_invite->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_invite->isColumnHidden(column)) {
                QString data = ui->tableView_invite->model()->data(ui->tableView_invite->model()->index(row, column)).toString().simplified();
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


void MainWindow::on_afficher_tout_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    ui->tableView_invite->setModel(tmpinvite.afficher());
}

void MainWindow::on_envoyer_clicked()
{
    //    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    //    QItemSelectionModel *select = ui->tableView_invite->selectionModel();

    //    QString email_recipient =select->selectedRows(4).value(0).data().toString();
    //    QString nom_recipient =select->selectedRows(1).value(0).data().toString();
    //    QString sexe_recipient =select->selectedRows(5).value(0).data().toString();


    //    QDialog *d=new Dialog(email_recipient,nom_recipient,sexe_recipient,this);
    //    d->show();
    //    d->exec();
}


void MainWindow::on_trier_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    if (ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("nom",ui->ordre_invite->currentText()));
    else if (!ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("sexe",ui->ordre_invite->currentText()));
    else if (!ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("date_naissance",ui->ordre_invite->currentText()));
    else if (ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("nom, sexe",ui->ordre_invite->currentText()));
    else if (ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("nom, date_naissance",ui->ordre_invite->currentText()));
    else if (!ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("sexe, date_naissance",ui->ordre_invite->currentText()));
    else if (ui->checkBox_nom_invite->isChecked() && ui->checkBox_sexe_invite->isChecked() && ui->checkBox_date_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("nom, sexe, date_naissance",ui->ordre_invite->currentText()));
    else if (ui->checkBox_cin_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("cin",ui->ordre_invite->currentText()));
    else if (ui->checkBox_mail_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.trier("mail",ui->ordre_invite->currentText()));
}

void MainWindow::on_stats_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    stats stats_window(this);
    stats_window.setModal(true);
    stats_window.show();
    stats_window.exec();
    QDialog d;
}

void MainWindow::on_contract_invite_clicked()
{
    static int turn=1;
    if (turn==1)
    {
        contract_animation->start();
        ui->contract_invite->setText("Expand");
    }
    else
    {
        expand_animation->start();
        ui->contract_invite->setText("Contract");
    }
    turn*=-1;
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
}

void MainWindow::on_lineEdit_recherche_invite_textChanged(const QString &arg1)
{
    if (!ui->checkBox_cin_invite->isChecked() && ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked() && !ui->checkBox_mail_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.rechercher_nom(arg1));
    else if (ui->checkBox_cin_invite->isChecked() && !ui->checkBox_nom_invite->isChecked() && !ui->checkBox_sexe_invite->isChecked() && !ui->checkBox_date_invite->isChecked() && !ui->checkBox_mail_invite->isChecked())
        ui->tableView_invite->setModel(tmpinvite.rechercher_cin(arg1));
}

void MainWindow::on_ajouter_table_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    int nb=ui->nombrePlacesLineEdit_table->text().toInt();
    QString nom=ui->nomServeurLineEdit_table->text();
    QString ref=ui->reference_table->text();
    table table(nb,nom,ref);

    bool nom_verif=chaine_regex.exactMatch(ui->nomServeurLineEdit_table->text());
    bool nombre_verif=ui->nombrePlacesLineEdit_table->text().toInt()<7 && ui->nombrePlacesLineEdit_table->text().toInt()>0;

    if (ui->nombrePlacesLineEdit_table->text()!="" && ui->nomServeurLineEdit_table->text()!="")
    {
        if (!nom_verif)
            QMessageBox::warning(this,"Erreur lors de l'ajout","Nom invalid");
        else if (!nombre_verif)
            QMessageBox::warning(this,"Erreur lors de l'ajout","Nombre invalid");
        else
        {
            bool test=table.ajouter();

            if (test)
            {

                int nb=ui->tableView_table->model()->rowCount();
                ui->comboBox_tables->clear();

                for (int i=0;i<nb;i++)
                {
                    QString num_table = ui->tableView_table->model()->index(i, 0).data().toString();
                    ui->comboBox_tables->addItem(num_table);
                }
                ui->tableView_table->setModel(tmptable.afficher());

            }

            ui->nombrePlacesLineEdit_table->setText("");
            ui->nomServeurLineEdit_table->setText("");
        }
    }
    else
        QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez remplir tous les champs");


}


void MainWindow::on_modifier_table_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    if (ui->modifier_table->isChecked())
    {

        ui->modifier_table->setText("Modifiable");
        QSqlTableModel *tableModel_2= new QSqlTableModel();
        tableModel_2->setTable("TABLES");
        tableModel_2->select();
        ui->tableView_table->setModel(tableModel_2);
    }
    else
    {
        ui->modifier_table->setText("Modifier");
        ui->tableView_table->setModel(tmptable.afficher());

    }
}

void MainWindow::on_supprimer_table_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QItemSelectionModel *select_2 = ui->tableView_table->selectionModel();

    int num =select_2->selectedRows(0).value(0).data().toInt();
    bool existe=tmptable.invite_existe(num);
    if (!existe)
    {
        bool test=tmptable.supprimer(num);
        if (test)
        {

            ui->tableView_table->setModel(tmptable.afficher());
            ui->statusbar->showMessage("Table supprimée");
            int nb=ui->tableView_table->model()->rowCount();
            ui->comboBox_tables->clear();

            for (int i=0;i<nb;i++)
            {
                QString num_table = ui->tableView_table->model()->index(i, 0).data().toString();
                ui->comboBox_tables->addItem(num_table);
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur lors de la suppression","Table Contient des invites");
    }
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    ui->tableView_table->setModel(tmptable.recherche(arg1));
}

void MainWindow::on_trier_table_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    if (ui->checkBox_numero->isChecked() && !ui->checkBox_nombre->isChecked() && !ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("numero",ui->ordre_table->currentText()));
    else if (!ui->checkBox_numero->isChecked() && ui->checkBox_nombre->isChecked() && !ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("nb_places",ui->ordre_table->currentText()));
    else if (!ui->checkBox_numero->isChecked() && !ui->checkBox_nombre->isChecked() && ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("nom_serveur",ui->ordre_table->currentText()));
    else if (ui->checkBox_numero->isChecked() && ui->checkBox_nombre->isChecked() && !ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("numero, nb_places",ui->ordre_table->currentText()));
    else if (ui->checkBox_numero->isChecked() && !ui->checkBox_nombre->isChecked() && ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("numero, nom_serveur",ui->ordre_table->currentText()));
    else if (!ui->checkBox_numero->isChecked() && ui->checkBox_nombre->isChecked() && ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("nb_places, nom_serveur",ui->ordre_table->currentText()));
    else if (ui->checkBox_numero->isChecked() && ui->checkBox_nombre->isChecked() && ui->checkBox_nomserv->isChecked())
        ui->tableView_table->setModel(tmptable.trier("numero, nb_places, nom_serveur",ui->ordre_table->currentText()));
}

void MainWindow::on_affecter_table_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");


    QItemSelectionModel *select_affect = ui->tableView_invite->selectionModel();
    QString cin =select_affect->selectedRows(0).value(0).data().toString();


    //int nb_table= QInputDialog::getText(this, "Affectation de table", "Saisir le numéro de la table?").toInt();
    int nb_table= ui->comboBox_tables->currentText().toInt();
    int test=tmpinvite.affecter_table(cin,nb_table,6);
    if (!test)
        ui->tableView_invite->setModel(tmpinvite.afficher());
    else if (test==1)
        QMessageBox::warning(this,"Erreur lors de l'affectation","Table Inéxistante");
    else if (test==2)
        QMessageBox::warning(this,"Erreur lors de l'affectation","Table Pleine");

}

void MainWindow::on_contract_table_clicked()
{
    static int turn=1;



    if (turn==1)
    {
        contract_animation_2->start();
        ui->contract_table->setText("Expand");
    }

    else
    {
        expand_animation_2->start();
        ui->contract_table->setText("Contract");
    }
    turn*=-1;
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
}

//void MainWindow::on_imprimer_invite_clicked()
//{
//    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
//    QString strStream;
//    QTextStream out(&strStream);

//    const int rowCount = ui->tableView_invite->model()->rowCount();
//    const int columnCount = ui->tableView_invite->model()->columnCount();

//    out <<  "<html>\n"
//            "<head>\n"
//            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
//         <<  QString("<title>%1</title>\n").arg("Title")
//          <<  "</head>\n"
//              "<body bgcolor=#ffffff link=#5000A0>\n"
//              "<table border=1 cellspacing=0 cellpadding=2>\n";

//    // headers
//    out << "<thead><tr bgcolor=#f0f0f0>";
//    for (int column = 0; column < columnCount; column++)
//        if (!ui->tableView_invite->isColumnHidden(column))
//            out << QString("<th>%1</th>").arg(ui->tableView_invite->model()->headerData(column, Qt::Horizontal).toString());
//    out << "</tr></thead>\n";

//    // data table
//    for (int row = 0; row < rowCount; row++) {
//        out << "<tr>";
//        for (int column = 0; column < columnCount; column++) {
//            if (!ui->tableView_invite->isColumnHidden(column)) {
//                QString data = ui->tableView_invite->model()->data(ui->tableView_invite->model()->index(row, column)).toString().simplified();
//                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
//            }
//        }
//        out << "</tr>\n";
//    }
//    out <<  "</table>\n"
//            "</body>\n"
//            "</html>\n";

//    QTextDocument *document = new QTextDocument();
//    document->setHtml(strStream);

//    QPrinter printer;

//    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
//    if (dialog->exec() == QDialog::Accepted) {
//        document->print(&printer);
//    }

//    delete document;
//}

void MainWindow::on_reset_table_clicked()
{
    ui->nombrePlacesLineEdit_table->setText("");
    ui->nomServeurLineEdit_table->setText("");
}

void MainWindow::on_aucun_clicked()
{
    ui->checkBox_cin_invite->setChecked(false);
    ui->checkBox_mail_invite->setChecked(false);
    ui->checkBox_date_invite->setChecked(false);
    ui->checkBox_sexe_invite->setChecked(false);
    ui->checkBox_nom_invite->setChecked(false);

}

void MainWindow::on_aucun_table_clicked()
{
    ui->checkBox_nombre->setChecked(false);
    ui->checkBox_nomserv->setChecked(false);
    ui->checkBox_numero->setChecked(false);
}


//IHEB


void MainWindow::on_ajouter_client_clicked()
{
    MainWindow w;

    bool mail_verif = mail_regex.exactMatch(ui->email_client->text());
    bool nom_verif=nom_regex.exactMatch(ui->prenom_client->text());
    bool prenom_verif=prenom_regex.exactMatch((ui->nom_client->text()));
    bool tel_verif=tel_regex.exactMatch(ui->tel_client->text());
    bool budget_verif=budget_regex.exactMatch(ui->budget_client->text());
    bool cin_verif=cin_regex.exactMatch(ui->cin_client->text());

    QString nom;
    int CIN=ui->cin_client->text().toInt();
    nom= ui->nom_client->text();
    bool test2=true;
    QString prenom= ui->prenom_client->text();
    QDate date_naissance = ui->date_client->date();
    QString mail=ui->email_client->text();
    QString telephone=ui->tel_client->text();
    float budget=ui->budget_client->text().toFloat();
    // qDebug()<<CIN<<nom<<prenom<<date_naissance<<mail<<telephone<<budget;
    if (!mail_verif || !nom_verif || !cin_verif || !budget_verif || !prenom_verif || !tel_verif)
    {
        QMessageBox::warning(this,"Erreur lors de l'ajout","format non valide");
        test2=false;

    }
    else
    {
        /* mail=ui->email_client->text();
         nom= ui->nom_client->text();*/
        test2=true;


    }

    client c(CIN,nom,prenom,date_naissance,telephone,mail,budget);
    if(test2)
    {
        bool test=c.ajouter();
        if(test)
        {

            QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
            ui->tableView_client->setModel(tempclient.afficher());

        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_modifier_client_clicked()
{


    if (ui->modifier_client->isChecked())
    {
        //ui->pushButton_4->setDisabled(true);
        ui->modifier_client->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("CLIENT");

        tableModel->select();
        ui->tableView_client->setModel(tableModel);


    }
    else
    {
        ui->modifier_client->setText("modifier client");
        ui->tableView_client->setModel(tempclient.afficher());

    }


}

void MainWindow::on_supprimer_client_clicked()
{
    QItemSelectionModel *select=ui->tableView_client->selectionModel();
    int CIN =select->selectedRows(0).value(0).data().toInt();
    QString cin_2 =select->selectedRows(0).value(0).data().toString();


    int ref=select->selectedRows(5).value(0).data().toInt();

    qDebug()<< ref;

    if (tempreservation.supprimer_cin(cin_2))
    {
        ui->tableView_reservation->setModel(tempreservation.afficher());
    }



    if(tempclient.supprimer(CIN))
    {
        ui->tableView_client->setModel(tempclient.afficher());

        //w.show();
        QMessageBox::information(nullptr, QObject::tr("ajout client"),
                                 QObject::tr("suppression réussie\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                              QObject::tr("suppression échouée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_recherche_client_textChanged(const QString &arg1)
{

    ui->tableView_client->setModel(tempclient.rechercheclient(arg1));

    //    if (arg1=="")
    //    {
    //        ui->tableView_client->setModel(tempclient.afficher());
    //    }
    //    else
    //    {
    //        ui->tableView_client->setModel(tempclient.rechercheclient(arg1));
    //    }
}


void MainWindow::on_exporter_client_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_clients.pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM CLIENT ");
    q.exec();
    QString pdf="<br> <img src='D:/Users/dhiaa/Desktop/gestion_invités/background.jpeg' height='84' width='288'/> <h1  style='color:red'>       LISTE DES CLIENTS  <br></h1>\n <br> <table>  <tr>  <th> CIN </th> <th> NOM </th> <th> PRENOM </th> <th> DATE NAISSANCE  </th> <th>E-MAIL </th>  </tr>  <th>BUDGET </th>  </tr>" ;


    while ( q.next()) {

        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>  <td>"+q.value(5).toString()+"       </td>  " ;

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void MainWindow::on_imprimer_client_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_client->model()->rowCount();
    const int columnCount = ui->tableView_client->model()->columnCount();

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
        if (!ui->tableView_client->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_client->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_client->isColumnHidden(column)) {
                QString data = ui->tableView_client->model()->data(ui->tableView_client->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_trier_client_clicked()
{
    qDebug() << "clicked";
    if (ui->checkBox_nom_client->isChecked() && !ui->checkBox_prenom_client->isChecked() && !ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("nom",ui->ordre_client->currentText()));
    else if (!ui->checkBox_nom_client->isChecked() && ui->checkBox_prenom_client->isChecked() && !ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("prenom",ui->ordre_client->currentText()));
    else if (!ui->checkBox_nom_client->isChecked() && !ui->checkBox_prenom_client->isChecked() && ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("budget",ui->ordre_client->currentText()));
    else if (ui->checkBox_nom_client->isChecked() && ui->checkBox_prenom_client->isChecked() && !ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("nom,prenom",ui->ordre_client->currentText()));
    else if (ui->checkBox_nom_client->isChecked() && !ui->checkBox_prenom_client->isChecked() && ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("nom,budget",ui->ordre_client->currentText()));
    else if (!ui->checkBox_nom_client->isChecked() && ui->checkBox_prenom_client->isChecked() && ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("prenom,budget",ui->ordre_client->currentText()));
    else if (ui->checkBox_nom_client->isChecked() && ui->checkBox_prenom_client->isChecked() && ui->checkBox_budget_client->isChecked())
        ui->tableView_client->setModel(tempclient.trier("nom,prenom,budget",ui->ordre_client->currentText()));


}

void MainWindow::on_ajouter_reservation_clicked()
{

    QString reference= ui->reference_reservation->text();
    QDate date_reservation = ui->date_reservation->date();
    QString cin_client=ui->comboBox_reservations->currentText();

    float prix= ui->prix_reservation->text().toFloat();
    int nb_invites=ui->nb_invites_reservation->text().toInt();

    QString localisation= ui->localisation_reservation->text();

    qDebug()<<reference<<date_reservation<<prix<<nb_invites<<localisation;

    reservation r(reference,date_reservation,prix,nb_invites,localisation,cin_client);
    bool test=r.ajouter();
    if(test)
    {
        QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
        ui->tableView_reservation->setModel(tempreservation.afficher());

        //int nb=ui->tableView_reservation->model()->rowCount();


        QSqlQueryModel *model2=new QSqlQueryModel();
            QString id;
            model2->setQuery("select * from CLIENT");
        ui->comboBox_reservations->removeItem(ui->comboBox_reservations->currentIndex());
        ui->comboBox_reservations->setModel(model2);



    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_modifier_reservation_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    if (ui->modifier_reservation->isChecked())
    {

        ui->modifier_reservation->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("RESERVATION");
        tableModel->select();
        ui->tableView_reservation->setModel(tableModel);
    }
    else
    {
        ui->modifier_reservation->setText("Modifier");
        ui->tableView_reservation->setModel(tempreservation.afficher());

    }
}

void MainWindow::on_supprimer_reservation_clicked()
{
    QItemSelectionModel *select=ui->tableView_reservation->selectionModel();
    int CIN =select->selectedRows(0).value(0).data().toInt();
    bool test=tempreservation.supprimer(CIN);

    if(test)
    {
        ui->tableView_reservation->setModel(tempreservation.afficher());

        //w.show();
        QMessageBox::information(nullptr, QObject::tr("ajout client"),
                                 QObject::tr("suppression réussie\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                              QObject::tr("suppression échouée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_trier_reservation_clicked()
{
    qDebug() << "clicked";

    if (ui->checkBox_localisation_reservation->isChecked() && !ui->checkBox_prix_reservation->isChecked() && !ui->checkBox_nb_invites_reservation->isChecked())
    {
        ui->tableView_reservation->setModel(tempreservation.trier("localisation",ui->ordre_reservation->currentText()));
        qDebug() << "if";
    }
    else if (!ui->checkBox_localisation_reservation->isChecked() && ui->checkBox_prix_reservation->isChecked() && !ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("prix",ui->ordre_reservation->currentText()));
    else if (!ui->checkBox_localisation_reservation->isChecked() && !ui->checkBox_prix_reservation->isChecked() && ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("nb_invites",ui->ordre_reservation->currentText()));
    else if (ui->checkBox_localisation_reservation->isChecked() && ui->checkBox_prix_reservation->isChecked() && !ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("localisation,prix",ui->ordre_reservation->currentText()));
    else if (ui->checkBox_localisation_reservation->isChecked() && !ui->checkBox_prix_reservation->isChecked() && ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("localisation,nb_invites",ui->ordre_reservation->currentText()));
    else if (!ui->checkBox_localisation_reservation->isChecked() && ui->checkBox_prix_reservation->isChecked() && ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("prix,nb_invites",ui->ordre_reservation->currentText()));
    else if (ui->checkBox_localisation_reservation->isChecked() && ui->checkBox_prix_reservation->isChecked() && ui->checkBox_nb_invites_reservation->isChecked())
        ui->tableView_reservation->setModel(tempreservation.trier("localisation,prix,nb_invites",ui->ordre_reservation->currentText()));
}

void MainWindow::on_recherche_reservation_textChanged(const QString &arg1)
{
    ui->tableView_reservation->setModel(tempreservation.recherchereservation(arg1));
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if (data!="#")
        cin_recu+=data;
    else
    {
        //ui->tableView_notifications->setModel(tmpinvite.rechercher_cin(cin_recu));
        QMessageBox::information(nullptr, QObject::tr("Notification"),
                                 QObject::tr("Nouveau invité à la porte\n"), QMessageBox::Ok);

        tmpinvite.update(cin_recu,"permission","pending");

         ui->tableView_invite->setModel(tmpinvite.afficher());
         tmpinvite.update_num_entree(cin_recu,ui->tableView_notifications->model()->rowCount());
         ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());


        cin_recu="";
    }



}
void MainWindow::on_refuser_clicked()
{
    QItemSelectionModel *select=ui->tableView_notifications->selectionModel();
    QString cin= select->selectedRows(0).value(0).data().toString();
    tmpinvite.update(cin,"permission","refuse");
    ui->tableView_invite->setModel(tmpinvite.afficher());
    A.write_to_arduino("Acces Refuse");
    ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());

}


void MainWindow::on_accepter_clicked()
{
    QItemSelectionModel *select=ui->tableView_notifications->selectionModel();
    QString cin= select->selectedRows(0).value(0).data().toString();
    QString nom =select->selectedRows(1).value(0).data().toString();
    QString num_table=select->selectedRows(7).value(0).data().toString();
    QString email_invite=select->selectedRows(4).value(0).data().toString();

    Smtp* smtp = new Smtp("dhia.abdelli1@esprit.tn", "Dpstream1", "smtp.gmail.com", 465);

    QString sexe=select->selectedRows(5).value(0).data().toString();

    QString msg="";

    if (sexe=="Femme")
        msg= "Bonjour, Mme. "+nom+" Votre num de table est: "+num_table;
    else if (sexe=="Homme")
        msg= "Bonjour, Mr. "+nom+" Votre num de table est: "+num_table;


    const char * p= msg.toStdString().c_str();


    A.write_to_arduino(p);

    tmpinvite.update(cin,"permission","accepte");
    ui->tableView_invite->setModel(tmpinvite.afficher());
    //ui->tableView_notifications->setModel(tmpinvite.rechercher_cin(cin));
    ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());

    //ui->tableView_invite->setModel(tmpinvite.update(cin,"permission","accepté"));



    smtp->sendMail("dhia.abdelli1@esprit.tn", email_invite , "Notification d'entrée" ,"Bonjour "+nom+",\nBienvenue à la salle. Votre numéro de table est "+num_table+".\nNous vous souhaitons une bonne soirée.\n\nCordialement,\nBoudinar Wedding Planner.\n");


}

void MainWindow::on_enter_clicked()
{
    QString cin= QInputDialog::getText(this, "SAISIE", "Saisir CIN");
    ui->tableView_notifications->setModel(tmpinvite.rechercher_cin(cin));
}

void MainWindow::on_envoyer_invite_clicked()
{
    QSound::play("D:/Users/dhiaa/Desktop/gestion_invités/click.wav");
    QItemSelectionModel *select = ui->tableView_invite->selectionModel();

    QString email_recipient =select->selectedRows(4).value(0).data().toString();
    QString nom_recipient =select->selectedRows(1).value(0).data().toString();
    QString sexe_recipient =select->selectedRows(5).value(0).data().toString();


    QDialog *d=new Dialog(email_recipient,nom_recipient,sexe_recipient,this);
    d->show();
    d->exec();
}

void MainWindow::on_tabWidget_2_tabBarClicked(int index)
{
    QSqlQueryModel *model2=new QSqlQueryModel();
        QString id;
        model2->setQuery("select * from CLIENT");
    ui->comboBox_reservations->setModel(model2);
}

void MainWindow::on_entrer_clicked()
{
    QString cin_recu=ui->enter_cin->text();


   tmpinvite.update(cin_recu,"permission","pending");

    ui->tableView_invite->setModel(tmpinvite.afficher());



    tmpinvite.update_num_entree(cin_recu,ui->tableView_notifications->model()->rowCount());
    ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());


    cin_recu="";
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    ui->tableView_notifications->setModel(tmpinvite.afficher_notifications());
}

void MainWindow::on_ajouter_departement_clicked()
{


        QString reference= ui->lineEdit_reference->text();
        QString nom= ui->lineEdit_nomm->text();
        int nb_employes= ui->lineEdit_nbemployes->text().toInt();

        departement d(reference,nom,nb_employes);
        bool test=d.ajouter();


        if(test)

      {ui->tableView_departement->setModel(tmpdepartement.afficher());
              ui->comboBox_ref_deppersonnel->setModel(tmpdepartement.refdep());
        QMessageBox::information(nullptr, QObject::tr("ajout departement"),
                                  QObject::tr("departement ajoutè.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::information(nullptr, QObject::tr("ajout departement"),
                                  QObject::tr("ajout echouèe.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);}



void MainWindow::on_reset_departement_clicked()
{
    ui->lineEdit_nomm->setText("");
    ui->lineEdit_nbemployes->setText("");
    ui->lineEdit_reference->setText("");
}



void MainWindow::on_modifier_departement_clicked()
{
    {

              QString reference= ui->lineEdit_reference->text();
              QString nom= ui->lineEdit_nomm->text();
              int nb_employes = ui->lineEdit_nbemployes->text().toInt();

                     departement d(reference,nom,nb_employes);

            bool test = tmpdepartement.update(reference,nom,nb_employes);


            if(test)

            {
                 ui->tableView_departement->setModel(tmpdepartement.afficher());
                QMessageBox::information(nullptr, QObject::tr("update "),
                            QObject::tr("departement modifie\n"
            "Click Cancel to exit."), QMessageBox::Cancel);}
            else
                QMessageBox::critical(nullptr, QObject::tr("update "),
                            QObject::tr("departement non modifie\n"
            "Click Cancel to exit."), QMessageBox::Cancel);}

    }




void MainWindow::on_sypprimer_departement_clicked()
{
    QString nom=ui->lineEdit_nomm->text();
    QString reference= ui->lineEdit_reference->text();
    int nb_employes= ui->lineEdit_nbemployes->text().toInt();



    bool test=tmpdepartement.supprimer(reference);

    if(test)
    {             ui->tableView_departement->setModel(tmpdepartement.afficher());

        QMessageBox::information(nullptr, QObject::tr("supprimer departemnt"),
                              QObject::tr("supp ressuie.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

          }
              else
                {  QMessageBox::information(nullptr, QObject::tr("supprimer departement"),
                              QObject::tr("supp echouèe.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
}







void MainWindow::on_ajouter_personnel_clicked()

{
          int cin= ui->lineEdit_cinpersonnel->text().toInt();
          QString nom= ui->lineEdit_nompersonnel->text();
          QString prenom= ui->lineEdit_prenompersonnel->text();
          QString departement=ui->comboBox_persodep->currentText();
          QString mobile= ui->lineEdit_mobilepersonnel->text();
          QDate date_naissance=ui->dateEdit_personnel->date();
          QString salaire=ui->lineEdit_salairepersonnel->text();
           QString ref_dep=ui->comboBox_ref_deppersonnel->currentText();



          personnel p(cin,nom,prenom,departement,mobile,date_naissance,salaire,ref_dep);


          if(mobile.size()<8)


        {
              p.ajouter();

              ui->tableView_personnel->setModel(tmppersonnel.afficher());
          QMessageBox::information(nullptr, QObject::tr("ajout personnel"),
                                    QObject::tr("personnel ajoutè.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

                }
                    else
                        QMessageBox::information(nullptr, QObject::tr("ajout personnel"),
                                    QObject::tr("ajout echouèe.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}



void MainWindow::on_reset_personnel_clicked()
{

}

void MainWindow::on_modifier_personnel_clicked()
{
          int cin= ui->lineEdit_cinpersonnel->text().toInt();
          QString nom= ui->lineEdit_nompersonnel->text();
          QString prenom= ui->lineEdit_prenompersonnel->text();
          QString departement=ui->comboBox_persodep->currentText();
          QString mobile= ui->lineEdit_mobilepersonnel->text();
          QDate date_naissance=ui->dateEdit_personnel->date();
          QString salaire=ui->lineEdit_salairepersonnel->text();
          QString ref_dep=ui->comboBox_ref_deppersonnel->currentText();
         personnel p(cin,nom,prenom,mobile,departement,date_naissance,salaire,ref_dep);

        bool test = tmppersonnel.update(cin,nom,prenom,departement,mobile,date_naissance,salaire,ref_dep);


        if(test)

        {
             ui->tableView_personnel->setModel(tmppersonnel.afficher());
            QMessageBox::information(nullptr, QObject::tr("update "),
                        QObject::tr("personnel modifie\n"
        "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("update "),
                        QObject::tr("personnel non modifie\n"
        "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_supprimer_personnel_clicked()
{
    QItemSelectionModel *select = ui->tableView_personnel->selectionModel();

    int cin =select->selectedRows(0).value(0).data().toInt();

    if(tmppersonnel.supprimer(cin))
    {
        ui->tableView_personnel->setModel(tmppersonnel.afficher());
        QMessageBox::information(nullptr, QObject::tr("supression"),
                                  QObject::tr("personnel supprimé.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::information(nullptr, QObject::tr("supression"),
                                  QObject::tr("supression echouèe.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pdf_personnel_clicked()
{
    personnel p;
    p.creerpdf();
}


void MainWindow::on_lineEdit_recherchepersonnel_textChanged(const QString &arg1)
{
    personnel p;
        ui->tableView_personnel->setModel(p.chercher(ui->lineEdit_recherchepersonnel->text()));
}

void MainWindow::on_stat_personnel_clicked()
{



    Stat *w = new Stat();
    w->make();
    w->show();
}

void MainWindow::on_tri_cin_personnel_clicked()
{
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();



               model->setQuery("select * from personnel order by CAST(cin as INT) asc");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("mobile"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
               model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));
               model->setHeaderData(7, Qt::Horizontal, QObject::tr("ref_dep"));
                        ui->tableView_personnel->setModel(model);
                        ui->tableView_personnel->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();
}

void MainWindow::on_tri_salaire_personnel_clicked()
{
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();



               model->setQuery("select * from personnel order by CAST(salaire as INT) asc");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
               model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));
               model->setHeaderData(7, Qt::Horizontal, QObject::tr("ref_dep"));
                        ui->tableView_personnel->setModel(model);
                        ui->tableView_personnel->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();
}
void MainWindow::on_tri_nom_personnel_clicked()
{
    {
        QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();



                   model->setQuery("select * from personnel order by nom");

                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
                   model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));
                   model->setHeaderData(7, Qt::Horizontal, QObject::tr("ref_dep"));
                            ui->tableView_personnel->setModel(model);
                            ui->tableView_personnel->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();
    }
}

void MainWindow::on_pushButton_val_p_clicked()
{
            int reference_p = ui->lineEdit_Ref_p->text().toInt();
            int quantite_p = ui->lineEdit_quantite_p->text().toInt();
            QString type_p= ui->comboBox_Type_p->currentText();
            qreal prix_p= ui->lineEdit_Prix_p->text().toFloat();
            QDate date_p = ui->dateEdit_p->date();
            produits p (reference_p,quantite_p,type_p,prix_p,date_p);
            bool test=p.ajouter_p();

            if (test)
            {
                ui->tableView_Produits->setModel(tmpprod.afficher_p());
                ui->lineEdit_Ref_p->setText("");
                ui->lineEdit_quantite_p->setText("");
                ui->lineEdit_Prix_p->setText("");
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("Ajout effectué .\n"),QMessageBox::Cancel);
            }
            else
{QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                       QObject::tr("Ajout non effectué .\n"),QMessageBox::Cancel);}
}
void MainWindow::on_pushButton_Supp_p_clicked()
{
    QItemSelectionModel *select = ui->tableView_Produits->selectionModel();

    int reference_p =select->selectedRows(0).value(0).data().toInt();

    if(tmpprod.supprimer_p(reference_p))
    {
        ui->tableView_Produits->setModel(tmpprod.afficher_p());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectué .\n"),QMessageBox::Cancel);
     }

}
void MainWindow::on_pushButton_Modifier_p_clicked()
{
    if (ui->pushButton_Modifier_p->isChecked())
    {
        //ui->pushButton_Modifier->setDisabled(true);
        ui->pushButton_Modifier_p->setText("Modifier...");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("produits");
        tableModel->select();
        ui->tableView_Produits->setModel(tableModel);
    }
    else
    {
        ui->pushButton_Modifier_p->setText("Modifier");
        ui->tableView_Produits->setModel(tmpprod.afficher_p());

    }
}
void MainWindow::on_pushButton_Recherche_p_clicked()
{
    if (ui->comboBox_p->currentIndex()==0)
    {
        int reference_p=ui->lineEdit_Recherche_p->text().toInt();
        QSqlQueryModel *verif_reference=tmpprod.rechercher_reference_p(reference_p);
        if (verif_reference!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_reference);

        }
    }
    else if (ui->comboBox_p->currentIndex()==1)
    {
        QString type_p;
        if (ui->radioButton_perissables->isChecked())
        type_p=ui->radioButton_perissables->text();
        else if (ui->radioButton_durables->isChecked())
        type_p=ui->radioButton_durables->text();

        QSqlQueryModel *verif_type=tmpprod.rechercher_type_p(type_p);
        if (verif_type!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_type);
        }
    }

    else if (ui->comboBox_p->currentIndex()==2)
    {
        QDate date_p=ui->dateEdit_recherche_p->date();
        QSqlQueryModel *verif_datee=tmpprod.rechercher_date_p(date_p);
        if (verif_datee!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_datee);
        }

    }
    else if (ui->comboBox_p->currentIndex()==3)
    {
        int quantite_p=ui->lineEdit_Recherche_p->text().toInt();
        QSqlQueryModel *verif_reference=tmpprod.rechercher_quantite_p(quantite_p);
        QDate date_p=ui->dateEdit_recherche_p->date();
        QString type_p;
        if (verif_reference!=nullptr)
        {
            if (ui->radioButton_perissables->isChecked())
               type_p=ui->radioButton_perissables->text();
            else if (ui->radioButton_durables->isChecked())
                type_p=ui->radioButton_durables->text();
            QSqlQueryModel *verif_critere=tmpprod.rechercher_critere_p(quantite_p,type_p,date_p);
            if (verif_critere!=nullptr)
            {
                ui->tableView_Produits->setModel(verif_critere);
            }
        }
        else
            QMessageBox::warning(this,"Erreur","réessayer");

    }

}
void MainWindow::on_pushButton_afficher_p_clicked()
{
    ui->tableView_Produits->setModel(tmpprod.afficher_p());
}

void MainWindow::on_pushButton_val_f_clicked()
{
            QString CIN_f = ui->lineEdit_CIN_f->text();
            QString telephone_f = ui->lineEdit_tel_f->text();
            QString type_f = ui->comboBox_type_f->currentText();
            QString RIB_f = ui->lineEdit_RIB_f->text();

            fournisseurs f (CIN_f,telephone_f,type_f,RIB_f);
            bool test=f.ajouter_f();

            if (test)
            {
                ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
                ui->lineEdit_CIN_f->setText("");
                ui->lineEdit_tel_f->setText("");
                ui->lineEdit_RIB_f->setText("");
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("Ajout effectué .\n"),QMessageBox::Cancel);
            }
            else
{       QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                       QObject::tr("Ajout non effectué .\n"),QMessageBox::Cancel);}
}
void MainWindow::on_pushButton_supp_f_clicked()
{
    QItemSelectionModel *select = ui->tableView_Fournisseurs->selectionModel();

    int CIN_f =select->selectedRows(0).value(0).data().toInt();

    if(tmpf.supprimer_f(CIN_f))
    {
        ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectué .\n"),QMessageBox::Cancel);
     }
}


void MainWindow::on_pushButton_modifier_f_clicked()
{

    if (ui->pushButton_modifier_f->isChecked())
               {
                  // ui->pushButton_modifier->setDisabled(true);
                   ui->pushButton_modifier_f->setText("Modifiable");
                   QSqlTableModel *tableModel= new QSqlTableModel();
                   tableModel->setTable("fournisseurs");
                   tableModel->select();
                   ui->tableView_Fournisseurs->setModel(tableModel);
               }
               else
               {
                   ui->pushButton_modifier_f->setText("Modifier");
                   ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());

               }
}


    void MainWindow::on_pushButton_afficher_f_clicked()
    {
        ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
    }

void MainWindow::on_pushButton_rechercher_f_clicked()
{
    ui->tableView_Fournisseurs->setModel(tmpf.afficher_f(  ));
     QString CIN_f= ui->lineEdit_rechercher_f->text();
     ui->tableView_Fournisseurs->setModel(tmpf.rechercher_fournisseurs(CIN_f));
}



void MainWindow::on_pushButton_Exporter_p_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_produits.pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;

        q.prepare("SELECT * FROM produits ");
        q.exec();
        QString pdf="<br> <img src='C:/Users/lenovo/Documents/Gestion_stock/wedding bells.png' height='20' width='50'/> <h1  style='color:blue'>       LISTE DES PRODUITS  <br></h1>\n <br> <table>  <tr>  <th> REFERENCE </th>  <th> QUANTITE </th>  <th>TYPE </th>  <th> PRIX  " ;


        while ( q.next()) {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"    </td>  <td>    " +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"</td>             </td>" ;

        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size());
        doc.print(&printer);
}

void MainWindow::on_pushButton_exporter_f_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    EXCEL obj(fileName, "mydata", ui->tableView_Fournisseurs);

    //colums to export
    obj.addField(0, "CIN", "char(20)");
    obj.addField(1, "telephone", "char(20)");
    obj.addField(2, "type", "char(20)");
    obj.addField(3, "RIB", "char(20)");

    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
void MainWindow::on_configuration_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_confirmer_langue_clicked()
{
    if (ui->comboBox_langue->currentText()=="Français")
    {
        translator->load("D:\\Users\\dhiaa\\Desktop\\working_on\\wedding_planner_fr");
        qApp->installTranslator(translator);
        ui->retranslateUi(this);
        ui->comboBox_langue->setCurrentText("Français");
    }
    else if (ui->comboBox_langue->currentText()=="English")
    {
        translator->load("D:\\Users\\dhiaa\\Desktop\\working_on\\wedding_planner_en");
        qApp->installTranslator(translator);
        ui->retranslateUi(this);
        ui->comboBox_langue->setCurrentText("English");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    Smtp* smtp = new Smtp("dhia.abdelli1@esprit.tn", "Dpstream1", "smtp.gmail.com", 465);
    smtp->sendMail("dhia.abdelli1@esprit.tn", "dhia.abdelli1@esprit.tn" , "Signalisation Problème" ,ui->plainTextEdit_probleme->toPlainText());
    ui->plainTextEdit_probleme->clear();
}
