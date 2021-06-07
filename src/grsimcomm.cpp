#include "grsimcomm.h"

GrSimComm::GrSimComm(int port)
{
    this->_socket = new QUdpSocket();
    this->_port = port;
    clear();
}

void GrSimComm::addPacket(Color color, Packet packet)
{
    this->_packets[color][packet.id] = packet;
}

void GrSimComm::send()
{
    auto add = [&](const Packet packet,grSim_Robot_Command *command)
    {
        command->set_id(packet.id);
        command->set_kickspeedx(packet.kickspeedx);
        command->set_kickspeedz(packet.kickspeedz);
        command->set_spinner(packet.spinner);
        command->set_velangular(packet.velangular);
        command->set_velnormal(packet.velnormal);
        command->set_veltangent(packet.veltangent);
        command->set_wheelsspeed(packet.wheelsspeed);
        command->set_wheel1(packet.wheel1);
        command->set_wheel2(packet.wheel2);
        command->set_wheel3(packet.wheel3);
        command->set_wheel4(packet.wheel4);
    };
    for(const auto &team: _packets)
    {
        grSim_Packet pack;
        pack.mutable_commands()->set_isteamyellow(team.first == YELLOW);
        pack.mutable_commands()->set_timestamp(_timestamp);
        for(auto packet:team.second)
            add(packet.second,pack.mutable_commands()->add_robot_commands());
        send(pack);
    }
}

void GrSimComm::setTimestamp(double newTimestamp)
{
    _timestamp = newTimestamp;
}

void GrSimComm::clear()
{
    _packets = TeamPackets();
    for(int i = 0; i < 2;i++)
        for(int j = 0; j < 16; j ++)
            _packets[(Color)i][j].id = j;
}

const TeamPackets &GrSimComm::packets() const
{
    return _packets;
}

void GrSimComm::send(grSim_Packet packet)
{
    QByteArray buffer(packet.ByteSize(), 0);
    packet.SerializeToArray(buffer.data(),buffer.size());
    _socket->writeDatagram(buffer,QHostAddress::LocalHost,_port);
}

void GrSimComm::setPort(int newPort)
{
    _port = newPort;
}
