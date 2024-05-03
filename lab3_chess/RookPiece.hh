#ifndef _ROOKPIECE_H__

#define _ROOKPIECE_H__


#include "ChessPiece.hh"

#include "ChessBoard.hh"


using Student::ChessBoard;

using Student::ChessPiece;


/**

 * Student implementation of a Rook chess piece.

 * The class is defined within the Student namespace.

 */

namespace Student

{

    class RookPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            RookPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = Rook;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                // std::cout << toRow << toColumn << ' ';

                int curRow = this->getRow();

                int curCol = this->getColumn();

                if(curCol != toColumn && curRow != toRow){

                    return false;

                }

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


            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265C";

                }

                return "\u2656";

            }


            ~RookPiece(){


            }   

    };

}


#endif
