#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QModelIndex>

class QTableView;
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

signals:

public slots:
    void updateSampleTag(const QModelIndex &index);

private:
    NamesModel *p_model;
    QTableView *p_table;
    QHBoxLayout *p_hboxLayout;
    PreviewWidget *p_preview;
    StringDelegate *p_delegate;
};

#endif // MAINVIEW_H
