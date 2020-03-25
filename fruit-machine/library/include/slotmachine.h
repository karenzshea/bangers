#ifndef SLOT_MACHINE_SLOT_MACHINE_H
#define SLOT_MACHINE_SLOT_MACHINE_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>

#include "player.h"


void introduction(double cost);

double calculatePayoutPct(double min, double max, size_t idx, size_t total);

template <class Container>
void printContainer(Container const& container) {
    for (auto const& c : container)
    {
        std::cout << c;
    }
    std::cout << "\n";
}

template <class Container> class SlotMachine
{
public:
    typedef typename Container::value_type ContentType;

    SlotMachine(Container && _symbols)
        : symbols(std::move(_symbols)), rand(0, std::floor(symbols.size() / 2) - 1) {}
    void introduce() {
        std::cout << "   Win on this slot machine:\n";
        printContainer(symbols);
    }
    double spin(double payment) {
        payload += payment;

        std::vector<ContentType> result(bars);
        std::transform(begin(result), end(result), begin(result),
                       [&](auto) { return getRandomSymbol(); });

        printContainer(result);

        auto payout = processPayout(result);

        return payout;
    }

    double processPayout(std::vector<ContentType> const &result) {
        double payout = 0.0;

        auto same = std::all_of(begin(result), end(result), [&](auto const& v) { return result.front() == v; });

        if (same)
        {
            size_t pos = std::distance(begin(symbols), std::find(begin(symbols), end(symbols), result.front()));
            auto pct = calculatePayoutPct(minPayout, maxPayout, pos, symbols.size() - 1);
            payout = payload * pct;
        }

        return payout;
    }

    ContentType getRandomSymbol() {
        auto gen = std::abs(std::round(rand(rng)));
        auto val = (int)gen % (int)symbols.size();

        assert(val <= symbols.size() - 1);

        return symbols.at(val);
    }
    const double& getPayload() const {
        return payload;
    }
    const double& getCostToPlay() const {
        return costToPlay;
    }
    void setBars(unsigned int num) {
        bars = num;
    }
    void setCostToPlay(double amt) {
        costToPlay = amt;
    }
    void setMinPayout(double amt) {
        minPayout = amt;
    }
    void setMaxPayout(double amt) {
        maxPayout = amt;
    }
private:

    const Container symbols;
    double payload = 5.0;
    unsigned int bars = 3;
    double minPayout = 0.25;
    double maxPayout = 0.9;
    double costToPlay = 0.25;

    std::random_device r{};
    std::seed_seq seed{r()};
    std::mt19937 rng{seed};
    std::normal_distribution<> rand;
};

template <class T>
void Play(Player& player, SlotMachine<T>& slot_machine) {
    auto cost = slot_machine.getCostToPlay();
    if (player.has() < cost)
        return;

    player.pay(cost);
    player.play();

    auto payout = slot_machine.spin(cost);

    if (payout > 0.0)
    {
        std::cout << "   You won " << payout << "! ✨✨✨" << std::endl;
        player.earn(payout);
        player.announceMoney();
    }
}

#endif
