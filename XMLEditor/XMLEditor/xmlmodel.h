#ifndef XMLMODEL_H
#define XMLMODEL_H

#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QAbstractItemModel>
#include "xmlnode.h"

class XMLModel : public QAbstractItemModel
{
    Q_OBJECT
    public:
        XMLModel(QObject *parent = 0);
        ~XMLModel();
        void setRootNode(XMLNode* node);
        QModelIndex index(int row, int column,const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        QVariant headerData(int section,Qt::Orientation Orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
    private:
        XMLNode* mRootNode;
        XMLNode* nodeFromIndex(const QModelIndex &index) const;
        QStringList mColumnsCaption;
    signals:
        void signalRevertAll();
};

#endif // SETTINGSMODEL_H
