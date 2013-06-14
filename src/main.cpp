#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int id = QFontDatabase::addApplicationFont("fonts/Junction/Junction_02.ttf");
    QStringList families = QFontDatabase::applicationFontFamilies(id);
    qDebug() << families;
    QFont font("Junction");
    app.setFont(font);

    MainWindow mw;
    mw.show();
    return app.exec();
}
