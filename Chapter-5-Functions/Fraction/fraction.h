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

#ifndef FRACTION_H
#define FRACTION_H
#include <QString>

class Fraction{
public:
  void set(int numerator,int denominator);
  Fraction();
  Fraction(const double d);
  Fraction(const int num,const int dem);
  QString toString();
  double toDouble();
  Fraction add(const Fraction & other);
  Fraction subtract(const Fraction & other);
  Fraction multiply(const Fraction & other);
  Fraction divide(const Fraction & other);

  //Exercises 5.3.1.1
  friend Fraction operator+(const Fraction& f1,const Fraction& f2);
  friend Fraction operator-(const Fraction& f1,const Fraction& f2);
  friend Fraction operator*(const Fraction& f1,const Fraction& f2);
  friend Fraction operator/(const Fraction& f1,const Fraction& f2);

  //Fraction=Fraction+double/int
  Fraction operator+(const int i);
  Fraction operator+(const double d);

  //Fraction=double/int+Fraction
  friend Fraction operator+(const int i,const Fraction& f);
  friend Fraction operator+(const double d,const Fraction& f);
  
  Fraction simplify(Fraction& f);
  Fraction simplify();

  int numerator()const{return m_nNumerator;}
  int denominator()const{return m_nDenominator;}

private:
  int m_nNumerator,m_nDenominator;
  
};

#endif
