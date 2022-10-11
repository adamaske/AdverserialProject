#pragma once
#include <iostream>
#include <vector>

//#define WHITE 'W'
//#define BLACK 'B'

//const int width = 8;
//const int height = 8;

class Chess
{
public:
	void PrintBoard();
	void CreateBoard();
	void MakeMove(int, int, int, int);
	void Move();
	void StartGame();
	bool IsCheck(char);
	bool AnyValidMoves(char);
	char REPICKPIECE = 'N';
	bool GameOver();
	void NextPlayer();
	char player = 'W';
	std::vector<std::string> previousMoves;
	//Piece* pieces[height][width];
};

