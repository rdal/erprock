#ifndef HISTORIESCONTROLLER_H
#define HISTORIESCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for histories
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for histories.
*/
class HistoriesController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of HistoriesController.
    */
    explicit HistoriesController(QObject *parent = 0);

    /*!
    Beforing adding a history, this method checks if there is already a history with that name
    and if its name has less than 100 characters.
      \param history The History object to be added.
      \return Returns the Status Control of the operation.
      \sa updateHistory(), removeHistory(), getHistoryById() and getHistories()
    */
    Utilities::StatusControl addHistory(History *history);

    /*!
    Beforing updating a history, this method checks if there is a history with that name,
    and if its name has less than 100 characters.
      \param name The name whose history will be updated.
      \param history The History object to be updated.
      \return Returns the Status Control of the operation.
      \sa addHistory(), removeHistory(), getHistoryById() and getHistories()
    */
    Utilities::StatusControl updateHistory(History *history);

    /*!
    Beforing removing an history, this method checks if there is a history with that id.
      \param id The id whose history will be removed.
      \return Returns the Status Control of the operation.
      \sa addHistory(), updateHistory(), getHistoryById() and getHistories()
    */
    Utilities::StatusControl removeHistory(int id);

    /*!
    Get a history by its id.
      \param id The History id.
      \return Returns the history object associated with the given id.
      \sa addHistory(), updateHistory(), removeHistory() and getHistories()
    */
    History *getHistoryById(int id);

    /*!
    This method returns all the histories that were previously stored at database.
      \return Returns all stored histories.
      \sa addHistory(), updateHistory(), removeHistory() and getHistoryById()
    */
    QList<History*> *getHistories();

private:
    DatabaseController *dbController;
    
signals:
    
public slots:
    
};

#endif // HISTORIESCONTROLLER_H
