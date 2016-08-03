/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QDebug>

#include <stdio.h>

QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class DownloadManager: public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;
    QStringList m_basenames;

public:
    DownloadManager();
    void doDownload(const QUrl &url);
    QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);

public slots:
    void execute();
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
};

class Patient{

private:
    int m_A;
    int m_C;
    int m_G;
    int m_T;
    bool m_isInfected;
    QString m_fileName;

public:
    Patient(int A,int C,int G,int T, bool infected,QString filename);
    bool analysis();
    void incrementA(const int i){m_A+=i;}
    void incrementC(const int i){m_C+=i;}
    void incrementG(const int i){m_G+=i;}
    void incrementT(const int i){m_T+=i;}
    int getA()const{return m_A;}
    int getC()const{return m_C;}
    int getG()const{return m_G;}
    int getT()const{return m_T;}
    bool isInfected()const{return m_isInfected;}
};

Patient::Patient(int A, int C, int G, int T, bool infected, QString filename):
    m_A(A),m_C(C),m_G(G),m_T(T),m_isInfected(infected),m_fileName(filename){

}

DownloadManager::DownloadManager()
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    m_basenames.clear();
}

void DownloadManager::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#ifndef QT_NO_SSL
    //Copy the reply error to download error.
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }
    m_basenames.push_front(basename);
    return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void DownloadManager::execute()
{
    //We take the arguments of the command line, filter them and downloaded.
    //Get arguments
    QStringList args = QCoreApplication::instance()->arguments();
    args.takeFirst();           // skip the first argument, which is the program's name

    //Execution without parameters, show message and exit
    if (args.isEmpty()) {
        printf("Qt Download example - downloads all URLs in parallel\n"
               "Usage: download url1 [url2... urlN]\n"
               "\n"
               "Downloads the URLs passed in the command-line to the local directory\n"
               "If the target file already exists, a .0, .1, .2, etc. is appended to\n"
               "differentiate.\n");
        QCoreApplication::instance()->quit();
        return;
    }

    //Iterate parameters and downloaded
    foreach (QString arg, args) {
        QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
        doDownload(url);
    }
}

void DownloadManager::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

//When the request of download is already finish, this slot is called.
void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    //Get reply and use it data to display to the user.
    QUrl url = reply->url();

    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    }

    else {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply))
            printf("Download of %s succeeded (saved to %s)\n",
                   url.toEncoded().constData(), qPrintable(filename));
    }


    currentDownloads.removeAll(reply);
    reply->deleteLater();


    if (currentDownloads.isEmpty()){

        // all downloads finished
        //Start analysis of each one.
        QList<Patient> patientList;
        patientList.clear();
        patientList.reserve(m_basenames.size());
        float infectedPersons=0;

        //Obtain values
        foreach(QString basename_subject,m_basenames){
            QFile file(basename_subject);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                printf("Could not open file: %s",qPrintable(basename_subject));
                continue;
            }
            QByteArray text=file.readAll();
            if(text.size()==0)
                qDebug()<<"The Byte Array did not get any text \n";

            Patient temp(0,0,0,0,false,basename_subject);

            foreach(char character,text){
                if(character=='A')
                    temp.incrementA(1);
                else if(character=='C')
                    temp.incrementC(1);
                else if(character=='G')
                    temp.incrementG(1);
                else if(character=='T')
                    temp.incrementT(1);
                else
                    continue;
            }

            patientList.push_front(temp);


        }

        foreach(Patient patient,patientList){
            printf("A: %s \t",qPrintable(QString().number(patient.getA())));
            printf("C: %s \t",qPrintable(QString().number(patient.getC())));
            printf("G: %s \t",qPrintable(QString().number(patient.getG())));
            printf("T: %s \t\n",qPrintable(QString().number(patient.getT())));
            if((patient.getT()>patient.getA()) &&
                    (patient.getT()>patient.getC())&&
                    (patient.getT()>patient.getG())){
                printf("This patient is infected \n");
                infectedPersons++;
            }
            else{
                printf("This patient is not infected \n");
            }
        }

        printf("The percent of infected patient is: %s \n",
               qPrintable(QString().number(round(100*infectedPersons/patientList.size()))));

        QCoreApplication::instance()->quit();
    }
}


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    DownloadManager manager;
    //Trigger one time the download execute.
    QTimer::singleShot(0, &manager, SLOT(execute()));

    app.exec();

}

#include "main.moc"
