#include "info_tour.h"
#include "ui_info_tour.h"
Info_tour::Info_tour(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_tour)
{
    ui->setupUi(this);
}
Info_tour::~Info_tour()
{
    delete ui;
}
