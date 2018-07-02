#ifndef PRODUCTCATEGORY_H
#define PRODUCTCATEGORY_H

#include <QObject>

//!  Product category basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Product category.
*/
class ProductCategory : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of ProductCategory. Use this constructor when category already exists.
    */
    explicit ProductCategory(int id, QString name, QObject *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of ProductCategory. Use this constructor when category doesn't exist.
    */
    explicit ProductCategory(QString name, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductCategory();


    //! Get the id of product category.
    /*!
      Return the id of product category
      \return Returns the id of product category
      \sa setId()
    */
    int getId();

    //! Get the name of product category.
    /*!
      Return the name of product category
      \return Returns the name of product category
      \sa setName()
    */
    QString getName();


    //! Set the id of product category.
    /*!
      \param id The id of product category
      \sa getId()
    */
    void setId(int id);

    //! Set the name of product category.
    /*!
      \param name The name of product category
      \sa getName()
    */
    void setName(QString name);

private:
    int id;
    QString name;

signals:

public slots:

};

#endif // PRODUCTCATEGORY_H
