#include "help.h"
#include "ui_help.h"
#include <QPainter>

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    this->setGeometry(QRect(450,300,299,310));
    this->setFixedSize(1000,500);
}

help::~help()
{
    delete ui;
}

void help::acceptstart_B()
{
    this->show();
    this->raise();
}

void help::on_pushButton_clicked()
{
    emit emitsignal_B1();
    this->hide();
}

void help::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(0,0,1000,500);
    painter.drawPixmap(0,0,1000,500,QPixmap(":/image/open.jpg"));
}
