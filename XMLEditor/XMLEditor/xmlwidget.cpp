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

    mSelectionModel = new QItemSelectionModel(mModel);
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
        //delete mSelectionModel;

        mModel = new TreeModel(filename);
        //mSelectionModel = new QItemSelectionModel(mModel);


        mTreeView->setModel(mModel);
        //mTreeView->setSelectionModel(mSelectionModel);

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

void XMLWidget::slotInsertSubTag()
{
    QModelIndex index = mTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = mTreeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        //if (!model->headerData(column, Qt::Horizontal).isValid())
          //  model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    mTreeView->selectionModel()->setCurrentIndex(model->index(0, 0, index), QItemSelectionModel::ClearAndSelect);
}

void XMLWidget::slotInsertTag()
{
    QModelIndex index = mTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = mTreeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
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
