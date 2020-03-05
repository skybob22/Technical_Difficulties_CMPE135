#include "gtest/gtest.h"
#include "Player.h"

TEST(PlayerTests,PlayerNumberTest){
    Player* player1 = Player::createPlayer(Player::PlayerType::Human,1);
    Player* player2 = Player::createPlayer(Player::PlayerType::Computer,2);

    //Currently only supports 2 players, but test possible extended functionality
    Player* player3 = Player::createPlayer(Player::PlayerType::Human,3);

    EXPECT_EQ(static_cast<int>(1),player1->getPlayerNumber());
    EXPECT_EQ(static_cast<int>(2),player2->getPlayerNumber());
    EXPECT_EQ(static_cast<int>(3),player3->getPlayerNumber());

    delete player1;
    delete player2;
    delete player3;
}