#include "ChessBoard.hh"

#include "ChessPiece.hh"

#include "PawnPiece.hh"

#include "RookPiece.hh"

#include "BishopPiece.hh"

#include "QueenPiece.hh"

#include "KnightPiece.hh"

#include "KingPiece.hh"

#include <iostream>



using Student::ChessBoard;

using Student::ChessPiece;

// using namespace Student;


std::ostringstream ChessBoard::displayBoard()

{

    std::ostringstream outputString;
    for(auto i : WhitePieces){
        outputString<<"color: white"<< "  type: "<< i->getType() << "  RC: "<< i->getRow()<< i->getColumn();
        if(i->getType() == King){
            outputString<< "   KING";
        }
        outputString<<std::endl;

    }
    for(auto i : BlackPieces){
        outputString<<"color: Black"<< "  type: "<< i->getType() << "  RC: "<< i->getRow()<< i->getColumn();
        if(i->getType() == King){
            outputString<< "   KING";
        }
        outputString<<std::endl;

    }

    // top scale

    outputString << "  ";

    for (int i = 0; i < numCols; i++)

    {

        outputString << i;

    }

    outputString << std::endl

                 << "  ";

    // top border

    for (int i = 0; i < numCols; i++)

    {

        outputString << "-";

    }

    outputString << std::endl;


    for (int row = 0; row < numRows; row++)

    {

        outputString << row << "|";

        for (int column = 0; column < numCols; column++)

        {

            ChessPiece *piece = board.at(row).at(column);

            outputString << (piece == nullptr ? " " : piece->toString());

        }

        outputString << "|" << std::endl;

    }


    // bottom border

    outputString << "  ";

    for (int i = 0; i < numCols; i++)

    {

        outputString << "-";

    }

    outputString << std::endl

                 << std::endl;


    return outputString;

}


ChessBoard::ChessBoard(int numRow, int numCol){

    numRows = numRow;

    numCols = numCol;

    board = std::vector<std::vector<ChessPiece *>>(numRows, std::vector<ChessPiece *>(numCols, nullptr));

}


ChessBoard::~ChessBoard(){

    // std::cout<< "destructor" << numRows << numCols << std::endl;

    for (int i = 0; i < numRows; i++){

        for (int j = 0; j < numCols; j++){

            delete board.at(i).at(j);

        }

    }

}



void ChessBoard::isValidScan(int n, int m){

    // outputString<<"in va"
    printf("isvalidScan\n");


    for(int i = 0; i < n; i++){

        for(int j = 0; j < m; j++){

            for(int k = 0; k < n; k++){

                for(int x = 0; x < m; x++){

                    bool test = isValidMove(i,j,k,x);

                    if(test){
                        std::cout << "from: " << i<< j<< "to: " << k<<x << std::endl;

                    }



                }

            }

        }

    }

}


int ChessBoard::isValidScan_score(int n, int m, Color turn){
    int white_moves = 0;
    int black_moves = 0;
    int diff = 0;

    for(auto i : WhitePieces){
        for(int k = 0; k < n; k++){
            for(int x = 0; x < m; x++){

                if(isValidMoveSimple(i->getRow(),i->getColumn(),k,x)){
                    white_moves++;
                }
            }
        }    
    }

    for(auto i : BlackPieces){
        for(int k = 0; k < n; k++){
            for(int x = 0; x < m; x++){

                if(isValidMoveSimple(i->getRow(),i->getColumn(),k,x)){
                    black_moves++;
                }
            }
        }    
    }

    if(turn == White){
        diff = white_moves - black_moves;
    }
    else{
        diff = black_moves - white_moves;

    }

    return diff;
}




void ChessBoard::underThreatScan(int n, int m){



    for(int k = 0; k < n; k++){

        for(int x = 0; x < m; x++){

            isPieceUnderThreat(k,x);

            // if(test){

            // std::cout<<"  "<<k<<x<<std::endl;

            // }


        }

    }

}


