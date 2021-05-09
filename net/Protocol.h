#include "../GlobalFunctions.h"

enum EDatagramType{
    UNUSED,
    Management,
    Gamerule,
    Card,
    Event,
    MAX
};

struct FGeneralDatagram{
    FGeneralDatagram(EDatagramType dgType, const char dg[35]){
        memcpy(content, dg, sizeof(char)*35);
    }
    EDatagramType dgType;
    char content[35] = "";
};
struct FManagementDatagram{
    FManagementDatagram(FGeneralDatagram dg){
        eventType = dg.content[0];
        memcpy(&playerID, &dg.content[1], 2);
    }
    uint8_t eventType;
    unsigned short playerID;
};

class ProtocolBuilder{
    public:
    static FGeneralDatagram assembleJoinRequest(const unsigned short playerID){
        char dgContents[35];
        dgContents[0] = (char)EDatagramType::Management;
        memcpy(&dgContents[1], &playerID, sizeof(char)*2);
        return FGeneralDatagram(EDatagramType::Management, dgContents);
    }
};
