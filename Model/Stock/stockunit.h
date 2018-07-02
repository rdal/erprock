#ifndef STOCKUNIT_H
#define STOCKUNIT_H

#include <QObject>

//!  Stock Unit basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Stock Unit.
*/
class StockUnit : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of StockUnit. Use this constructor when unit already exists.
    */
    explicit StockUnit(int id, QString name, QObject *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of StockUnit. Use this constructor when unit doesn't exist.
    */
    explicit StockUnit(QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~StockUnit();

    //! Get the id of stock unit.
    /*!
      Return the id of stock unit
      \return Returns the id of stock unit
      \sa setId()
    */
    int getId();

    //! Get the name of stock unit.
    /*!
      Return the name of stock unit
      \return Returns the name of stock unit
      \sa setName()
    */
    QString getName();


    //! Set the id of stock unit.
    /*!
      \param id The id of stock unit
      \sa getId()
    */
    void setId(int id);

    //! Set the name of stock unit.
    /*!
      \param name The name of stock unit
      \sa getName()
    */
    void setName(QString name);

private:
    int id;
    QString name;

signals:

public slots:

};

#endif // STOCKUNIT_H
