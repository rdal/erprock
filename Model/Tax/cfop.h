#ifndef CFOP_H
#define CFOP_H

#include <QObject>

//!  CFOP basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Tax Rate.
*/
class Cfop : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of Cfop.
    */
    explicit Cfop(QString cfop, QString description, QString application, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Cfop();

    //! Get the cfop of Cfop Object.
    /*!
      Return the cfop of Cfop object
      \return Returns the cfop of Cfop Object
      \sa setCfop()
    */
    QString getCfop();

    //! Get the description of cfop.
    /*!
      Return the cfop of Cfop object
      \return Returns the cfop
      \sa setDescription()
    */
    QString getDescription();

    //! Get the application of cfop.
    /*!
      Return the application of Cfop object
      \return Returns the application
      \sa setApplication()
    */
    QString getApplication();

    //! Set the cfop of Cfop Object
    /*!
      \param cfop The cfop of Cfop object
      \sa getCfop()
    */
    void setCfop(QString cfop);

    //! Set the description of Cfop Object
    /*!
      \param description The description of Cfop object
      \sa getDescription()
    */
    void setDescription(QString description);

    //! Set the application of Cfop Object
    /*!
      \param application The application of Cfop object
      \sa getDescription()
    */
    void setApplication(QString application);

private:
    QString cfop;
    QString description;
    QString application;

signals:

public slots:

};

#endif // CFOP_H
