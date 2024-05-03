#ifndef __BISHOPPIECE_H__

#define __BISHOPPIECE_H__


#include "ChessPiece.hh"


/**

 * Student implementation of a Bishop chess piece.

 * The class is defined within the Student namespace.

 */

namespace Student

{

    class BishopPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            BishopPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = Bishop;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                int curRow = this->getRow();

                int curCol = this->getColumn();


                if(std::abs(toRow - this->getRow()) != std::abs(toColumn - this->getColumn())){

                    return false;

                }


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


            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265D";

                }

                return "\u2657";

            }


            ~BishopPiece(){

                

            }   

    };

}


#endif