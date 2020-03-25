#include "player.h"

Player::Player(double startMoney) : money(startMoney) {}

void Player::earn(double amt) {
    money += amt;
}

bool Player::pay(double amt) {
    bool afford = amt <= money;
    if (afford)
    {
        money -= amt;
    }
    return afford;
}

double const & Player::has() const {
    return money;
}

void Player::announceMoney() {
    std::cout << "   You have " << money << " ! 💰" << std::endl;
}

void Player::play() {
    plays += 1;
    if (plays % 10 == 0) announceMoney();
    highScore = std::max(money, highScore);
}

double const & Player::getHighScore() const {
    return highScore;
}

unsigned int Player::getPlays() const {
    return plays;
}


