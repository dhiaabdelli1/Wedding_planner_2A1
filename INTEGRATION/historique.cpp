#include "historique.h"

historique::historique()
{

}
void historique::save(QString reference,QString nom)
{    QFile file ("D:/Users/dhiaa/Desktop/Wedding_planner_2A1/INTEGRATIONhistorique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << reference+"\n"+nom << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("D:/Users/dhiaa/Desktop/Wedding_planner_2A1/INTEGRATIONhistorique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
