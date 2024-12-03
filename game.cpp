#include "game.h"
#include <random>
using namespace std;
Game::Game() {
	grid = Grid();
	blocks = {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("sound/music.mp3");
	PlayMusicStream(music);
	music = LoadMusicStream("sound/music.mp3");
	rotateSound = LoadSound("sound/rotate.mp3");
	clearSound = LoadSound("sound/clear.mp3");

}
Game::~Game() {
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}
Block Game::GetRandomBlock() {
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

vector<Block> Game::GetAllBlocks() {
	return { IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock() };
}

void Game::Draw() {
	grid.Draw();
	currentBlock.Draw(11,11);
	nextBlock.Draw(270, 340);
}


void Game::MoveBlockLeft() {
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || !BlockFits()) currentBlock.Move(0, 1);
	}
}
void Game::MoveBlockRight() {
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || !BlockFits()) currentBlock.Move(0, -1);
	}
}
void Game::MoveBlockDown() {
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateBlock()
{
	if (!gameOver) {
		currentBlock.Rotate();
		if (IsBlockOutside() || !BlockFits())currentBlock.UndoRotation();
		else PlaySound(rotateSound);
	}
}

bool Game::IsBlockOutside()
{
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column))return true;
	}
	return false;
}



void Game::HandleInput() {

	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0) {
		gameOver = false;
		Reset();
	}
	switch (keyPressed) {
		
	case KEY_LEFT: 
		MoveBlockLeft();
		break;

	case KEY_RIGHT:
		MoveBlockRight();
		break;

	case KEY_DOWN:
		UpdateScore(0, 1);
		MoveBlockDown();
		break;
	case KEY_UP:
		RotateBlock();
		break;


	}
}

void Game::LockBlock(){
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;

	}
	currentBlock = nextBlock;
	if (BlockFits() == false) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared=grid.ClearFullRows();
	if (rowsCleared > 0) {
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
	

}

bool Game::BlockFits()
{
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellEmpty(item.row, item.column) == false)return false;
		
	}
	return true;
}

void Game::Reset()
{
	grid.Intialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints)
{
	switch (LinesCleared) {
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}


