#ifndef ENTRIESCONTROLLER_H
#define ENTRIESCONTROLLER_H

#include <QObject>
#include "databasecontroller.h"
#include "utilities.h"

//!  Controller for prices
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for prices management.
*/
class EntriesController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of PriceController.
    */
    explicit EntriesController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~EntriesController();

    /*!
      \param entry The Entry object to be added.
      \return Returns the Status Control of the operation.
      \sa updateEntry(), removeEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    Utilities::StatusControl addEntry(Entry *entry);

    /*!
      \param entry The Entry object to be updated.
      \return Returns the Status Control of the operation.
      \sa addEntry(), removeEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    Utilities::StatusControl updateEntry(Entry *entry);

    /*!
    Remove an entry by its id.
      \param id The id whose entry will be removed.
      \return Returns the Status Control of the operation.
      \sa addEntry(), updateEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    Utilities::StatusControl removeEntry(int id);

    /*!
    Get an entry by its id.
      \param id The Entry's id.
      \return Returns the entry object associated with the given id.
      \sa addEntry(), updateEntry(), removeEntry(), getEntriesBetweenDates() and getEntries()
    */
    Entry *getEntryById(int id);

    /*!
    Get all entries between two dates.
      \param startDate The initial data.
      \param endDate The final data.
      \return Returns all entries between two given dates.
      \sa addEntry(), updateEntry(), removeEntry(), getEntryById() and getEntries()
    */
    QList<Entry*> *getEntriesBetweenDates(QDateTime startDate, QDateTime endDate);

    /*!
    This method returns all entries that were previously stored at database.
      \return Returns all stored entries.
      \sa addEntry(), updateEntry(), removeEntry(), getEntryById() and getEntriesBetweenDates()
    */
    QList<Entry*> *getEntries();

private:

    DatabaseController *dbController;
    
signals:
    
public slots:
    
};

#endif // ENTRIESCONTROLLER_H
