#include "xmlmodel.h"
#include <QDebug>

XMLModel::XMLModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    mRootNode = 0;
    mColumnsCaption << tr("Parameter") << tr("Value");
}

XMLModel::~XMLModel()
{
}

void XMLModel::setRootNode(XMLNode *node)
{
    mRootNode=node;
}

QModelIndex XMLModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!mRootNode)
        return QModelIndex();

    XMLNode *parentNode = nodeFromIndex(parent);
    return createIndex(row, column, parentNode->getNodes()[row]);
}

XMLNode *XMLModel::nodeFromIndex( const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<XMLNode *>(index.internalPointer());
    else
        return mRootNode;
}

int XMLModel::rowCount(const QModelIndex& parent) const
{
    XMLNode *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->getNodes().count();
}

int XMLModel::columnCount(const QModelIndex&) const
{
    return mColumnsCaption.size();
}
QModelIndex XMLModel::parent(const QModelIndex& child) const
{
    XMLNode* node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();

    XMLNode* parentNode = node->getParent();
    if (!parentNode)
        return QModelIndex();

    XMLNode* grandparentNode = parentNode->getParent();
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->getNodes().indexOf(parentNode);
    return createIndex(row, child.column(), parentNode);
}

QVariant XMLModel::data(const QModelIndex& index, int role) const
{
    if ((role != Qt::DisplayRole) && (role!= Qt::EditRole))
        return QVariant();
    XMLNode *node = nodeFromIndex(index);
    if (!node)
        return QVariant();
    switch(index.column())
    {
        case 0:
            return node->getName();
        break;
        case 1:
            return node->getValue();
        break;
        default:
            return QVariant();
        break;
    }
    return QVariant();
}

bool XMLModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.column() != 1 )
        return false;
    if(role==Qt::EditRole)
    {
        XMLNode *node = nodeFromIndex(index);
        node->setValue(value);
        return true;
    }
    return false;
}

QVariant XMLModel::headerData(int section,Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole && section < mColumnsCaption.size() )
        return mColumnsCaption[section];
    return QVariant();
}

Qt::ItemFlags XMLModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    if (index.isValid())
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;;
    return theFlags;
}

