#include "start.h"
#include "tank.h"
#include "ui_start.h"
#include <QPainter>

start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    this->setGeometry(QRect(450,300,299,310));
    this->setFixedSize(1000,500);
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_A_clicked()
{
    emit emitsignal_A();
    this->hide();
}

void start::on_pushButton_B_clicked()
{
    emit emitsignal_B();
    this->hide();
}

void start::acceptstart_B1()
{
    this->show();
    this->raise();
}

void start::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(0,0,1000,500);
    painter.drawPixmap(0,0,1000,500,QPixmap(":/image/open.jpg"));
}



