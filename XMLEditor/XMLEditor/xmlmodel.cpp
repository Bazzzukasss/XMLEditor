#include "xmlmodel.h"
#include <QDebug>

XMLModel::XMLModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    mRootNode = 0;
    mColumnsCaption << tr("TAG") << tr("VALUE") << tr("ATTRIBUTE");
}

XMLModel::~XMLModel()
{
    delete mRootNode;
}

void XMLModel::setRootNode(XMLNode *node)
{
    delete mRootNode;
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

int XMLModel::rowCount(const QModelIndex& index) const
{
    XMLNode *parentNode = nodeFromIndex(index);
    if (!parentNode)
        return 0;
    return parentNode->getNodes().count();
}

int XMLModel::columnCount(const QModelIndex&  index) const
{
    if(index.isValid())
    {
        XMLNode* node = nodeFromIndex(index);
        if(node)
            return node->getAttributes().size() + mColumnsCaption.size();
    }
    return mColumnsCaption.size()+5;
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
    int column =index.column();
    QString value;
    switch(column)
    {
        case 0:
            return node->getName();
        break;
        case 1:
            value = node->getValue().toString();
            if(!value.isEmpty())
                return (role == Qt::EditRole) ? value : "value = " + value;
            else
                return value;
        break;
        default:
            if(column < node->getAttributes().size())
            {
                QString aValue=node->getAttributes()[column].value().toString();
                QString aName=node->getAttributes()[column].name().toString();
                return (role == Qt::EditRole) ? aValue : aName+" = "+aValue;
            }
            else
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
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if( section >= mColumnsCaption.size() )
            section = mColumnsCaption.size()-1;
        return mColumnsCaption[section];
    }

    return QVariant();
}

Qt::ItemFlags XMLModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    if (index.isValid())
    {
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;
        if(index.column()!=0)
            theFlags|=Qt::ItemIsEditable;
    }
    return theFlags;
}

