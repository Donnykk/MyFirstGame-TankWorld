#ifndef START_H
#define START_H

#include <QWidget>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~start();

private slots:
    void on_pushButton_A_clicked();
    void on_pushButton_B_clicked();
    void acceptstart_B1();

signals:
    void emitsignal_A();
    void emitsignal_B();

private:
    Ui::start *ui;
};

#endif // START_H
