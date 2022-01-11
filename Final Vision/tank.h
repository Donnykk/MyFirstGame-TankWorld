#ifndef TANK_H
#define TANK_H

#include <QMainWindow>

namespace Ui {
class Tank;
}

class Tank : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tank(QWidget *parent = 0);
    ~Tank();
    void paintEvent(QPaintEvent *event);
    void InitTank();
    void InitBullet();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void Tank_update();
    void CreateObs();
    void Shoot_update();
    void IsGoal_A();
    void IsGoal_B();
    void Createshield();
    void Getshield();
    void CreateDamageBuff();
    void GetDamageBuff();
    void acceptstart_A();
    void ifBoom();
    void CreateBoom();

private:
    Ui::Tank *ui;
    QTimer *timer;
    QString Display;
    QRect TankHead;
    QRect TankHead_;
    QRect Bomb;
    QRect Shield;
    QRect DamageBuff;
    QVector<QRect> TankBody;
    QVector<QRect> TankBody_;
    QRect Bullet;
    QRect Bullet_;
    QVector<QRect> Boom;
    QVector<QRect> obs;
    int Blood_A;
    int Blood_B;
    int nDirection;
    int nDirection_;
    int bDirection;
    int bDirection_;
    int Damage_A;
    int Damage_B;
    bool shoot;
    bool shoot_;
    bool hit;
    bool hit_;
    bool blsRun;
    bool blsOver;
    bool Painkiller;
    bool DamageReset_A;
    bool DamageReset_B;
    bool Haveshield_A;
    bool Haveshield_B;
};
#endif // TANK_H
