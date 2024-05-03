#ifndef __PAWNPIECE_H__

#define __PAWNPIECE_H__


#include "ChessPiece.hh"


/**

 * Student implementation of a Pawn chess piece.

 * The class is defined within the Student namespace.

 */

namespace Student

{

    class PawnPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            PawnPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = Pawn;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                //black moves in increasing row order

                int curRow = this->getRow();

                int curCol = this->getColumn();

                Color color = this->getColor();
                // if(toRow == 5 && toColumn== 4){
                //     return true;
                // }

                if(color == Black){


                    if(toRow <= curRow){

                        return false;

                    }

                    if(toRow - curRow == 1){

                        if(toColumn - curCol == 0){

                            if(boardVar.getPiece(toRow, toColumn) == nullptr){

                                return true;

                            }

                        } 

                        if(toColumn - curCol == -1){
                            if(boardVar.getPiece(toRow, toColumn) != nullptr || (toRow == boardVar.White_EP.first && toColumn == boardVar.White_EP.second)){
                            printf("here1\n");

                                return true;

                            }

                        }

                        if(toColumn - curCol == 1){

                            if(boardVar.getPiece(toRow, toColumn) != nullptr  || (toRow == boardVar.White_EP.first && toColumn == boardVar.White_EP.second)){
                            printf("here2\n");

                                return true;

                            }

                        }

                    } else if(toRow - curRow == 2){

                        if(curRow == 1){

                            if(toColumn - curCol == 0){
                                if(boardVar.getPiece(toRow - 1, toColumn) == nullptr){

                                    if(boardVar.getPiece(toRow, toColumn) == nullptr){
                                        // boardVar.Black_EP = std::make_pair(curRow + 1, curCol);
                                        return true;


                                    }
                                }

                            } 

                        }

                    }

                    return false;

                } else {

                    if(toRow >= curRow){

                        return false;

                    } // if pawn tries to move backwards or on same row

                    if(toRow - curRow == -1){

                        if(toColumn - curCol == 0){

                            if(boardVar.getPiece(toRow, toColumn) == nullptr){

                                return true;

                            }

                        } 

                        if(toColumn - curCol == 1){

                            if(boardVar.getPiece(toRow, toColumn) != nullptr  || (toRow == boardVar.Black_EP.first && toColumn == boardVar.Black_EP.second)){
                            printf("here3\n");

                                return true;

                            }

                        }

                        if(toColumn - curCol == -1){

                            if(boardVar.getPiece(toRow, toColumn) != nullptr  || (toRow == boardVar.Black_EP.first && toColumn == boardVar.Black_EP.second)){
                            printf("here4\n");

                                return true;

                            }

                        }

                    } else if(toRow - curRow == -2){

                        if(curRow == boardVar.getNumRows() - 2){

                            if(toColumn - curCol == 0){

                                if(boardVar.getPiece(toRow + 1, toColumn) == nullptr){

                                    if(boardVar.getPiece(toRow, toColumn) == nullptr){
                                        // boardVar.White_EP = std::make_pair(curRow - 1, curCol);

                                        return true;

                                    } 

                                }

                            } 

                        }

                    }

                    return false;

                }

            }


            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265F";

                }

                return "\u2659";

            }


            ~PawnPiece(){


            }   

    };

}


#endif