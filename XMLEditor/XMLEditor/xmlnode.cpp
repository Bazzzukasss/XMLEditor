#include "xmlnode.h"

XMLNode::XMLNode( XMLNode *parent, const XMLData &xmlData)
    ://QObject(0),
    mParent(parent),
    mName(xmlData.mName),
    mValue(xmlData.mValue),
    mAttributes(xmlData.mAttributes)
{

}

XMLNode::~XMLNode()
{
    qDeleteAll(mNodes);
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

const QList<XMLNode *>& XMLNode::getNodes() const
{
    return mNodes;
}

int XMLNode::getAttributesCount() const
{
    return mAttributes.size();
}

void XMLNode::Generate(int subNodesCount)
{
    this->mName = "genNodeName"+QString().number(subNodesCount);
    this->mValue = "genNodeValue"
                   ""+QString().number(subNodesCount);

    for(int n=0;n<subNodesCount;n++)
    {
        QXmlStreamAttributes xmlAttributes;
        for(int a=0;a<subNodesCount;a++)
            xmlAttributes.push_back(QXmlStreamAttribute("attributesName"+QString().number(a),"attributesValue"+QString().number(a)));
        XMLData xmlData{"SubNodeName"+QString().number(n),"SubNodeValuee"+QString().number(n),xmlAttributes};
        addNode(new XMLNode(this,xmlData));
    }
}
