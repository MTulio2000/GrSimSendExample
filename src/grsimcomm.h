#ifndef GRSIMCOMM_H
#define GRSIMCOMM_H
#include <vector>
#include <map>
#include <QUdpSocket>
#include "packet.h"
#include "include/grSim_Packet.pb.h"

enum Color:int
{
    BLUE,
    YELLOW
};

using namespace std;

typedef map<int,Packet> Packets;
typedef map<Color,Packets> TeamPackets;
class GrSimComm
{
private:
    TeamPackets _packets;
    QUdpSocket *_socket;
    int _port;
    double _timestamp;
    void send(grSim_Packet packet);

public:
    GrSimComm(int port);
    void addPacket(Color color,Packet packet);
    void send();
    void setPort(int newPort);
    void setTimestamp(double newTimestamp);
    void clear();
    const TeamPackets &packets() const;
};

#endif // GRSIMCOMM_H
