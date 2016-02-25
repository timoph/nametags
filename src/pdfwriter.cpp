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
#include <QFontMetrics>

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
        image.load(":/pics/badge.png");
    }

    QPainter painter;
    painter.begin(&printer);
    QFont firstNameFont = painter.font();
    firstNameFont.setPointSize(26);
    QFontMetrics fontMetrics(firstNameFont);
    int halfFontHeight = fontMetrics.height() / 1.1;

    QFont lastNameFont = painter.font();
    lastNameFont.setPointSize(20);
    //TODO: fixme - this is ugly
    QRectF upperHalf(0, 0, printer.pageRect().width() / 2, printer.pageRect().height() / 4);
    qreal w = (upperHalf.width() / 2);
    qreal h = (upperHalf.height() / 2);
    QRectF upperFirstNameRect (w/2, h - halfFontHeight, w, h/2);
    QRectF upperLastNameRect (w/2, h + halfFontHeight, w, h/2);

    QRectF upperHalf2(printer.pageRect().width() / 2, 0, printer.pageRect().width() / 2, printer.pageRect().height() / 4); //2);
    QRectF upperFirstNameRect2 (printer.pageRect().width() / 2 + w/2, h - halfFontHeight, w, h/2);
    QRectF upperLastNameRect2 (printer.pageRect().width() / 2 + w/2, h + halfFontHeight, w, h/2);

    QRectF lowerHalf(0, printer.pageRect().height() / 4, printer.pageRect().width() / 2, printer.pageRect().height() / 4);
    QRectF lowerFirstNameRect (w/2, upperHalf.height() + h - halfFontHeight, w, h/2);
    QRectF lowerLastNameRect (w/2, upperHalf.height() + h + halfFontHeight, w, h/2);

    QRectF lowerHalf2(printer.pageRect().width() / 2, printer.pageRect().height() / 4, printer.pageRect().width() / 2, printer.pageRect().height() / 4);
    QRectF lowerFirstNameRect2 (printer.pageRect().width() / 2 + w/2, lowerHalf2.height() + h - halfFontHeight, w, h/2);
    QRectF lowerLastNameRect2 (printer.pageRect().width() / 2 + w/2, lowerHalf2.height() + h + halfFontHeight, w, h/2);

    QRectF upperHalf3(0, printer.pageRect().height() / 2, printer.pageRect().width() / 2, printer.pageRect().height() / 4); //2);
    QRectF upperFirstNameRect3 (w/2, printer.pageRect().height() / 2 + h - halfFontHeight, w, h/2);
    QRectF upperLastNameRect3 (w/2, printer.pageRect().height() / 2 + h + halfFontHeight, w, h/2);

    QRectF upperHalf4(printer.pageRect().width() / 2, printer.pageRect().height() / 2, printer.pageRect().width() / 2, printer.pageRect().height() / 4); //2);
    QRectF upperFirstNameRect4 (printer.pageRect().width() / 2 + w/2, printer.pageRect().height() / 2 + h - halfFontHeight, w, h/2);
    QRectF upperLastNameRect4 (printer.pageRect().width() / 2 + w/2, printer.pageRect().height() / 2 + h + halfFontHeight, w, h/2);

    QRectF lowerHalf3(0, 3* printer.pageRect().height() / 4, printer.pageRect().width() / 2, printer.pageRect().height() / 4);
    QRectF lowerFirstNameRect3 (w/2, 3 * printer.pageRect().height() / 4 + h - halfFontHeight, w, h/2);
    QRectF lowerLastNameRect3 (w/2, 3 * printer.pageRect().height() / 4 + h + halfFontHeight, w, h/2);

    QRectF lowerHalf4(printer.pageRect().width() / 2, 3 * printer.pageRect().height() / 4, printer.pageRect().width() / 2, printer.pageRect().height() / 4);
    QRectF lowerFirstNameRect4 (printer.pageRect().width() / 2 + w/2, 3 * printer.pageRect().height() / 4 + h - halfFontHeight, w, h/2);
    QRectF lowerLastNameRect4 (printer.pageRect().width() / 2 + w/2, 3 * printer.pageRect().height() / 4 + h + halfFontHeight, w, h/2);

    painter.setPen(Qt::black);


    for(int i = 0; i < m_content.count(); i++) {
        // first name
        painter.setFont(firstNameFont);
        painter.drawImage(upperHalf, image, image.rect());
        while(fontMetrics.boundingRect(m_content.at(i).first).width() >= upperFirstNameRect.width()) {
            firstNameFont.setPixelSize(firstNameFont.pixelSize() - 1);
            if(firstNameFont.pixelSize() < 8) break;
        }
        painter.drawText(upperFirstNameRect, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);

        // last name
        painter.setFont(lastNameFont);
        painter.drawText(upperLastNameRect, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(upperHalf2, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(upperFirstNameRect2, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(upperLastNameRect2, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

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

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(lowerHalf2, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(lowerFirstNameRect2, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(lowerLastNameRect2, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(upperHalf3, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(upperFirstNameRect3, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(upperLastNameRect3, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(upperHalf4, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(upperFirstNameRect4, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(upperLastNameRect4, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(lowerHalf3, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(lowerFirstNameRect3, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(lowerLastNameRect3, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
        }

        if(i+1 < m_content.count()) {
            i++;
            painter.drawImage(lowerHalf4, image);
            // first name
            painter.setFont(firstNameFont);
            painter.drawText(lowerFirstNameRect4, Qt::AlignHCenter | Qt::AlignBottom, m_content.at(i).first);
            // last name
            painter.setFont(lastNameFont);
            painter.drawText(lowerLastNameRect4, Qt::AlignHCenter | Qt::AlignTop, m_content.at(i).second);
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
