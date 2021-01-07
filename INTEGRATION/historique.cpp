#include "historique.h"

historique::historique()
{

}
void historique::save(QString reference,QString nom)
{    QFile file ("C:/Users/asus/Desktop/barkia/INTEGRATION/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << reference+"\n"+nom << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/Users/asus/Desktop/barkia/INTEGRATION/historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
