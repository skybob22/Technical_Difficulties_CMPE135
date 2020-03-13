#include "HardComputer.h"
#include <fstream>
#include <sstream>

const std::string HardComputer::FILE_PATH = "./Data/ML_Data.csv";
std::mutex HardComputer::FILE_LOCK;
const unsigned int HardComputer::HISTORY_LENGTH = 4;

/**
 * @brief Creates a HardComputer object
 * @param playerNum The player number (1,2...)
 */
HardComputer::HardComputer(int playerNum):Computer(playerNum){
    parseFromFile(FILE_PATH);
}

/**
 * @brief Destroys a HardComputer object
 */
HardComputer::~HardComputer(){
    writeToFile(FILE_PATH);
}

/**
 * @brief Reads in history from a file
 * @param filename The filename/path to read from
 */
void HardComputer::parseFromFile(std::string filename){
    std::lock_guard<std::mutex> fileLock(FILE_LOCK);
    //Read in file
    std::ifstream dataFile;
    dataFile.open(filename);
    if(!dataFile.is_open()){
        //Unable to read file, start with empty list
        return;
    }

    //TODO: Make the parsing more efficient?
    std::string tempString;
    while (std::getline(dataFile, tempString)) {
        try {
            //Grab a line at a time
            std::stringstream line, first, second;
            line << tempString;

            //Separate the line into the 4-choice sequence and player response (separated by ':')
            std::getline(line, tempString, ':'); //Get first half of line
            first << tempString;
            std::getline(line, tempString); //Get rest/second half of line
            second << tempString;

            //Parse the comma separated n-choice sequence into a deque
            std::deque<PlayerChoice::Choice> choiceSequence;
            while (std::getline(first, tempString, ',')) {
                choiceSequence.push_back(PlayerChoice::stringToChoice(tempString));
            }

            //Parse the player responses
            std::getline(second, tempString, ','); //get response
            PlayerChoice::Choice value = PlayerChoice::stringToChoice(tempString);
            std::getline(second,tempString);//Get count for said response
            unsigned long count = std::stoul(tempString);

            //Add the current pattern to the map
            historyMap[choiceSequence][value] = count;
        }
        catch (std::invalid_argument &err) {
            //Data file is corrupted in some way, ignore this line
        }
    }
    dataFile.close();
}

/**
 * @brief Writes the current learned history to a file
 * @param filename The filename/path to write to
 */
void HardComputer::writeToFile(std::string filename){
    std::lock_guard<std::mutex> fileLock(FILE_LOCK);
    //Write to file
    std::ofstream dataFile;
    dataFile.open(filename);

    for(auto entry : historyMap){
        for(std::pair<PlayerChoice::Choice,unsigned long> subEntry : entry.second) {
            //Print the n-choice sequence
            for (unsigned int j = 0; j < std::get<0>(entry).size(); j++) {
                dataFile << PlayerChoice::toString(std::get<0>(entry)[j]);
                if (j < std::get<0>(entry).size() - 1) {
                    //Separate the list by commas
                    dataFile << ',';
                }
            }
            //Print the player choice(s) after the previous n-long sequence
            dataFile << ':' << PlayerChoice::toString(std::get<0>(subEntry)) << ',' << std::get<1>(subEntry);
            dataFile << std::endl << std::flush;
        }
    }
    dataFile.close();
}

/**
 * @brief Uses Machine Learning algorithm to try and pick the winning move
 * @return The (hopefully) winning choice
 */
PlayerChoice::Choice HardComputer::getPlayerChoice(){
    //Use ML algorithm, check if current pattern exists in map
    auto pattMatch = historyMap.find(matchHistory);
    if(pattMatch == historyMap.end() || pattMatch->second.empty()){
        //No data to work from, return random option
        return Computer::getRandomChoice();
    }

    //We know element exists in the map, find the most likely value for the player to choose next
    std::pair<PlayerChoice::Choice,unsigned long> expectedVal = *(pattMatch->second.begin());
    for(std::pair<PlayerChoice::Choice,unsigned long> element : pattMatch->second){
        if(element.second > std::get<1>(expectedVal)){
            expectedVal = element;
        }
    }

    //Expected value for player to play is std::get<0>(expectedVal)
    //Find options that beat it
    std::vector<PlayerChoice::Choice> winningChoices(0);
    for(PlayerChoice::Choice choice : PlayerChoice::getEnumList()){
        if(PlayerChoice::evaluateMatchup(std::get<0>(expectedVal),choice) > 0){
            //The current option is expected to win, so add it to the list
            winningChoices.push_back(choice);
        }
    }

    if(winningChoices.empty()){
        //Shouldn't happen, but if there are no winning choices, pick randomly
        return Computer::getRandomChoice();
    }

    //Pick random choice from list of choices that should win (in case there is more than 1)
    unsigned int randomChoice = rand()%winningChoices.size();
    return winningChoices[randomChoice];
}

/**
 * @brief Updates the running history with the results of the last match
 * @param result The results of the last match (Choices and who won)
 */
void HardComputer::notifyPlayer(const GameResult result){
    PlayerChoice::Choice opChoice = result.playerChoices[1-(getPlayerNumber()-1)];
    PlayerChoice::Choice myChoice = result.playerChoices[getPlayerNumber()-1];

    /*
     * Add the current pattern to the history
     * Increments value if already in map, otherwise adds it
     * Initialization of unsigned long has defined behavior of 0
     */
    historyMap[matchHistory][opChoice]++;

    if(matchHistory.size() >= (HISTORY_LENGTH-(HISTORY_LENGTH%2))){
        //If we are at the desired history length, remove the first 2 entries to keep the same length (Since we're adding 2)
        matchHistory.erase(matchHistory.begin(),matchHistory.begin()+2); //Remove the first two to make room
    }
    matchHistory.push_back(opChoice);
    matchHistory.push_back(myChoice);
}