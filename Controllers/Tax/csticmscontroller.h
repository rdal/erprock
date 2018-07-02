#ifndef CSTICMSCONTROLLER_H
#define CSTICMSCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for product origins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product origins management.
*/
class CstIcmsController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CstIcmsController.
    */
    explicit CstIcmsController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstIcmsController();

    /*!
    Beforing adding a product origin, this method checks if there is already a product origins with that code
    and if its name has less than 30 characters.
      \param cstIcms The CstIcms object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCstIcms(), removeCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    Utilities::StatusControl addCstIcms(CstIcms *cstIcms);

    /*!
    Beforing updating a product origin, this method checks if there is a product origin with that code,
    and if its name has less than 100 characters.
      \param code The code whose product origin will be updated.
      \param cstIcms The CstIcms object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCstIcms(), removeCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    Utilities::StatusControl updateCstIcms(QString code, CstIcms *cstIcms);

    /*!
    Beforing removing an product origin, this method checks if there is a product origin with that code.
      \param code The code whose product origin will be removed.
      \return Returns the Status Control of the operation.
      \sa addCstIcms(), updateCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    Utilities::StatusControl removeCstIcms(QString code);

    /*!
    Get an product origin by its code.
      \param code The CstIcms code.
      \return Returns the product origin object associated with the given code.
      \sa addCstIcms(), updateCstIcms(), removeCstIcms() and getCstIcmss()
    */
    CstIcms *getCstIcmsByCode(QString code);

    /*!
    This method returns all the product origins that were previously stored at database.
      \return Returns all stored product origins.
      \sa addCstIcms(), updateCstIcms(), removeCstIcms() and getCstIcmsByCode()
    */
    QList<CstIcms*> *getCstIcmss();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CSTICMSCONTROLLER_H
