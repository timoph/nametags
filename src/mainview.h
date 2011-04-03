#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QModelIndex>

class TableView;
class QHBoxLayout;
class NamesModel;
class PreviewWidget;
class StringDelegate;
class PdfWriter;

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

signals:

public slots:
    void updateSampleTag(const QModelIndex &index);

private:
    NamesModel *p_model;
    TableView *p_table;
    QHBoxLayout *p_hboxLayout;
    PreviewWidget *p_preview;
    StringDelegate *p_delegate;
    PdfWriter *p_pdfCreator;

    QString m_picture;
};

#endif // MAINVIEW_H
