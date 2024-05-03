#ifndef __QUEENPIECE_H__

#define __QUEENPIECE_H__


#include "ChessPiece.hh"


/**

 * Student implementation of a Queen chess piece.

 * The class is defined within the Student namespace.

 */

namespace Student

{

    class QueenPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            QueenPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = Queen;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                int curRow = this->getRow();

                int curCol = this->getColumn();

                // check for bishop
                if(std::abs(toRow - this->getRow()) != std::abs(toColumn - this->getColumn())){
                    //check for rook
                    if(curCol != toColumn && curRow != toRow){

                        return false;

                    }

                }
                if(curCol != toColumn && curRow != toRow){  // BISHOP CHECK
                    if(curRow < toRow){

                        //moving down

                        if((curCol > toColumn)){

                            //down and left

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow + i, curCol - i) != nullptr){

                                    return false;

                                }

                            }

                            return true;

                        }

                        if((curCol < toColumn)){

                            //down and right

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow + i, curCol + i) != nullptr){

                                    return false;

                                }

                            }


                            return true;

                        }

                    }

                    if(curRow > toRow){

                        //moving up

                        if((curCol > toColumn)){

                            //up and left

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow - i, curCol - i) != nullptr){

                                    return false;

                                }

                            }


                            return true;

                        }

                        if((curCol < toColumn)){

                            //up and right

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow - i, curCol + i) != nullptr){

                                    return false;

                                }

                            }


                            return true;

                        }

                    }
                    

                    return false; // IDK

                }
                else{ // ROOK CHECK

                    if(curRow != toRow){

                        //moving along col

                        if((curRow - toRow) < 0){

                            //moving down

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow + i, curCol) != nullptr){

                                    return false;

                                }

                            }

                            return true;


                        }

                        if((curRow - toRow) > 0){

                            //moving up

                            for(int i = 1; i < std::abs(curRow - toRow); i++ ){

                                if(boardVar.getPiece(curRow - i, curCol) != nullptr){

                                    return false;

                                }

                            }

                            return true;


                        }

                        //moving right

                    }

                    else if(curCol != toColumn){

                        //moving along row

                        if((curCol - toColumn) < 0){

                            //moving right

                            for(int i = 1; i < std::abs(curCol - toColumn); i++ ){

                                if(boardVar.getPiece(curRow, curCol + i) != nullptr){

                                    return false;

                                }

                            }

                            return true;


                        }

                        if((curCol - toColumn) > 0){

                            //moving left

                            for(int i = 1; i < std::abs(curCol - toColumn); i++ ){

                                if(boardVar.getPiece(curRow, curCol - i) != nullptr){

                                    return false;

                                }

                            }

                            return true;


                        }

                    }

                    

                    

                    return false;
                }

            }


            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265B";

                }

                return "\u2655";

            }


            ~QueenPiece(){

                

            }   

    };

}


#endif