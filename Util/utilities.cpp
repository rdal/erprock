#include "utilities.h"
#include "databasecontroller.h"

#include <QMessageBox>

Utilities::Utilities(QObject *parent) :
    QObject(parent)
{
}

QString Utilities::getBundlePath()
{
    const char *pathPtr;

#ifdef Q_OS_MAC
    CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,kCFURLPOSIXPathStyle);
    pathPtr = CFStringGetCStringPtr(macPath,CFStringGetSystemEncoding());
#elif (defined Q_OS_WIN)
	pathPtr = ".";
#endif

    QString ret(pathPtr);

#ifdef Q_OS_MAC
    CFRelease(appUrlRef);
    CFRelease(macPath);
#endif

    return ret;
}

QString Utilities::getResourcesPath()
{
    return (Utilities::getBundlePath() + RESOURCES_FOLDER);
}



QString Utilities::stripCPFChars(QString str)
{
    QStringList piecesDots = str.split(".");
    QStringList piecesDash = piecesDots.at(2).split("-");

    QStringList resultCPFStrList;
    resultCPFStrList << piecesDots.at(0) << piecesDots.at(1) << piecesDash.at(0) << piecesDash.at(1);
    QString resultCPF = resultCPFStrList.join("");

    return resultCPF;
}

bool Utilities::isCpfValid(QString cpfStr)
{
    bool ret = false;
    if(cpfStr.count() == 11)
    {
        char cpf[12];
        int multiplicador1[]={10,9,8,7,6,5,4,3,2};
        int multiplicador2[]={11,10,9,8,7,6,5,4,3};
        int i;
        int total;
        int dv1;
        int dv2;
        int nr;

        const char* cCPF = cpfStr.toLocal8Bit().constData();

        cpf[0] = cCPF[0];
        cpf[1] = cCPF[1];
        cpf[2] = cCPF[2];
        cpf[3] = cCPF[3];
        cpf[4] = cCPF[4];
        cpf[5] = cCPF[5];
        cpf[6] = cCPF[6];
        cpf[7] = cCPF[7];
        cpf[8] = cCPF[8];
        cpf[9] = cCPF[9];
        cpf[10] = cCPF[10];
        cpf[11] = cCPF[11];

        //CALCULO
        //CALCULO DO PRIMEIRO DV
        total = 0;
        for (i=0;i<9;i++)
        {
            nr = (int)cpf[i]-48;
            total=total+ nr * multiplicador1[i];
        }
        dv1 = (total * 10) % 11;
        if (dv1 == 10) dv1 = 0;

        //CALCULO DO SEGUNDO DV
        total = 0;
        for (i=0;i<9;i++)
        {
            nr = (int)cpf[i]-48;
            total += nr * multiplicador2[i];
        }
        dv2 = ((total + (2 * dv1)) * 10) % 11;

        if( ((char)(dv1+48)==cpf[9]) && ((char)(dv2+48)==cpf[10]) )
        {
            ret = true;
        }

    }

    return ret;
}

QString Utilities::stripCNPJChars(QString str)
{
    QStringList piecesDots = str.split(".");
    QStringList piecesSlash = piecesDots.at(2).split("/");
    QStringList piecesDash = piecesSlash.at(1).split("-");

    QStringList resultCNPJStrList;
    resultCNPJStrList << piecesDots.at(0) << piecesDots.at(1) << piecesSlash.at(0) << piecesDash.at(0) << piecesDash.at(1);
    QString resultCNPJ = resultCNPJStrList.join("");

    return resultCNPJ;
}

bool Utilities::isCNPJValid(QString str)
{
    bool ret = false;
    if(str.count() == 14)
    {

        char cnpj[14];

        const char *cCNPJ = str.toLatin1().constData();
        cnpj[0] = cCNPJ[0];
        cnpj[1] = cCNPJ[1];
        cnpj[2] = cCNPJ[2];
        cnpj[3] = cCNPJ[3];
        cnpj[4] = cCNPJ[4];
        cnpj[5] = cCNPJ[5];
        cnpj[6] = cCNPJ[6];
        cnpj[7] = cCNPJ[7];
        cnpj[8] = cCNPJ[8];
        cnpj[9] = cCNPJ[9];
        cnpj[10] = cCNPJ[10];
        cnpj[11] = cCNPJ[11];
        cnpj[12] = cCNPJ[12];
        cnpj[13] = cCNPJ[13];

        int i,j=9,icnpj[14],somador=0,div,digito1,div2,digito2;



        for(i=0;i<14;i++)
        {
            icnpj[i]=cnpj[i]-48;
        }

        //soma dos digitos.

        for(i=0;i<5;i++)
        {
            if(i!=4)
            {
                somador+=icnpj[i]*(5-i);
            }
        }

        for(i=4;i<12 && j!=1;i++)
        {
            somador+=icnpj[i]*(j--);
        }

        //DIVISAO

        div=somador%11;

        //1 DIGITO

        if(div<2)
        {
            digito1=0;
        }
        else
        {
            digito1=11-div;
        }

        //2 DIGITO

        somador=0;
        j=9;

        for(i=0;i<6;i++)
        {
            if(i!=5)
            {
                somador+=icnpj[i]*(6-i);
            }
        }

        for(i=5;i<13 && j!=1;i++)
        {
            somador+=icnpj[i]*(j--);
        }

        div2=somador%11;

        if(div2<2)
        {
            digito2=0;
        }
        else
        {
            digito2=11-div2;
        }

        //VALIDAR DIGITOS.

        if( (digito1==icnpj[12]) && (digito2==icnpj[13]) )
        {
            ret = true;
        }
    }

    return ret;
}

