#include "tank.h"
#include "ui_tank.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>
#include <QPushButton>
Tank::Tank(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tank),shoot(false),shoot_(false),blsRun(false),Blood_A(100),Blood_B(100),Painkiller(false),Damage_A(10),Damage_B(10)
{
    ui->setupUi(this);
    this->setGeometry(QRect(500,50,200,250));
    this->setFixedSize(900,980);

}

Tank::~Tank()
{
    delete ui;
}

void Tank::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!blsRun)
        InitTank();

    //画游戏的背景
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(10,10,880,880);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.drawRect(20,20,860,860);
    painter.drawPixmap(20,20,860,860,QPixmap(":/image/grass.jpg"));

    //炮弹
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::red);
    painter.drawPixmap(Bullet,QPixmap(":/image/Bullet.jpg"));
    painter.drawPixmap(Bullet_,QPixmap(":/image/Bullet.jpg"));

    //障碍物
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::white);
    for(int i=0;i<obs.size();i++)
    {
        painter.drawPixmap(obs[i],QPixmap(":/image/wall.jpg"));
    }

    //道具
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    painter.drawPixmap(Shield,QPixmap(":/image/Shield.jpg"));
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    painter.drawPixmap(DamageBuff,QPixmap(":/image/DamageBuff.jpg"));

    //地雷
    for(int i=0;i<4;i++)
    {
        painter.drawPixmap(Boom[i],QPixmap(":/image/Boom.jpg"));
    }

    //坦克
    painter.drawPixmap(TankBody[0],QPixmap(":/image/tb11.jpg"));
    painter.drawPixmap(TankBody[1],QPixmap(":/image/tb22.jpg"));
    painter.drawPixmap(TankBody[2],QPixmap(":/image/tb33.jpg"));
    painter.drawPixmap(TankBody[3],QPixmap(":/image/tb44.jpg"));
    painter.drawPixmap(TankBody[4],QPixmap(":/image/tb55.jpg"));
    painter.drawPixmap(TankBody[5],QPixmap(":/image/tb66.jpg"));
    painter.drawPixmap(TankBody[6],QPixmap(":/image/tb77.jpg"));
    painter.drawPixmap(TankBody[7],QPixmap(":/image/tb88.jpg"));
    painter.drawPixmap(TankBody[8],QPixmap(":/image/tb99.jpg"));
    painter.drawPixmap(TankHead,QPixmap(":/image/Tankhead_.png"));
    painter.drawPixmap(TankHead_,QPixmap(":/image/TankHead.png"));
    painter.drawPixmap(TankBody_[0],QPixmap(":/image/tb1.jpg"));
    painter.drawPixmap(TankBody_[1],QPixmap(":/image/tb2.jpg"));
    painter.drawPixmap(TankBody_[2],QPixmap(":/image/tb3.jpg"));
    painter.drawPixmap(TankBody_[3],QPixmap(":/image/tb4.jpg"));
    painter.drawPixmap(TankBody_[4],QPixmap(":/image/tb5.jpg"));
    painter.drawPixmap(TankBody_[5],QPixmap(":/image/tb6.jpg"));
    painter.drawPixmap(TankBody_[6],QPixmap(":/image/tb7.jpg"));
    painter.drawPixmap(TankBody_[7],QPixmap(":/image/tb8.jpg"));
    painter.drawPixmap(TankBody_[8],QPixmap(":/image/tb9.jpg"));
    if(Blood_A==0)
    {
        painter.drawPixmap(TankBody[0].left()-10,TankBody[0].top()-20,100,100,QPixmap(":/image/baozha.jpg"));
    }
    if(Blood_B==0)
    {
        painter.drawPixmap(TankBody_[0].left()-10,TankBody_[0].top()-20,100,100,QPixmap(":/image/baozha.jpg"));
    }

    //游戏结束
    QFont font1("黑体",40);
    painter.setFont(font1);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawText(240,460,Display);

    //血量
    QFont font2("黑体",27);
    painter.setFont(font2);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawText(20,950,"Angel:");
    painter.drawText(250,950,QString::number(Blood_A));
    painter.drawText(580,950,"Demon:");
    painter.drawText(780,950,QString::number(Blood_B));

}


