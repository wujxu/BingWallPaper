#include <QCoreApplication>
#include "wallpaper.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    WallPaper wallpaper;
    wallpaper.getWallPaper();
    return app.exec();
}
