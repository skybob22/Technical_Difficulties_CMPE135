#include "gtest/gtest.h"
#include "WinEval.h"

TEST(WinEvalTests,ExhaustiveEvalTest){

    //Produces a result where first choice beats second choice
    std::vector<std::vector<PlayerChoice>> Victory{
        {PlayerChoice::Rock,PlayerChoice::Scissors},
        {PlayerChoice::Paper,PlayerChoice::Rock},
        {PlayerChoice::Scissors,PlayerChoice::Paper}
    };

    //Produces a draw
    std::vector<std::vector<PlayerChoice>> Draw{
        {PlayerChoice::Rock,PlayerChoice::Rock},
        {PlayerChoice::Paper,PlayerChoice::Paper},
        {PlayerChoice::Scissors,PlayerChoice::Scissors}
    };

    //Check all possible combinations that result in a winner and loser
    for(unsigned int i=0;i<2;i++){
        //Round 1 expect player 1 to win and round 2 expect player 2 to win
        for(unsigned int j=0;j<Victory.size();j++) {
            EXPECT_EQ(static_cast<int>(i + 1), WinEval::checkResult({Victory[j][i],Victory[j][1-i]}));
        }
    }

    //Check all possible draw combinations
    for(unsigned int i=0;i<Draw.size();i++){
        EXPECT_EQ(static_cast<int>(0),WinEval::checkResult({Draw[i][0],Draw[i][1]}));
    }
}