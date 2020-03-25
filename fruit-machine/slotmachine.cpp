#include "slotmachine.h"

void introduction(double cost) {
  std::cout << std::setprecision(4);
  std::cout << "✨✨✨✨✨✨✨✨✨✨✨" << "\n"
            << "\n"
            << " 🎩🐸👉 welcome 🎰" << "\n"
            << " Hit [enter] to play!" << "\n"
            << " " << cost << " per spin 🐸" << "\n"
            << "\n"
            << "✨✨✨✨✨✨✨✨✨✨✨" << "\n";
}

double calculatePayoutPct(double min, double max, size_t idx, size_t total) {
    const auto low = std::exp(min);
    const auto high = std::exp(max);
    auto tmp = (((double)idx / double(total)) * (high - low)) + low;
    return std::log(tmp);
}

