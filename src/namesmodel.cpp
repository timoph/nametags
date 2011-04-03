#include "namesmodel.h"

NamesModel::NamesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int NamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_content.count();
}

int NamesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant NamesModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(index.isValid()) {
        if(index.column() == 0) {
            return m_content.at(index.row()).first;
        }
        else if(index.column() == 1) {
            return m_content.at(index.row()).second;
        }
    }

    return QVariant();
}

void NamesModel::setContent(const QList<QPair<QString, QString> > &content)
{
    m_content = content;
    reset();
}

QVariant NamesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Vertical) {
        return section + 1;
    }
    else {
        if(section == 0) {
            return tr("First name");
        }
        else if(section == 1) {
            return tr("Last name");
        }
        else {
            return QVariant();
        }
    }

    return QVariant();
}

bool NamesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

Qt::ItemFlags NamesModel::flags(const QModelIndex &index) const
{
    if(index.isValid()) {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    return !Qt::ItemIsEnabled;
}

QList<QPair<QString,QString> > NamesModel::contents() const
{
    return m_content;
}
