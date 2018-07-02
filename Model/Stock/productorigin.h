#ifndef PRODUCTORIGIN_H
#define PRODUCTORIGIN_H

#include <QObject>

//!  Product origin basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Product origin.
*/
class ProductOrigin : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of ProductOrigin. Use this constructor when origin already exists.
    */
    explicit ProductOrigin(QString code, QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductOrigin();

    //! Get the code of product origin.
    /*!
      Return the code of product origin
      \return Returns the code of product origin
      \sa setCode()
    */
    QString getCode();

    //! Get the name of product origin.
    /*!
      Return the name of product origin
      \return Returns the name of product origin
      \sa setName()
    */
    QString getName();


    //! Set the code of product origin.
    /*!
      \param code The code of product origin
      \sa getCode()
    */
    void setCode(QString code);

    //! Set the name of product origin.
    /*!
      \param name The name of product origin
      \sa getName()
    */
    void setName(QString name);

private:
    QString code;
    QString name;

signals:

public slots:

};

#endif // PRODUCTORIGIN_H
