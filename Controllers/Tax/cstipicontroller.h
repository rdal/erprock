#ifndef CSTIPICONTROLLER_H
#define CSTIPICONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for product origins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product origins management.
*/
class CstIpiController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CstIpiController.
    */
    explicit CstIpiController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstIpiController();

    /*!
    Beforing adding a product origin, this method checks if there is already a product origins with that code
    and if its name has less than 30 characters.
      \param cstIpi The CstIpi object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCstIpi(), removeCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    Utilities::StatusControl addCstIpi(CstIpi *cstIpi);

    /*!
    Beforing updating a product origin, this method checks if there is a product origin with that code,
    and if its name has less than 100 characters.
      \param code The code whose product origin will be updated.
      \param cstIpi The CstIpi object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCstIpi(), removeCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    Utilities::StatusControl updateCstIpi(QString code, CstIpi *cstIpi);

    /*!
    Beforing removing an product origin, this method checks if there is a product origin with that code.
      \param code The code whose product origin will be removed.
      \return Returns the Status Control of the operation.
      \sa addCstIpi(), updateCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    Utilities::StatusControl removeCstIpi(QString code);

    /*!
    Get an product origin by its code.
      \param code The CstIpi code.
      \return Returns the product origin object associated with the given code.
      \sa addCstIpi(), updateCstIpi(), removeCstIpi() and getCstIpis()
    */
    CstIpi *getCstIpiByCode(QString code);

    /*!
    This method returns all the product origins that were previously stored at database.
      \return Returns all stored product origins.
      \sa addCstIpi(), updateCstIpi(), removeCstIpi() and getCstIpiByCode()
    */
    QList<CstIpi*> *getCstIpis();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CSTIPICONTROLLER_H
