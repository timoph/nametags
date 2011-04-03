#include "previewwidget.h"

#include <QFile>
#include <QVBoxLayout>
#include <QDeclarativeView>
#include <QGraphicsObject>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    p_qmlView = new QDeclarativeView();
    p_qmlView->setSource(QUrl::fromLocalFile("src/preview.qml"));
    p_qmlView->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    p_rootObject = p_qmlView->rootObject();

    p_vbox = new QVBoxLayout;
    p_vbox->addWidget(p_qmlView);

    setLayout(p_vbox);
}

void PreviewWidget::setPicture(const QString &file)
{

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
