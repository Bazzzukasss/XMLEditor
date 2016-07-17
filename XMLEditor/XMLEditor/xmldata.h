#ifndef XMLDATA_H
#define XMLDATA_H

#include <QString>
#include <QXmlStreamAttributes>
#include <QVariant>

struct XMLData{
    QString mName;
    QVariant mValue;
    QXmlStreamAttributes mAttributes;
};
#endif // XMLDATA_H
