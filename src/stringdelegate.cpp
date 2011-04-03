#include "stringdelegate.h"
#include <QLineEdit>
#include <QModelIndex>
#include <QVariant>

StringDelegate::StringDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *StringDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    if(index.isValid()) {
        return new QLineEdit(index.data().toString(), parent);
    }
    else {
        return new QWidget(parent);
    }
}

void StringDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.isValid()) {
        QLineEdit *e = qobject_cast<QLineEdit *>(editor);
        if(e) {
            e->setText(index.data().toString());
        }
    }
}

void StringDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
}

QSize StringDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index);
}
