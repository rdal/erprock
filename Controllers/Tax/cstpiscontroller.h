#ifndef CSTPISCONTROLLER_H
#define CSTPISCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for product origins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product origins management.
*/
class CstPisController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CstPisController.
    */
    explicit CstPisController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstPisController();

    /*!
    Beforing adding a product origin, this method checks if there is already a product origins with that code
    and if its name has less than 30 characters.
      \param cstPis The CstPis object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCstPis(), removeCstPis(), getCstPisByCode() and getCstPiss()
    */
    Utilities::StatusControl addCstPis(CstPis *cstPis);

    /*!
    Beforing updating a product origin, this method checks if there is a product origin with that code,
    and if its name has less than 100 characters.
      \param code The code whose product origin will be updated.
      \param cstPis The CstPis object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCstPis(), removeCstPis(), getCstPisByCode() and getCstPiss()
    */
    Utilities::StatusControl updateCstPis(QString code, CstPis *cstPis);

    /*!
    Beforing removing an product origin, this method checks if there is a product origin with that code.
      \param code The code whose product origin will be removed.
      \return Returns the Status Control of the operation.
      \sa addCstPis(), updateCstPis(), getCstPisByCode() and getCstPiss()
    */
    Utilities::StatusControl removeCstPis(QString code);

    /*!
    Get an product origin by its code.
      \param code The CstPis code.
      \return Returns the product origin object associated with the given code.
      \sa addCstPis(), updateCstPis(), removeCstPis() and getCstPiss()
    */
    CstPis *getCstPisByCode(QString code);

    /*!
    This method returns all the product origins that were previously stored at database.
      \return Returns all stored product origins.
      \sa addCstPis(), updateCstPis(), removeCstPis() and getCstPisByCode()
    */
    QList<CstPis*> *getCstPiss();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CSTPISCONTROLLER_H
