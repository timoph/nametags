#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

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

signals:

public slots:
    void updateSampleTag();

private:
    NamesModel *p_model;
    QTableView *p_table;
    QHBoxLayout *p_hboxLayout;
    PreviewWidget *p_preview;
    StringDelegate *p_delegate;
};

#endif // MAINVIEW_H
