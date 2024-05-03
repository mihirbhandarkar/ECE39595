#ifndef _KNIGHTPIECE_H__
#define _KNIGHTPIECE_H__


#include "ChessPiece.hh"

#include "ChessBoard.hh"
#include <map>


using Student::ChessBoard;

using Student::ChessPiece;


/**

 * Student implementation of a Rook chess piece.

 * The class is defined within the Student namespace.

 */
using namespace std; 
namespace Student

{

    class KnightPiece : public ChessPiece

    {

        private:

            Color pieceColor;

            Type pieceType;

            // ChessBoard currBoard;

        public: 

            KnightPiece(ChessBoard &board, Color color, int row, int column)

            : ChessPiece(board, color, row, column) {

                pieceColor = color;

                typeVar = Knight;

            }


            bool canMoveToLocation(int toRow, int toColumn){

                // std::cout << toRow << toColumn << ' ';

                int curRow = this->getRow();

                int curCol = this->getColumn();

                map<int, int> posible_moves = {{curRow + 2,curCol + 1}, {curRow + 2,curCol + -1}, {curRow + 1,curCol + 2}, {curRow + 1,curCol -2}, 
                                                                  {curRow - 2,curCol + 1}, {curRow - 2,curCol + -1}, {curRow - 1,curCol + 2}, {curRow - 1,curCol -2}};

                
                // printf("posible_moves[toRow] == %d\n\n",posible_moves[toRow]);
                // for(const auto& elem : posible_moves)
                // {
                // std::cout << elem.first << " " << elem.second << " " << "\n";
                // }
                if((curRow + 2) == toRow && (((curCol + 1) == toColumn) || ((curCol - 1) == toColumn)) ) {
                    return true;
                } 
                else if((curRow + 1) == toRow && (((curCol + 2) == toColumn) || ((curCol - 2) == toColumn)) ) {
                    return true;
                }
                else if((curRow - 1) == toRow && (((curCol + 2) == toColumn) || ((curCol - 2) == toColumn)) ) {
                    return true;
                }
                else if((curRow - 2) == toRow && (((curCol + 1) == toColumn) || ((curCol - 1) == toColumn)) ) {
                    return true;
                }   
                else {
                    return false;
                }
                

                return false;

            }

            //NEED TO DO CHANGE COLOR

            const char *toString(){

                if (pieceColor == Black) {

                    return "\u265E";

                }

                return "\u2658";

            }


            ~KnightPiece(){


            }   

    };

}


#endif
