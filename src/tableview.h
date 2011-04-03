#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
    QList<QPair<QString,QString> > selectedContent() const;

signals:

public slots:

};

#endif // TABLEVIEW_H
