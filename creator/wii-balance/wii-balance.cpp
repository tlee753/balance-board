#include "wii-balance.h"
#include "ui_wii-balance.h"

WiiBalance::WiiBalance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WiiBalance)
{
    ui->setupUi(this);
}

WiiBalance::~WiiBalance()
{
    delete ui;
}