void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn){

    if(getPiece(startRow, startColumn) != nullptr){

        // if(col == White){

        WhitePieces.remove(getPiece(startRow, startColumn));

            // std::cout<<getPiece(startRow, startColumn)->getType() <<std::endl;

        // }

        // else if(col == Black){

        BlackPieces.remove(getPiece(startRow, startColumn));

            // std::cout<<getPiece(startRow, startColumn)->getType() <<std::endl;


        // }

        delete getPiece(startRow, startColumn);

        board[startRow][startColumn] = nullptr;

    }  

    ChessPiece *newPiece = nullptr;

    if(ty == Bishop){

        newPiece = new BishopPiece(*this, col, startRow, startColumn);

    } 

    else if(ty == Rook){

        newPiece = new RookPiece(*this, col, startRow, startColumn);

    } else if(ty == King){

        newPiece = new KingPiece(*this, col, startRow, startColumn);

    } else if(ty == Pawn){

        newPiece = new PawnPiece(*this, col, startRow, startColumn);

    } else if(ty == Knight){

        newPiece = new KnightPiece(*this, col, startRow, startColumn);

    } else if(ty == Queen){

        newPiece = new QueenPiece(*this, col, startRow, startColumn);

    }

    board[startRow][startColumn] = newPiece;

    if(col == Black){

        BlackPieces.emplace_back(newPiece);

    }

    else if(col == White){

        WhitePieces.emplace_back(newPiece);

    }   

}
bool ChessBoard::isValidMoveSimple(int fromRow, int fromColumn, int toRow, int toColumn){
    // std::cout<<"from:  "<<fromRow<< fromColumn<< "  to: "<< toRow<< toColumn << std::endl;


    if(getPiece(fromRow, fromColumn) == nullptr){
        // checks for inital piece

        // std::cout << "Here1 " << toRow << toColumn << std::endl;

        return false;

    }

    if((toRow == fromRow) && (toColumn == fromColumn)){
        // is actually trying to move

        // std::cout << "Here2 " << toRow << toColumn << std::endl;

        return false;

    }

    if((toRow >= numRows) || (toColumn >= numCols)){
        // in bounds of board

        // std::cout << "Here3 " << toRow << toColumn << std::endl;

        return false;

    }

    if(getPiece(toRow, toColumn) != nullptr){
        // if trying to take peice op color

        if(getPiece(toRow, toColumn)->getColor() == getPiece(fromRow, fromColumn)->getColor()){

            // std::cout << "Here4 " << toRow << toColumn << std::endl;

            return false;

        } 

    }
    // all other cond met now check peice logic
    return getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn);
}



bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn){
    // std::cout<<"from:  "<<fromRow<< fromColumn<< "  to: "<< toRow<< toColumn << std::endl;

        // return false;
    // return isValidMoveSimple(fromRow, fromColumn, toRow, toColumn);


    if(getPiece(fromRow, fromColumn) == nullptr){
        // checks for inital piece

        // std::cout << "Here1 " << toRow << toColumn << std::endl;

        return false;

    }

    if((toRow == fromRow) && (toColumn == fromColumn)){
        // is actually trying to move

        // std::cout << "Here2 " << toRow << toColumn << std::endl;

        return false;

    }

    if((toRow >= numRows) || (toColumn >= numCols)){
        // in bounds of board

        // std::cout << "Here3 " << toRow << toColumn << std::endl;

        return false;

    }

    if(getPiece(toRow, toColumn) != nullptr){
        // if trying to take peice op color

        if(getPiece(toRow, toColumn)->getColor() == getPiece(fromRow, fromColumn)->getColor()){

            // std::cout << "Here4 " << toRow << toColumn << std::endl;

            return false;

        } 

    }
    // all other cond met now check peice logic
    // return getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn);

    // std::pair<int,int> white_temp = White_EP; 
    // std::pair<int,int> black_temp = Black_EP; 

    if(getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn)){
        // std::cout<<"king threat check"<< std::endl;

        Color fromColor = getPiece(fromRow, fromColumn)->getColor();
        Type fromType = getPiece(fromRow, fromColumn)->getType();
        bool KUT = false;


        if(getPiece(toRow, toColumn) != nullptr){
            Color toColor = getPiece(toRow, toColumn)->getColor();
            Type toType = getPiece(toRow, toColumn)->getType();

            createChessPiece(fromColor, fromType, toRow, toColumn ); // moves peice
            BlackPieces.remove(getPiece(fromRow, fromColumn));
            WhitePieces.remove(getPiece(fromRow, fromColumn));
            delete getPiece(fromRow, fromColumn);
            board[fromRow][fromColumn] = nullptr;

            for(int row = 0; row < (numRows); row++){
                for(int col = 0; col < numCols; col++ ){
                    if(getPiece(row,col) != nullptr){
                        if(getPiece(row,col)->getColor() == fromColor && getPiece(row,col)->getType() == King){
                            KUT = isPieceUnderThreat(row,col);
                        }
                    }
                }
            }


            createChessPiece(fromColor, fromType, fromRow, fromColumn ); // moves peice back to orginal loc
            createChessPiece(toColor, toType, toRow, toColumn ); // moves peice back to orginal loc

        }
        else{
            BlackPieces.remove(getPiece(fromRow, fromColumn));
            WhitePieces.remove(getPiece(fromRow, fromColumn));

            delete getPiece(fromRow, fromColumn);
            board[fromRow][fromColumn] = nullptr;
            createChessPiece(fromColor, fromType, toRow, toColumn ); // moves peice
            for(int row = 0; row < (numRows); row++){
                for(int col = 0; col < numCols; col++ ){
                    if(getPiece(row,col) != nullptr){
                        if(getPiece(row,col)->getColor() == fromColor && getPiece(row,col)->getType() == King){
                            // printf("king check\n");

                            KUT = isPieceUnderThreat(row,col);
                        }
                    }
                }
            }

            createChessPiece(fromColor, fromType, fromRow, fromColumn ); // moves peice back to orginal loc
            BlackPieces.remove(getPiece(toRow, toColumn));
            WhitePieces.remove(getPiece(toRow, toColumn));

            delete getPiece(toRow, toColumn);
            board[toRow][toColumn] = nullptr;


        }
        // printf("\n\nKUT = %d\n\n", KUT);
            // std::cout<<"from:  "<<fromRow<< fromColumn<< "  to: "<< toRow<< toColumn << std::endl;

        // if(!KUT){

        // }
        // White_EP = white_temp;
        // Black_EP = black_temp;
        return !KUT;

    } 
    // White_EP = white_temp;
    // Black_EP = black_temp;
    return false;

}


bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn){

    if(getPiece(fromRow,fromColumn) == nullptr){

        return false;

    }

    Color color = getPiece(fromRow, fromColumn)->getColor();

    Type type = getPiece(fromRow, fromColumn)->getType();

    if(color != turn){

        return false;

    }

    // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;

    // printf("white_ep.first: %d  white_ep.second: %d\n", White_EP.first, White_EP.second);
    // printf("Black_ep.first: %d  Black_ep.second: %d\n", Black_EP.first, Black_EP.second);



        // printf("heresss\n");
    if(isValidMove(fromRow,fromColumn, toRow, toColumn)){
        if(turn == White && getPiece(fromRow,fromColumn)->getType() == Pawn && (fromRow - toRow) == 2){
            // printf("in white \n\n");
            White_EP = std::make_pair(fromRow - 1, fromColumn);

        }
        if(turn == Black && getPiece(fromRow,fromColumn)->getType() == Pawn && (fromRow - toRow) == -2){
            Black_EP = std::make_pair(fromRow + 1, fromColumn);
        }

        // std::cout << "Here4 " << toRow << toColumn << std::endl;;

        WhitePieces.remove(getPiece(fromRow,fromColumn));

        BlackPieces.remove(getPiece(fromRow,fromColumn));

        if(type == King && (fromColumn - toColumn) == -2 && turn == White){

            WhitePieces.remove(getPiece(0,7));

            BlackPieces.remove(getPiece(0,7));

            createChessPiece(color, type, toRow, toColumn);
            createChessPiece(color, Rook, 0, 5);

            delete getPiece(fromRow, fromColumn);
            delete getPiece(0, 7);


            board.at(fromRow).at(fromColumn) = nullptr;
            board.at(0).at(7) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            Black_EP = std::make_pair(-1,-1);

            turn = (Color) ((turn + 1) % 2);

            return true;



        }
        else if(type == King && (fromColumn - toColumn) == 2 && turn == White){

            WhitePieces.remove(getPiece(0,0));

            BlackPieces.remove(getPiece(0,0));

            createChessPiece(color, type, toRow, toColumn);
            createChessPiece(color, Rook, 0, 3);

            delete getPiece(fromRow, fromColumn);
            delete getPiece(0, 0);


            board.at(fromRow).at(fromColumn) = nullptr;
            board.at(0).at(0) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            Black_EP = std::make_pair(-1,-1);

            turn = (Color) ((turn + 1) % 2);

            return true;



        }
        else if(type == King && (fromColumn - toColumn) == -2 && turn == Black){

            WhitePieces.remove(getPiece(7,7));

            BlackPieces.remove(getPiece(7,7));

            createChessPiece(color, type, toRow, toColumn);
            createChessPiece(color, Rook, 7, 5);

            delete getPiece(fromRow, fromColumn);
            delete getPiece(7, 7);


            board.at(fromRow).at(fromColumn) = nullptr;
            board.at(7).at(7) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            White_EP = std::make_pair(-1,-1);

            turn = (Color) ((turn + 1) % 2);

            return true;



        }
        else if(type == King && (fromColumn - toColumn) == 2 && turn == Black){

            WhitePieces.remove(getPiece(7,0));

            BlackPieces.remove(getPiece(7,0));

            createChessPiece(color, type, toRow, toColumn);
            createChessPiece(color, Rook, 7, 3);

            delete getPiece(fromRow, fromColumn);
            delete getPiece(7, 0);


            board.at(fromRow).at(fromColumn) = nullptr;
            board.at(7).at(0) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            White_EP = std::make_pair(-1,-1);

            turn = (Color) ((turn + 1) % 2);

            return true;



        }
        



        if(type == Pawn){
            if(color == White && toRow == 0){
                createChessPiece(color, Queen, toRow, toColumn);

                delete getPiece(fromRow, fromColumn);

                board.at(fromRow).at(fromColumn) = nullptr;                
                Black_EP = std::make_pair(-1,-1);

                turn = (Color) ((turn + 1) % 2);

                return true;

            }
            else if(color == Black && toRow == (numRows - 1)){
                createChessPiece(color, Queen, toRow, toColumn);

                delete getPiece(fromRow, fromColumn);

                board.at(fromRow).at(fromColumn) = nullptr;
                White_EP = std::make_pair(-1,-1);

                turn = (Color) ((turn + 1) % 2);

                return true;
                
            }
        }



        if(toRow == White_EP.first && toColumn == White_EP.second && turn == Black){
            createChessPiece(color, type, toRow, toColumn);

            delete getPiece(fromRow, fromColumn);
            board.at(fromRow).at(fromColumn) = nullptr;



            delete getPiece(toRow-1, toColumn);
            WhitePieces.remove(getPiece(toRow-1,toColumn));
            BlackPieces.remove(getPiece(toRow-1,toColumn));
            board.at(toRow-1).at(toColumn) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            White_EP = std::make_pair(-1,-1);
            turn = (Color) ((turn + 1) % 2);

            return true;

        }
        if(toRow == Black_EP.first && toColumn == Black_EP.second && turn == White){
            // printf("HERE\n");
            createChessPiece(color, type, toRow, toColumn);

            delete getPiece(fromRow, fromColumn);
            board.at(fromRow).at(fromColumn) = nullptr;



            delete getPiece(toRow+1, toColumn);
            WhitePieces.remove(getPiece(toRow+1,toColumn));
            BlackPieces.remove(getPiece(toRow+1,toColumn));
            board.at(toRow+1).at(toColumn) = nullptr;


            // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




            Black_EP = std::make_pair(-1,-1);
            turn = (Color) ((turn + 1) % 2);

            return true;

        }




        createChessPiece(color, type, toRow, toColumn);

        delete getPiece(fromRow, fromColumn);

        board.at(fromRow).at(fromColumn) = nullptr;

        // std::cout<<"white size: "<<WhitePieces.size()<<std::endl;




        if(turn == White){
            Black_EP = std::make_pair(-1,-1);

        }
        else{
            White_EP = std::make_pair(-1,-1);

        }
        turn = (Color) ((turn + 1) % 2);

        return true;


    }

    return false;

}

