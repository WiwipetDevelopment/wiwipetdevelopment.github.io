#ifndef CRYPTO_H
#define CRYPTO_H

#include <QString>
#include <QVector>

class Crypto{
public:
  //public members functions
  Crypto(unsigned short key=1,QString opseq="p",unsigned short charsiz=1);//
  QString encrypt(const QString& str);
  QString decrypt(const QString& str);
  QString permute(const QString& str);
  QString unpermute(const QString& str);
  QString shift(const QString& str);//
  QString unshift(const QString& str);//
  
private:
  //variables
 unsigned short m_usKey;
 QString m_qsOpSequence;
 unsigned short m_usCharSetSize;
 QVector<int> m_vPerm;
 
 //private functions
 
 static int limitedRand(int min,int max);//
 QVector<int> randomPerm(int n);//
};
#endif
