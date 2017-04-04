#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

class GameOfLife{
	public:
		void initialize(int initialPattern);
		void proceed(int t);
		void display();
		GameOfLife(int heightValue, int widthValue);
		GameOfLife();
	private:
		int height;
		int width;
		bool world[256][256];
};
void GameOfLife::initialize(int initialPattern){
	const bool GLIDER[3][3] = {
		{1,1,1},
		{1,0,0},
		{0,1,0}
	};
	const bool LIGHTWEIGHT[4][5] = {
		{0,1,0,0,1},
		{1,0,0,0,0},
		{1,0,0,0,1},
		{1,1,1,1,0}
	};
	const bool PULSAR[13][13] = {
		{0,0,1,1,0,0,0,0,0,1,1,0,0},
		{0,0,0,1,1,0,0,0,1,1,0,0,0},
		{1,0,0,1,0,1,0,1,0,1,0,0,1},
		{1,1,1,0,1,1,0,1,1,0,1,1,1},
		{0,1,0,1,0,1,0,1,0,1,0,1,0},
		{0,0,1,1,1,0,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,0,1,1,1,0,0},
		{0,1,0,1,0,1,0,1,0,1,0,1,0},
		{1,1,1,0,1,1,0,1,1,0,1,1,1},
		{1,0,0,1,0,1,0,1,0,1,0,0,1},
		{0,0,0,1,1,0,0,0,1,1,0,0,0},
		{0,0,1,1,0,0,0,0,0,1,1,0,0}
	};
	memset(world, 0, sizeof(world));
	switch(initialPattern){
		case 1:
			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					world[i + height/2 - 1][j + width/2 - 1] = GLIDER[i][j];
			break;
		case 2:
			for(int i=0; i<4; i++)
				for(int j=0; j<5; j++)
					world[i + height/2 - 2][j + width/2 - 2] = LIGHTWEIGHT[i][j];
			break;
		case 3:
			for(int i=0; i<13; i++)
				for(int j=0; j<13; j++)
					world[i + height/2 - 6][j + width/2 - 6] = PULSAR[i][j];
			break;
		default:
			srand(time(NULL));
			int fill = height*width * initialPattern/100;
			int tmpForFill = fill;
			while(fill){
				int randomHeight = rand() % height, 
					randomWidth  = rand() % width;
				if(!world[randomHeight][randomWidth]){
					fill--;
					world[randomHeight][randomWidth] = 1;
				}
			}
			break;
	}
}

void GameOfLife::display(){
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++)
			cout<<world[i][j]<<" ";
		cout<<endl;
	}
}

GameOfLife::GameOfLife(int heightValue, int widthValue): height(heightValue), width(widthValue)
{

}

GameOfLife::GameOfLife(): height(80), width(23)
{

}
int main(){
	int height, width;
	cin >> height >> width;
	GameOfLife game(height, width);
	
	int type;
	cin >> type;
	game.initialize(type);
	game.display();

	return 0;
}
