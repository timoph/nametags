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
    void addRowTriggered();
    void selectPictureTriggered();
    void toggleToolBarVisible(bool visible);

private:
    QMenu *p_fileMenu;
    QMenu *p_editMenu;
    QMenu *p_tagsMenu;
    QToolBar *p_toolBar;
    QAction *p_quitAction;
    QAction *p_createPdfAction;
    QAction *p_readNamesAction;
    QAction *p_saveListAction;
    QAction *p_appendNameAction;
    QAction *p_createPdfFromSelectedAction;
    QAction *p_addRowAction;
    QAction *p_selectPictureAction;
    QAction *p_toolBarVisibleAction;
    MainView *p_mainView;
};

#endif // MAINWINDOW_H
