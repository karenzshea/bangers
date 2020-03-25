#include "slotmachine.h"

const double costToPlay{0.25};

int main()
{
    introduction(costToPlay);

    Player player{costToPlay * 50};
    player.announceMoney();

    SlotMachine<std::vector<std::string>> slot_machine{
        {"🍓", "🍑", "🍈", "🍇", "🍌", "🍋", "🍒", "💣", "💰", "🔔", "💎"}
    };

    std::cout << "\n";
    slot_machine.introduce();

    bool play = true;
    while (play)
    {
        std::string input;
        std::getline(std::cin, input);

        if (input == "end")
            play = false;

        Play(player, slot_machine);

        play = play && player.has() >= costToPlay;
    }

    std::cout << "   Game over! 💸" << "\n";
    player.announceMoney();
    std::cout << "   High score: " << player.getHighScore() << "\n";
    std::cout << "   Play streak: " << player.getPlays() << "\n";
    std::cout << "   Slot machine made: " << slot_machine.getPayload() << "\n";
    std::cout << std::endl;
}
