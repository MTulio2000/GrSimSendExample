#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "grsimcomm.h"

typedef map<Color,QStandardItemModel*> Models;

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_btn_add_clicked();

    void on_btn_send_clicked();

    void on_btn_clear_clicked();

    void updateTable();

    void on_btn_update_clicked();

private:
    Ui::Home *ui;
    GrSimComm *_comm;
    Models _models;
};
#endif // HOME_H
