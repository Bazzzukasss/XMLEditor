#ifndef XMLNODE_H
#define XMLNODE_H

#include <QObject>
#include <QXmlStreamAttributes>
#include <QList>
#include <QString>
#include <QVariant>

#include "xmldata.h"

class XMLNode:public QObject{
    Q_OBJECT
public:
    XMLNode( XMLNode *parent = 0,const XMLData &xmlData = XMLData());
    ~XMLNode();
    void addNode(XMLNode *node);

    QXmlStreamAttributes getAttributes() const;
    void setAttributes(const QXmlStreamAttributes &attributes);

    XMLNode *getParent() const;
    void setParent(XMLNode *parent);

    QString getName() const;
    void setName(const QString &name);

    QVariant getValue() const;
    void setValue(const QVariant &value);

    QList<XMLNode *> getNodes() const;

private:
    XMLNode* mParent;
    QString mName;
    QVariant mValue;
    QXmlStreamAttributes mAttributes;
    QXmlStreamAttributes mOriginalAttributes;
    QList<XMLNode*> mNodes;
};

#endif // XMLNODE_H




