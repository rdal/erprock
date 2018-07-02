#ifndef CSTICMS_H
#define CSTICMS_H

#include <QObject>

//!  Cst Icms basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Cst Icms.
*/
class CstIcms : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of CstIcms.
    */
    explicit CstIcms(QString code, QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstIcms();

    //! Get the code of cst icms.
    /*!
      Return the code of cst icms
      \return Returns the code of cst icms
      \sa setCode()
    */
    QString getCode();

    //! Get the name of cst icms.
    /*!
      Return the name of cst icms
      \return Returns the name of cst icms
      \sa setName()
    */
    QString getName();


    //! Set the code of cst icms.
    /*!
      \param code The code of cst icms
      \sa getCode()
    */
    void setCode(QString code);

    //! Set the name of cst icms.
    /*!
      \param name The name of cst icms
      \sa getName()
    */
    void setName(QString name);

private:
    QString code;
    QString name;

signals:

public slots:

};

#endif // CSTICMS_H
