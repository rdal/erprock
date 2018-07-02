#ifndef SALEPRODUCTORDER_H
#define SALEPRODUCTORDER_H

#include <QObject>

//!  SaleProductOrder basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for SaleProductOrder.
*/
class SaleProductOrder : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of SaleProductOrder. Use this constructor when updating a new SaleProductOrder Object
    */
    explicit SaleProductOrder(int id, QString productCode, int quantity, QString cstIcmsCode, QString cstIpiCode,
                              QString cstPisCode, QString cstCofinsCode, QString icmsPercentName, QString ipiPercentName,
                              QString pisPercentName, QString cofinsPercentName, QString cfopCode, QString storeCnpj,
                              double value, QObject *parent = 0);

    //! Default constructor.
    /*!
    * Create a new instance of SaleProductOrder. Use this constructor when creating a new SaleProductOrder Object
    */
    explicit SaleProductOrder(QString productCode, int quantity, QString cstIcmsCode, QString cstIpiCode, QString cstPisCode,
                              QString cstCofinsCode, QString icmsPercentName, QString ipiPercentName, QString pisPercentName,
                              QString cofinsPercentName, QString cfopCode, QString storeCnpj, double value, QObject *parent = 0);

    //! Get SaleProductOrder's id.
    /*!
      Return the SaleProductOrder's id
      \return Returns the SaleProductOrder's id
    */
    int getId();

    //! Get SaleProductOrder's product code.
    /*!
      Return the SaleProductOrder's product code
      \return Returns the SaleProductOrder's product code
      \sa setProductCode()
    */
    QString getProductCode();

    //! Get SaleProductOrder's quantity.
    /*!
      Return the SaleProductOrder's quantity
      \return Returns the SaleProductOrder's quantity
      \sa setQuantity()
    */
    int getQuantity();

    //! Get SaleProductOrder's cst icms code.
    /*!
      Return the SaleProductOrder's cst icms code
      \return Returns the SaleProductOrder's cst icms code
      \sa setCstIcmsCode()
    */
    QString getCstIcmsCode();

    //! Get SaleProductOrder's cst ipi code.
    /*!
      Return the SaleProductOrder's cst ipi code
      \return Returns the SaleProductOrder's cst ipi code
      \sa setCstIpiCode()
    */
    QString getCstIpiCode();

    //! Get SaleProductOrder's cst pis code.
    /*!
      Return the SaleProductOrder's cst pis code
      \return Returns the SaleProductOrder's cst pis code
      \sa setCstPisCode()
    */
    QString getCstPisCode();

    //! Get SaleProductOrder's cst cofins code.
    /*!
      Return the SaleProductOrder's cst cofins code
      \return Returns the SaleProductOrder's cst cofins code
      \sa setCstCofinsCode()
    */
    QString getCstCofinsCode();

    //! Get SaleProductOrder's icms percent name.
    /*!
      Return the SaleProductOrder's icms percent name
      \return Returns the SaleProductOrder's icms percent name
      \sa setIcmsPercentName()
    */
    QString getIcmsPercentName();

    //! Get SaleProductOrder's ipi percent name.
    /*!
      Return the SaleProductOrder's ipi percent name
      \return Returns the SaleProductOrder's ipi percent name
      \sa setIpiPercentName()
    */
    QString getIpiPercentName();

    //! Get SaleProductOrder's pis percent name.
    /*!
      Return the SaleProductOrder's pis percent name
      \return Returns the SaleProductOrder's pis percent name
      \sa setPisPercentName()
    */
    QString getPisPercentName();

    //! Get SaleProductOrder's cofins percent name.
    /*!
      Return the SaleProductOrder's cofins percent name
      \return Returns the SaleProductOrder's cofins percent name
      \sa setCofinsPercentName()
    */
    QString getCofinsPercentName();

    //! Get SaleProductOrder's cfop code.
    /*!
      Return the SaleProductOrder's icms cfop code
      \return Returns the SaleProductOrder's cfop code
      \sa setCfopCode()
    */
    QString getCfopCode();

