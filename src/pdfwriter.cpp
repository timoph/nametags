#include "pdfwriter.h"

#include <QDebug>
#include <QPainter>
#include <QPrinter>
#include <QDir>
#include <QDateTime>
#include <QImage>
#include <QSize>
#include <QFont>
#include <QPixmap>

PdfWriter::PdfWriter(QObject *parent) :
    QThread(parent)
{
    m_image = "";
}

void PdfWriter::create(const QList<QPair<QString, QString> > &content, const QString &image)
{
    if(content.isEmpty()) {
        qDebug() << "empty list at" << __PRETTY_FUNCTION__;
        return;
    }

    m_content = content;
    m_image = image;

    start();
}

void PdfWriter::run()
{
    printTags();
}

void PdfWriter::printTags()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    //printer.setResolution(QPrinter::HighResolution);

    //this could be asked from the user..
    printer.setOutputFileName(QString("%1/nametags-%2.pdf")
                              .arg(QDir::homePath())
                              .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmm")));

    QImage image;
    if(QFile::exists(m_image)) {
        image.load(m_image);
    }
    else {
        image.load(":/pics/summit-fi.jpg");
    }
    if(image.isNull()) qDebug() << "perkele";
    QPainter painter;
    painter.begin(&printer);
    QFont firstNameFont = painter.font();
    firstNameFont.setPointSize(40);

    QFont lastNameFont = painter.font();
    lastNameFont.setPointSize(24);

    QRectF upperHalf(0, 0, printer.pageRect().width(), printer.pageRect().height() / 2);
    qreal w = (upperHalf.width()/2);
    qreal h = (upperHalf.height()/2);
    QRectF upperFirstNameRect (w, h + h/3, w, h/3);
    QRectF upperLastNameRect (w, h + h/3, w, 2*h/3);
    QRectF lowerHalf(0, printer.pageRect().height() / 2, printer.pageRect().width(), printer.pageRect().height() / 2);

    painter.setPen(Qt::black);
    for(int i = 0; i < m_content.count(); i++) {
        // first name
        painter.setFont(firstNameFont);
        painter.setBrush(Qt::black);
        painter.drawImage(upperHalf, image, image.rect());
        painter.drawText(upperFirstNameRect, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);

        // last name
        painter.setFont(lastNameFont);
        painter.drawImage(lowerHalf, image);
        painter.drawText(upperLastNameRect, Qt::AlignCenter, m_content.at(i).second);

        // second name tag to the page if needed
        if(i+1 < m_content.count()) {
            i++;
            // first name
            painter.setFont(firstNameFont);
            painter.drawImage(upperHalf, image);
            //painter.drawText(QRect(0, 100, 100, 100), m_content.at(i).first);

            // last name
            painter.setFont(lastNameFont);
            painter.drawImage(lowerHalf, image);
            //painter.drawText(QRect(0, 174, 100, 100), m_content.at(i).second);
        }

        // next page if needed
        if(i + 1 < m_content.count()) {
            printer.newPage();
        }
    }

    painter.end();

    emit printingFinished();
}
