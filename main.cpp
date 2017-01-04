#include<iostream>
#include<time.h>                        // For clock() and clock_t
#include<windows.h>                     // For clearing console
#include<process.h>                     // For exit()
#include<stdlib.h>

// Helpers
const int ROW = 35;
const int COL = 40;
const int MAX_CELL = ROW * COL;         // Total grid cells
const bool CLEAR_SCR = true;            // Set false to disable clearscreen after each generation
#define cord(i,j) (j*ROW+i)      // For Accesing 2D index in 1D array

void drawline(char symbol,int size)
{
	int i=0;
	while(i++<=size) std::cout<<symbol;
}

// Main Class
class board
{
		bool *cell;
	public:
		board(){
			std::cout<< "Pass Init Array First \n Exiting." ;
			exit(0);
		}
		board(bool *arr):cell(arr){
		};
	    void timer(float time);
	    void copy(bool *temp);
	    void print(int *gen);
	    void reset();
	    void check();
	    void clearscreen();
	    bool intro();


};
bool board::intro()
{
	system("CLS");
	std::cout<<"\n\n\tConways Game Of Life\n";
	std::cout<<"\n\tRules:\n\t> Each cell with one or no neighbors and 4 or more neigbours dies."
			    		 "\n\t> Each cell with two or three neighbors survives."
			             "\n\t> Each cell with three neighbors becomes alive yo.\n";
	char ch;
	std::cout<<"\n\tStart Simulation ( Y , N ) :";
	std::cin>>ch;
	if(ch=='Y'||ch=='y')
		return 1;
	else
		return 0;

}
void board::timer(float s) {
	clock_t wait;
	wait = clock() + s * CLOCKS_PER_SEC;
	while (clock() < wait) {
	}
}
void board::check()
{
	bool temp[MAX_CELL]={0};
	for(int i=0; i<ROW; i++)
	{
		int low  = (i + 1) % ROW;
		int up = (i- 1 + ROW) % ROW;

		for(int j=0; j<COL; j++)
		{
			int right = (j + 1) % COL;
			int left  = (j - 1 + COL) % COL;

			int count = cell[cord(up,left)] + cell[cord(up,right)] + cell[cord(up,j)] + cell[cord(low,j)]   + cell[cord(low,left)] + cell[cord(low,right)]+ cell[cord(i,left)]  + cell[cord(i,right)];

						if (count == 2)
			                temp[cord(i,j)] = cell[cord(i,j)];
			            else if (count == 3)
			                temp[cord(i,j)] = 1;
			            else
			                temp[cord(i,j)] = 0;
		}

	}
	copy(temp);
}
void board::reset()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {

				cell[cord(i,j)] = 0;
									  }
			}
}
void board::copy(bool *temp) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {

			cell[cord(i,j)] = temp[cord(i,j)];
		}
	}
}
void board::print(int *gen)
{
		std::cout<<"\n ";
	    drawline(char(254),COL+3);
	    std::cout<< "\t\t"<<char(16)<<" Generation "<<char(26)<<" "<< *gen+1;

	    for(int i=0;i<ROW;i++)
	    {
	    	std::cout<<"\n";
	    	std::cout<<" "<<char(219)<<" ";

			for(int j=0;j<COL;j++)
			{
				int k = cord(i,j);
				char a = cell[k] ? char(177) : ' ';
				std::cout<<a;
			}
			std::cout<<" "<<char(219)<<" ";
	    }
	    std::cout<<"\n ";
	    drawline(char(254),COL+3);

}

	// This Function Taken From Stackoverflow
void board::clearscreen()
{
		HANDLE hOut;
	    COORD Position;

	    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	    Position.X = 0;
	    Position.Y = 0;


	    SetConsoleCursorPosition(hOut, Position);
}
    // End

	// Driver Program


auto main()->int
{

	// Initialization Of Cell Board
	// Pass Coordinates Of Live Cells
    // Dont know how to simplify initialiation of live cells

	bool cell_board[MAX_CELL]={0};
	cell_board[cord(5,5)] = 1;
	cell_board[cord(5,6)] = 1;
	cell_board[cord(5,7)] = 1;
	cell_board[cord(6,7)] = 1;
	cell_board[cord(7,6)] = 1;

	cell_board[cord(16,16)] = 1;
	cell_board[cord(16,17)] = 1;
	cell_board[cord(16,18)] = 1;
	cell_board[cord(17,18)] = 1;
	cell_board[cord(18,17)] = 1;


	board *game = new board(cell_board);

    // Loops until user press Y or y
	start:
	if(!(*game).intro())
		goto start;

    system("CLS");
	int i=0;
	do{
		if(CLEAR_SCR)
		game->clearscreen();
		game->print(&i);
		game->check();


	} while(i++<200);

	delete game;
	return 0;
}

