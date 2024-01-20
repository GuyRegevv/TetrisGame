#pragma once

#include <iostream>
#include <string.h>

using namespace std;

class gameConfig
{

public:

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int P1OFFSET = 0;
	static constexpr int P2OFFSET = 18;
	
	

	//string p1Keys = "xas";
	//string p2Keys = "jkm";

	int O_blockCoordinates[8] = { 6,1,6,2,7,1,7,2 };
	int I_blockCoordinates[8] = { 6,1,6,2,6,3,6,4 };
	int J_blockCoordinates[8] = { 6,1,6,2,6,3,5,3 };
	int L_blockCoordinates[8] = { 5,1,5,2,5,3,6,3 };
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


