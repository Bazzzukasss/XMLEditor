#ifndef XMLWIDGET_H
#define XMLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QTreeView>
#include <QVBoxLayout>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QLabel>

#include "xmlmodel.h"

class XMLWidget : public QFrame
{
    Q_OBJECT
public:
    XMLWidget(QWidget *parent = Q_NULLPTR);
    ~XMLWidget();
public slots:
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotToOldFormat();
    void slotToNewFormat();
    void slotViewResize();
    void slotRevertAll();
private:
    QLabel* mCurrentFileLabel;
    QTreeView* mTreeView;
    XMLModel* mModel;
    QItemSelectionModel* mSelectionModel;
    QString mCurrentFileName;
    XMLNode* mRootNode;
    void setCurrentFileName(const QString& filename);
    void build();
};

#endif // XMLWIDGET_H
