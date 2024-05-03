#ifndef __KINGPIECE_H__

#define __KINGPIECE_H__


#include "ChessPiece.hh"
#include <stdlib.h>
#include <iostream>

/**

 * Student implementation of a King chess piece.

 * The class is defined within the Student namespace.

 */

namespace Student

{

    class KingPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            KingPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = King;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                int curRow = this->getRow();
                int curCol = this->getColumn();
            
    
                if( (std::abs(curCol - toColumn) > 1 || std::abs(curRow - toRow) > 1)){
                    // std::cout<< toRow <<" "<< curRow - toRow<<" " << curCol - toColumn<<std::endl;
                    if((curRow - toRow )== 0 && (curCol - toColumn) == -2){
                        if(boardVar.getPiece(0, 7) != nullptr){
                            if(boardVar.getPiece(0, 7)->getType() == Rook && boardVar.getPiece(0, 7)->getColor() == White){
                                if(boardVar.getPiece(0, 6) != nullptr || boardVar.getPiece(0, 5) != nullptr){
                                    return false;
                                }
                                // bool ret1 = boardVar.isPieceUnderThreat_simple(7,1,White);
                                bool ret1 = boardVar.isPieceUnderThreat_simple(0,6,White);
                                bool ret2 = boardVar.isPieceUnderThreat_simple(0,5,White);

                                if(ret1 || ret2){
                                    return false;
                                }
                                // printf("here\n");
                                return true;
                            }


                        }
                        if(boardVar.getPiece(7, 7) != nullptr){
                            // printf("here\n");
                            if(boardVar.getPiece(7, 7)->getType() == Rook && boardVar.getPiece(7, 7)->getColor() == Black){
                                if(boardVar.getPiece(7, 6) != nullptr || boardVar.getPiece(7, 5) != nullptr){
                                    return false;
                                }
                                // // bool ret1 = boardVar.isPieceUnderThreat_simple(7,1,White);
                                bool ret1 = boardVar.isPieceUnderThreat_simple(7,6,Black);
                                bool ret2 = boardVar.isPieceUnderThreat_simple(7,5,Black);

                                if(ret1 || ret2){
                                    return false;
                                }
                                // printf("here\n");
                                return true;
                            }
                            
                        }

                    }              
                    else if((curRow - toRow )== 0 && (curCol - toColumn) == 2){
                        if(boardVar.getPiece(0, 0) != nullptr){
                            if(boardVar.getPiece(0, 0)->getType() == Rook && boardVar.getPiece(0, 0)->getColor() == White){
                                if(boardVar.getPiece(0, 1) != nullptr || boardVar.getPiece(0, 2) != nullptr || boardVar.getPiece(0, 3) != nullptr ){
                                    return false;
                                }
                                // bool ret1 = boardVar.isPieceUnderThreat_simple(7,1,White);
                                bool ret1 = boardVar.isPieceUnderThreat_simple(0,3,White);
                                bool ret2 = boardVar.isPieceUnderThreat_simple(0,2,White);

                                if(ret1 || ret2){
                                    return false;
                                }
                                return true;
                            }
                        }
                        else if(boardVar.getPiece(7, 0) != nullptr){
                            if(boardVar.getPiece(7, 0)->getType() == Rook && boardVar.getPiece(7, 0)->getColor() == Black){
                                if(boardVar.getPiece(7, 1) != nullptr || boardVar.getPiece(7, 2) != nullptr || boardVar.getPiece(7, 3) != nullptr ){
                                    return false;
                                }
                                // bool ret1 = boardVar.isPieceUnderThreat_simple(7,1,White);
                                bool ret1 = boardVar.isPieceUnderThreat_simple(7,3,Black);
                                bool ret2 = boardVar.isPieceUnderThreat_simple(7,2,Black);

                                if(ret1 || ret2){
                                    return false;
                                }
                                return true;
                            }
                        }
                    }
                    
                    return false;
                }
                    


                return true;

            }


            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265A";

                }

                return "\u2654";

            }


            ~KingPiece(){


            }   

    };

}


#endif


