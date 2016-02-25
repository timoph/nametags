#include "previewwidget.h"

#include <QVBoxLayout>
#ifndef QT5BUILD
#include <QDeclarativeView>
#else
#include <QQuickView>
#include <QQuickItem>
#include <QWidget>
#endif
#include <QGraphicsObject>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
#ifndef QT5BUILD
    p_qmlView = new QDeclarativeView();
    p_qmlView->setSource(QUrl("qrc:/preview.qml"));
    p_qmlView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
#else
    p_qmlView = new QQuickView();
    p_qmlView->setSource(QUrl("qrc:/preview.qml"));
    p_qmlView->setResizeMode(QQuickView::SizeRootObjectToView);
#endif
    p_rootObject = p_qmlView->rootObject();

    // https://bugreports.qt-project.org/browse/QTBUG-25643 - needs to be fixed in Qt
    p_vbox = new QVBoxLayout;
#ifdef QT5BUILD
	p_vbox->addWidget(QWidget::createWindowContainer(p_qmlView));
#else
	p_vbox->addWidget(p_qmlView);
#endif

    setLayout(p_vbox);
}

void PreviewWidget::setPicture(const QString &file)
{
    QObject *bg = p_rootObject->findChild<QObject *>("bgimage");
    if(bg) {
        bg->setProperty("source", file);
    }
}

void PreviewWidget::setNameText(const QString &first, const QString &last)
{
    QObject *firstName = p_rootObject->findChild<QObject *>("firstname");
    if(firstName) {
        firstName->setProperty("text", first);
    }

    QObject *lastName = p_rootObject->findChild<QObject *>("lastname");
    if(lastName) {
        lastName->setProperty("text", last);
    }
}
