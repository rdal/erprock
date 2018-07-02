#include "cfop.h"

Cfop::Cfop(QString cfop, QString description, QString application, QObject *parent) :
    QObject(parent)
{
    this->cfop = cfop;
    this->description = description;
    this->application = application;
}

Cfop::~Cfop()
{
}

QString Cfop::getCfop()
{
    return this->cfop;
}

QString Cfop::getDescription()
{
    return this->description = description;
}

QString Cfop::getApplication()
{
    return this->application = application;
}

void Cfop::setCfop(QString cfop)
{
    this->cfop = cfop;
}

void Cfop::setDescription(QString description)
{
    this->description = description;
}

void Cfop::setApplication(QString application)
{
    this->application = application;
}

