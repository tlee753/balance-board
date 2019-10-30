#ifndef WIIBALANCE_H
#define WIIBALANCE_H

#include <QMainWindow>

namespace Ui {
class WiiBalance;
}

class WiiBalance : public QMainWindow
{
    Q_OBJECT

public:
    explicit WiiBalance(QWidget *parent = nullptr);
    ~WiiBalance();

private:
    Ui::WiiBalance *ui;
};

#endif // WIIBALANCE_H
