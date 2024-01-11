#pragma once

#include <iostream>
#include <string.h>

using namespace std;

class gameConfig
{

public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	string p1Keys = "adx";
	string p2Keys = "jlm";

	int O_blockCoordinates[8] = { 6,1,6,2,7,1,7,2 };
	int I_blockCoordinates[8] = { 5,1,6,1,7,1,8,1 };
	int J_blockCoordinates[8] = { 5,1,5,2,5,2,7,2 };
	int L_blockCoordinates[8] = { 5,2,6,2,7,2,7,1 };
	int S_blockCoordinates[8] = { 5,2,6,2,6,1,7,1 };
	int Z_blockCoordinates[8] = { 5,1,6,1,6,2,7,2 };
	int T_blockCoordinates[8] = { 5,1,6,1,6,2,7,1 };

	int* coordsArr[7] = { O_blockCoordinates,
						  I_blockCoordinates,
						  J_blockCoordinates,
						  L_blockCoordinates,
						  S_blockCoordinates,
						  Z_blockCoordinates,
						  T_blockCoordinates };

};


