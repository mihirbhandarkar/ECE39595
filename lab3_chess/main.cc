#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>
// int n = 6;
// int m = 6;
// void isValidScan(Student::ChessBoard);
// void underThreatScan(Student::ChessBoard);

void test_part1_4x4_1()
{
    Student::ChessBoard sBoard(8,8);

    sBoard.createChessPiece(White,Pawn,6,4);
    // sBoard.createChessPiece(Black,Bishop,1,3);
    // sBoard.createChessPiece(Black,Rook,1,1);
    sBoard.createChessPiece(White,King,0,0);
    // sBoard.createChessPiece(Black,Queen,3,0);
    // sBoard.createChessPiece(Black,King,7,4);
    // sBoard.createChessPiece(Black,Queen,3,2);
    // sBoard.createChessPiece(Black,Queen,2,1);
    sBoard.createChessPiece(Black,King,7,7);
    sBoard.createChessPiece(Black,Pawn,4,5);
    // sBoard.movePiece(7,7,7,6);

    // std::cout<< sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(0,0,0,1);
    std::cout<< sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(7,7,6,7);
    std::cout<< sBoard.displayBoard().str() << std::endl;
    printf("whichEP.first %d  second: %d\n",sBoard.White_EP.first , sBoard.White_EP.second );
    sBoard.isValidScan(8,8);
    printf("whichEP.first %d  second: %d\n",sBoard.White_EP.first , sBoard.White_EP.second );

    sBoard.movePiece(6,4,4,4);

    // // sBoard.movePiece(7,6,7,7);

    // // printf("in main\n");
    std::cout<< sBoard.displayBoard().str() << std::endl;
    // printf("whichEP.first %d  second: %d\n",sBoard.White_EP.first , sBoard.White_EP.second );
    sBoard.movePiece(4,5,5,4);

    // sBoard.movePiece(0,7,0,6);


    // sBoard.createChessPiece(Black,Queen,2,2);
    std::cout<< sBoard.displayBoard().str() << std::endl;

    // // sBoard.movePiece(2,2,2,1);
    // std::cout<< "number of white moves: " << sBoard.isValidScan_score(4,4, White) << std::endl;
    // std::cout<< "white score: " << sBoard.scoreBoard() << std::endl;
    // std::cout<< "white highscore: " << sBoard.getHighestNextScore() << std::endl;
    // printf("bool: %d\n",sBoard.isValidMove(2,2,1,1));


    // sBoard.isValidScan(8,8);
    // // sBoard.underThreatScan(4,4);
    // sBoard.movePiece(1,3,0,3);

    // sBoard.movePiece(0,0,1,0);
    // std::cout<< sBoard.displayBoard().str() << std::endl;

    return;
}

int main()
{
    test_part1_4x4_1();
    return EXIT_SUCCESS;
}