void Tank::InitTank()
{
    Haveshield_A=false;
    Haveshield_B=false;
    DamageReset_A=false;
    DamageReset_B=false;
    blsRun=true;
    blsOver=false;
    hit=false;
    hit_=false;
    nDirection = 2;
    Createshield();
    CreateDamageBuff();
    CreateBoom();
    QRect rect(440,100,10,10);
    TankHead = rect;
    for(int i=0;i<3;i++)
    {
       for(int j=0;j<3;j++)
       {
           QRect rect(420+10*j,40+10*i,10,10);
           TankBody.push_back(rect);
       }
    }
    nDirection_ = 1;
    QRect rect_(420,740,10,10);
    TankHead_ = rect_;
    for(int i=0;i<3;i++)
    {
       for(int j=0;j<3;j++)
       {
           QRect rect_(400+10*j,760+10*i,10,10);
           TankBody_.push_back(rect_);
       }
    }
    CreateObs();
    timer=new QTimer(this);//设定坦克计时器
    timer->start(100);//设定时间
    connect(timer,SIGNAL(timeout()),SLOT(Tank_update()));
    QTimer * Bullettimer=new QTimer(this);//设定炮弹计时器
    Bullettimer->start(10);
    connect(Bullettimer,SIGNAL(timeout()),SLOT(Shoot_update()));
    QTimer * Shieldtimer=new QTimer(this);//设定护盾计时器
    Shieldtimer->start(50000);
    connect(Shieldtimer,SIGNAL(timeout()),SLOT(Createshield()));
    QTimer * DamageBuffTimer=new QTimer(this);
    DamageBuffTimer->start(60000);
    connect(DamageBuffTimer,SIGNAL(timeout()),SLOT(CreateDamageBuff()));
}

