#include "personnel.h"
#include "QDebug"
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextDocument>
personnel::personnel()
{

}

personnel::personnel(QString cin, QString nom, QString prenom, QString departement, QString mobile, QDate date_naissance, QString salaire,QString ref_dep)
{

        this->cin=cin;
        this->nom=nom;
        this->prenom=prenom;
        this->departement=departement;
        this->mobile=mobile;
        this->date_naissance=date_naissance;
        this->salaire=salaire;
        this->ref_dep=ref_dep;


}




bool personnel::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO personnel (cin, nom, prenom,departement,mobile,date_naissance,salaire,ref_dep) "
                  "VALUES (:cin, :nom, :prenom,:departement,:mobile,:date_naissance,:salaire,:ref_dep)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":departement",departement);
    query.bindValue(":mobile",mobile);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":salaire",salaire);
    query.bindValue(":ref_dep",ref_dep);



    return query.exec();


}



QSqlQueryModel * personnel::afficher()
{
QSqlQueryModel * model = new QSqlQueryModel();

model->setQuery("select *from personnel");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("ref_dep"));



    return model;
}

bool personnel::supprimer(QString cin)
{

    QSqlQuery qry;
        //QString mat = QString::number(cin);
        qry.prepare("Delete from personnel where cin = :cin");
        qry.bindValue(":cin",cin);
        return qry.exec();
}




bool personnel::update(QString cin, QString nom, QString prenom, QString departement, QString mobile, QDate date_naissance, QString salaire,QString ref_dep)
{
    QSqlQuery query;
    query.prepare("UPDATE personnel SET cin= :cin , nom= :nom , prenom= :prenom , departement= :departement , mobile= :mobile , date_naissance = :date_naissance , salaire= :salaire ,ref_dep= :ref_dep WHERE cin = :cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom",nom );
    query.bindValue(":prenom", prenom);
    query.bindValue(":departement", departement);
    query.bindValue(":mobile", mobile);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":salaire", salaire);
    query.bindValue(":ref_dep", ref_dep);

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
    QString pdf="<br><img src='/C:/Users/ASUS/Documents/build-elaaqt-Desktop_Qt_5_9_9_MinGW_32bit-Debug/logo.png' height='42' width='144'/> <h1  style='color:pink'>tableau personnel  <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th>  <th>PRENOM </th> <th>MOBILE </th>  <th>DEPARTEMENT </th> <th>DATE_NAISSANCE </th> <th>SALAIRE </th> <th>REF_DEP </th> </tr> " ;


    while ( q.next()) {
pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>   <td> " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" </td>   <td>"+q.value(3).toString()+"</td> <td>"+q.value(4).toString()+"<td> <td>"+q.value(5).toString()+" </td> <td> "+q.value(6).toString()+" </td> </td>";

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}








QSqlQueryModel * personnel::chercher(QString r)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from personnel where upper(nom) like upper('%"+r+"%') or upper(prenom) like upper('%"+r+"%') or upper(cin) like upper('%"+r+"%') ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mobile"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ref_dep"));


        return model;
}


bool personnel::ajouter_image(QString cin)
{
    QByteArray byte;
    QString filename=QFileDialog::getOpenFileName(0,"open image","D:\\","image files (*.png");
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly))
    {
        byte=file.readAll();
        file.close();
    }

    QSqlQuery qry;
    qry.prepare("UPDATE personnel SET photo= :photo where cin=:cin");
    qry.bindValue(":photo",byte,QSql::In | QSql::Binary);
    qry.bindValue(":cin",cin);

    return qry.exec();
}
