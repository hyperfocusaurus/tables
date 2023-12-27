#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "raylib.h"

size_t array_index_from_cell_index(unsigned int cols, cell_index_t index);
cell_t get_cell(table_t table, unsigned int col_index, unsigned int row_index);

void dump_table(table_t table)
{
	for (unsigned int row = 0; row <= table.rows; row++)
	{
		for(unsigned int col = 0; col <= table.cols; col++)
		{
			char buf[12] = {0};
			char* bufp = buf;
			memset(bufp, ' ', 4);
			bufp += 4;
			if (col == 0) {
				if (row != 0){
					size_t count = sprintf(bufp, "%d", row);
					if (count > 1) {
						bufp -= (count / 2);
						sprintf(bufp, "%d", row);
					}
					bufp += count;
				} else {
					*bufp = ' ';
					bufp += 1;
				}
			} else {
				if (row == 0) {
					sprintf(bufp, "%c", 'A' + col - 1);
					bufp +=1;
				}
				else
				{
					cell_t cell = get_cell(table, col, row);
					if (cell.contents != NULL)
					{
						sprintf(bufp, "%s", cell.contents);
						bufp += strlen(cell.contents);
					}
					else
					{
						sprintf(bufp, "%c", ' ');
						bufp += 1;
					}
				}
			}
			memset(bufp, ' ', 4);
			bufp+=4;
			printf("%s", buf);
			if (col == table.cols) putchar('\n');
		}
	}
}

table_t* create_table(unsigned int cols, unsigned int rows)
{
	table_t* res = malloc(sizeof(table_t));
	res->cells = malloc(sizeof(cell_t) * rows * cols);
	memset(res->cells, 0, sizeof(cell_t) * rows * cols);
	res->cols = cols;
	res->rows = rows;

	for (unsigned int row = 1; row <= rows; row++) 
	{
		for (unsigned int col = 1; col <= cols; col++)
		{
			int i = array_index_from_cell_index(cols, (cell_index_t){col, row});
			cell_t* cell = &res->cells[i];
			cell->index = (cell_index_t){row, col};
		}
	}

	return res;
}

void draw_cell(cell_t cell, unsigned int col_width, unsigned int row_height)
{
	unsigned int x = cell.index.col * col_width;
	unsigned int y = cell.index.row * row_height + (row_height / 2);
	if (cell.contents != NULL)
	{
		DrawText(cell.contents, x, y, 20, LIGHTGRAY);
	}
}

cell_index_t cell_ref_to_index(const char* cell_ref)
{
	char col;
	int row;
	sscanf(cell_ref, "%c%d", &col, &row);
	col -= 'A';
	return (cell_index_t) {
		col + 1,
		row,
	};
}

size_t array_index_from_cell_index(unsigned int cols, cell_index_t index) {
	int row = index.row - 1;
	int col = index.col - 1;
	return (row * cols) + col;
}

void set_cell(table_t* table, const char* cell_ref, const char* contents)
{
	cell_index_t index = cell_ref_to_index(cell_ref);
	size_t array_index = array_index_from_cell_index(table->cols, index);
	cell_t* cell = &table->cells[array_index];
	cell->contents = realloc(cell->contents, strlen(contents) + 1);
	if (cell->contents == NULL) {
		fprintf(stderr, "Buy more RAM lol!\n");
		exit(1);
	}
	strcpy(cell->contents, contents);
}

cell_t get_cell(table_t table, unsigned int col_index, unsigned int row_index)
{
	assert(row_index <= table.rows);
	assert(col_index <= table.cols);
	size_t i = array_index_from_cell_index(table.cols, (cell_index_t) {
		col_index,
		row_index,
	});
	assert(i < (table.rows * table.cols));
	return table.cells[i];
}

void draw_table(table_t table)
{
	const unsigned int col_width = 50;
	const unsigned int row_height = 30;
	char buf;
	for (unsigned int i = 0; i <= table.cols; i++) {
		unsigned int x = i * col_width;
		unsigned int y = 20;
		buf = 'A' + (i-1);
		if (i > 0) {
			DrawText(&buf, x + (col_width / 2), y, 20, LIGHTGRAY);
		}
		DrawRectangleLines(x, 0, col_width, row_height, WHITE);
	}
	for (unsigned int row_index = 1; row_index <= table.rows; row_index++) {
		for (unsigned int col_index = 0; col_index <= table.cols; col_index++) {
			unsigned int x = col_index * col_width;
			unsigned int y = row_index * row_height;
			if (col_index == 0) {
				char buf[128];
				sprintf(buf, "%d", row_index);
				DrawText(buf, x + (col_width / 2), y + (row_height / 2), 20, LIGHTGRAY);
			} else {
				assert(row_index <= table.rows);
				assert(col_index <= table.cols);
				draw_cell(get_cell(table, col_index, row_index), col_width, row_height);
			}
			DrawRectangleLines(x, y, col_width, row_height, WHITE);
		}
	}
}
