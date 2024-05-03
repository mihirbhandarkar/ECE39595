#include "Chess.h"

#include "ChessPiece.hh"

#include "ChessBoard.hh"


using Student::ChessBoard;

using Student::ChessPiece;


ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column) : boardVar(board)

{

    colorVar = color;

    rowVar = row;

    colVar = column;

}


Color ChessPiece::getColor(){

    return colorVar;

}


Type ChessPiece::getType(){

    return typeVar;

}


int ChessPiece::getRow(){

    return rowVar;

}


int ChessPiece::getColumn(){

    return colVar;

}


void ChessPiece::setPosition(int row, int column){

    rowVar = row;

    colVar = column;

}
