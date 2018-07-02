#include "productcontroller.h"

ProductController::ProductController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

ProductController::~ProductController()
{
    //dbController = NULL;
}

Utilities::StatusControl ProductController::addProduct(Product *product)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->productAlreadyExists(product->getCode());
        bool barCodeExists = dbController->barCodeAlreadyExists(product->getBarCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(barCodeExists)
        {
            ret = Utilities::BAR_CODE_ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewProduct(product);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }

    return ret;
}

Utilities::StatusControl ProductController::updateProduct(QString code, Product *product)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->productAlreadyExists(code);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->updateProduct(code, product);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Utilities::StatusControl ProductController::removeProduct(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeProduct(code);
        if(!result)
        {
            ret = Utilities::UNKNOWN_ERROR;
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Product *ProductController::getProductByCode(QString code)
{
    Product *product = NULL;
    if(dbController->isConnectionOpen())
    {
        product = dbController->getProductByCode(code);
    }
    return product;
}

QList<Product*> *ProductController::getProducts()
{
    QList<Product*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getProducts();
    }

    return ret;
}

int ProductController::getQuantityByCode(QString code)
{
    int ret = -1;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getProductsQuantityByCode(code);
    }

    return ret;
}
