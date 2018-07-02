#ifndef MANUFACTURERCONTROLLER_H
#define MANUFACTURERCONTROLLER_H

#include <QObject>

#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for manufacturer
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for manufacturer management.
*/
class ManufacturerController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of ManufacturerController.
    */
    explicit ManufacturerController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ManufacturerController();

    /*!
    Beforing adding a manufacturer, this method checks if there is already a manufacturer with that CNPJ,
    if its name has less than 100 characters, and if the given CNPJ is valid.
      \param manufacturer The Manufacturer object to be added.
      \return Returns the Status Control of the operation.
      \sa updateManufacturer(), removeManufacturer(), getManufacturerByCNPJ() and getManufacturers()
    */
    Utilities::StatusControl addManufacturer(Manufacturer *manufacturer);

    /*!
    Beforing updating a manufacturer, this method checks if there is a manufacturer with that CNPJ,
    and if its name has less than 100 characters.
      \param manufacturer The Manufacturer object to be updated.
      \return Returns the Status Control of the operation.
      \sa addManufacturer(), removeManufacturer(), getManufacturerByCNPJ() and getManufacturers()
    */
    Utilities::StatusControl updateManufacturer(Manufacturer *manufacturer);

    /*!
    Beforing removing an manufacturer, this method checks if there is a manufacturer with that CNPJ.
      \param cnpj The cnpj whose manufacturer will be removed.
      \return Returns the Status Control of the operation.
      \sa addManufacturer(), updateManufacturer(), getManufacturerByCNPJ() and getManufacturers()
    */
    Utilities::StatusControl removeManufacturer(QString cnpj);

    /*!
    Get an manufacturer by its CNPJ.
      \param cnpj The Manufacturer's CNPJ.
      \return Returns the manufacturer object associated with the given CNPJ.
      \sa addManufacturer(), updateManufacturer(), removeManufacturer() and getManufacturers()
    */
    Manufacturer *getManufacturerByCNPJ(QString cnpj);

    /*!
    This method returns all the manufacturers that were previously stored at database.
      \return Returns all stored manufacturers.
      \sa addManufacturer(), updateManufacturer(), removeManufacturer() and getManufacturerByCNPJ()
    */
    QList<Manufacturer*> *getManufacturers();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // MANUFACTURERCONTROLLER_H
