#include <QTextStream>
#include "crypto.h"

int main(){
  QTextStream cout(stdout);
  QString str1("CarlosEnriqueHernandezIbarra")
    ,str2("Beto es el perro mas loco del vecindario,Su comida favorita es el betabel y "
          "nadie sabe porque Es un excelente cazador de ratas, su score es de 17 ratas");
  
  //Es un excelente cazador de ratas, su score es de 17 ratas "
  //"y una fue con un peso de 1.5 kg, superando el record de Timmy el gato en paris"
  //" en 2008

  cout<<"Original string: "<<str2<<endl;
  cout<<"Length: "<<str2.length()<<endl;
  
  
  //Al parecer hay problemas con el key, por ejemplo el key 256789 no desencrypta bien
  //Tambien cuando no estan en orden los caracteres, al parecer falto un acomodo de
  //caracteres(descriptar)

  Crypto crypt(672185,"ppsspspsppps",(unsigned short)str2.length());

//HFunciona 672185,6072185,36072185
  //No Funciona 60721854
  
  //Talvez por el limite como max. del us 65535
  QString temp(str2);
  temp=crypt.permute(temp);
  cout<<"1: "<<temp<<endl;
  //temp=crypt.shift(temp);
  //cout<<"2 :" <<temp<<endl;

  //temp=crypt.unshift(temp);
  //cout<<"3: "<<temp<<endl;
  temp=crypt.unpermute(temp);
  cout<<"4 :" <<temp<<endl;
 
  return 0;
}