bool ChessBoard::isPieceUnderThreat(int row, int column){

    if(getPiece(row,column) == nullptr){

        return false;

    }


    Color color = getPiece(row,column)->getColor();



    if(color != White){

        //check all white piece attack

        for(auto n : WhitePieces){


                // std::cout<<"white:  "<<n->getRow()<< n->getColumn()<< " takes black: "<< row<< column << std::endl;
            if(isValidMoveSimple(n->getRow(), n->getColumn(), row, column)){



                return true;

            }

        

        }

    }

    if(color != Black){

        for(auto n : BlackPieces){

            if(isValidMoveSimple(n->getRow(), n->getColumn(), row, column)){

                // std::cout<<"Black: "<<n->getRow()<< n->getColumn() << " takes white: "<< row<< column << std::endl;


                return true;

            }

        }

    }

    return false;


}

bool ChessBoard::isPieceUnderThreat_simple(int row, int column, Color color){


    // Color color = getPiece(row,column)->getColor();



    if(color != White){

        //check all white piece attack

        for(auto n : WhitePieces){


            if(isValidMoveSimple(n->getRow(), n->getColumn(), row, column)){

                // std::cout<<"white:  "<<n->getRow()<< n->getColumn()<< " takes black: "<< row<< column << std::endl;

                return true;

            }

        

        }

    }

    if(color != Black){

        for(auto n : BlackPieces){

            if(isValidMoveSimple(n->getRow(), n->getColumn(), row, column)){

                // std::cout<<"Black: "<<n->getRow()<< n->getColumn() << " takes white: "<< row<< column << std::endl;


                return true;

            }

        }

    }

    return false;


}

