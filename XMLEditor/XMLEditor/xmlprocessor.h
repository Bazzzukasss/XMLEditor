#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "xmlnode.h"

class XMLProcessor : public QObject
{
    Q_OBJECT
public:
    static XMLProcessor* getInstance();
    static bool Load(const QString& fileName,XMLNode* node);
    static bool Save(const QString& fileName,const XMLNode* node);
    ~XMLProcessor();
signals:
    void signalError(const QString& message);
private:
    static bool load(QXmlStreamReader& reader,XMLNode* node);
    static bool save(QXmlStreamWriter& writer,const XMLNode* node);
    static XMLProcessor* mInstance;
    explicit XMLProcessor(QObject *parent = 0):QObject(parent){}
    XMLProcessor(const XMLProcessor&):QObject(0){}
    XMLProcessor &operator=(const XMLProcessor&){return *this;}
};

#endif // XMLPROCESSOR_H
