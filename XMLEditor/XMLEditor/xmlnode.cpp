#include "xmlnode.h"

XMLNode::XMLNode( XMLNode *parent, const XMLData &xmlData)
    :QObject(0),
    mParent(parent),
    mName(xmlData.mName),
    mValue(xmlData.mValue),
    mAttributes(xmlData.mAttributes),
    mOriginalAttributes(xmlData.mAttributes)
{

}

XMLNode::~XMLNode()
{
    for(XMLNode* node : mNodes)
        delete node;
}

void XMLNode::addNode(XMLNode *node)
{
    mNodes.append(node);
}

QXmlStreamAttributes XMLNode::getAttributes() const
{
    return mAttributes;
}

void XMLNode::setAttributes(const QXmlStreamAttributes &attributes)
{
    mAttributes = attributes;
}

XMLNode *XMLNode::getParent() const
{
    return mParent;
}

void XMLNode::setParent(XMLNode *parent)
{
    mParent = parent;
}

QString XMLNode::getName() const
{
    return mName;
}

void XMLNode::setName(const QString &name)
{
    mName = name;
}

QVariant XMLNode::getValue() const
{
    return mValue;
}

void XMLNode::setValue(const QVariant &value)
{
    mValue = value;
}

QList<XMLNode *> XMLNode::getNodes() const
{
    return mNodes;
}
