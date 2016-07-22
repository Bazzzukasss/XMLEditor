#include <QDebug>
#include <QFileDialog>
#include <QFont>

#include "xmlwidget.h"
#include "xmlprocessor.h"

XMLWidget::XMLWidget(QWidget *parent)
    :QFrame(parent)
{
    mModel = nullptr;
    mSelectionModel = nullptr;
    mTreeView = new QTreeView(this);
    mCurrentFileLabel = new QLabel(this);
    updateFileLabel("");
    mModel =  new TreeModel(":/res/res/xml_source_format.xml");
    mTreeView->setModel(mModel);
    mTreeView->expandAll();
    slotViewResize();

    mSelectionModel = new QItemSelectionModel(mModel,this);
    mTreeView->setSelectionModel(mSelectionModel);

    connect(mTreeView,          SIGNAL(expanded(QModelIndex)),  this,   SLOT(slotViewResize()));
    connect(mTreeView,          SIGNAL(collapsed(QModelIndex)), this,   SLOT(slotViewResize()));

    build();
}

XMLWidget::~XMLWidget()
{
    delete mModel;
}

void XMLWidget::build()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(mCurrentFileLabel);
    mainLayout->addWidget(mTreeView);

    mainLayout->setMargin(2);
    mainLayout->setSpacing(4);
}

//SLOTS
void XMLWidget::slotOpen()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", mModel->getFileName(), "files(*.xml )");
    if(!filename.isEmpty())
    {
        delete mModel;
        mModel = new TreeModel(filename);
        mTreeView->setModel(mModel);
        mTreeView->expandAll();
        updateFileLabel(filename);
    }
}
void XMLWidget::slotSave()
{
    mModel->Save();
}
void XMLWidget::slotSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file", mModel->getFileName(), "files(*.xml )");
    if(!filename.isEmpty())
    {
        mModel->Save(filename);
        updateFileLabel(filename);
    }
}

void XMLWidget::slotToOldFormat()
{

}

void XMLWidget::slotToNewFormat()
{

}

void XMLWidget::slotViewResize()
{
    for(int column=0;column<mModel->columnCount();++column)
        mTreeView->resizeColumnToContents(column);
}

void XMLWidget::slotRevertAll()
{
    //emit mModel->signalRevertAll();
    emit mModel->layoutChanged();
}

void XMLWidget::slotInsert()
{
    QModelIndex index = mSelectionModel->currentIndex();

    if (!mModel->insertRow(index.row()+1, index.parent()))
        return;

    for (int column = 0; column < mModel->columnCount(index.parent()); ++column)
    {
        QModelIndex child = mModel->index(index.row()+1, column, index.parent());
        mModel->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}
void XMLWidget::slotDelete()
{
    QModelIndex index = mSelectionModel->currentIndex();
    mModel->removeRow(index.row(), index.parent());
}
void XMLWidget::updateFileLabel(const QString& filename)
{
    mCurrentFileLabel->setText("<b>Curent file  :   </b>" + filename);
}
