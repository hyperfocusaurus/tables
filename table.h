#pragma once

typedef struct {
	unsigned int col;
	unsigned int row;
} cell_index_t;

typedef struct {
	cell_index_t index;
	char* contents;
} cell_t;

typedef struct {
	cell_t* cells;
	cell_index_t cursor;
	unsigned int cols;
	unsigned int rows;
} table_t;

table_t* create_table(unsigned int cols, unsigned int rows);
void draw_table(table_t table);
void set_cell(table_t* table, const char* cell_ref, const char* contents);
void dump_table(table_t table);
