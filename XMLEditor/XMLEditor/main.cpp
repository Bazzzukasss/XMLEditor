#include "mainwindow.h"
#include <QApplication>

#include "xmlprocessor.h"
#include "xmlmodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //XMLNode* node = new XMLNode();
    //XMLProcessor::Load(QString(":/res/res/xml_new_format.xml"),node);
    //XMLProcessor::Load(QString(":/res/res/test.xml"),node);
    //XMLProcessor::Save(QString("/tmp/test_sv.xml"),node);
    //XMLModel model;
    //model.setRootNode(node);
    //delete node;
    MainWindow w;
    w.show();

    return a.exec();
}
