#include "mainview.h"
#include "namesmodel.h"
#include "nameparser.h"
#include "previewwidget.h"
#include "stringdelegate.h"
#include "tableview.h"
#include "pdfwriter.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>

#include <QDebug>

MainView::MainView(QWidget *parent) :
    QWidget(parent)
{
    m_picture = "pics/summit-fi.jpg";
    p_model = NamesModel::instance();
    p_table = new TableView;
    p_table->setAlternatingRowColors(true);
    p_table->horizontalHeader()->setStretchLastSection(true);
    p_table->setModel(p_model);
    p_delegate = new StringDelegate;
    p_table->setItemDelegate(p_delegate);
    p_table->setSelectionMode(QTableView::ExtendedSelection);
    p_table->setSelectionBehavior(QTableView::SelectRows);

    p_optionsBar = new QToolBar;

    p_preview = new PreviewWidget;

    p_vboxLayout = new QVBoxLayout;
    p_vboxLayout->addWidget(p_optionsBar);
    p_vboxLayout->addWidget(p_preview);

    p_hboxLayout = new QHBoxLayout;
    p_hboxLayout->addWidget(p_table, 2);
    p_hboxLayout->addLayout(p_vboxLayout, 5);

    setLayout(p_hboxLayout);

    createActions();

    p_pdfCreator = new PdfWriter(this);

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
        fileName = QFileDialog::getSaveFileName(this, tr("!!Save as.."), QDir::homePath());
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

void MainView::sendAllNamesToCreator()
{
    qDebug() << p_model->contents().count() << " name tags needs to be created";

    QString destFile = getSaveFileName();
    if(!destFile.isEmpty()) {
        p_pdfCreator->create(p_model->contents(), m_picture, destFile);
    }
}

void MainView::sendSelectedNamesToCreator()
{
    qDebug() << p_table->selectedContent().count() << " name tags needs to be created";

    QString destFile = getSaveFileName();
    if(!destFile.isEmpty()) {
        p_pdfCreator->create(p_table->selectedContent(), m_picture, destFile);
    }
}

void MainView::setPicture(const QString &file)
{
    if(file != m_picture) {
        p_preview->setPicture(file);
        m_picture = file;
    }
}

QString MainView::picture() const
{
    return m_picture;
}

QString MainView::getSaveFileName()
{
    QString destFile = QFileDialog::getSaveFileName(this, tr("Save as.."), QDir::homePath(), "PDF files (*.pdf)");
    //destFile = QString("%1/nametags-%2.pdf").arg(QDir::homePath()).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmm"));
    if(!destFile.isEmpty() && !destFile.toLower().endsWith(".pdf")) {
        destFile.append(".pdf");
    }
    return destFile;
}

void MainView::createActions()
{

    p_foldingGroup = new QActionGroup(this);
    p_simpleTagAction = p_foldingGroup->addAction(tr("!!simple"));
    p_simpleTagAction->setCheckable(true);
    p_simpleTagAction->setToolTip(tr("!!simpe tool tip"));

    p_onceFoldedTagAction = p_foldingGroup->addAction(tr("!!once"));
    p_onceFoldedTagAction->setCheckable(true);
    p_onceFoldedTagAction->setToolTip(tr("!!once folded tool tip"));

    p_twiceFolderTagAction = p_foldingGroup->addAction(tr("!!twice"));
    p_twiceFolderTagAction->setCheckable(true);
    p_twiceFolderTagAction->setChecked(true); //TODO settings
    p_twiceFolderTagAction->setToolTip(tr("!!twice folded tool tip"));

    p_foldingGroup->setExclusive(true);

    p_optionsBar->addActions(p_foldingGroup->actions());

    p_showRulerAction = p_optionsBar->addAction(tr("!!ruler"));
    p_showRulerAction->setCheckable(true);
    p_showRulerAction->setChecked(true); //TODO: settings
    p_showRulerAction->setToolTip(tr("!!rules tool tip"));

    p_alignmentGroup = new QActionGroup(this);

    p_leftAction = p_alignmentGroup->addAction(tr("!!left"));
    p_leftAction->setCheckable(true);
    p_leftAction->setToolTip(tr("!!left align tool tip"));

    p_centerAction = p_alignmentGroup->addAction(tr("!!center"));
    p_centerAction->setCheckable(true);
    p_centerAction->setChecked(true);
    p_centerAction->setToolTip(tr("!!center align tool tip"));

    p_rightAction = p_alignmentGroup->addAction(tr("!!right"));
    p_rightAction->setCheckable(true);
    p_rightAction->setToolTip(tr("!!right align tool tip"));

    p_alignmentGroup->setExclusive(true);

    p_optionsBar->addActions(p_alignmentGroup->actions());
}
