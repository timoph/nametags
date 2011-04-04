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
    m_output = "";
}

void PdfWriter::create(const QList<QPair<QString, QString> > &content, const QString &image, const QString &outPut)
{
    if(content.isEmpty()) {
        qDebug() << "empty list at" << __PRETTY_FUNCTION__;
        return;
    }

    m_content = content;
    m_image = image;
    m_output = outPut;

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
    printer.setOutputFileName(m_output);

    QImage image;
    if(QFile::exists(m_image)) {
        image.load(m_image);
    }
    else {
        image.load(":/pics/summit-fi.jpg");
    }

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
    QRectF upperLastNameRect (w, h + 2*h/3, w, h/3);

    QRectF lowerHalf(0, printer.pageRect().height() / 2, printer.pageRect().width(), printer.pageRect().height() / 2);
    QRectF lowerFirstNameRect (w, upperHalf.height() + h + h/3, w, h/3);
    QRectF lowerLastNameRect (w, upperHalf.height() + h + 2*h/3, w, h/3);
    painter.setPen(Qt::black);
    for(int i = 0; i < m_content.count(); i++) {
        // first name
        painter.setFont(firstNameFont);
        painter.drawImage(upperHalf, image, image.rect());
        painter.drawText(upperFirstNameRect, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);

        // last name
        painter.setFont(lastNameFont);
        painter.drawText(upperLastNameRect, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);

        // second name tag to the page if needed
        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(lowerHalf, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(lowerFirstNameRect, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(lowerLastNameRect, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

        // next page if needed
        if(i + 1 < m_content.count()) {
            printer.newPage();
        }
    }

    painter.end();

    m_output = "";
    m_image = "";
    emit printingFinished();
}