//    //! Get SaleProductOrder's price id.
//    /*!
//      Return the SaleProductOrder's price id
//      \return Returns the SaleProductOrder's price id
//    */
//    int getPriceId();

    //! Get SaleProductOrder's store cnpj.
    /*!
      Return the SaleProductOrder's store cnpj
      \return Returns the SaleProductOrder's store cnpj
      \sa setStoreCnpj()
    */
    QString getStoreCnpj();

    //! Get SaleProductOrder's value.
    /*!
      Return the SaleProductOrder's value
      \return Returns the SaleProductOrder's value
      \sa setValue()
    */
    double getValue();


    //! Set SaleProductOrder's product code.
    /*!
      \param productCode SaleOrder's product code
      \sa getProductCode()
    */
    void setProductCode(QString productCode);

    //! Set SaleProductOrder's quantity.
    /*!
      \param quantity SaleOrder's quantity
      \sa getQuantity()
    */
    void setQuantity(int quantity);

    //! Set SaleProductOrder's cst icms code.
    /*!
      \param cstIcmsCode SaleOrder's cst icms code
      \sa getCstIcmsCode()
    */
    void setCstIcmsCode(QString cstIcmsCode);

    //! Set SaleProductOrder's cst ipi code.
    /*!
      \param cstIpiCode SaleOrder's cst ipi code
      \sa getCstIpiCode()
    */
    void setCstIpiCode(QString cstIpiCode);

    //! Set SaleProductOrder's cst pis code.
    /*!
      \param cstPisCode SaleOrder's cst pis code
      \sa getCstPisCode()
    */
    void setCstPisCode(QString cstPisCode);

    //! Set SaleProductOrder's cst cofins code.
    /*!
      \param cstCofinsCode SaleOrder's cst cofins code
      \sa getCstCofinsCode()
    */
    void setCstCofinsCode(QString cstCofinsCode);

    //! Set SaleProductOrder's icms percent name.
    /*!
      \param icmsPercentName SaleOrder's icms percent name
      \sa getIcmsPercentName()
    */
    void setIcmsPercentName(QString icmsPercentName);

    //! Set SaleProductOrder's ipi percent name.
    /*!
      \param ipiPercentName SaleOrder's ipi percent name
      \sa getIpiPercentName()
    */
    void setIpiPercentName(QString ipiPercentName);

    //! Set SaleProductOrder's pis percent name.
    /*!
      \param pisPercentName SaleOrder's pis percent name
      \sa getPisPercentName()
    */
    void setPisPercentName(QString pisPercentName);

    //! Set SaleProductOrder's cofins percent name.
    /*!
      \param cofinsPercentName SaleOrder's cofins percent name
      \sa getCofinsPercentName()
    */
    void setCofinsPercentName(QString cofinsPercentName);

    //! Set SaleProductOrder's cfop code.
    /*!
      \param cfopCode SaleOrder's cfop code
      \sa getCfopCode()
    */
    void setCfopCode(QString cfopCode);

//    //! Set SaleProductOrder's price id.
//    /*!
//      \param priceId SaleOrder's price id
//      \sa getPriceId()
//    */
//    void setPriceId(int priceId);

    //! Set SaleProductOrder's store cnpj.
    /*!
      \param storeCnpj SaleOrder's store cnpj
      \sa getStoreCnpj()
    */
    void setStoreCnpj(QString storeCnpj);

    //! Set SaleProductOrder's value.
    /*!
      \param value SaleOrder's value
      \sa getValue()
    */
    void setValue(double value);

private:
    int id;
    QString productCode;
    int quantity;
    QString cstIcmsCode;
    QString cstIpiCode;
    QString cstPisCode;
    QString cstCofinsCode;
    QString icmsPercentName;
    QString ipiPercentName;
    QString pisPercentName;
    QString cofinsPercentName;
    QString cfopCode;
    //int priceId;
    QString storeCnpj;
    double value;

signals:

public slots:

};

#endif // SALEPRODUCTORDER_H
