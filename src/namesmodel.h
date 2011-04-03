#ifndef NAMESMODEL_H
#define NAMESMODEL_H

#include <QAbstractTableModel>

class NamesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    static NamesModel *instance();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QList<QPair<QString,QString> > contents() const;

signals:

public slots:
    void setContent(const QList<QPair<QString,QString> > &content);

private:
    explicit NamesModel(QObject *parent = 0);
    QList<QPair<QString,QString> > m_content;
    static NamesModel *p_instance;
};

#endif // NAMESMODEL_H
