#include "gtest/gtest.h"
#include "GameManager.h"

#include <iostream>

TEST(GameManagerTests,NumRoundsTest){
    GameManager gameManager;

    //Check default number of rounds (20)
    ASSERT_NO_THROW(gameManager.startGame(Game::GameMode::EVE)); //Use EVE so that no human input is needed
    //Dont care what results actually are (since they're random), just that the size is correct
    EXPECT_EQ(static_cast<unsigned int>(20),gameManager.getMatchHistory().size());

    //Try a different number of rounds
    gameManager.setNumRounds(100);
    ASSERT_NO_THROW( gameManager.startGame(Game::GameMode::EVE));
    //Dont care what results actually are (since they're random), just that the size is correct
    EXPECT_EQ(static_cast<unsigned int>(100),gameManager.getMatchHistory().size());

    //Try a different number of rounds
    gameManager.setNumRounds(1000);
    ASSERT_NO_THROW(gameManager.startGame(Game::GameMode::EVE));
    //Dont care what results actually are (since they're random), just that the size is correct
    EXPECT_EQ(static_cast<unsigned int>(1000),gameManager.getMatchHistory().size());
}