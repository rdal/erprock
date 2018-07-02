#ifndef CSTIPI_H
#define CSTIPI_H

#include <QObject>

//!  Cst Ipi basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Cst Ipi.
*/
class CstIpi : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of CstIpi.
    */
    explicit CstIpi(QString code, QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstIpi();

    //! Get the code of cst ipi.
    /*!
      Return the code of cst ipi
      \return Returns the code of cst ipi
      \sa setCode()
    */
    QString getCode();

    //! Get the name of cst ipi.
    /*!
      Return the name of cst ipi
      \return Returns the name of cst ipi
      \sa setName()
    */
    QString getName();


    //! Set the code of cst ipi.
    /*!
      \param code The code of cst ipi
      \sa getCode()
    */
    void setCode(QString code);

    //! Set the name of cst ipi.
    /*!
      \param name The name of cst ipi
      \sa getName()
    */
    void setName(QString name);

private:
    QString code;
    QString name;

signals:

public slots:

};

#endif // CSTIPI_H
