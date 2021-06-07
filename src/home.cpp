#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    _comm = new GrSimComm(20011);

    auto initialize = [this](QTableView *table,Color color)
    {
        _models[color] = new QStandardItemModel(12,16,this);
        _models[color]->setColumnCount(12);
        _models[color]->setRowCount(16);

        for(int i = 0; i < 12;i++)
        {
            _models[color]->setHeaderData(i,Qt::Orientation::Horizontal,QVariant(Packet::name(i)));
            table->setColumnWidth(i,50);
            table->setRowHeight(i,5);
        }
        for(int i = 0; i < 16;i++)
            _models[color]->setHeaderData(i,Qt::Orientation::Vertical,QVariant(""));

        table->setModel(_models[color]);
    };
    initialize(ui->tbl_packets_blue,BLUE);
    initialize(ui->tbl_packets_yellow,YELLOW);

    updateTable();

    connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(updateTable()));
    connect(ui->btn_clear,SIGNAL(clicked()),this,SLOT(updateTable()));
    connect(ui->btn_send,SIGNAL(clicked()),this,SLOT(updateTable()));
}

Home::~Home()
{
    delete ui;
}

void Home::on_btn_add_clicked()
{
    Packet packet;
    packet.id = ui->cbb_id->currentIndex();
    packet.kickspeedx = ui->txt_kickspeedx->text().toDouble();
    packet.kickspeedz = ui->txt_kickspeedz->text().toDouble();
    packet.spinner = ui->chk_spinner->isChecked();
    packet.velangular = ui->txt_velangular->text().toDouble();
    packet.velnormal = ui->txt_velnormal->text().toDouble();
    packet.veltangent = ui->txt_veltangent->text().toDouble();
    packet.wheel1 = ui->txt_w1->text().toDouble();
    packet.wheel2 = ui->txt_w2->text().toDouble();
    packet.wheel3 = ui->txt_w3->text().toDouble();
    packet.wheel4 = ui->txt_w4->text().toDouble();
    packet.wheelsspeed = ui->chk_wheelspeed->isChecked();
    _comm->addPacket(ui->chk_yellow->isChecked()?YELLOW:BLUE,packet);
}

void Home::on_btn_send_clicked()
{
    _comm->setTimestamp(ui->txt_timestamp->text().toDouble());
    _comm->send();
}

void Home::on_btn_clear_clicked()
{
    _comm->clear();
}

void Home::updateTable()
{
    TeamPackets packets = _comm->packets();
    for(int i = 0; i < 2;i++)
    {
        for(int j = 0; j < 16; j ++)
        {

            for(int k = 0; k < 12;k++)
            {
                QModelIndex index = _models[(Color)i]->index(j,k,QModelIndex());
                _models[(Color)i]->setData(index,packets[(Color)i][j].value(k));
            }
        }
    }
}

void Home::on_btn_update_clicked()
{
    _comm->setPort(ui->txt_port->text().toInt());
}