void Tank::Tank_update()
{
    if(blsOver)
    {
        Display="游戏  结束！";
        timer->stop();
    }
    else
    {
        Display="";
        Getshield();
        GetDamageBuff();
        IsGoal_A();
        IsGoal_B();
        if(Blood_A==0 || Blood_B==0)
        {
            blsOver=true;
        }
        switch (nDirection)
        {
        case 1:
            for(int i=0;i<9;i++)
            {
                TankBody[i].setTop(TankBody[i].top()-10);
                TankBody[i].setBottom(TankBody[i].bottom()-10);
            }
            TankHead.setTop(TankBody[0].top()-10);
            TankHead.setBottom(TankBody[0].top());
            TankHead.setLeft(TankBody[0].left()+10);
            TankHead.setRight(TankBody[0].right()+10);
            break;
        case 2:
            for(int i=0;i<9;i++)
            {
                TankBody[i].setTop(TankBody[i].top()+10);
                TankBody[i].setBottom(TankBody[i].bottom()+10);
            }
            TankHead.setTop(TankBody[0].bottom()+20);
            TankHead.setBottom(TankBody[0].bottom()+30);
            TankHead.setLeft(TankBody[0].left()+10);
            TankHead.setRight(TankBody[0].right()+10);
            break;
        case 3:
            for(int i=0;i<9;i++)
            {
                TankBody[i].setLeft(TankBody[i].left()-10);
                TankBody[i].setRight(TankBody[i].right()-10);
            }
            TankHead.setTop(TankBody[0].top()+10);
            TankHead.setBottom(TankBody[0].bottom()+10);
            TankHead.setLeft(TankBody[0].left()-10);
            TankHead.setRight(TankBody[0].left());
            break;
        case 4:
            for(int i=0;i<9;i++)
            {
                TankBody[i].setLeft(TankBody[i].left()+10);
                TankBody[i].setRight(TankBody[i].right()+10);
            }
            TankHead.setTop(TankBody[0].top()+10);
            TankHead.setBottom(TankBody[0].bottom()+10);
            TankHead.setLeft(TankBody[0].right()+20);
            TankHead.setRight(TankBody[0].right()+30);
            break;
        default:;
        }
        switch (nDirection_)
        {
        case 1:
            for(int i=0;i<9;i++)
            {
                TankBody_[i].setTop(TankBody_[i].top()-10);
                TankBody_[i].setBottom(TankBody_[i].bottom()-10);
            }
            TankHead_.setTop(TankBody_[0].top()-10);
            TankHead_.setBottom(TankBody_[0].top());
            TankHead_.setLeft(TankBody_[0].left()+10);
            TankHead_.setRight(TankBody_[0].right()+10);
            break;
        case 2:
            for(int i=0;i<9;i++)
            {
                TankBody_[i].setTop(TankBody_[i].top()+10);
                TankBody_[i].setBottom(TankBody_[i].bottom()+10);
            }
            TankHead_.setTop(TankBody_[0].bottom()+20);
            TankHead_.setBottom(TankBody_[0].bottom()+30);
            TankHead_.setLeft(TankBody_[0].left()+10);
            TankHead_.setRight(TankBody_[0].right()+10);
            break;
        case 3:
            for(int i=0;i<9;i++)
            {
                TankBody_[i].setLeft(TankBody_[i].left()-10);
                TankBody_[i].setRight(TankBody_[i].right()-10);
            }
            TankHead_.setTop(TankBody_[0].top()+10);
            TankHead_.setBottom(TankBody_[0].bottom()+10);
            TankHead_.setLeft(TankBody_[0].left()-10);
            TankHead_.setRight(TankBody_[0].left());
            break;
        case 4:
            for(int i=0;i<9;i++)
            {
                TankBody_[i].setLeft(TankBody_[i].left()+10);
                TankBody_[i].setRight(TankBody_[i].right()+10);
            }
            TankHead_.setTop(TankBody_[0].top()+10);
            TankHead_.setBottom(TankBody_[0].bottom()+10);
            TankHead_.setLeft(TankBody_[0].right()+20);
            TankHead_.setRight(TankBody_[0].right()+30);
            break;
        default:;
        }
        InitBullet();
        bool whetherBreak=false;
        for(int i=0;i<obs.size();i++)
        {

            if(TankHead.intersects(obs[i]))
            {
                hit=true;
                break;
            }
            for(int j=0;j<TankBody.size();j++)
            {
                if(TankBody[j].intersects(obs[i]))
                {
                    hit=true;
                    whetherBreak=true;
                    break;
                }
            }
            if(whetherBreak)
                break;
        }
        switch(nDirection)
        {
        case 1:
            if(TankHead.top()<=20)
                hit=true;
            break;
        case 2:
            if(TankHead.bottom()>=860)
                hit=true;
            break;
        case 3:
            if(TankHead.left()<=20)
                hit=true;
            break;
        case 4:
            if(TankHead.right()>=860)
                hit=true;
            break;
        default:;
        }
        if(hit)
        {
                if(nDirection==1)
                    nDirection=4;
                else if(nDirection==2)
                    nDirection=3;
                else if(nDirection==3)
                    nDirection=1;
                else
                    nDirection=2;
                hit = false;
        }

        whetherBreak=false;
        for(int i=0;i<obs.size();i++)
        {

            if(TankHead_.intersects(obs[i]))
            {
                hit_=true;
                break;
            }
            for(int j=0;j<TankBody_.size();j++)
            {
                if(TankBody_[j].intersects(obs[i]))
                {
                    hit_=true;
                    whetherBreak=true;
                    break;
                }
            }
            if(whetherBreak)
                break;
        }
        switch(nDirection_)
        {
        case 1:
            if(TankHead_.top()<=20)
                hit_=true;
            break;
        case 2:
            if(TankHead_.bottom()>=860)
                hit_=true;
            break;
        case 3:
            if(TankHead_.left()<=20)
                hit_=true;
            break;
        case 4:
            if(TankHead_.right()>=860)
                hit_=true;
            break;
        default:;
        }
        if(hit_)
        {
                if(nDirection_==1)
                    nDirection_=4;
                else if(nDirection_==2)
                    nDirection_=3;
                else if(nDirection_==3)
                    nDirection_=1;
                else
                    nDirection_=2;
                hit_ = false;
        }
        if(DamageReset_A)
        {
            Damage_A=10;
        }
        if(DamageReset_B)
        {
            Damage_B=10;
        }
        ifBoom();
        update();
    }
}

