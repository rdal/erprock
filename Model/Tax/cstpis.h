#ifndef CSTPIS_H
#define CSTPIS_H

#include <QObject>

//!  Cst Pis basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Cst Pis.
*/
class CstPis : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of CstPis.
    */
    explicit CstPis(QString code, QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstPis();

    //! Get the code of cst pis.
    /*!
      Return the code of cst pis
      \return Returns the code of cst pis
      \sa setCode()
    */
    QString getCode();

    //! Get the name of cst pis.
    /*!
      Return the name of cst pis
      \return Returns the name of cst pis
      \sa setName()
    */
    QString getName();


    //! Set the code of cst pis.
    /*!
      \param code The code of cst pis
      \sa getCode()
    */
    void setCode(QString code);

    //! Set the name of cst pis.
    /*!
      \param name The name of cst pis
      \sa getName()
    */
    void setName(QString name);

private:
    QString code;
    QString name;

signals:

public slots:

};

#endif // CSTPIS_H
