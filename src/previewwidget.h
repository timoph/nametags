#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

class QDeclarativeView;
class QVBoxLayout;
class QGraphicsObject;

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    QSize sizeHint();
    void setNameText(const QString &first, const QString &last);

signals:

public slots:
    void setPicture(const QString &file);

private:
    QDeclarativeView *p_qmlView;
    QVBoxLayout *p_vbox;
    QGraphicsObject *p_rootObject;
};

#endif // PREVIEWWIDGET_H