void Tank::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *key = (QKeyEvent*) event;
    switch (key->key())
    {
    case Qt::Key_W: nDirection=1;
        timer->start(100);
        break;
    case Qt::Key_S: nDirection=2;
        timer->start(100);
        break;
    case Qt::Key_A: nDirection=3;
        timer->start(100);
        break;
    case Qt::Key_D: nDirection=4;
        timer->start(100);
        break;
    case Qt::Key_Shift: shoot = true;
        break;

    case Qt::Key_Up: nDirection_=1;
        timer->start(100);
        break;
    case Qt::Key_Down: nDirection_=2;
        timer->start(100);
        break;
    case Qt::Key_Left: nDirection_=3;
        timer->start(100);
        break;
    case Qt::Key_Right: nDirection_=4;
        timer->start(100);
        break;
    case Qt::Key_Space: shoot_ = true;
        break;
    default:;
    }
}


void Tank::CreateObs()
{
    for(int i=11;i<=18;i++)
    {
        for(int j=10;j<=38;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=48;j<=76;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
    }
    for(int i=25;i<=31;i++)
    {
        for(int j=10;j<=20;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=28;j<=38;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=48;j<=58;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=66;j<=76;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
    }
    for(int i=39;i<=47;i++)
    {
        for(int j=18;j<=30;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=56;j<=68;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
    }
    for(int i=70;i<=78;i++)
    {
        for(int j=10;j<=38;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=48;j<=76;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
    }
    for(int i=55;i<=61;i++)
    {
        for(int j=10;j<=20;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=28;j<=38;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=48;j<=58;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
        for(int j=66;j<=76;j++)
        {
            QRect rect(10*i,10*j,10,10);
            obs.push_back(rect);
        }
    }
}

void Tank::InitBullet()
{
    if(shoot)
    {
        QRect rect1(TankHead.left(),TankHead.top()-10,10,10);
        QRect rect2(TankHead.left(),TankHead.bottom(),10,10);
        QRect rect3(TankHead.left()-10,TankHead.top(),10,10);
        QRect rect4(TankHead.right(),TankHead.top(),10,10);
        switch(nDirection)
        {
        case 1:
            Bullet = rect1;
            bDirection = 1;
            break;
        case 2:
            Bullet = rect2;
            bDirection = 2;
            break;
        case 3:
            Bullet = rect3;
            bDirection = 3;
            break;
        case 4:
            Bullet = rect4;
            bDirection = 4;
            break;
        }
        shoot = false;
    }

    if(shoot_)
    {
        QRect rect1(TankHead_.left(),TankHead_.top()-10,10,10);
        QRect rect2(TankHead_.left(),TankHead_.bottom(),10,10);
        QRect rect3(TankHead_.left()-10,TankHead_.top(),10,10);
        QRect rect4(TankHead_.right(),TankHead_.top(),10,10);
        switch(nDirection_)
        {
        case 1:
            Bullet_ = rect1;
            break;
        case 2:
            Bullet_ = rect2;
            break;
        case 3:
            Bullet_ = rect3;
            break;
        case 4:
            Bullet_ = rect4;
            break;
        }
        bDirection_=nDirection_;
        shoot_ = false;
    }
}

void Tank::Shoot_update()
{
    QRect rect1(Bullet.left(),Bullet.top()-10,10,10);
    QRect rect2(Bullet.left(),Bullet.bottom(),10,10);
    QRect rect3(Bullet.left()-10,Bullet.top(),10,10);
    QRect rect4(Bullet.right(),Bullet.top(),10,10);
    switch(bDirection)
    {
    case 1:
        Bullet = rect1;
        break;
    case 2:
        Bullet = rect2;
        break;
    case 3:
        Bullet = rect3;
        break;
    case 4:
        Bullet = rect4;
        break;
    }

    QRect rect1_(Bullet_.left(),Bullet_.top()-10,10,10);
    QRect rect2_(Bullet_.left(),Bullet_.bottom(),10,10);
    QRect rect3_(Bullet_.left()-10,Bullet_.top(),10,10);
    QRect rect4_(Bullet_.right(),Bullet_.top(),10,10);
    switch(bDirection_)
    {
    case 1:
        Bullet_ = rect1_;
        break;
    case 2:
        Bullet_ = rect2_;
        break;
    case 3:
        Bullet_ = rect3_;
        break;
    case 4:
        Bullet_ = rect4_;
        break;
    }
    update();
}

void Tank::IsGoal_A()
{
    if(Haveshield_B)
    {
        QRect rect(5000,5000,10,10);
        Bullet = rect;
        DamageReset_A = true;
        Haveshield_B=false;
        return;
    }
    if(TankHead_.intersects(Bullet))
    {
        Blood_B -= Damage_A;
        QRect rect(5000,5000,10,10);
        Bullet = rect;
        DamageReset_A = true;
        return;
    }
    for(int i=0;i<TankBody_.size();i++)
    {
        if(TankBody_[i].intersects(Bullet))
        {
            Blood_B -= Damage_A;
            QRect rect(5000,5000,10,10);
            Bullet = rect;
            DamageReset_A = true;
            break;
        }
    }
}

void Tank::IsGoal_B()
{
    if(Haveshield_A)
    {
        QRect rect(5000,5000,10,10);
        Bullet = rect;
        DamageReset_B = true;
        Haveshield_A=false;
    }
    if(TankHead.intersects(Bullet_))
    {
        Blood_A -= Damage_B;
        QRect rect(5000,5000,10,10);
        Bullet_ = rect;
        DamageReset_B = true;
        return;
    }
    for(int i=0;i<TankBody.size();i++)
    {
        if(TankBody[i].intersects(Bullet_))
        {
            Blood_A -= Damage_B;
            QRect rect(5000,5000,10,10);
            Bullet_ = rect;
            DamageReset_B = true;
            break;
        }
    }
}

void Tank::Createshield()
{
    QRect rect(420,420,40,40);
    Shield=rect;
    update();
}

void Tank::Getshield()
{
    for(int i=0;i<TankBody.size();i++)
    {
        if(Shield.intersects(TankBody[i]))
        {
            QRect rect(2000,2000,20,20);
            Shield=rect;
            Haveshield_A=true;
            return;
        }
    }
    for(int i=0;i<TankBody_.size();i++)
    {
        if(Shield.intersects(TankBody_[i]))
        {
            QRect rect(2000,2000,20,20);
            Shield=rect;
            Haveshield_B=true;
            return;
        }
    }
}

void Tank::acceptstart_A()
{
    this->show();
    this->raise();
}

void Tank::CreateDamageBuff()
{
    srand((int)time(0));
    int t1=rand() % 800+20;
    int t2=rand() % 4;
    int x,y;
    if(t2==0)
    {
        x=50;
        y=t1;
    }
    if(t2==1)
    {
        x=t1;
        y=50;
    }
    if(t2==2)
    {
        x=820;
        y=t1;
    }
    if(t2==3)
    {
        x=t1;
        y=820;
    }
    QRect rect(x,y,40,40);
    DamageBuff = rect;
    update();
}

void Tank::GetDamageBuff()
{
    for(int i=0;i<TankBody.size();i++)
    {
        if(DamageBuff.intersects(TankBody[i]))
        {
            QRect rect(5000,5000,40,40);
            DamageBuff = rect;
            Damage_A = 2*Damage_A;
            DamageReset_A = false;
            return;
        }
    }
    for(int i=0;i<TankBody_.size();i++)
    {
        if(DamageBuff.intersects(TankBody_[i]))
        {
            QRect rect(5000,5000,40,40);
            DamageBuff = rect;
            Damage_B = 2*Damage_B;
            DamageReset_B = false;
            return;
        }
    }
}

void Tank::CreateBoom()
{
    QRect rect1(30,70,40,40);
    Boom.push_back(rect1);
    QRect rect2(290,400,40,40);
    Boom.push_back(rect2);
    QRect rect3(420,790,40,40);
    Boom.push_back(rect3);
    QRect rect4(800,590,40,40);
    Boom.push_back(rect4);
}

void Tank::ifBoom()
{
    for(int i=0;i<4;i++)
    {
        if(TankHead.intersects(Boom[i]))
        {
            Blood_A=0;
            blsOver=true;
            return;
        }
        for(int j=0;j<9;j++)
        {
            if(TankBody[i].intersects(Boom[i]))
            {
                Blood_A=0;
                blsOver=true;
                return;
            }
        }
        if(TankHead_.intersects(Boom[i]))
        {
            Blood_B=0;
            blsOver=true;
            return;
        }
        for(int j=0;j<9;j++)
        {
            if(TankBody_[i].intersects(Boom[i]))
            {
                Blood_B=0;
                blsOver=true;
                return;
            }
        }
    }
}


