#ifndef PDFWRITER_H
#define PDFWRITER_H

#include <QThread>
#include <QPair>

class PdfWriter : public QThread
{
    Q_OBJECT
public:
    explicit PdfWriter(QObject *parent = 0);

signals:
    void printingFinished();

protected:
    void run();

public slots:
    void create(const QList<QPair<QString,QString> > &content, const QString &image, const QString &outPut);

private:
    void printTags();

private:
    QList<QPair<QString,QString> > m_content;
    QString m_image;
    QString m_output;

};

#endif // PDFWRITER_H
