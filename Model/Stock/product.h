#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

//!  Product basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Product.
*/
class Product : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Product.
    */
    explicit Product(QString code, QString barCode, int productCategoryId, QString manufacturerCnpj,
                     QString name, QString description, QString cstIcms, QString cstIpi,
                     QString cstPis, QString cstCofins, QString icmsPercentName, QString ipiPercentName,
                     QString pisPercentName, QString cofinsPercentName, QString cfopCode, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Product();

    //! Get product's code.
    /*!
      Return the product's code
      \return Returns the product's code
      \sa setCode()
    */
    QString getCode();

    //! Get product's bar code.
    /*!
      Return the product's bar code
      \return Returns the product's bar code
      \sa setBarCode()
    */
    QString getBarCode();

    //! Get product category id.
    /*!
      Return the product category id
      \return Returns the product category id
      \sa setProductCategoryId()
    */
    int getProductCategoryId();

    //! Get manufacturer's cnpj.
    /*!
      Return the manufacturer's cnpj
      \return Returns the manufacturer's cnpj
      \sa setManufacturerCnpj()
    */
    QString getManufacturerCnpj();

    //! Get product's name.
    /*!
      Return the product's name
      \return Returns the product's name
      \sa setName()
    */
    QString getName();

    //! Get product's description.
    /*!
      Return the product's description
      \return Returns the product's description
      \sa setDescription()
    */
    QString getDescription();

    //! Get product's cstIcms.
    /*!
      Return the product's CST ICMS
      \return Returns the product's cstIcms
      \sa setCstIcms()
    */
    QString getCstIcms();

    //! Get product's cstIpi.
    /*!
      Return the product's CST IPI
      \return Returns the product's cstIpi
      \sa setCstIpi()
    */
    QString getCstIpi();

    //! Get product's cstPis.
    /*!
      Return the product's CST PIS
      \return Returns the product's cstPis
      \sa setCstPis()
    */
    QString getCstPis();

    //! Get product's cstCofins.
    /*!
      Return the product's CST COFINS
      \return Returns the product's cstCofins
      \sa setCstCofins()
    */
    QString getCstCofins();

    //! Get product's icmsPercentName.
    /*!
      Return the product's ICMS percent name
      \return Returns the product's icmsPercentName
      \sa setIcmsPercentName()
    */
    QString getIcmsPercentName();

    //! Get product's ipiPercentName.
    /*!
      Return the product's IPI percent name
      \return Returns the product's ipiPercentName
      \sa setIpiPercentName()
    */
    QString getIpiPercentName();

    //! Get product's pisPercentName.
    /*!
      Return the product's PIS percent name
      \return Returns the product's pisPercentName
      \sa setPisPercentName()
    */
    QString getPisPercentName();

    //! Get product's cofinsPercentName.
    /*!
      Return the product's COFINS percent name
      \return Returns the product's cofinsPercentName
      \sa setCofinsPercentName()
    */
    QString getCofinsPercentName();

    //! Get product's cfop code.
    /*!
      Return the product's CFOP code
      \return Returns the product's cfopCode
      \sa setCfopCode()
    */
    QString getCfopCode();

//    //! Get product's purchase price.
//    /*!
//      Return the product's purchase price
//      \return Returns the product's purchase price
//      \sa setPurchasePrice()
//    */
//    double getPurchasePrice();

//    //! Get product's selling price.
//    /*!
//      Return the product's selling price
//      \return Returns the product's selling price
//      \sa setSellingPrice()
//    */
//    double getSellingPrice();

//    //! Get quantity of products.
//    /*!
//      Return the quantity of products
//      \return Returns the quantity of products
//      \sa setQuantity()
//    */
//    double getQuantity();


    //! Set product's code.
    /*!
      \param code Product's code
      \sa getCode()
    */
    void setCode(QString code);

    //! Set product's bar code.
    /*!
      \param barCode Product's bar code
      \sa getBarCode()
    */
    void setBarCode(QString barCode);

    //! Set product category id.
    /*!
      \param productCategoryId Product category id
      \sa getProductCategoryId()
    */
    void setProductCategoryId(int productCategoryId);

    //! Set manufacturer cnpj.
    /*!
      \param manufacturerCnpj Product manufacturer id
      \sa getProductCategoryId()
    */
    void setManufacturerCnpj(QString manufacturerCnpj);

    //! Set product's name.
    /*!
      \param name Product's name
      \sa getName()
    */
    void setName(QString name);

    //! Set product's description.
    /*!
      \param description Product's description
      \sa getDescription()
    */
    void setDescription(QString description);

    //! Set product's cstIcms.
    /*!
      \param cstIcms Product's CST ICMS
      \sa getCstIcms()
    */
    void setCstIcms(QString cstIcms);

    //! Set product's cstIpi.
    /*!
      \param cstIpi Product's CST IPI
      \sa getCstIpi()
    */
    void setCstIpi(QString cstIpi);

    //! Set product's cstPis.
    /*!
      \param cstPis Product's CST PIS
      \sa getCstPis()
    */
    void setCstPis(QString cstPis);

    //! Set product's cstCofins.
    /*!
      \param cstCofins Product's CST COFINS
      \sa getCstCofins()
    */
    void setCstCofins(QString cstCofins);

    //! Set product's icmsPercentName.
    /*!
      \param icmsPercentName Product's ICMS percent name
      \sa getIcmsPercentName()
    */
    void setIcmsPercentName(QString icmsPercentName);

    //! Set product's ipiPercentName.
    /*!
      \param ipiPercentName Product's IPI percent name
      \sa getIpiPercentName()
    */
    void setIpiPercentName(QString ipiPercentName);

    //! Set product's pisPercentName.
    /*!
      \param pisPercentName Product's PIS percent name
      \sa getPisPercentName()
    */
    void setPisPercentName(QString pisPercentName);

    //! Set product's cofinsPercentName.
    /*!
      \param cofinsPercentName Product's COFINS percent name
      \sa getCofinsPercentName()
    */
    void setCofinsPercentName(QString cofinsPercentName);

    //! Set product's cfopCode.
    /*!
      \param cfopCode Product's CFOP code
      \sa getCfopCode()
    */
    void setCfopCode(QString cfopCode);

//    //! Set product's purchase price.
//    /*!
//      \param purchasePrice Product's purchase price
//      \sa getPurchasePrice()
//    */
//    void setPurchasePrice(double purchasePrice);

//    //! Set product's selling price.
//    /*!
//      \param sellingPrice Product's selling price
//      \sa getSellingPrice()
//    */
//    void setSellingPrice(double sellingPrice);

//    //! Set quantity of products.
//    /*!
//      \param quantity Quantity of products
//      \sa getQuantity()
//    */
//    void setQuantity(double quantity);

private:
    QString code;
    QString barCode;
    int productCategoryId;
    QString manufacturerCnpj;
    QString name;
    QString description;
//    double purchasePrice;
//    double sellingPrice;
    QString cstIcms;
    QString cstIpi;
    QString cstPis;
    QString cstCofins;
    QString icmsPercentName;
    QString ipiPercentName;
    QString pisPercentName;
    QString cofinsPercentName;
    QString cfopCode;
//    int taxSituation; /// TODO: Enum => tributado, isento, nao-tributado, base de calculo reduzida, imune (http://www.praticacontabil.com.br/fiscal/cod_sit_trib.htm)
//    double quantity;

signals:

public slots:

};

#endif // PRODUCT_H
