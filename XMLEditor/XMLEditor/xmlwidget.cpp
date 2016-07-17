#include <QDebug>
#include <QFileDialog>
#include <QFont>

#include "xmlwidget.h"
#include "xmlprocessor.h"

XMLWidget::XMLWidget(QWidget *parent)
    :QFrame(parent)
{

    //mCurrentFileName = mConfig->getFilePath();
    mTreeView = new QTreeView(this);
    //mListView = new QListView(this);
    mButtonSave = new QPushButton("Save",this);
    mButtonSaveAs = new QPushButton("Save As...",this);
    mButtonRevertAll = new QPushButton("Revert All",this);
    mCurrentFileLabel = new QLabel("<b>Configuration  :   </b>" + mCurrentFileName,this);

    mModel =  new XMLModel(this);
    mSelectionModelTree = new QItemSelectionModel(mModel,this);
    //mSelectionModelList = new QItemSelectionModel(mModel,this);

    mTreeView->setModel(mModel);
    //mListView->setModel(mModel);
    mTreeView->setSelectionModel(mSelectionModelTree);
    //mListView->setSelectionModel(mSelectionModelList);

    //mListView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    connect(mButtonSave,        SIGNAL(clicked(bool)),          this,   SLOT(slotSave()));
    connect(mButtonSaveAs,      SIGNAL(clicked(bool)),          this,   SLOT(slotSaveAs()));
    connect(mButtonRevertAll,   SIGNAL(clicked(bool)),          this,   SLOT(slotRevertAll()));
    connect(mTreeView,          SIGNAL(expanded(QModelIndex)),  this,   SLOT(slotViewResize()));
    connect(mTreeView,          SIGNAL(collapsed(QModelIndex)), this,   SLOT(slotViewResize()));
    connect(mListView,          SIGNAL(clicked(QModelIndex)),   this,   SLOT(slotUpdateTreeView(QModelIndex)));
    connect(mSelectionModelList,SIGNAL(currentChanged(QModelIndex,QModelIndex)),   this,   SLOT(slotUpdateTreeView(QModelIndex,QModelIndex)));

    initializeModel();
    build();

}

XMLWidget::~XMLWidget()
{
    delete mRootNode;
}

void XMLWidget::initializeModel()
{
    //mRootNode = generateNode(new SettingsNode(mSettings));
    mRootNode = new XMLNode();
    XMLProcessor::Load(QString(":/res/res/test.xml"),mRootNode);
    mModel->setRootNode(mRootNode);
    //mSelectionModelList->setCurrentIndex(mModel->index(1,0,mListView->rootIndex()),QItemSelectionModel::Current);
    //mListView->setCurrentIndex(mModel->index(1,0,mListView->rootIndex()));
    //mTreeView->setCurrentIndex(mModel->index(0,1,mTreeView->rootIndex()));
    //slotUpdateTreeView(mModel->index(0,1,mTreeView->rootIndex()));
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
void XMLWidget::slotSave()
{
    XMLProcessor::Save(QString(mCurrentFileName),mRootNode);
}
void XMLWidget::slotUpdateTreeView(QModelIndex curIndex,QModelIndex prevIndex)
{
    mTreeView->setRootIndex(curIndex);
    slotViewResize();
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

void XMLWidget::build()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* viewesLayout = new QHBoxLayout();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(mButtonRevertAll);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(mButtonSaveAs);
    buttonsLayout->addWidget(mButtonSave);

    //viewesLayout->addWidget(mListView);
    viewesLayout->addWidget(mTreeView);

    mainLayout->addWidget(mCurrentFileLabel);
    mainLayout->addLayout(viewesLayout);
    mainLayout->addLayout(buttonsLayout);

    mainLayout->setMargin(2);
    mainLayout->setSpacing(4);
}
