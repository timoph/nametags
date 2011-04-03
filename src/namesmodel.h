#ifndef NAMESMODEL_H
#define NAMESMODEL_H

#include <QAbstractTableModel>

class NamesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit NamesModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:
    void setContent(const QList<QPair<QString,QString> > &content);

private:
    QList<QPair<QString,QString> > m_content;
};

#endif // NAMESMODEL_H
