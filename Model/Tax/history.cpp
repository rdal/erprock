#include "history.h"

History::History(int id, QString name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
}

History::History(QString name, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->name = name;
}

int History::getId()
{
    return this->id;
}

QString History::getName()
{
    return this->name;
}

void History::setName(QString name)
{
    this->name = name;
}
