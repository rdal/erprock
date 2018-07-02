#ifndef CSTCOFINSCONTROLLER_H
#define CSTCOFINSCONTROLLER_H

#include <QObject>

#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for cofins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for cofins management.
*/
class CstCofinsController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CstCofinsController.
    */
    explicit CstCofinsController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstCofinsController();

    /*!
    Beforing adding a cofins, this method checks if there is already a cofins with that code
    and if its name has less than 30 characters.
      \param cstCofins The CstCofins object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCstCofins(), removeCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    Utilities::StatusControl addCstCofins(CstCofins *cstCofins);

    /*!
    Beforing updating a cofins, this method checks if there is a cofins with that code,
    and if its name has less than 100 characters.
      \param code The code whose cofins will be updated.
      \param cstCofins The CstCofins object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCstCofins(), removeCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    Utilities::StatusControl updateCstCofins(QString code, CstCofins *cstCofins);

    /*!
    Beforing removing an cofins, this method checks if there is a cofins with that code.
      \param code The code whose cofins will be removed.
      \return Returns the Status Control of the operation.
      \sa addCstCofins(), updateCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    Utilities::StatusControl removeCstCofins(QString code);

    /*!
    Get an cofins by its code.
      \param code The CstCofins code.
      \return Returns the cofins object associated with the given code.
      \sa addCstCofins(), updateCstCofins(), removeCstCofins() and getCstCofinss()
    */
    CstCofins *getCstCofinsByCode(QString code);

    /*!
    This method returns all the cofins that were previously stored at database.
      \return Returns all stored cofins.
      \sa addCstCofins(), updateCstCofins(), removeCstCofins() and getCstCofinsByCode()
    */
    QList<CstCofins*> *getCstCofinss();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CSTCOFINSCONTROLLER_H
