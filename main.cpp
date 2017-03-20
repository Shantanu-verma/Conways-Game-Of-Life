#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <thread>

using namespace std;
class conway_game{

  uint32_t ROWS,COLS;
  float TIME;
  typedef vector<int> grid;
  typedef vector<int>::size_type sizet;
  grid board;

public:
  conway_game(uint32_t R, uint32_t C, float t = 0.3):ROWS(R),COLS(C),TIME(t){ }
  conway_game():ROWS(30),COLS(25),TIME(0.3){ }
  conway_game(conway_game &rhs){

    this->board = rhs.board;
    this->ROWS  = rhs.ROWS;
    this->COLS  = rhs.COLS;
  }
  explicit conway_game(conway_game &&rhs){

    this->board = rhs.board;
    this->ROWS  = rhs.ROWS;
    this->COLS  = rhs.COLS;
  }

  uint32_t _at(uint32_t i,uint32_t j){
    return i*COLS+j;
  }

  auto const get_map()->decltype(this->board) const{
    return this->board;
  }

  void initialize(){
    for(sizet i = 0;i<ROWS;i++)
      for(sizet j = 0;j<COLS;j++)
        this->board.push_back(0);
  }

  void copy_grid_from(const grid &rhs){

    this->board.erase(board.begin(),board.end());
    this->board = rhs;
  }

  void pattern_fill(){

    // Set Pattern
  board[_at(5,5)] = 1;
  board[_at(5,6)] = 1;
  board[_at(5,7)] = 1;
  board[_at(6,7)] = 1;
  board[_at(7,6)] = 1;

  board[_at(16,16)] = 1;
  board[_at(16,17)] = 1;
  board[_at(16,18)] = 1;
  board[_at(17,18)] = 1;
  board[_at(18,17)] = 1;

  }
  void display(){

    ostringstream out;
    system("CLS");
    this_thread::sleep_for(100ms);
    for(sizet i = 0;i<ROWS;i++){
      for(sizet j = 0;j<COLS;j++){
        uint8_t sym = board.at(_at(i,j))?'#':' ';
        out<<sym<<' ';
      }
      out<<'\n';
    }
    cout<<out.str();
  }

  size_t get_size() const{
    return this->board.size();
  }
  void process_grid(){
    grid temp(board);
    for(sizet i = 0;i<ROWS;i++){

      int up    = (i + 1) % ROWS;
      int down  = (i - 1 + ROWS) % ROWS;

      for(sizet j = 0;j<COLS;j++){
        int left  = (j - 1 + COLS) % COLS;
        int right = (j + 1) % COLS;
        int count = temp[_at(i,left)]  + temp[_at(i,right)]  + temp[_at(up,j)]      + temp[_at(down,j)] + 
                    temp[_at(up,left)] + temp[_at(up,right)] + temp[_at(down,left)] + temp[_at(down,right)];

        if(count == 3)      board[_at(i,j)] = 1;
        else if(count != 2) board[_at(i,j)] = 0;

      }
    }
  }
};
int main(){
  conway_game a(30,30,0.2f);
  cout<<"\n\n\tConways Game Of Life\n";
  cout<<"\n\tRules:\n\t> Each cell with one or no neighbors and 4 or more neigbours dies."
                   "\n\t> Each cell with two or three neighbors survives."
                   "\n\t> Each cell with three neighbors becomes alive yo.\n";
  this_thread::sleep_for(5s);
  a.initialize();
  a.pattern_fill();
  while(true){

    a.display();
    a.process_grid();

  }
  cin.get();
}