float ChessBoard::scoreBoard(){
    float white_score = 0;
    float black_score = 0;

    float score = 0;

    Color color = this->turn;

    for(auto i : WhitePieces){
        if(i->getType() == Pawn){
            white_score += 1;
        }
        else if(i->getType() == Knight){
            white_score += 3;
        }
        else if(i->getType() == Bishop){
            white_score += 3;
        }
        else if(i->getType() == Rook){
            white_score += 5;
        }            
        else if(i->getType() == Queen){
            white_score += 9;
        }
        else if(i->getType() == King){
            white_score += 200;
        }
    }

    for(auto i : BlackPieces){
        if(i->getType() == Pawn){
            black_score += 1;
        }
        else if(i->getType() == Knight){
            black_score += 3;
        }
        else if(i->getType() == Bishop){
            black_score += 3;
        }
        else if(i->getType() == Rook){
            black_score += 5;
        }            
        else if(i->getType() == Queen){
            black_score += 9;
        }
        else if(i->getType() == King){
            black_score += 200;
        }
    }
    
    for(int i = 0; i < numRows; i++){

        for(int j = 0; j < numCols; j++){

            for(int k = 0; k < numRows; k++){

                for(int x = 0; x < numCols; x++){

                    bool valid = isValidMove(i,j,k,x);



                    if(valid){

                        if(getPiece(i,j)->getColor() == White){
                            white_score += 0.1;

                        }
                        else{
                            black_score += 0.1;
                        }

                    }

                    // std::cout<<test<< " from: "<<i<<j <<" to: "<<k<<x<<std::endl;



                }

            }

        }

    }


    if(color == White){
        // score = 0.1 * this->isValidScan_score(this->getNumRows(), this->getNumCols(), color);
        score = white_score - black_score;
    }
    else if(color == Black){
        // score = 0.1 * this->isValidScan_score(this->getNumRows(), this->getNumCols(), color);
        score = black_score - white_score;
    }
    return score;
}

float ChessBoard::getHighestNextScore(){
    float high_score = scoreBoard();
    // return isValidMove(2,2,2,2);
    std::vector<int> rows = {};
    std::vector<int> cols = {};

    if(this->turn == White){
        printf("in white\n");
        std::list<ChessPiece>::iterator it;
        for (auto i : WhitePieces){
            rows.emplace_back(i->getRow());
            cols.emplace_back(i->getColumn());

        }
        for(int j = 0; j < int(rows.size()); j++){
           for(int k = 0; k < this->getNumRows(); k++){

                for(int x = 0; x < this->getNumCols(); x++){
                    float score = score_check(rows[j],cols[j],k,x, high_score);
                    // printf("prev: %f curr: %f\n", high_score, score);
                    if(score > high_score){
                        high_score = score;
                    }

                    // printf("size of white vec %ld\n", WhitePieces.size());

                }

            }
        }
    }
    else if(this->turn == Black){
        printf("in black\n");
        std::list<ChessPiece>::iterator it;
        for (auto i : BlackPieces){
            rows.emplace_back(i->getRow());
            cols.emplace_back(i->getColumn());

        }
        for(int j = 0; j < int(rows.size()); j++){
           for(int k = 0; k < this->getNumRows(); k++){

                for(int x = 0; x < this->getNumCols(); x++){
                    float score = score_check(rows[j],cols[j],k,x, high_score);
                    // printf("prev: %f curr: %f\n", high_score, score);
                    if(score > high_score){
                        high_score = score;
                    }

                    // printf("size of white vec %ld\n", WhitePieces.size());

                }

            }
        }
    }
    return high_score;
}

