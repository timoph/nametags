#include "nameparser.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

#include <QDebug>

NameParser *NameParser::p_instance = 0;

NameParser::NameParser(QObject *parent) :
    QThread(parent)
{
    m_separator = "#";
    m_fileName = "";
}

NameParser *NameParser::instance()
{
    if(!p_instance) {
        p_instance = new NameParser;
    }
    return p_instance;
}

void NameParser::readNames(const QString &file)
{
    if(isRunning()) {
        qDebug() << "thread already running";
        return;
    }
    else {
        m_fileName = file;
        start();
    }
}

void NameParser::readNamesFile()
{
    if(!QFile::exists(m_fileName)) {
        emit error(tr("Specified file does not exist"));
        return;
    }
    else {
        QFile file(m_fileName);
        if(file.open(QFile::ReadOnly)) {
            QTextStream in(&file);
            QStringList content;
            while(!in.atEnd()) {
                content.append(in.readLine());
            }
            if(!content.isEmpty()) {
                parseContent(content);
            }
            else {
                emit error(tr("No content found from the specified file"));
            }
        }
        else {
            emit error(tr("Opening for reading failed"));
            return;
        }
    }
}

void NameParser::parseContent(const QStringList &content)
{
    QList<QPair<QString, QString> > names;
    foreach(QString s, content) {
        QStringList l = s.split(m_separator);
        if(l.count() != 2) {
            qDebug() << "Skipping faulty line: " << l.join(" ");
            continue;
        }
        else {
            names.append(QPair<QString,QString>(l.at(0), l.at(1)));
        }
    }

    namesRead(names);
}

QString NameParser::separator() const
{
    return m_separator;
}

void NameParser::setSeparator(const QString &str)
{
    m_separator = str;
}

void NameParser::run()
{
    readNamesFile();
}

QString NameParser::fileName() const
{
    return m_fileName;
}
