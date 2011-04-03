#ifndef PDFWRITER_H
#define PDFWRITER_H

#include <QObject>

class PdfWriter : public QObject
{
    Q_OBJECT
public:
    explicit PdfWriter(QObject *parent = 0);

signals:

public slots:

};

#endif // PDFWRITER_H
