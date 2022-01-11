#ifndef HELP_H
#define HELP_H

#include <QWidget>

namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~help();

private slots:
    void acceptstart_B();
    void on_pushButton_clicked();

signals:
    void emitsignal_B1();

private:
    Ui::help *ui;
};

#endif // HELP_H
