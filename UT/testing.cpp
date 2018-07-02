#include "testing.h"
#include "usercontroller.h"
#include "manufacturercontroller.h"
#include "productcategorycontroller.h"
#include "customercontroller.h"
#include "productorigincontroller.h"
#include "csticmscontroller.h"

#include <QDebug>

Testing::Testing(QObject *parent) :
    QObject(parent)
{
}

Testing::~Testing()
{
}

void Testing::addUser()
{
    User *u = new User("27277813006", User::CASH, "Sicrano", "f1259a0f2372b808ec26f3a3b4df94e0");
    UserController *userController = new UserController();
    Utilities::StatusControl status =  userController->addUser(u);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateUser()
{
    User *u = new User("27277813006", User::CASH, "Beltrano", "f1259a0f2372b808ec26f3a3b4df94e0");
    UserController *userController = new UserController();
    Utilities::StatusControl status =  userController->updateUser(u);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeUser()
{
    QString cpf("04635478723");
    UserController *userController = new UserController();
    Utilities::StatusControl status =  userController->removeUser(cpf);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::getUsers()
{
    UserController *userController = new UserController();
    QList<User*> *users =  userController->getUsers();

    int count = users->count();
    for(int i=0; i<count; i++)
    {
        User *u = users->at(i);
        qDebug() << "========== Usuarios ==========";
        qDebug() << "CPF: " << u->getCpf();
        qDebug() << "Role: " << QString::number(u->getRole());
        qDebug() << "Name: " << u->getName();
        qDebug() << "Password: " << u->getPassword();
        qDebug() << "==============================";
    }
}

void Testing::addManufacturer()
{
    Manufacturer *m = new Manufacturer("14205511000154", "123456", "SoftSO", "SoftSO Soluções em Tecnologia", "+55 (11) 31687555",
                                       "", "Rafael", "rafael.donato@softso.com.br", "Rua Joaquim Floriano",
                                       871, "salas 131/132", "Itaim Bibi", "São Paulo",
                                       "SP", "04534013");
    ManufacturerController *manufacturerController = new ManufacturerController();
    Utilities::StatusControl status =  manufacturerController->addManufacturer(m);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateManufacturer()
{
    Manufacturer *m = new Manufacturer("14205511000154", "123456", "SoftSO", "SoftSO Soluções em Tecnologia", "+55 (11) 31687555",
                                       "", "Rafael", "rafael.donato@softso.com.br", "Rua Joaquim Floriano",
                                       871, "salas 131/132", "Itaim Bibi", "São Paulo",
                                       "SP", "04534013");
    ManufacturerController *manufacturerController = new ManufacturerController();
    Utilities::StatusControl status =  manufacturerController->updateManufacturer(m);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeManufacturer()
{
    QString cnpj("14205511000154");
    ManufacturerController *manufacturerController = new ManufacturerController();
    Utilities::StatusControl status =  manufacturerController->removeManufacturer(cnpj);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::addProductCategory()
{
    ProductCategory *pc = new ProductCategory("Eletrônicos");
    ProductCategoryController *productCategoryController = new ProductCategoryController();
    Utilities::StatusControl status =  productCategoryController->addProductCategory(pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateProductCategory()
{
    ProductCategory *pc = new ProductCategory(1, "Livros");
    ProductCategoryController *productCategoryController = new ProductCategoryController();
    Utilities::StatusControl status =  productCategoryController->updateProductCategory(pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeProductCategory()
{
    ProductCategoryController *productCategoryController = new ProductCategoryController();
    Utilities::StatusControl status =  productCategoryController->removeProductCategory(1);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::addPhysicalCustomer()
{
    PhysicalCustomer *pc = new PhysicalCustomer("93842254873", "Usain Bolt", QDateTime::fromString("01/04/1980","dd/MM/yyyy"), "+55 (11) 31687555", "usain@bolt.com", "Av. Ibirapuera", 680, "", "Ibirapuera", "São Paulo", "SP", "04543666");
    CustomerController *physicalCustomerController = new CustomerController();
    Utilities::StatusControl status =  physicalCustomerController->addCustomer(pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updatePhysicalCustomer()
{
    PhysicalCustomer *pc = new PhysicalCustomer("93842254873", "Usain Bolt", QDateTime::fromString("01/04/1980","dd/MM/yyyy"), "+55 (11) 31687555", "usain@boltyyyy.com", "Av. Ibirapuera", 680, "", "Ibirapuera", "São Paulo", "SP", "04543000");
    CustomerController *physicalCustomerController = new CustomerController();
    Utilities::StatusControl status =  physicalCustomerController->updateCustomer(pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removePhysicalCustomer()
{
    CustomerController *physicalCustomerController = new CustomerController();
    Utilities::StatusControl status =  physicalCustomerController->removeCustomer("93842254873");
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::addEnterpriseCustomer()
{
    EnterpriseCustomer *ec = new EnterpriseCustomer("96247415000133", "5432", "Apple", "Apple Inc.", "+55 (11) 31684080", "+55 (11) 66666666", "Steve", "contact@apple.com", "Av. das Nações Unidas", 2998, "Bloco G", "Itaim Bibi", "São Paulo", "SP", "04523100");
    CustomerController *enterpriseCustomerController = new CustomerController();
    Utilities::StatusControl status =  enterpriseCustomerController->addCustomer(ec);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateEnterpriseCustomer()
{
    EnterpriseCustomer *ec = new EnterpriseCustomer("96247415000133", "54321", "Apple", "Apple Inc.", "+55 (11) 31684080", "+55 (11) 66666666", "Steve", "contact@apple.com", "Av. das Nações Unidas", 2998, "Bloco G", "Itaim Bibi", "São Paulo", "SP", "04523100");
    CustomerController *enterpriseCustomerController = new CustomerController();
    Utilities::StatusControl status =  enterpriseCustomerController->updateCustomer(ec);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeEnterpriseCustomer()
{
    CustomerController *enterpriseCustomerController = new CustomerController();
    Utilities::StatusControl status =  enterpriseCustomerController->removeCustomer("96247415000133");
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::addProductOrigin()
{
    ProductOrigin *po = new ProductOrigin("3", "dsfafda");
    ProductOriginController *productOriginController = new ProductOriginController();
    Utilities::StatusControl status =  productOriginController->addProductOrigin(po);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateProductOrigin()
{
    ProductOrigin *pc = new ProductOrigin("2", "Estrangeira - Adquirida no mercado interno");
    ProductOriginController *productOriginController = new ProductOriginController();
    Utilities::StatusControl status =  productOriginController->updateProductOrigin("2", pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeProductOrigin()
{
    ProductOriginController *productOriginController = new ProductOriginController();
    Utilities::StatusControl status =  productOriginController->removeProductOrigin("3");
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::addCstIcms()
{
    CstIcms *po = new CstIcms("00", "dsfafda");
    CstIcmsController *cstIcmsController = new CstIcmsController();
    Utilities::StatusControl status =  cstIcmsController->addCstIcms(po);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::updateCstIcms()
{
    CstIcms *pc = new CstIcms("00", "Fuuu");
    CstIcmsController *cstIcmsController = new CstIcmsController();
    Utilities::StatusControl status =  cstIcmsController->updateCstIcms("00", pc);
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

void Testing::removeCstIcms()
{
    CstIcmsController *cstIcmsController = new CstIcmsController();
    Utilities::StatusControl status =  cstIcmsController->removeCstIcms("00");
    if(status == Utilities::NO_ERR)
    {
        //int a = 0;
    }
}

