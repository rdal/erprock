#ifndef CSTCOFINS_H
#define CSTCOFINS_H

#include <QObject>

//!  Cst Cofins basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Cst Cofins.
*/
class CstCofins : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of CstCofins.
    */
    explicit CstCofins(QString code, QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstCofins();

    //! Get the code of cst cofins.
    /*!
      Return the code of cst cofins
      \return Returns the code of cst cofins
      \sa setCode()
    */
    QString getCode();

    //! Get the name of cst cofins.
    /*!
      Return the name of cst cofins
      \return Returns the name of cst cofins
      \sa setName()
    */
    QString getName();


    //! Set the code of cst cofins.
    /*!
      \param code The code of cst cofins
      \sa getCode()
    */
    void setCode(QString code);

    //! Set the name of cst cofins.
    /*!
      \param name The name of cst cofins
      \sa getName()
    */
    void setName(QString name);

private:
    QString code;
    QString name;

signals:

public slots:

};

#endif // CSTCOFINS_H
