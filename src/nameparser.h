#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include <QThread>
#include <QList>
#include <QPair>

class NameParser : public QThread
{
    Q_OBJECT
public:
    static NameParser *instance();
    void readNames(const QString &file);
    QString separator() const;
    QString fileName() const;

signals:
    void namesRead(const QList<QPair<QString, QString> > &names);
    void error(const QString &msg);

public slots:
    void setSeparator(const QString &str);

protected:
    void run();

private:
    explicit NameParser(QObject *parent = 0);
    void readNamesFile();
    void parseContent(const QStringList &content);

    QString m_separator;
    static NameParser *p_instance;
    QString m_fileName;
};

#endif // NAMEPARSER_H
