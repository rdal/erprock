#ifndef CFOPCONTROLLER_H
#define CFOPCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for cfops
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product cfops.
*/
class CfopController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CfopController.
    */
    explicit CfopController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CfopController();

    /*!
    Beforing adding a cfop, this method checks if there is already a cfop object with that cfop.
      \param cfopObj The Cfop object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCfop(), removeCfop(), getCfopByCfop(), getCfops() and importCfop()
    */
    Utilities::StatusControl addCfop(Cfop *cfopObj);

    /*!
    Beforing updating a cfop, this method checks if there is a cfop with that cfop,
    and if its cfop has less than 100 characters.
      \param cfop The cfop whose object will be updated.
      \param cfopObj The Cfop object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCfop(), removeCfop(), getCfopByCfop(), getCfops() and importCfop()
    */
    Utilities::StatusControl updateCfop(QString cfop, Cfop *cfopObj);

    /*!
    Beforing removing an cfop, this method checks if there is a cfop with that cfop.
      \param cfop The cfop whose object will be removed.
      \return Returns the Status Control of the operation.
      \sa addCfop(), updateCfop(), getCfopByCfop(), getCfops() and importCfop()
    */
    Utilities::StatusControl removeCfop(QString cfop);

    /*!
    Get a cfop object by its cfop.
      \param cfop The cfop.
      \return Returns the cfop object associated with the given cfop.
      \sa addCfop(), updateCfop(), removeCfop(), getCfops() and importCfop()
    */
    Cfop *getCfopByCfop(QString cfop);

    /*!
    This method returns all the cfops that were previously stored at database.
      \return Returns all stored cfops.
      \sa addCfop(), updateCfop(), removeCfop(), getCfopByCfop() and importCfop()
    */
    QList<Cfop*> *getCfops();

    /*!
    This method reads the input file's contents, parse it, and store the values into cfop database.
      \param filepath The filepath to be read.
      \sa addCfop(), updateCfop(), removeCfop(), getCfopByCfop() and getCfops()
    */
    void importCfop(QString filepath);

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CFOPCONTROLLER_H