QString Utilities::getDefaultCNPJ()
{
    DatabaseController *databaseController = DatabaseController::getInstance();
    return databaseController->getDefaultStore()->getCNPJ();
}

////QString Utilities::getDefaultCustomerAccount()
////{
////    DatabaseController *databaseController = DatabaseController::getInstance();
////    return databaseController->getDefaultCustomerAccount();
////}

//QString Utilities::getDefaultProviderAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultProviderAccount();
//}

////QString Utilities::getDefaultCashAccount()
////{
////    DatabaseController *databaseController = DatabaseController::getInstance();
////    return databaseController->getDefaultCashAccount();
////}

//QString Utilities::getDefaultIcmsToRecoverAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultIcmsToRecoverAccount();
//}

//QString Utilities::getDefaultPisToRecoverAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultPisToRecoverAccount();
//}

//QString Utilities::getDefaultCofinsToRecoverAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultCofinsToRecoverAccount();
//}

//QString Utilities::getDefaultProductStockAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultProductStockAccount();
//}

//QString Utilities::getDefaultDebtorSaleAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultDebtorSaleAccount();
//}

//QString Utilities::getDefaultCreditorSaleAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultCreditorSaleAccount();
//}

//QString Utilities::getDefaultIcmsInSalesDebtorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultIcmsInSalesDebtorAccount();
//}

//QString Utilities::getDefaultIcmsInSalesCreditorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultIcmsInSalesCreditorAccount();
//}

//QString Utilities::getDefaultPisInSalesDebtorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultPisInSalesDebtorAccount();
//}

//QString Utilities::getDefaultPisInSalesCreditorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultPisInSalesCreditorAccount();
//}

//QString Utilities::getDefaultCofinsInSalesDebtorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultCofinsInSalesDebtorAccount();
//}

//QString Utilities::getDefaultCofinsInSalesCreditorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultCofinsInSalesCreditorAccount();
//}

//QString Utilities::getDefaultGoodsShippingDebtorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultGoodsShippingDebtorAccount();
//}

//QString Utilities::getDefaultGoodsShippingCreditorAccount()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getDefaultGoodsShippingCreditorAccount();
//}

//int Utilities::getBuyProductHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getBuyProductHistoryId();
//}

//int Utilities::getTaxCreditHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getTaxCreditHistoryId();
//}

//int Utilities::getSaleHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getSaleHistoryId();
//}

//int Utilities::getIcmsInSalesHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getIcmsInSalesHistoryId();
//}

//int Utilities::getPisInSalesHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getPisInSalesHistoryId();
//}

//int Utilities::getCofinsInSalesHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getCofinsInSalesHistoryId();
//}

//int Utilities::getGoodsShippingHistoryId()
//{
//    DatabaseController *databaseController = DatabaseController::getInstance();
//    return databaseController->getGoodsShippingHistoryId();
//}

QString Utilities::getPaymentFormName(PaymentForm paymentForm)
{
    QString ret = "";
    switch(paymentForm)
    {
        case MONEY:
        {
            ret = tr("Money");
            break;
        }
        case VISA:
        {
            ret = tr("Visa");
            break;
        }
        case MASTERCARD:
        {
            ret = tr("MasterCard");
            break;
        }
        case DINERS:
        {
            ret = tr("Diners");
            break;
        }
        case AMEX:
        {
            ret = tr("American Express");
            break;
        }
        case BANK_TICKET:
        {
            ret = tr("Bank Ticket");
            break;
        }
        default:
        {
            break;
        }
    }

    return ret;
}
