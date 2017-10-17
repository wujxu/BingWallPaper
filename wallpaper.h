#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QPixmap>

class WallPaper : public QObject
{
    Q_OBJECT

public:
    WallPaper();
    void getWallPaper();

private:
    static const QString PIC_URL_HEAD;
    static const QString PIC_PATH;

    void getWebSource();

    QNetworkAccessManager *manager;

private slots:
    void getPicUrl(QNetworkReply *webReply);
    void downloadPic(QUrl picUrl);
    void savePic(QNetworkReply *picReply);

signals:
    void picUrlFound(QUrl);
};

#endif // WALLPAPER_H
