#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define COLS 5
#define ROWS 10

int main(void)
{
	table_t* table = create_table(COLS, ROWS);

	set_cell(table, "A1", "1.5");
	set_cell(table, "B9", "4.9");
	
	InitWindow(800, 600, "Tables");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		draw_table(*table);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

