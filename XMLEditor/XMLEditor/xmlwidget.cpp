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
    setCurrentFileName("");
    mModel =  new XMLModel();
    mRootNode = 0;
    mTreeView->setModel(mModel);

    mSelectionModel = new QItemSelectionModel(mModel,this);
    mTreeView->setSelectionModel(mSelectionModel);

    //connect(mTreeView,          SIGNAL(expanded(QModelIndex)),  this,   SLOT(slotViewResize()));
    //connect(mTreeView,          SIGNAL(collapsed(QModelIndex)), this,   SLOT(slotViewResize()));

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
    QString filename = QFileDialog::getOpenFileName(this, "Open file", mCurrentFileName, "files(*.xml )");
    if(!filename.isEmpty())
    {
        setCurrentFileName(filename);
        mRootNode = new XMLNode();
        XMLProcessor::Load(filename,mRootNode);
        mModel->setRootNode(mRootNode);
    }
}
void XMLWidget::slotSave()
{
    XMLProcessor::Save(QString(mCurrentFileName),mRootNode);
}
void XMLWidget::slotSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file", mCurrentFileName, "files(*.xml )");
    if(!filename.isEmpty())
    {
        setCurrentFileName(filename);
        slotSave();
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
    for(int column=0;column<5;++column)
        mTreeView->resizeColumnToContents(column);
}

void XMLWidget::slotRevertAll()
{
    emit mModel->signalRevertAll();
    emit mModel->layoutChanged();
}

void XMLWidget::setCurrentFileName(const QString& filename)
{
    mCurrentFileName = filename;
    mCurrentFileLabel->setText("<b>Curent file  :   </b>" + mCurrentFileName);
}
