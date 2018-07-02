#include "productcategorycontroller.h"

ProductCategoryController::ProductCategoryController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

ProductCategoryController::~ProductCategoryController()
{
    //dbController = NULL;
}

Utilities::StatusControl ProductCategoryController::addProductCategory(ProductCategory *productCategory)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->productCategoryAlreadyExists(productCategory->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewProductCategory(productCategory);
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

Utilities::StatusControl ProductCategoryController::updateProductCategory(ProductCategory *productCategory)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->updateProductCategory(productCategory);
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

Utilities::StatusControl ProductCategoryController::removeProductCategory(int id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeProductCategory(id);
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

ProductCategory *ProductCategoryController::getProductCategoryById(int id)
{
    ProductCategory *productCategory = NULL;
    if(dbController->isConnectionOpen())
    {
        productCategory = dbController->getProductCategoryById(id);
    }
    return productCategory;
}

QList<ProductCategory*> *ProductCategoryController::getProductCategories()
{
    QList<ProductCategory*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getProductCategories();
    }

    return ret;
}
