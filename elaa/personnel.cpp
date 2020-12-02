#include "personnel.h"
#include "QDebug"
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextDocument>
personnel::personnel()
{

}

personnel::personnel(int cin, QString nom, QString prenom, QString mobile, QString departement, QDate date_naissance, int salaire)
{

this->cin=cin;
        this->nom=nom;
this->prenom=prenom;
    this->mobile=mobile;
    this->departement=departement;
    this->date_naissance=date_naissance;
    this->salaire=salaire;


}




bool personnel::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO personnel (cin, nom, prenom,departement,mobile,date_naissance,salaire) "
                  "VALUES (:cin, :nom, :prenom,:departement,:mobile,:date_naissance,:salaire)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
     query.bindValue(":departement",departement);
    query.bindValue(":mobile",mobile);

    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":salaire",salaire);



    return query.exec();


}



QSqlQueryModel * personnel::afficher()
{
QSqlQueryModel * model = new QSqlQueryModel();

model->setQuery("select *from personnel");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("departement"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("mobile"));

model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


    return model;
}

bool personnel::supprimer(int cin)
{

    QSqlQuery qry;
        QString mat = QString::number(cin);
        qry.prepare("Delete from personnel where cin = :cin");
        qry.bindValue(":cin",cin);
        return qry.exec();
}




bool personnel::update(int cin, QString nom, QString prenom, QString mobile, QString departement, QDate date_naissance, int salaire)
{
    QSqlQuery query;
    query.prepare("UPDATE personnel SET cin= :cin , nom= :nom , prenom= :prenom , departement= :departement , mobile= :mobile , date_naissance = :date_naissance , salaire= :salaire WHERE cin = :cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom",nom );
    query.bindValue(":prenom", prenom);
    query.bindValue(":departement", departement);
    query.bindValue(":mobile", mobile);

    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":salaire", salaire);

    return    query.exec();
}
void personnel::creerpdf()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM personnel ");
    q.exec();
    QString pdf="<br><img src='/C:/Users/ASUS/Documents/build-elaaqt-Desktop_Qt_5_9_9_MinGW_32bit-Debug/logo.png' height='42' width='144'/> <h1  style='color:pink'>tableau personnel  <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th>  <th>PRENOM </th> <th>MOBILE </th>  <th>DEPARTEMENT </th> <th>DATE_NAISSANCE </th> <th>SALAIRE </th> </tr> " ;


    while ( q.next()) {
pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>   <td> " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" </td>   <td>"+q.value(3).toString()+"</td> <td>"+q.value(4).toString()+"<td> <td>"+q.value(5).toString()+" </td> <td> "+q.value(6).toString()+" </td> </td>";

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}



QSqlQueryModel * personnel::cherchernom(QString rech)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from personnel where upper(nom) like upper('%"+rech+"%') ");


     model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


         return model;
 }
QSqlQueryModel * personnel::chercherprenom(QString rech)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from personnel where upper(prenom) like upper('%"+rech+"%')");


     model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


         return model;
 }
QSqlQueryModel * personnel::cherchermobile(QString rech)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from personnel where upper(departement) like upper('%"+rech+"%')");

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


     return model;
}

QSqlQueryModel *personnel::chercher(QString rech , QString rech1,QString  rech2)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from personnel where upper(nom) like upper('%"+rech+"%') and upper(prenom) like upper('%"+rech1+"%') and upper(mobile) like upper('%"+rech2+"%') ");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


    return model;
}

