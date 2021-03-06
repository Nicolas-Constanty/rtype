//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IPROTOCOLGAMEHANDLER_HPP
#define RTYPE_IPROTOCOLGAMEHANDLER_HPP

#include "ProtocolGamePackage.hpp"

class PREF_EXPORT IProtocolGameHandler {
public:
    virtual ~IProtocolGameHandler() {}

public:
    virtual void onGetSTATUSPackage(STATUSPackageGame const &) = 0;
    virtual void onGetPINGPackage(PINGPackageGame const &) = 0;
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &) = 0;
    virtual void onGetCREATEPackage(CREATEPackageGame const &) = 0;
    virtual void onGetBEAMPackage(BEAMPackageGame const &) = 0;
    virtual void onGetSHOTPackage(SHOTPackageGame const &) = 0;
    virtual void onGetDIEPackage(DIEPackageGame const &) = 0;
    virtual void onGetTAKEPackage(TAKEPackageGame const &) = 0;
    virtual void onGetCALLPackage(CALLPackageGame const &) = 0;
    virtual void onGetMOVEPackage(MOVEPackageGame const &) = 0;
    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &) = 0;
    virtual void onGetREBORNPackage(REBORNPackageGame const &) = 0;
    virtual void onGetFAILUREPackage(FAILUREPackageGame const &) = 0;
    virtual void onGetDISCONNECTPackage(DISCONNECTPackageGame const &) = 0;
    virtual void onGetENEMYSHOTPackage(ENEMYSHOTPackageGame const &) = 0;
    virtual void onGetUPGRADEPackage(UPGRADEPackageGame const &) = 0;
    virtual void onGetMATEPackage(MATEPackageGame const &) = 0;
    virtual void onGetGAMEOVERPackage(GAMEOVERPackageGame const &) = 0;
    virtual void onGetDEATHPackage(DEATHPackage const &) = 0;
    virtual void onGetRECONNECTPackage(RECONNECTPackageGame const &) = 0;
};

#endif //RTYPE_IPROTOCOLGAMEHANDLER_HPP
