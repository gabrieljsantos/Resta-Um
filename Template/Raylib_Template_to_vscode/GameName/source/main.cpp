#include <iostream>
#include "raylib.h"

#define NO_EXPAND(a) #a
#define STR(a) NO_EXPAND(a)
#define FIND_ASSET(AssetPath) STR(CONTENT_PATH) AssetPath
#define FIND_CONFIG(ConfigPath) STR(CONFIG_PATH) ConfigPath

int main()
{
	InitWindow(800, 600, STR(GAME_NAME));
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
		DrawFPS(100, 100);
		DrawText("Raylib-Template", 300, 300, 20, YELLOW);

		EndDrawing();
	}

	std::cout << "Config  Path:" << STR(CONFIG_PATH) << "\n";
	std::cout << "Content Path:" << STR(CONTENT_PATH) << "\n";

	return 0;
}
