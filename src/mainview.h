#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QModelIndex>

class TableView;
class QHBoxLayout;
class QVBoxLayout;
class NamesModel;
class PreviewWidget;
class StringDelegate;
class PdfWriter;
class QToolBar;
class QAction;
class QActionGroup;

class MainView : public QWidget
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);
    void saveInTxtFile();
    void sendAllNamesToCreator();
    void sendSelectedNamesToCreator();
    void setPicture(const QString &file);
    QString picture() const;
    QString getSaveFileName();

signals:

public slots:
    void updateSampleTag(const QModelIndex &index);

private:
    void createActions();

    NamesModel *p_model;
    TableView *p_table;
    QHBoxLayout *p_hboxLayout;
    QVBoxLayout *p_vboxLayout;
    PreviewWidget *p_preview;
    StringDelegate *p_delegate;
    PdfWriter *p_pdfCreator;
    QToolBar *p_optionsBar;

    //Actions
    QAction *p_simpleTagAction;
    QAction *p_onceFoldedTagAction;
    QAction *p_twiceFolderTagAction;
    QAction *p_showRulerAction;
    QAction *p_leftAction;
    QAction *p_centerAction;
    QAction *p_rightAction;

    QActionGroup *p_alignmentGroup;
    QActionGroup *p_foldingGroup;

    QString m_picture;
};

#endif // MAINVIEW_H
