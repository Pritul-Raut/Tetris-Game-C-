
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>


using namespace std;

double lastUpdateTime = 0;
bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}
int main()
{
	
	InitWindow(500, 620, "Tetris");
	SetTargetFPS(60);
	Font font = LoadFontEx("font/monogram.ttf",64,0,0);
	Game game = Game();
		
	
	while (WindowShouldClose()==false) {
		UpdateMusicStream(game.music);
		game.HandleInput();
		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}
		
		BeginDrawing();
		ClearBackground(darkblue);
		DrawTextEx(font, "Pritul's Tetris", { 320,10 }, 22, 1, GRAY);
		DrawLine(320, 32, 490, 32, RED);
		DrawTextEx(font, "Score", { 365,65 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 370,225 }, 38, 2, WHITE);
		if(game.gameOver) DrawTextEx(font, "GAME OVER", { 320,550 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320,110,170,110 }, 0.3, 6, lightblue);

		char scoreText[10];
		sprintf_s(scoreText,"%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, { 320+(170-textSize.x)/2,135}, 38, 2, WHITE);

		
		DrawRectangleRounded({ 320,265,170,230 }, 0.3, 6, lightblue);
		
		game.Draw();
		EndDrawing();
		
	}
	CloseWindow();
}
