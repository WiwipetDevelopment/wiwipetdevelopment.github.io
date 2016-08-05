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

#include "fraction.h"
#include <math.h>


Fraction::Fraction():m_nNumerator(1),m_nDenominator(1){

}

Fraction::Fraction(const double d){
    double temp=d;
    int count=0;

    while(1){
        if(fmod(temp,10.0)==0)
            break;
        temp*=10;
        ++count;
    }
    m_nNumerator=temp;
    m_nDenominator=pow(10,count);
}

Fraction::Fraction(const int num, const int dem):m_nNumerator(num),m_nDenominator(dem){
  if(m_nDenominator==0)
      m_nDenominator=1;

}

void Fraction::set(const int numerator,const int denominator){
  
  m_nNumerator=numerator;
  m_nDenominator=denominator;
  
}

QString Fraction::toString(){
  
  return QString("%1 / %2.").arg(m_nNumerator).arg(m_nDenominator);
}


double Fraction::toDouble(){
  
  return 1.0*(m_nNumerator/m_nDenominator);
}

Fraction Fraction::add(const Fraction & other){

  Fraction tempFraction;
  if(m_nDenominator==other.m_nDenominator){
  
    tempFraction.m_nNumerator=m_nNumerator+other.m_nNumerator;
    tempFraction.m_nDenominator=m_nDenominator;
  }
  
  else{  
    tempFraction.m_nNumerator=(m_nNumerator*other.m_nDenominator)+(m_nDenominator*other.m_nNumerator);
    tempFraction.m_nDenominator=m_nDenominator*other.m_nDenominator;
  }
  
  return simplify(tempFraction);
}

Fraction Fraction::simplify(Fraction& f){
  
  const int sizeArray=46;
  const int aPrimes[]={ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
                        101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
                        151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };
  
  
  for(int i=0; i< sizeArray;){
    
    if((f.numerator()%aPrimes[i]==0)&&(f.denominator()%aPrimes[i]==0))
      f.set(f.numerator()/aPrimes[i],f.denominator()/aPrimes[i]);
    
    else
      ++i;
  }
  return f;
}

Fraction Fraction::subtract(const Fraction & other){
  
  Fraction tempFraction;
  
   if(m_nDenominator==other.m_nDenominator){
  
    tempFraction.m_nNumerator=m_nNumerator-other.m_nNumerator;
    tempFraction.m_nDenominator=m_nDenominator;
  }
  
  else{  
    tempFraction.m_nNumerator=(m_nNumerator*other.m_nDenominator)-(m_nDenominator*other.m_nNumerator);
    tempFraction.m_nDenominator=m_nDenominator*other.m_nDenominator;
  }
  
  return simplify(tempFraction);
}

Fraction Fraction::multiply (const Fraction & other){
  Fraction tempFraction;
 
  tempFraction.m_nNumerator=m_nNumerator*other.m_nNumerator;
  tempFraction.m_nDenominator=m_nDenominator*other.m_nDenominator;
  
  return simplify(tempFraction);
  
}

Fraction Fraction::divide(const Fraction& other){
  Fraction tempFraction;

  tempFraction.m_nNumerator=m_nNumerator*other.m_nDenominator;
  tempFraction.m_nDenominator=m_nDenominator*other.m_nNumerator;
  
  return simplify(tempFraction);
  
}

Fraction Fraction::simplify(){
    return this->simplify(*this);
}

Fraction operator+(const Fraction& f1,const Fraction& f2){
    Fraction temp;
    if(f1.denominator()==f2.denominator())
        temp.set(f1.numerator()+f2.numerator(),f1.denominator());
    else
        temp.set((f1.numerator()*f2.denominator())+(f2.numerator()*f1.denominator()),
                 f1.denominator()*f2.denominator());

    return temp.simplify();
}

Fraction operator-(const Fraction& f1,const Fraction& f2){
    Fraction temp;
    if(f1.denominator()==f2.denominator())
        temp.set(f1.numerator()-f2.numerator(),f1.denominator());
    else
        temp.set((f1.numerator()*f2.denominator())-(f2.numerator()*f1.denominator()),
                 f1.denominator()*f2.denominator());

    return temp.simplify();
}

Fraction operator*(const Fraction& f1,const Fraction& f2){
    Fraction temp;
    temp.set(f1.numerator()*f2.numerator(),
                      f1.denominator()*f2.denominator());
    return temp.simplify();
}

Fraction operator/(const Fraction& f1,const Fraction& f2){
    Fraction temp;
    temp.set(f1.numerator()*f2.denominator(),
            f1.denominator()*f2.numerator());
    return temp.simplify();
}

//Fraction=Fraction + double/int

Fraction Fraction::operator+(const int i){
    Fraction temp;
    temp=*this+(double)i;
    return temp.simplify();
}

Fraction Fraction::operator+(const double d){
    return *this+Fraction(d);
}

//Fraction=double/int + Fraction
Fraction operator+(const int i, const Fraction& f){
    Fraction temp;
    temp=f+(double)i;
    return temp.simplify();
}

Fraction operator+(const double d,const Fraction& f){
    return f+Fraction(d);
}
