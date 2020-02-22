#ifndef WIN_EVAL_H
#define WIN_EVAL_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "PlayerChoice.h"

class WinEval{
public:
    static int checkResult(std::vector<PlayerChoice> playerInputs);

private:
    static const std::unordered_map<PlayerChoice,std::unordered_set<PlayerChoice>> MATCHUP_MAP;
};

#endif