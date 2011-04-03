#include "tableview.h"
#include "namesmodel.h"

#include <QDebug>

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
}

QList<QPair<QString,QString> > TableView::selectedContent() const
{
    QList<QPair<QString,QString> > content;

    QModelIndexList list = selectedIndexes();

    //qDebug() << "list size is" << list.count() << "at" << __PRETTY_FUNCTION__;

    if(list.count() > 0) {
        int lastrow = -1;
        for(int i = 0; i < list.count(); i++) {
            if(list.at(i).row() == lastrow) {
                continue;
            }
            else {
                QString fn = NamesModel::instance()->contents().at(list.at(i).row()).first;
                QString ln = NamesModel::instance()->contents().at(list.at(i).row()).second;
                content.append(QPair<QString,QString>(fn,ln));
                //qDebug() << fn << ln;
                lastrow = list.at(i).row();
            }
        }
    }

    return content;
}
