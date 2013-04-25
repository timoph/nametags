#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#ifndef QT5BUILD
class QDeclarativeView;
class QGraphicsObject;
#else
class QQuickView;
class QQuickItem;
#endif
class QVBoxLayout;

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
#ifndef QT5BUILD
    QDeclarativeView *p_qmlView;
    QGraphicsObject *p_rootObject;
#else
    QQuickView *p_qmlView;
    QQuickItem *p_rootObject;
#endif
    QVBoxLayout *p_vbox;
};

#endif // PREVIEWWIDGET_H
