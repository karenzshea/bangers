#ifndef SLOT_MACHINE_PLAYER
#define SLOT_MACHINE_PLAYER

#include <iostream>
#include <algorithm>

class Player
{
public:
    Player(double startMoney);
    void earn(double amt);
    bool pay(double amt);
    double const & has() const;
    void announceMoney();
    void play();
    double const & getHighScore() const;
    unsigned int getPlays() const;
private:
    double highScore = 0.0;
    double money;
    unsigned int plays = 0;
};

#endif
