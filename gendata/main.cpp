#include <QCoreApplication>
#include <QFile>
#include <QString>

int main()
{
    QFile file ("data_co");
    file.open(QIODevice::WriteOnly);
    int size = 32;
   int count = size*size;
   QString string = QString::number(32)+"\n";
   for(int i = 0;i<count;i++){
       int x = i%size;
       int y = i/size;
       double val = (x+y)%2==0? 1:-1;
//       double val = qrand()*2.0/RAND_MAX-1;
       string += QString::number(i) + "\t" + QString::number(val) + "\n";
   }
   file.write(string.toUtf8());
   file.close();
   return 0;
}
