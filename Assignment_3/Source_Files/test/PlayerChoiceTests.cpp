#include "gtest/gtest.h"
#include "PlayerChoice.h"

TEST(PlayerChoiceTests,ExhaustiveEvalTest){

    //Produces a result where first choice beats second choice
    std::vector<std::vector<PlayerChoice::Choice>> Victory{
        {PlayerChoice::Choice::Rock,PlayerChoice::Choice::Scissors},
        {PlayerChoice::Choice::Paper,PlayerChoice::Choice::Rock},
        {PlayerChoice::Choice::Scissors,PlayerChoice::Choice::Paper}
    };

    //Produces a draw
    std::vector<std::vector<PlayerChoice::Choice>> Draw{
        {PlayerChoice::Choice::Rock,PlayerChoice::Choice::Rock},
        {PlayerChoice::Choice::Paper,PlayerChoice::Choice::Paper},
        {PlayerChoice::Choice::Scissors,PlayerChoice::Choice::Scissors}
    };

    //Check all possible combinations that result in a winner and loser
    for(unsigned int i=0;i<Victory.size();i++){
        EXPECT_LE(static_cast<int>(-1),PlayerChoice::evaluateMatchup(Victory[i][0],Victory[i][1]));
    }
    for(unsigned int i=0;i<Victory.size();i++){
        EXPECT_GE(static_cast<int>(1),PlayerChoice::evaluateMatchup(Victory[i][1],Victory[i][0]));
    }

    //Check all possible draw combinations
    for(unsigned int i=0;i<Draw.size();i++){
        EXPECT_EQ(static_cast<int>(0),PlayerChoice::evaluateMatchup(Draw[i][0],Draw[i][1]));
    }
}

TEST(PlayerChoiceTests,ToStringTest){
    PlayerChoice::Choice val1 = PlayerChoice::Choice::Rock;
    EXPECT_EQ("Rock",PlayerChoice::toString(val1));

    val1 = PlayerChoice::Choice::Paper;
    EXPECT_EQ("Paper",PlayerChoice::toString(val1));

    val1 = PlayerChoice::Choice::Scissors;
    EXPECT_EQ("Scissors",PlayerChoice::toString(val1));
}

TEST(PlayerChoiceTests,ToEnumTest){
    std::vector<std::string> rockStrings = {"Rock","rock","RoCk","rOcK","R","r"};
    for(std::string val : rockStrings){
        EXPECT_EQ(PlayerChoice::Choice::Rock,PlayerChoice::stringToChoice(val));
    }

    std::vector<std::string> paperStrings = {"Paper","paper","PaPeR","pApEr","P","p"};
    for(std::string val : paperStrings){
        EXPECT_EQ(PlayerChoice::Choice::Paper,PlayerChoice::stringToChoice(val));
    }

    std::vector<std::string> scissorStrings = {"Scissors","scissors","ScIsSoRs","sCiSsOrS","S","s"};
    for(std::string val : scissorStrings){
        EXPECT_EQ(PlayerChoice::Choice::Scissors,PlayerChoice::stringToChoice(val));
    }

    //Will throw an "invalid agrument" error if string is invalid
    EXPECT_ANY_THROW(PlayerChoice::stringToChoice("Random garbage string"));
}

TEST(PlayerChoiceTests,EnumListTest){
    std::vector<PlayerChoice::Choice> expected = {PlayerChoice::Choice::Rock,PlayerChoice::Choice::Paper,PlayerChoice::Choice::Scissors};
    EXPECT_EQ(expected,PlayerChoice::getEnumList());
}