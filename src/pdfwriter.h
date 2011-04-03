#ifndef PDFWRITER_H
#define PDFWRITER_H

#include <QObject>
#include <QPair>

class PdfWriter : public QObject
{
    Q_OBJECT
public:
    explicit PdfWriter(QObject *parent = 0);

signals:

public slots:
    void create(const QList<QPair<QString,QString> > &content, const QString &image);

};

#endif // PDFWRITER_H
