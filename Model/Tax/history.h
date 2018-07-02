#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>

//!  History basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for History.
*/
class History : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
	/*!
    * Create a new instance of History.
    */
	explicit History(QString name, QObject *parent = 0);
	
    /*!
    * Create a new instance of History. Use this constructor when ID already exists.
    */
    explicit History(int id, QString name, QObject *parent = 0);


    //! Get the id of history.
    /*!
      Return the id of history
      \return Returns the id of history
    */
    int getId();

    //! Get the name of history.
    /*!
      Return the name of history
      \return Returns the name of history
      \sa setName()
    */
    QString getName();

    //! Set the name of history.
    /*!
      \param name The name of history
      \sa getName()
    */
    void setName(QString name);


private:
    int id;
    QString name;
    
signals:
    
public slots:
    
};

#endif // HISTORY_H