float ChessBoard::score_check(int fromRow, int fromColumn, int toRow, int toColumn, float score){

    if(getPiece(fromRow, fromColumn) == nullptr){
        // checks for inital piece

        // std::cout << "Here1 " << toRow << toColumn << std::endl;

        return score;

    }

    if((toRow == fromRow) && (toColumn == fromColumn)){
        // is actually trying to move

        // std::cout << "Here2 " << toRow << toColumn << std::endl;

        return score;

    }

    if((toRow >= numRows) || (toColumn >= numCols)){
        // in bounds of board

        // std::cout << "Here3 " << toRow << toColumn << std::endl;

        return score;

    }

    if(getPiece(toRow, toColumn) != nullptr){
        // if trying to take peice op color

        if(getPiece(toRow, toColumn)->getColor() == getPiece(fromRow, fromColumn)->getColor()){

            // std::cout << "Here4 " << toRow << toColumn << std::endl;

            return score;

        } 

    }
    // all other cond met now check peice logic
    // return getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn);

    if(getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn)){
        // std::cout<<"king threat check"<< std::endl;

        Color fromColor = getPiece(fromRow, fromColumn)->getColor();
        Type fromType = getPiece(fromRow, fromColumn)->getType();
        bool KUT = false;


        if(getPiece(toRow, toColumn) != nullptr){
            Color toColor = getPiece(toRow, toColumn)->getColor();
            Type toType = getPiece(toRow, toColumn)->getType();

            createChessPiece(fromColor, fromType, toRow, toColumn ); // moves peice
            BlackPieces.remove(getPiece(fromRow, fromColumn));
            WhitePieces.remove(getPiece(fromRow, fromColumn));
            delete getPiece(fromRow, fromColumn);
            board[fromRow][fromColumn] = nullptr;

            for(int row = 0; row < (numRows); row++){
                for(int col = 0; col < numCols; col++ ){
                    if(getPiece(row,col) != nullptr){
                        if(getPiece(row,col)->getColor() == fromColor && getPiece(row,col)->getType() == King){
                            KUT = isPieceUnderThreat(row,col);
                        }
                    }
                }
            }
            if(!KUT){
                score = scoreBoard();
            }


            createChessPiece(fromColor, fromType, fromRow, fromColumn ); // moves peice back to orginal loc
            createChessPiece(toColor, toType, toRow, toColumn ); // moves peice back to orginal loc

        }
        else{
            BlackPieces.remove(getPiece(fromRow, fromColumn));
            WhitePieces.remove(getPiece(fromRow, fromColumn));

            delete getPiece(fromRow, fromColumn);
            board[fromRow][fromColumn] = nullptr;
            createChessPiece(fromColor, fromType, toRow, toColumn ); // moves peice
            for(int row = 0; row < (numRows); row++){
                for(int col = 0; col < numCols; col++ ){
                    if(getPiece(row,col) != nullptr){
                        if(getPiece(row,col)->getColor() == fromColor && getPiece(row,col)->getType() == King){
                            KUT = isPieceUnderThreat(row,col);
                        }
                    }
                }
            }
            if(!KUT){
                score = scoreBoard();
            }

            createChessPiece(fromColor, fromType, fromRow, fromColumn ); // moves peice back to orginal loc
            BlackPieces.remove(getPiece(toRow, toColumn));
            WhitePieces.remove(getPiece(toRow, toColumn));

            delete getPiece(toRow, toColumn);
            board[toRow][toColumn] = nullptr;


        }


    } 
    return score;
}

// Ensuring the piece that moves is of the correct color.

// The piece should not move to the same spot.

// Like in chess, the piece should not be obstructed by another piece between its initial and final

// position.


// The piece should not move out of bounds.

// The final position should not contain another piece of the same color