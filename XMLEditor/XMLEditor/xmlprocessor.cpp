#include <QFile>
#include "xmlprocessor.h"

XMLProcessor* XMLProcessor::mInstance = nullptr;

XMLProcessor *XMLProcessor::getInstance()
{
    if(mInstance == nullptr)
        mInstance = new XMLProcessor();
    return mInstance;
}

XMLProcessor::~XMLProcessor()
{
    delete mInstance;
}

bool XMLProcessor::Load(const QString &fileName, XMLNode *node)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);
        reader.isStartDocument();
        load(reader,node);

        if (reader.hasError())
        {
            //emit signalError(tr("Failed loading file:\n\"%1\"\nError:\n%2").arg(file.fileName()).arg(reader.errorString()));
            return false;
        }

        return true;
    }
    return false;
}

bool XMLProcessor::Save(const QString &fileName, const XMLNode *node)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter writer(&file);

        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        save(writer,node);
        writer.writeEndDocument();

        if (writer.hasError())
        {
            //emit error(tr("Failed to save configuration file:\n\"%1\"\n").arg(file.fileName()));
            return false;
        }
        return true;
    }
    return false;
}

#include <QDebug>

bool XMLProcessor::load(QXmlStreamReader &reader, XMLNode *node)
{
    std::vector<XMLData> stack;
    XMLData data;
    XMLNode* currentNode=node;
    XMLNode* subNode;
    size_t stackSize = 0;

    while (!reader.atEnd())
    {
        reader.readNext();
        switch (reader.tokenType())
        {
            case QXmlStreamReader::StartElement:

                data.mAttributes = reader.attributes();
                data.mName = reader.name().toString();
                data.mValue.clear();

                subNode = new XMLNode(currentNode,data);
                currentNode->addNode( subNode );
                currentNode = subNode;

                if (stackSize < stack.size())
                    stack.resize(stackSize);

                stack.emplace_back(data);
                ++stackSize;

                break;
            case QXmlStreamReader::EndElement:
                if (stackSize == stack.size())
                    currentNode->setValue(stack.back().mValue);
                --stackSize;
                currentNode = currentNode->getParent();
                break;
            case QXmlStreamReader::Characters:
                stack.back().mValue = reader.text().toString();
                break;
            default:
                break;
        }
    }

    return true;
}

bool XMLProcessor::save(QXmlStreamWriter &writer, const XMLNode *node)
{
    for (XMLNode* subNode : node->getNodes())
    {
        writer.writeStartElement(subNode->getName());
        writer.writeAttributes(subNode->getAttributes());
        if(!subNode->getValue().isNull())
            writer.writeCharacters(subNode->getValue().toString());
        save(writer,subNode);
        writer.writeEndElement();
    }

    return true;
}

