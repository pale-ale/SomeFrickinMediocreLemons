#pragma once
#include "../GlobalFunctions.h"
enum class EDatagramType{
    UNUSED,
    Management,
    Gamerule,
    Card,
    Event,
    MAX
};

enum class EPlayerEventType{
    UNUSED,
    Join,
    Leave,
    MAX
};

struct FGeneralDatagram{
    FGeneralDatagram(const char dg[35]=""){
        memcpy(content, dg, sizeof(char)*35);
    }
    char content[35] = "";
};

struct FManagementDatagram{
    FManagementDatagram(EPlayerEventType t, unsigned short playerID){
        data[0]=(char)EDatagramType::Management;
        data[1]=(char)t;
        memcpy(&data[2], &playerID, 2);
    }
    FManagementDatagram(const FGeneralDatagram *dg){
        memcpy(&data, dg->content, 35);
    }

    FManagementDatagram(const char* dg){
        memcpy(&data, &dg, 35);
    }
    EPlayerEventType getEventType() const { return (EPlayerEventType)data[1]; }
    unsigned short getPlayerID() const { unsigned short id; memcpy(&id, &data[2], 2); return id;}
    char data[35];
};

class ProtocolBuilder{
    public:
    static FManagementDatagram assembleJoinRequest(const unsigned short playerID){
        return FManagementDatagram(EPlayerEventType::Join, playerID);
    }

    static bool parseStringToDatagram(const char *data, FGeneralDatagram &outDatagram){
        EDatagramType dgType = (EDatagramType)data[0];
        if (dgType > EDatagramType::UNUSED && dgType < EDatagramType::MAX){
            //check if the type is valid/which type it is
            switch (dgType)
            {
            case EDatagramType::Management:
                outDatagram = FGeneralDatagram(data);
                return true;
                break;
            
            default:
                break;
            }

        }
        return false;
    }
};
