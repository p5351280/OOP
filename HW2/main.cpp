#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>

using namespace std;

class GameOfLife{
	public:
		void initialize(int initialPattern);
		void proceed(int processCount);
		void display();
		GameOfLife(int heightValue, int widthValue);
		GameOfLife();
		//const int SIZE = 260;
	private:
		//const int SIZE = 260;
		int height;
		int width;
		bool world[260][260];
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
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					world[i + height/2 - 1][j + width/2 - 1] = GLIDER[i-1][j-1];
			break;
		case 2:
			for(int i=1; i<=4; i++)
				for(int j=1; j<=5; j++)
					world[i + height/2 - 2][j + width/2 - 2] = LIGHTWEIGHT[i-1][j-1];
			break;
		case 3:
			for(int i=1; i<=13; i++)
				for(int j=1; j<=13; j++)
					world[i + height/2 - 6][j + width/2 - 6] = PULSAR[i-1][j-1];
			break;
		default:
			srand(time(NULL));
			int fill = height*width * initialPattern/100;
			int tmpForFill = fill;
			while(fill){
				int randomHeight = rand() % height + 1, 
					randomWidth = rand() % width + 1;
				if(!world[randomHeight][randomWidth]){
					fill--;
					world[randomHeight][randomWidth] = 1;
				}
			}
			break;
	}
}

void GameOfLife::proceed(int processCount){
	const int DIRECTION[8][2] = {{0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}};
	bool newWorld[260][260];
	for(int count=1; count<=processCount; count++){
		for(int i=1; i<=height; i++){
			for(int j=1; j<=width; j++){
				int countNeighbor = 0;
				for(int k=0; k<8; k++)
					if(world[ i + DIRECTION[k][0] ][ j + DIRECTION[k][1] ])	countNeighbor++;
				if(countNeighbor<2 || countNeighbor>3)	newWorld[i][j] = 0;
				else if(countNeighbor==3 && !world[i][j])	newWorld[i][j] = 1;
				else	newWorld[i][j] = world[i][j];
			}
		}
		memcpy(world, newWorld, sizeof(world));
		display();
		cout << "Count : " << count << endl;
		usleep(90000);
	}
}

void GameOfLife::display(){
	//for(int i=0; i<100; i++)	cout<<endl;
	system("clear");
	for(int i=1; i<=height; i++) {
		for(int j=1; j<=width; j++)
			cout<<world[i][j]<<" ";
		cout<<endl;
	}
}

GameOfLife::GameOfLife(int heightValue, int widthValue): height(heightValue), width(widthValue)
{

}

GameOfLife::GameOfLife(): height(23), width(80)
{

}

int main(){
	int execute = 1;
	while(execute){
		GameOfLife game;
		int height, width;
		system("clear");
		cout << "Please input height and width (16-256) (input 0 for initial value(23,80)) : ";
		cin >> height >> width;
		if(!height || !width)	game = GameOfLife();
		else if(height<16 || height>256 || width<16 || width>256){
			cout << "input error!\n";
			continue;
		}
		else	game = GameOfLife(height, width);
		int type;
		cout << "Please enter type for initialize (1-3 means types, 4-99 means percent of life) : ";
		cin >> type;
		if(type>99 || type<0){
			cout << "Type Error!\n";
			continue;
		}
		game.initialize(type);
		game.display();
		int numOfGeneration;
		cout << "Please input how many generation you want : ";
		cin >> numOfGeneration;
		game.proceed(numOfGeneration);
		cout << "Please input 0 if want to quit, else continue : ";
		cin >> execute;
	}
	return 0;
}
