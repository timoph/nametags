#include "mainwindow.h"
#include "mainview.h"
#include "nameparser.h"
#include "namesmodel.h"

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QFileDialog>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // file menu
    p_fileMenu = menuBar()->addMenu(tr("&File"));

    p_readNamesAction = new QAction(tr("Import from file.."), this);
    p_fileMenu->addAction(p_readNamesAction);
    connect(p_readNamesAction, SIGNAL(triggered()),
            this, SLOT(readNamesTriggered()));

    p_saveListAction = new QAction(tr("Save.."), this);
    p_fileMenu->addAction(p_saveListAction);
    connect(p_saveListAction, SIGNAL(triggered()),
            this, SLOT(saveListTriggered()));

    p_fileMenu->addSeparator();

    p_toolBarVisibleAction = new QAction(tr("Show toolbar"), this);
    p_toolBarVisibleAction->setCheckable(true);
    p_toolBarVisibleAction->setChecked(true);
    p_fileMenu->addAction(p_toolBarVisibleAction);
    connect(p_toolBarVisibleAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleToolBarVisible(bool)));

    p_fileMenu->addSeparator();

    p_quitAction = new QAction(tr("Quit"), this);
    connect(p_quitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    p_fileMenu->addAction(p_quitAction);

    // edit menu
    p_editMenu = menuBar()->addMenu(tr("&Edit"));

    p_addRowAction = new QAction(tr("Add row"), this);
    p_editMenu->addAction(p_addRowAction);
    connect(p_addRowAction, SIGNAL(triggered()),
            this, SLOT(addRowTriggered()));

    p_selectPictureAction = new QAction(tr("Select picture.."), this);
    p_editMenu->addAction(p_selectPictureAction);
    connect(p_selectPictureAction, SIGNAL(triggered()),
            this, SLOT(selectPictureTriggered()));

    // tags menu
    p_tagsMenu = menuBar()->addMenu(tr("&Name tags"));

    p_createPdfAction = new QAction(tr("Create PDFs"), this);
    p_tagsMenu->addAction(p_createPdfAction);
    connect(p_createPdfAction, SIGNAL(triggered()),
            this, SLOT(createPdfTriggered()));

    p_createPdfFromSelectedAction = new QAction(tr("Create PDFs from selected"), this);
    p_tagsMenu->addAction(p_createPdfFromSelectedAction);
    connect(p_createPdfFromSelectedAction, SIGNAL(triggered()),
            this, SLOT(createSelectedPdfTriggered()));

    // toolbar
    p_toolBar = addToolBar(tr("actions"));
    //p_toolBar->addAction(p_readNamesAction);
    p_toolBar->addAction(p_addRowAction);
    p_toolBar->addAction(p_createPdfAction);
    p_toolBar->addAction(p_createPdfFromSelectedAction);
    //p_toolBar->setVisible(false);

    p_mainView = new MainView;
    setCentralWidget(p_mainView);
}

void MainWindow::readNamesTriggered()
{
    // select file
    QString file = QFileDialog::getOpenFileName(this, tr("Select names file"),
                                 QDir::homePath(),
                                 "Text files (*.txt);;All files (*.*)");

    NameParser::instance()->readNames(file);
}

void MainWindow::createPdfTriggered()
{
    p_mainView->sendAllNamesToCreator();
}

void MainWindow::saveListTriggered()
{
    p_mainView->saveInTxtFile();
}

void MainWindow::appendNameTriggered()
{
    qDebug() << "not implemented yet";
}

void MainWindow::createSelectedPdfTriggered()
{
    p_mainView->sendSelectedNamesToCreator();
}

void MainWindow::addRowTriggered()
{
    NamesModel::instance()->insertRow(NamesModel::instance()->contents().count());
}

void MainWindow::selectPictureTriggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select names file"),
                                 QDir::homePath(),
                                 "Images (*.jpg *.png *.bmp)");

    p_mainView->setPicture(file);
}

void MainWindow::toggleToolBarVisible(bool visible)
{
    p_toolBar->setVisible(visible);
}
