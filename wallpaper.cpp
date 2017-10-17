#include "wallpaper.h"

const QString WallPaper::PIC_URL_HEAD = "/az/hprichbg/rb/";
const QString WallPaper::PIC_PATH = QDir::homePath() + "/" + "Pictures/bing/";

WallPaper::WallPaper()
{
    manager = new QNetworkAccessManager(this);
    connect(this, SIGNAL(picUrlFound(QUrl)), this, SLOT(downloadPic(QUrl)));
}

void WallPaper::getWallPaper()
{
    getWebSource();
}

void WallPaper::getWebSource()
{
    QUrl url("http://cn.bing.com");
    QNetworkRequest request;
    request.setUrl(url);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getPicUrl(QNetworkReply*)));
    manager->get(request);
}

void WallPaper::getPicUrl(QNetworkReply *webReply)
{
    disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getPicUrl(QNetworkReply*)));

    if (webReply->error() == QNetworkReply::NoError) {
        QByteArray webSource = webReply->readAll();

        // Find the index of picture url, and cut url from source
        int indexStart = webSource.indexOf(PIC_URL_HEAD);
        webSource = webSource.mid(indexStart);
        int indexEnd = webSource.indexOf("jpg") + 2;
        QUrl picUrl("http://cn.bing.com" + webSource.left(indexEnd + 1));
        qDebug().noquote() << tr("Getting picture from:") << endl << picUrl.toString();

        // Download the picture
        emit picUrlFound(picUrl);
    } else {
        qDebug().noquote() << tr("Error occurred during getting web source:") << endl << webReply->errorString();
        return;
    }
    webReply->deleteLater();
}

void WallPaper::downloadPic(QUrl picUrl)
{
    QNetworkRequest request;
    request.setUrl(picUrl);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(savePic(QNetworkReply*)));
    manager->get(request);
}

void WallPaper::savePic(QNetworkReply *picReply)
{
    disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(savePic(QNetworkReply*)));

    if (picReply->error() == QNetworkReply::NoError) {
        // Get picture from data
        QByteArray picData = picReply->readAll();

        // Save picture
        QString picName = "bing_" + QDateTime::currentDateTime().toString("yyyyMMdd") +".jpg";
        QFile picFile(PIC_PATH + picName);
        if (!picFile.open(QIODevice::WriteOnly)) {
            qDebug().noquote() << tr("Error occurred during saving picutre.");
            return;
        }
        picFile.write(picData);
        picFile.flush();
        picFile.close();

        // Change wallpaper
        QFile wallPaperFile(PIC_PATH + "bing_today.jpg");
        if (!wallPaperFile.open(QIODevice::WriteOnly)) {
            qDebug().noquote() << tr("Error occurred during changing wallpaper.");
            return;
        }
        wallPaperFile.write(picData);
        wallPaperFile.flush();
        wallPaperFile.close();
    } else {
        qDebug().noquote() << tr("Error occurred during getting picture:") << endl << picReply->errorString();
        return;
    }

    qDebug().noquote() << tr("Getting wallpaper succeeded!");

    // All done, close this application
    QCoreApplication::exit();
}
