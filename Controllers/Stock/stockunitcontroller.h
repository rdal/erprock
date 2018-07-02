#ifndef STOCKUNITCONTROLLER_H
#define STOCKUNITCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for stock units
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product stock units.
*/
class StockUnitController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of StockUnitController.
    */
    explicit StockUnitController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~StockUnitController();

    /*!
    Beforing adding a stock unit, this method checks if there is already a stock unit with that id
    and if its name has less than 30 characters.
      \param stockUnit The StockUnit object to be added.
      \return Returns the Status Control of the operation.
      \sa updateStockUnit(), removeStockUnit(), getStockUnitById() and getStockUnits()
    */
    Utilities::StatusControl addStockUnit(StockUnit *stockUnit);

    /*!
    Beforing updating a stock unit, this method checks if there is a stock unit with that id,
    and if its name has less than 100 characters.
      \param stockUnit The StockUnit object to be updated.
      \return Returns the Status Control of the operation.
      \sa addStockUnit(), removeStockUnit(), getStockUnitById() and getStockUnits()
    */
    Utilities::StatusControl updateStockUnit(StockUnit *stockUnit);

    /*!
    Beforing removing an stock unit, this method checks if there is a stock unit with that id.
      \param id The id whose stock unit will be removed.
      \return Returns the Status Control of the operation.
      \sa addStockUnit(), updateStockUnit(), getStockUnitById() and getStockUnits()
    */
    Utilities::StatusControl removeStockUnit(int id);

    /*!
    Get an stock unit by its id.
      \param id The StockUnit id.
      \return Returns the stock unit object associated with the given id.
      \sa addStockUnit(), updateStockUnit(), removeStockUnit() and getStockUnits()
    */
    StockUnit *getStockUnitById(int id);

    /*!
    This method returns all the stock units that were previously stored at database.
      \return Returns all stored stock units.
      \sa addStockUnit(), updateStockUnit(), removeStockUnit() and getStockUnitById()
    */
    QList<StockUnit*> *getStockUnits();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // STOCKUNITCONTROLLER_H
