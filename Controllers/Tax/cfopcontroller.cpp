#include "cfopcontroller.h"
#include "filenotfoundexception.h"

#include <QDomDocument>
#include <QFile>
#include <QDebug>

CfopController::CfopController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CfopController::~CfopController()
{
}

Utilities::StatusControl CfopController::addCfop(Cfop *cfopObj)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cfopAlreadyExists(cfopObj->getCfop());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewCfop(cfopObj);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }

    return ret;
}

Utilities::StatusControl CfopController::updateCfop(QString cfop, Cfop *cfopObj)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cfopAlreadyExists(cfopObj->getCfop());
        if(exists && (cfop != cfopObj->getCfop()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateCfop(cfop, cfopObj);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Utilities::StatusControl CfopController::removeCfop(QString cfop)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeCfop(cfop);
        if(!result)
        {
            ret = Utilities::UNKNOWN_ERROR;
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Cfop *CfopController::getCfopByCfop(QString cfop)
{
    Cfop *cfopObj = NULL;
    if(dbController->isConnectionOpen())
    {
        cfopObj = dbController->getCfopByCfop(cfop);
    }
    return cfopObj;
}

QList<Cfop*> *CfopController::getCfops()
{
    QList<Cfop*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getCfops();
    }

    return ret;
}

void CfopController::importCfop(QString filepath)
{
    try{
        QString contents = "";
        QFile file(filepath);

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            contents.append(line);
        }

        QDomDocument* doc = new QDomDocument();
        doc->setContent(contents);

        QDomElement docElem = doc->documentElement();
        QDomNode entryElem = docElem.firstChildElement("entry");
        for (; !entryElem.isNull(); entryElem = entryElem.nextSiblingElement("entry"))
        {
            QDomNode entryChildNode = entryElem.firstChild();

            if(!entryChildNode.isNull())
            {
                QString cfop = entryElem.firstChildElement("code").text().trimmed();
                QString description = entryElem.firstChildElement("description").text().trimmed();
                QString application = entryElem.firstChildElement("application").text().trimmed();

                Cfop *cfopObj = new Cfop(cfop, description, application);

                this->dbController->createNewCfop(cfopObj);
            }
        }
    }
    catch(FileNotFoundException &e) {
        qDebug() << "DB Config File Exception:" << e.what();
    }
}
