#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

class QDeclarativeView;
class QVBoxLayout;

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    QSize sizeHint();

signals:

public slots:
    void setPicture(const QString &file);

private:
    QDeclarativeView *p_qmlView;
    QVBoxLayout *p_vbox;
};

#endif // PREVIEWWIDGET_H
