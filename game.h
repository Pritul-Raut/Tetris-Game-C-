#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void HandleInput(); 
	void MoveBlockDown();
	bool gameOver;
	int score;
	Music music;
private:
	Grid grid;
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	Block GetRandomBlock();
	vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	void Reset();
	void UpdateScore(int LinesCleared,int moveDownPoints);
	vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

	Sound rotateSound;
	Sound clearSound;
};
