#ifndef PACKET_H
#define PACKET_H
#include <QString>

typedef struct Packet
{
    int id = -1;
    float kickspeedx;
    float kickspeedz;
    float veltangent;
    float velnormal;
    float velangular;
    bool spinner;
    bool wheelsspeed;
    float wheel1;
    float wheel2;
    float wheel3;
    float wheel4;
    double value(int index)
    {
        switch(index)
        {
            case 0: return id;
            case 1: return kickspeedx;
            case 2: return kickspeedz;
            case 3: return veltangent;
            case 4: return velnormal;
            case 5: return velangular;
            case 6: return spinner;
            case 7: return wheelsspeed;
            case 8: return wheel1;
            case 9: return wheel2;
            case 10: return wheel3;
            case 11: return wheel4;
        }
        return -1;
    };
    static QString name(int index)
    {
        switch(index)
        {
            case 0: return "id";
            case 1: return "kickspeedx";
            case 2: return "kickspeedz";
            case 3: return "veltangent";
            case 4: return "velnormal";
            case 5: return "velangular";
            case 6: return "spinner";
            case 7: return "wheelsspeed";
            case 8: return "w1";
            case 9: return "w2";
            case 10: return "w3";
            case 11: return "w4";
        }
        return "";
    };
}Packet;
#endif // PACKET_H
