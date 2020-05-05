#include "PawnChecker.h"
#include "ChessPiece.h"

//List of where all the white pawns start. Used to differentiate first move from subsequent ones)
const std::set<BoardCoordinate> PawnChecker::WHITE_STARTING_POS = {
        BoardCoordinate(6,0),
        BoardCoordinate(6,1),
        BoardCoordinate(6,2),
        BoardCoordinate(6,3),
        BoardCoordinate(6,4),
        BoardCoordinate(6,5),
        BoardCoordinate(6,6),
        BoardCoordinate(6,7)
};

//List of where all the black pawns start. Used to differentiate first move from subsequent ones
const std::set<BoardCoordinate> PawnChecker::BLACK_STARTING_POS = {
        BoardCoordinate(1,0),
        BoardCoordinate(1,1),
        BoardCoordinate(1,2),
        BoardCoordinate(1,3),
        BoardCoordinate(1,4),
        BoardCoordinate(1,5),
        BoardCoordinate(1,6),
        BoardCoordinate(1,7)
};

/**
 * @brief Creates a PawnChecker object
 */
PawnChecker::PawnChecker() = default;

/**
 * @brief Destroys a PawnChecker object
 */
PawnChecker::~PawnChecker() = default;

/**
 * @brief Checks if the desired position is valid to move to
 * @param current The current position of the piece
 * @param dest The position it wants to move to
 * @param boardState The current state of the board and location of other pieces
 * @return Whether or not the move is valid
 */
bool PawnChecker::isMoveValid(BoardCoordinate current,BoardCoordinate dest,const std::vector<std::vector<ChessPiece*>>& boardState) const{
    if(dest == current){
        //Staying put is not a valid 'move'
        return false;
    }

    //Make sure desired position is on board
    if(!MovementChecker::isPositionOnBoard(dest)){
        return false;
    }

    //Make sure there is a piece at the target location
    if(boardState[current.y][current.x] == nullptr){
        return false;
    }

    ChessColor myColor = boardState[current.y][current.x]->getColor();
    int direction = (myColor == White?-1:1);
    const std::set<BoardCoordinate>& startingPositions = (myColor==White?WHITE_STARTING_POS:BLACK_STARTING_POS);

    int dx = dest.x - current.x;
    int dy = dest.y - current.y;

    if( signbit(dy) != signbit(direction) || abs(dy) > 2 || abs(dx) > 1){
        //Pawn cannot move backwards, more than 2 forward or more than 1 sideways
        return false;
    }

    if(abs(dx) > 0){
        //Trying to take another piece
        if(abs(dy) != 1){
            return false;
        }
        if(boardState[dest.y][dest.x] == nullptr){
            return false;
        }
        return boardState[dest.y][dest.x]->getColor() != myColor;
    }

    if(abs(dy) == 2 && startingPositions.find(current) == startingPositions.end()){
        //Pawn can move 2 spaces, but only on first move
        return false;
    }

    //Moving forward
    bool moveValid = true;
    for(int i = direction;abs(i) <= abs(dy);i = i+direction){
        int atY = current.y + i;
        int atX = current.x;

        if(!MovementChecker::isPositionOnBoard(BoardCoordinate(atY,atX))){
            moveValid = false;
            break;
        }
        moveValid &= (boardState[atY][atX] == nullptr);
    }
    return moveValid;

}

/**
 * @brief Gets a list of all the places the piece can move
 * @param current The current position of the piece
 * @param boardState The board state showing where all the pieces are
 * @return A set containing all the valid positions
 */
std::set<BoardCoordinate> PawnChecker::getValidMoves(BoardCoordinate current, const std::vector<std::vector<ChessPiece*>>& boardState) const{

    std::set<BoardCoordinate> retVal;

    //Make sure there is a piece at the target location
    if(boardState[current.y][current.x] == nullptr){
        return retVal;
    }

    ChessColor myColor = boardState[current.y][current.x]->getColor();
    int direction = (myColor==White?-1:1);
    const std::set<BoardCoordinate>& startingPositions = (myColor==White?WHITE_STARTING_POS:BLACK_STARTING_POS);

    //Check moving forward
    for(int i=direction;abs(i) <= (startingPositions.find(current) != startingPositions.end()?2:1);i = i+direction){
        int atY = current.y + i;
        int atX = current.x;
        if(!MovementChecker::isPositionOnBoard(BoardCoordinate(atY,atX))){
            break;
        }

        if(boardState[atY][atX] == nullptr){
            //Square is empty, pawn can move forward
            retVal.emplace(atY,atX);
            continue;
        }
        else{
            //Piece is blocking way, cannot move
            break;
        }
    }

    //Check taking other pieces
    const std::vector<std::pair<int,int>> possibleDirections = {{direction,1},{direction,-1}};
    for(auto dir : possibleDirections){
        int atY = current.y + std::get<0>(dir);
        int atX = current.x + std::get<1>(dir);

        if(!MovementChecker::isPositionOnBoard(BoardCoordinate(atY,atX))){
            //Position is not on board
            continue;
        }

        if(boardState[atY][atX] == nullptr){
            //No piece to take, pawn cannot move diagonally
            continue;
        }
        if(boardState[atY][atX]->getColor() != boardState[current.y][current.x]->getColor()){
            //There is a piece of the opposite color to take
            retVal.emplace(atY,atX);
            continue;
        }
        else if(boardState[atY][atX]->getColor() == boardState[current.y][current.x]->getColor()){
            //Piece of the same color, cannot move there
            continue;
        }
    }

    return retVal;
}