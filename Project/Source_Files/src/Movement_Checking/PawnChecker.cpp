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

    int dx = dest.x - current.x;
    int dy = dest.y - current.y;

    //TODO: Try and find a way to do this without the if(color) and reduce duplicated code
    if(myColor == White){
        //White Piece
        if(!(dy >= -2 && dy < 0) || abs(dx) > 1){
            //Pawn cannot move backwards, or more than 1 sideways
            return false;
        }

        if(dy == -2){
            //Pawn is attempting to move 2 spaces, only valid on first move
            if(WHITE_STARTING_POS.find(current) == WHITE_STARTING_POS.end() || dx != 0){
                return false;
            }

            //Check if piece is blocking the way
            if(boardState[current.y-1][current.x] != nullptr){
                return false;
            }
            return boardState[dest.y][dest.x] == nullptr;
        }

        if(abs(dx) == 1){
            //Pawn is attempting to take another piece
            if(dy != -1){
                return false;
            }

            //Cannot move sideways if there is not a piece of the other color to take
            return (boardState[dest.y][dest.x] != nullptr && boardState[dest.y][dest.x]->getColor() != myColor);
        }

        //Pawn is moving 1 forward
        return boardState[dest.y][dest.x] == nullptr;
    }
    else{
        //Black Piece
        if(!(dy > 0 && dy <= 2) || abs(dx) > 1){
            //Pawn cannot move backwards, or more than 1 sideways
            return false;
        }

        if(dy == 2){
            //Pawn is attempting to move 2 spaces, only valid on first move
            if(BLACK_STARTING_POS.find(current) == BLACK_STARTING_POS.end() || dx != 0){
                return false;
            }

            //Check if piece is blocking the way
            if(boardState[current.y+1][current.x] != nullptr){
                return false;
            }
            return boardState[dest.y][dest.x] == nullptr;
        }

        if(abs(dx) == 1){
            //Pawn is attempting to take another piece
            if(dy != 1){
                return false;
            }

            //Cannot move sideways if there is not a piece of the other color to take
            return (boardState[dest.y][dest.x] != nullptr && boardState[dest.y][dest.x]->getColor() != myColor);
        }

        //Pawn is moving 1 forward
        return boardState[dest.y][dest.x] == nullptr;
    }
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
    //TODO: Try and find a way to do this without the if(color) and reduce duplicated code
    if(myColor == White){
        //Check forward movement
        for(int i=-1;i>=(WHITE_STARTING_POS.find(current) != WHITE_STARTING_POS.end()?-2:-1);i--){
            int atY = current.y + i;
            int atX = current.x;

            if(boardState[atY][atX] == nullptr){
                //The square is empty, piece can move there
                retVal.insert(BoardCoordinate(atY,atX));
                continue;
            }
            else{
                //Piece is blocking the way. Pawns cannot take forward
                break;
            }
        }

        //Check taking other pieces
        const std::vector<std::pair<int,int>> possibleDirections = {{-1,1},{-1,-1}};
        for(auto pos : possibleDirections){
            int atY = current.y + std::get<0>(pos);
            int atX = current.x + std::get<1>(pos);

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
                retVal.insert(BoardCoordinate(atY,atX));
                continue;
            }
            else if(boardState[atY][atX]->getColor() == boardState[current.y][current.x]->getColor()){
                //Piece of the same color, cannot move there
                continue;
            }
        }
    }
    else{
    //Check forward movement
        for(int i=1;i>=(BLACK_STARTING_POS.find(current) != BLACK_STARTING_POS.end()?2:1);i++){
            int atY = current.y + i;
            int atX = current.x;

            if(boardState[atY][atX] == nullptr){
                //The square is empty, piece can move there
                retVal.insert(BoardCoordinate(atY,atX));
                continue;
            }
            else{
                //Piece is blocking the way. Pawns cannot take forward
                break;
            }
        }

        //Check taking other pieces
        const std::vector<std::pair<int,int>> possibleDirections = {{1,1},{1,-1}};
        for(auto pos : possibleDirections){
            int atY = current.y + std::get<0>(pos);
            int atX = current.x + std::get<1>(pos);

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
                retVal.insert(BoardCoordinate(atY,atX));
                continue;
            }
            else if(boardState[atY][atX]->getColor() == boardState[current.y][current.x]->getColor()){
                //Piece of the same color, cannot move there
                continue;
            }
        }
    }

    return retVal;
}