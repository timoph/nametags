#ifndef STRINGDELEGATE_H
#define STRINGDELEGATE_H

#include <QItemDelegate>

class StringDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit StringDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // STRINGDELEGATE_H
