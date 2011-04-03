#include "mainwindow.h"
#include "mainview.h"
#include "nameparser.h"

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
    // menu
    p_fileMenu = menuBar()->addMenu(tr("&file"));

    p_readNamesAction = new QAction(tr("Read file"), this);
    p_fileMenu->addAction(p_readNamesAction);
    connect(p_readNamesAction, SIGNAL(triggered()),
            this, SLOT(readNamesTriggered()));

    p_saveListAction = new QAction(tr("Save.."), this);
    p_fileMenu->addAction(p_saveListAction);
    connect(p_saveListAction, SIGNAL(triggered()),
            this, SLOT(saveListTriggered()));

    p_createPdfAction = new QAction(tr("Create PDFs"), this);
    connect(p_createPdfAction, SIGNAL(triggered()),
            this, SLOT(createPdfTriggered()));

    p_createPdfFromSelectedAction = new QAction(tr("Create PDFs from selected"), this);
    p_fileMenu->addAction(p_createPdfFromSelectedAction);
    connect(p_createPdfFromSelectedAction, SIGNAL(triggered()),
            this, SLOT(createSelectedPdfTriggered()));

    p_fileMenu->addSeparator();

    p_quitAction = new QAction(tr("quit"), this);
    connect(p_quitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    p_fileMenu->addAction(p_quitAction);

    // toolbar
    p_toolBar = addToolBar(tr("actions"));
    p_toolBar->addAction(p_readNamesAction);

    // disable some action in the start
    p_createPdfAction->setEnabled(false);

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
    qDebug() << "not implemented yet";
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
    qDebug() << "not implemented yet";
}
