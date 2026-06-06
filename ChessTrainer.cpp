// ChessTrainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
using namespace std;

int main()
{
    cout << "=======================\n";
    cout << "WELCOME TO CHESSTRAINER\n";
    cout << "=======================\n";
    cout << "\nPress ENTER to continue\n";

    cin.get();

    Board chessBoard;

    chessBoard.printBoard();


    // Loop to move pieces
    bool whiteTurn = true;
    while (true) {
        if (whiteTurn)
            cout << "\nWhite to move\n";
        else
            cout << "\nBlack to move \n";
        std::string fromSquare;
        std::string toSquare;

        std::cout << "\nEnter move (example: e2 e4 or q to quit): ";
        std::cin >> fromSquare;

        if (fromSquare == "q")
            break;
        std::cin >> toSquare;

        Position from = chessBoard.parsePosition(fromSquare);
        Position to = chessBoard.parsePosition(toSquare);

        Piece piece = chessBoard.board[from.row][from.col]; // get piece

        // check turn
        if (whiteTurn && piece.color != WHITE) {
            cout << "Not your turn\n";
            continue;
        }
        if (!whiteTurn && piece.color != BLACK) {
            cout << "Not your turn\n";
            continue;
        }

        bool validMove = false;
        if (piece.type == PAWN) {
            validMove = chessBoard.isValidPawnMove(from, to);
        }
        else if (piece.type == ROOK) {
            validMove = chessBoard.isValidRookMove(from, to);
        }
        else if (piece.type == KNIGHT) {
            validMove = chessBoard.isValidKnightMove(from, to);
        }
        else if (piece.type == BISHOP) {
            validMove = chessBoard.isValidBishopMove(from, to);
        }
        else if (piece.type == QUEEN) {
            validMove = chessBoard.isValidQueenMove(from, to);
        }
        else if (piece.type == KING) {
            validMove = chessBoard.isValidKingMove(from, to);
        }
        if (!validMove) {
            cout << "\n** Illegal move **\n";
            continue;
        }
        if (chessBoard.wouldMoveLeaveKingInCheck(from, to)) {
                cout << "Cannot Move. King would be in check.\n";
                continue;
            }
            chessBoard.movePiece(from, to);
            std::cout << "\nUpdated Board:\n\n";
            chessBoard.printBoard();
            if (chessBoard.isCheckmate(WHITE))
            {
                cout << "CHECKMATE! Black wins!\n";
                break;
            }

            if (chessBoard.isCheckmate(BLACK))
            {
                cout << "CHECKMATE! White wins!\n";
                break;
            }
            whiteTurn = !whiteTurn;
        }
        if (chessBoard.isKingInCheck(WHITE)) {
            cout << "WHITE IS IN CHECK!\n";
        }

        if (chessBoard.isKingInCheck(BLACK)) {
            cout << "BLACK IS IN CHECK!\n";
        }
    
    std::cin.get();
    std::cin.get();

    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
