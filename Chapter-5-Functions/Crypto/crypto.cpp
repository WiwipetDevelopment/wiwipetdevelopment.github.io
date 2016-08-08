#include <QChar>
#include <QtAlgorithms>
#include <QByteArray>

#include "crypto.h"

Crypto::Crypto(unsigned short key,QString opseq,unsigned short charsiz):
  m_usKey(key),m_qsOpSequence(opseq),m_usCharSetSize(charsiz){
    
  }
  
QString Crypto::shift(const QString& str){
  
  QByteArray ba=str.toLocal8Bit();
  
  for(int i=0;i<ba.size();i++)
    ba[i]=ba[i]+m_usKey;
  
  QString temp(ba);
  return temp;
}

QString Crypto::unshift(const QString& str){
  
  QByteArray ba=str.toLocal8Bit();
  
  for(int i=0;i<ba.size();i++)
    ba[i]=ba[i]-m_usKey;
  
  QString temp(ba);
  return temp;
}

/* ##Static Function## */
int Crypto::limitedRand(int min,int max){
   srand(time(0));
   return min+rand()%(max-min);
}

QVector<int> Crypto::randomPerm(int n){
  srand(m_usKey);
  QVector<int> vTemp;
  
  for(int i=0; i<m_usCharSetSize;i++)
    vTemp<<limitedRand(0,n);
  
  qSort(vTemp);
  return vTemp;
}


QString Crypto::permute(const QString& str){

  QString keyString;
  keyString.setNum(m_usKey);
  const int arrayLength=keyString.size();
  QVector<QByteArray> seqTable;
  int count=0;
    
  //Loop de finalizacion de setence
  while(count<str.size()){
    //Loop de llenado de chars
    QByteArray setence;
    for(int i=0; i< arrayLength;i++){
      if(count <str.size())
        setence+=str[count];
      else
        setence+='-';
      ++count;
    }
    seqTable<<setence;
  }

  QString dest;
  int posKeeper=0;
  count=0;
  QVector<QChar> keySorter;

  //Ordenar key
  for(int i=0;i<keyString.size();++i)
    keySorter.push_back(keyString[i]);
  qSort(keySorter);
  
  //Hasta que se terminen de analizar cada caracter del key
  while(count<keyString.size()){
    //Loop donde determina cual numero de menor a mayor sigue de analizar.
    for(int j=0;j<keyString.size();j++){
      if(keySorter[count]==keyString[j]){
	posKeeper=j;
	++count;
	break;
      }
    }
    
    //Inicio acomodo de caracteres
    for(int k=0;k<seqTable.size();k++)
      dest+=seqTable[k][posKeeper]; 
  }
  return dest;
}

//Funciona con contraseñas maximas de 6 caracteres.
QString Crypto::unpermute(const QString& str){
  QString sKey;
  sKey.setNum(m_usKey);

  const int rows=str.length()/sKey.length();
  
  QVector<QByteArray> seqTable;
  int nCount=0;
  int nCountPos=0;
  QVector<QChar> keySorter;

  //Sort key
  for(int i=0; i<sKey.size();++i)
    keySorter.push_back(sKey[i]);
  qSort(keySorter);

  //Reserve space to Table
  seqTable.resize(sKey.length());
  
  //Fill Vector<QBA>
  for(int i=0;i<sKey.length();i++){
    QByteArray qbaBuffer;
    //Adding each character to a QBA to later insert it in its right position in Table
    for(int j=0;j<rows;j++){
      qbaBuffer+=str[nCount];
      ++nCount;
    }
    
    //Insert QBAs to their right position.
    for(int k=0;k<sKey.length();k++){
      if(keySorter[nCountPos]==sKey[k]){
          seqTable[k]=qbaBuffer;
	  ++nCountPos;
	  break;
      }
    }
  }

  QString dest;
  //Read and store uncryptying string
  for(int k=0;k<rows;k++)
    for(int l=0;l<sKey.length();l++)
      dest+=seqTable[l][k];
    
  return dest;
}

QString Crypto::encrypt(const QString& str){
  QString temp(str);
  
  for(int i=0;i<m_qsOpSequence.length();i++){
    if(m_qsOpSequence[i]=='s' || m_qsOpSequence[i]=='S')
      temp=shift(temp);
    if(m_qsOpSequence[i]=='p' || m_qsOpSequence[i]=='P')
      temp=permute(temp);
  }
  return temp;
}

QString Crypto::decrypt(const QString& str){
  QString temp(str);
  
  for(int i=m_qsOpSequence.length()-1;i>0;--i){
    if(m_qsOpSequence[i]=='s' || m_qsOpSequence[i]=='S')
      temp=unshift(temp);
    if(m_qsOpSequence[i]=='p' || m_qsOpSequence[i]=='P')
      temp=unpermute(temp);
  }
  return temp;
}

//end
