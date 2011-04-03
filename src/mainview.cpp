#include "mainview.h"
#include "namesmodel.h"
#include "nameparser.h"
#include "previewwidget.h"
#include "stringdelegate.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <QDebug>

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
    p_table->setSelectionMode(QTableView::ExtendedSelection);
    p_table->setSelectionBehavior(QTableView::SelectRows);

    p_preview = new PreviewWidget;

    p_hboxLayout = new QHBoxLayout;
    p_hboxLayout->addWidget(p_table, 2);
    p_hboxLayout->addWidget(p_preview, 5);

    setLayout(p_hboxLayout);

    connect(NameParser::instance(), SIGNAL(namesRead(QList<QPair<QString,QString> >)),
            p_model, SLOT(setContent(QList<QPair<QString,QString> >)), Qt::DirectConnection);

    connect(p_table, SIGNAL(clicked(QModelIndex)),
            this, SLOT(updateSampleTag(QModelIndex)));
}

void MainView::updateSampleTag(const QModelIndex &index)
{
    //qDebug() << p_model->data(index, Qt::DisplayRole).toString();
    //qDebug() << p_model->contents().at(index.row()).first << " " << p_model->contents().at(index.row()).second;
    p_preview->setNameText(p_model->contents().at(index.row()).first, p_model->contents().at(index.row()).second);
}

void MainView::saveInTxtFile()
{
    int rows = p_model->rowCount(QModelIndex());

    if(rows < 1) {
        qDebug() << "empty model at " << __PRETTY_FUNCTION__;
        return;
    }

    QList<QPair<QString,QString> > content = p_model->contents();

    QString fileName = NameParser::instance()->fileName();

    // in case no file has been opened
    if(fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, tr("Save as.."), QDir::homePath());
    }

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)) {
        qDebug() << "failed to open file for writing at " << __PRETTY_FUNCTION__;
        return;
    }

    QTextStream out(&file);
    QString sep = NameParser::instance()->separator();

    // this could be done in a better way
    QString output = "";
    for(int i = 0; i < content.count(); i++) {
        output.append(QString("%1%2%3\n")
                .arg(content.at(i).first)
                .arg(sep)
                .arg(content.at(i).second));
    }

    out << output;

    file.close();
}
