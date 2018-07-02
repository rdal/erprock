#ifndef PURCHASEPRODUCTORDER_H
#define PURCHASEPRODUCTORDER_H

#include <QObject>

//!  PurchaseProductOrder basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for PurchaseProductOrder.
*/
class PurchaseProductOrder : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of PurchaseProductOrder. Use this constructor when updating a new PurchaseProductOrder Object
    */
    explicit PurchaseProductOrder(int id, QString productCode, int quantity, QChar productOriginCode, QString cstIcmsCode,
                                  QString cstIpiCode, QString cstPisCode, QString cstCofinsCode, double icmsValue,
                                  double ipiValue, double pisValue, double cofinsValue, QString cfopCode,
                                  double unitPrice, QString storeCnpj, QObject *parent = 0);

    //! Default constructor.
    /*!
    * Create a new instance of PurchaseProductOrder. Use this constructor when creating a new PurchaseProductOrder Object
    */
    explicit PurchaseProductOrder(QString productCode, int quantity, QChar productOriginCode, QString cstIcmsCode,
                                  QString cstIpiCode, QString cstPisCode, QString cstCofinsCode, double icmsValue,
                                  double ipiValue, double pisValue, double cofinsValue,
                                  QString cfopCode, double unitPrice, QString storeCnpj, QObject *parent = 0);

    //! Get PurchaseProductOrder's id.
    /*!
      Return the PurchaseProductOrder's id
      \return Returns the PurchaseProductOrder's id
    */
    int getId();

    //! Get PurchaseProductOrder's product code.
    /*!
      Return the PurchaseProductOrder's product code
      \return Returns the PurchaseProductOrder's product code
      \sa setProductCode()
    */
    QString getProductCode();

    //! Get PurchaseProductOrder's quantity.
    /*!
      Return the PurchaseProductOrder's quantity
      \return Returns the PurchaseProductOrder's quantity
      \sa setQuantity()
    */
    int getQuantity();

    //! Get PurchaseProductOrder's product origin code.
    /*!
      Return the PurchaseProductOrder's product origin code
      \return Returns the PurchaseProductOrder's product origin code
      \sa setProductOriginCode()
    */
    QChar getProductOriginCode();

    //! Get PurchaseProductOrder's cst icms code.
    /*!
      Return the PurchaseProductOrder's cst icms code
      \return Returns the PurchaseProductOrder's cst icms code
      \sa setCstIcmsCode()
    */
    QString getCstIcmsCode();

    //! Get PurchaseProductOrder's cst ipi code.
    /*!
      Return the PurchaseProductOrder's cst ipi code
      \return Returns the PurchaseProductOrder's cst ipi code
      \sa setCstIpiCode()
    */
    QString getCstIpiCode();

    //! Get PurchaseProductOrder's cst pis code.
    /*!
      Return the PurchaseProductOrder's cst pis code
      \return Returns the PurchaseProductOrder's cst pis code
      \sa setCstPisCode()
    */
    QString getCstPisCode();

    //! Get PurchaseProductOrder's cst cofins code.
    /*!
      Return the PurchaseProductOrder's cst cofins code
      \return Returns the PurchaseProductOrder's cst cofins code
      \sa setCstCofinsCode()
    */
    QString getCstCofinsCode();

    //! Get PurchaseProductOrder's icms value.
    /*!
      Return the PurchaseProductOrder's icms value
      \return Returns the PurchaseProductOrder's icms value
      \sa setIcmsValue()
    */
    double getIcmsValue();

    //! Get PurchaseProductOrder's ipi value.
    /*!
      Return the PurchaseProductOrder's ipi value
      \return Returns the PurchaseProductOrder's ipi value
      \sa setIpiValue()
    */
    double getIpiValue();

    //! Get PurchaseProductOrder's pis value.
    /*!
      Return the PurchaseProductOrder's pis value
      \return Returns the PurchaseProductOrder's pis value
      \sa setPisValue()
    */
    double getPisValue();

    //! Get PurchaseProductOrder's cofins value.
    /*!
      Return the PurchaseProductOrder's cofins value
      \return Returns the PurchaseProductOrder's cofins value
      \sa setCofinsValue()
    */
    double getCofinsValue();

    //! Get PurchaseProductOrder's cfop code.
    /*!
      Return the PurchaseProductOrder's icms cfop code
      \return Returns the PurchaseProductOrder's cfop code
      \sa setCfopCode()
    */
    QString getCfopCode();

    //! Get PurchaseProductOrder's unit price.
    /*!
      Return the PurchaseProductOrder's icms unit price
      \return Returns the PurchaseProductOrder's unit price
      \sa setUnitPrice()
    */
    double getUnitPrice();

    //! Get PurchaseProductOrder's store cnpj.
    /*!
      Return the PurchaseProductOrder's store cnpj
      \return Returns the PurchaseProductOrder's store cnpj
      \sa setStoreCnpj()
    */
    QString getStoreCnpj();


    //! Set PurchaseProductOrder's product code.
    /*!
      \param productCode PurchaseProductOrder's product code
      \sa getProductCode()
    */
    void setProductCode(QString productCode);

    //! Set PurchaseProductOrder's quantity.
    /*!
      \param quantity PurchaseProductOrder's quantity
      \sa getQuantity()
    */
    void setQuantity(int quantity);

    //! Set PurchaseProductOrder's product origin code.
    /*!
      \param productOriginCode PurchaseProductOrder's product origin code
      \sa getProductOriginCode()
    */
    void setProductOriginCode(QChar productOriginCode);

    //! Set PurchaseProductOrder's cst icms code.
    /*!
      \param cstIcmsCode PurchaseProductOrder's cst icms code
      \sa getCstIcmsCode()
    */
    void setCstIcmsCode(QString cstIcmsCode);

    //! Set PurchaseProductOrder's cst ipi code.
    /*!
      \param cstIpiCode PurchaseProductOrder's cst ipi code
      \sa getCstIpiCode()
    */
    void setCstIpiCode(QString cstIpiCode);

    //! Set PurchaseProductOrder's cst pis code.
    /*!
      \param cstPisCode PurchaseProductOrder's cst pis code
      \sa getCstPisCode()
    */
    void setCstPisCode(QString cstPisCode);

    //! Set PurchaseProductOrder's cst cofins code.
    /*!
      \param cstCofinsCode PurchaseProductOrder's cst cofins code
      \sa getCstCofinsCode()
    */
    void setCstCofinsCode(QString cstCofinsCode);

    //! Set PurchaseProductOrder's icms value.
    /*!
      \param icmsValue PurchaseProductOrder's icms value
      \sa getIcmsValue()
    */
    void setIcmsValue(double icmsValue);

    //! Set PurchaseProductOrder's ipi value.
    /*!
      \param ipiValue PurchaseProductOrder's ipi value
      \sa getIpiValue()
    */
    void setIpiValue(double ipiValue);

    //! Set PurchaseProductOrder's pis value.
    /*!
      \param pisValue PurchaseProductOrder's pis value
      \sa getPisValue()
    */
    void setPisValue(double pisValue);

    //! Set PurchaseProductOrder's cofins value.
    /*!
      \param cofinsValue PurchaseProductOrder's cofins value
      \sa getCofinsValue()
    */
    void setCofinsValue(double cofinsValue);

    //! Set PurchaseProductOrder's cfop code.
    /*!
      \param cfopCode PurchaseProductOrder's cfop code
      \sa getCfopCode()
    */
    void setCfopCode(QString cfopCode);

    //! Set PurchaseProductOrder's unit price.
    /*!
      \param unitPrice PurchaseProductOrder's unit price
      \sa setUnitPrice()
    */
    void setUnitPrice(double unitPrice);

    //! Set PurchaseProductOrder's price id.
    /*!
      \param storeCnpj PurchaseProductOrder's store cnpj
      \sa getStoreCnpj()
    */
    void setStoreCnpj(QString storeCnpj);

private:
    int id;
    QString productCode;
    int quantity;
    QChar productOriginCode;
    QString cstIcmsCode;
    QString cstIpiCode;
    QString cstPisCode;
    QString cstCofinsCode;
    double icmsValue;
    double ipiValue;
    double pisValue;
    double cofinsValue;
    QString cfopCode;
    double unitPrice;
    QString storeCnpj;

signals:

public slots:

};

#endif // PURCHASEPRODUCTORDER_H
