#include "previewwidget.h"

#include <QFile>
#include <QVBoxLayout>
#include <QDeclarativeView>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    p_qmlView = new QDeclarativeView();
    p_qmlView->setSource(QUrl::fromLocalFile("src/preview.qml"));
    p_qmlView->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    p_vbox = new QVBoxLayout;
    p_vbox->addWidget(p_qmlView);

    setLayout(p_vbox);
}

void PreviewWidget::setPicture(const QString &file)
{

}

