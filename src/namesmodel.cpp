#include "namesmodel.h"

#include <QItemSelection>

#include <QDebug>

NamesModel *NamesModel::p_instance = 0;

NamesModel::NamesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

NamesModel *NamesModel::instance()
{
    if(!p_instance) {
        p_instance = new NamesModel;
    }

    return p_instance;
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
    if(role != Qt::EditRole) {
        return false;
    }
    else {
        //qDebug() << __PRETTY_FUNCTION__;
        QPair<QString,QString> pair = m_content.at(index.row());
        if(index.column() == 0) {
            pair.first = value.toString();
            m_content[index.row()] = pair;
            return true;
        }
        else if(index.column() == 1) {
            pair.second = value.toString();
            m_content[index.row()] = pair;
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

Qt::ItemFlags NamesModel::flags(const QModelIndex &index) const
{
    if(index.isValid()) {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return !Qt::ItemIsEnabled;
}

QList<QPair<QString,QString> > NamesModel::contents() const
{
    return m_content;
}

bool NamesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int i = 0; i < count; i++) {
        QPair<QString,QString> pair("","");
        m_content.append(pair);
    }
    endInsertRows();

    return true;
}
