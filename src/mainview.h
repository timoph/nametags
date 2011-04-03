#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QModelIndex>

class TableView;
class QHBoxLayout;
class NamesModel;
class PreviewWidget;
class StringDelegate;

class MainView : public QWidget
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);
    void saveInTxtFile();
    void sendAllNamesToCreator();
    void sendSelectedNamesToCreator();

signals:

public slots:
    void updateSampleTag(const QModelIndex &index);

private:
    NamesModel *p_model;
    TableView *p_table;
    QHBoxLayout *p_hboxLayout;
    PreviewWidget *p_preview;
    StringDelegate *p_delegate;
};

#endif // MAINVIEW_H
