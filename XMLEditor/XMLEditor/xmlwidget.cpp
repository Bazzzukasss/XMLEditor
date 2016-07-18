#include <QDebug>
#include <QFileDialog>
#include <QFont>

#include "xmlwidget.h"
#include "xmlprocessor.h"

XMLWidget::XMLWidget(QWidget *parent)
    :QFrame(parent)
{
    mTreeView = new QTreeView(this);
    mCurrentFileLabel = new QLabel("<b>Configuration  :   </b>" + mCurrentFileName,this);

    mModel =  new XMLModel(this);
    mSelectionModelTree = new QItemSelectionModel(mModel,this);

    mTreeView->setModel(mModel);
    mTreeView->setSelectionModel(mSelectionModelTree);

    connect(mTreeView,          SIGNAL(expanded(QModelIndex)),  this,   SLOT(slotViewResize()));
    connect(mTreeView,          SIGNAL(collapsed(QModelIndex)), this,   SLOT(slotViewResize()));

    initializeModel();
    build();

}

XMLWidget::~XMLWidget()
{
    delete mRootNode;
}

void XMLWidget::build()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(mCurrentFileLabel);
    mainLayout->addWidget(mTreeView);

    mainLayout->setMargin(2);
    mainLayout->setSpacing(4);
}

void XMLWidget::initializeModel()
{
    mRootNode = new XMLNode();
    XMLProcessor::Load(QString(":/res/res/test.xml"),mRootNode);
    mModel->setRootNode(mRootNode);
}

//SLOTS
void XMLWidget::slotOpen()
{

}
void XMLWidget::slotSave()
{
    XMLProcessor::Save(QString(mCurrentFileName),mRootNode);
}
void XMLWidget::slotSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Config file", mCurrentFileName, "files(*.xml )");
    if(!filename.isEmpty())
    {
        mCurrentFileName = filename;
        mCurrentFileLabel->setText("<b>Configuration  :   </b>" + mCurrentFileName);
        XMLProcessor::Save(QString(filename),mRootNode);
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
    mTreeView->resizeColumnToContents(0);
    mTreeView->resizeColumnToContents(1);
    mTreeView->resizeColumnToContents(2);
    //mTreeView->resizeColumnToContents(3);
}

void XMLWidget::slotRevertAll()
{
    emit mModel->signalRevertAll();
    emit mModel->layoutChanged();
}
