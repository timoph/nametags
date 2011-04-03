#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenu;
class QToolBar;
class QAction;
class MainView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void readNamesTriggered();
    void createPdfTriggered();
    void saveListTriggered();
    void appendNameTriggered();
    void createSelectedPdfTriggered();

private:
    QMenu *p_fileMenu;
    QToolBar *p_toolBar;
    QAction *p_quitAction;
    QAction *p_createPdfAction;
    QAction *p_readNamesAction;
    QAction *p_saveListAction;
    QAction *p_appendNameAction;
    QAction *p_createPdfFromSelectedAction;
    MainView *p_mainView;
};

#endif // MAINWINDOW_H
