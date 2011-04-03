#include "mainview.h"
#include "namesmodel.h"
#include "nameparser.h"
#include "previewwidget.h"
#include "stringdelegate.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>

MainView::MainView(QWidget *parent) :
    QWidget(parent)
{
    p_model = new NamesModel;
    p_table = new QTableView;
    p_table->setAlternatingRowColors(true);
    p_table->horizontalHeader()->setStretchLastSection(true);
    p_table->setModel(p_model);
    p_delegate = new StringDelegate;
    p_table->setItemDelegate(p_delegate);

    p_preview = new PreviewWidget;

    p_hboxLayout = new QHBoxLayout;
    p_hboxLayout->addWidget(p_table, 2);
    p_hboxLayout->addWidget(p_preview, 5);

    setLayout(p_hboxLayout);

    connect(NameParser::instance(), SIGNAL(namesRead(QList<QPair<QString,QString> >)),
            p_model, SLOT(setContent(QList<QPair<QString,QString> >)), Qt::DirectConnection);
}

void MainView::updateSampleTag()
{

}
