#ifndef GAME_H
#define GAME_H

#include "PlayerChoice.h"
#include "Player.h"
#include <vector>
#include <ostream>

class Game{
public:
    enum GameMode{
        PVP,
        PVE,
        EVE
    };

    struct GameResult{
        std::vector<PlayerChoice::Choice> playerChoices;
        int winner;

        GameResult():playerChoices(0),winner(0){
        }
        friend std::ostream& operator<<(std::ostream& stream,GameResult result);
    };

    explicit Game(GameMode);
    ~Game();

    void playGame();
    GameResult getResult() const;

private:
    std::vector<Player*> players;
    GameResult result;
};

#endif