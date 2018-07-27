#include "stdafx.h"
#include "Tilemapping.h"

// define Main Level

void setLevel() {
	for (int y = 0; y < 100; y += 2) {
		for (int x = 0; x < 100; x += 2) {
			level[y][x] = 0; // top left tile
			level[y][x + 1] = 1; // top right tile
			level[y + 1][x] = 2; // bottom left tile
			level[y + 1][x + 1] = 3; // bottom right tile
		}
	}
}

/*
int tileID = getTileIDFunctionWhateverItsCalled();

if (tileID == 0) { // grass
	if (rand() % 2) tileID += 1;
	if (rand() % 2) tileID += tiles_in_one_row;
}*/