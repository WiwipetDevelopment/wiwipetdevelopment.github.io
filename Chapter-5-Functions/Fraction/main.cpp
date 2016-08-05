/****************************************************************************
**
** Copyright (C) 2016 Wiwipet Development.
** Contact: char.mechanic92@gmail.com
**
** This file is part of the examples of An Introduction to Design Patterns with Qt .
**  Made by Wiwiped Development Team mainly for academic purposes.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code and binary form must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   * Neither the name of Wiwiped Development nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
****************************************************************************/

#include <QTextStream>
#include "fraction.h"

int main(){
  
  QTextStream cout(stdout);
  
  Fraction f1,f2;
  f1.set(4,16);
  f2.set(3,18);
  Fraction f3=f1.add(f2);
  
  QString t1=f1.toString();
  QString t2=f2.toString();
  QString t3=f3.toString();
  
  cout<<"Valor esperado 5/12"<<endl;
  cout<<t1<<'\n'<<t2<<'\n'<<t3<<'\n'<<endl;
  
  f1.set(175,52);
  f2.set(158,56);
  f3=f1.subtract(f2);
  
  t1=f1.toString();
  t3=f2.toString();
  t2=f3.toString();
  
  cout<<"Valor esperado 99/182"<<endl;
  cout<<t1<<'\n'<<t3<<'\n'<<t2<<'\n'<<endl;
  
  f1.set(4,8);
  f2.set(1,8);
  f3=f1.multiply(f2);
  
  t1=f1.toString();
  t3=f2.toString();
  t2=f3.toString();
  
  cout<<"Valor esperado 1/16"<<endl;
  cout<<t1<<'\n'<<t3<<'\n'<<t2<<'\n'<<endl;
  
  f1.set(1,4);
  f2.set(1,4);
  f3=f1.divide(f2);

  
  t1=f1.toString();
  t3=f2.toString();
  t2=f3.toString();
  
  cout<<"Valor esperado 1/4"<<endl;
  cout<<t1<<'\n'<<t3<<'\n'<<t2<<'\n'<<endl;

  f3=f1+f2;
  cout<<f3.toString()<<'\n';
  f3=f1*f2;
  cout<<f3.toString()<<'\n';

  Fraction f4(1,2);
  Fraction f5=f4+2;
  cout<<"F5 debe ser 3 o 6/2: "<<f5.toString()<<endl;

  f5=0.75+f4;
  cout<<"F5 debe ser 5/4 : "<<f5.toString()<<endl;

  return 0;
}
