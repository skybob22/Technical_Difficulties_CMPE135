#include "WinEval.h"

//Define the matchups for what wins against what
//Format {Choice,{Everything choice beats}}
const std::unordered_map<PlayerChoice,std::unordered_set<PlayerChoice>> WinEval::MATCHUP_MAP = {
        {PlayerChoice::Rock,{PlayerChoice::Scissors}},
        {PlayerChoice::Paper,{PlayerChoice::Rock}},
        {PlayerChoice::Scissors,{PlayerChoice::Paper}}
};

int WinEval::checkResult(std::vector<PlayerChoice> playerInputs){
    if(playerInputs.size() < 2){
        throw std::length_error("Input must have 2 player choices");
    }

    //Check if player 1 beat player 2
    auto p1Check = MATCHUP_MAP.find(playerInputs[0]);
    if(p1Check != MATCHUP_MAP.end()){
        if(p1Check->second.find(playerInputs[1]) != p1Check->second.end()){
            //Player 1 beat player 2
            return 1;
        }
    }

    //Check if player 2 beat player 1
    auto p2Check = MATCHUP_MAP.find(playerInputs[1]);
    if(p2Check != MATCHUP_MAP.end()){
        if(p2Check->second.find(playerInputs[0]) != p2Check->second.end()){
            //Player 1 beat player 2
            return 2;
        }
    }

    //If neither, they must have both picked the same thing and tied
    return 0;
}