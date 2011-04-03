#include "pdfwriter.h"

#include <QDebug>

PdfWriter::PdfWriter(QObject *parent) :
    QObject(parent)
{
}

void PdfWriter::create(const QList<QPair<QString, QString> > &content, const QString &image)
{
    if(content.isEmpty()) {
        qDebug() << "empty list at" << __PRETTY_FUNCTION__;
        return;
    }
    qDebug() << __PRETTY_FUNCTION__ << "is not implement..";
    qDebug() << "bgimage" << image;
    qDebug() << "content:";

    for(int i = 0; i < content.count(); i++) {
        qDebug() << content.at(i).first << content.at(i).second;
    }
}
