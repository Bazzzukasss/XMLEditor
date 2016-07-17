#ifndef SETTINGSVIEWWIDGET_H
#define SETTINGSVIEWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QSettings>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QColumnView>
#include <QListView>
#include <QListWidget>

#include "xmlmodel.h"

class XMLWidget : public QFrame
{
    Q_OBJECT
public:
    XMLWidget(QWidget *parent = Q_NULLPTR);
    ~XMLWidget();
public slots:
    void slotSave();
    void slotSaveAs();
    void slotViewResize();
    void slotRevertAll();
    void slotUpdateTreeView(QModelIndex curIndex,QModelIndex prevIndex = QModelIndex());
private:
    QLabel* mCurrentFileLabel;
    QTreeView* mTreeView;
    QListView* mListView;
    QPushButton* mButtonSave;
    QPushButton* mButtonSaveAs;
    QPushButton* mButtonRevertAll;
    QPushButton* mButtonReload;
    XMLModel* mModel;
    QItemSelectionModel* mSelectionModelTree;
    QItemSelectionModel* mSelectionModelList;
    QString mCurrentFileName;
    XMLNode* mRootNode;
    void build();
    void initializeModel();
};

#endif // SETTINGSVIEWWIDGET_H
