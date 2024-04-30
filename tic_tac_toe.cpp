#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <random>  
using namespace std;

class Board{
    private:
        char b[3][3];
    public:
        //constructor
        Board(){
            char a='1';
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++,a++)
                    b[i][j]=a; 
        }    
        //setter
        bool set_board(int n,char d){
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(b[i][j]==n+48){
                        b[i][j]=d;
                        return true;
                    }
            cout<<"place Pre-occupied"<<endl;
            return false;
        }
        //getter
        char get_char(int r,int c){return b[r][c];}
        //display
        Board display() const {
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                    cout<<setw(5)<<b[i][j];
                cout<<endl<<endl;;
            }
            return *this;
        }
        ~Board(){}
};
class Player{
    private:
        string name;
        char symbol;
    public:
        //constructor
        Player():name(""),symbol('\0'){};
        Player(string n,char s){
            name=n;
            symbol=toupper(s);
        }
        //setter
        Player set_name(string n){
            name=n;
            return *this;
        }
        Player set_symbol(char s){
            symbol=s;
            return *this;
        }
        //getter
        string get_name(){return name;}
        char get_symbol(){return symbol;}
        int take_turn(){
            int num;
            cout<<"Player "<<name<<" enter the cell no. on your move (1-9): ";
            cin >>num;
            while(num>9 || num<1){
                cout<<"!!!!! Enter valid input between 1 and 9 !!!!!! : ";
                cin>>num;
            }
            return num;
        }
        //destructor
        ~Player(){}
};

class Game{
    private:
        Board board;
        Player p1;
        Player p2;
        bool horizontal(){
            for(int i=0;i<3;i++){
                if(board.get_char(i,0)==board.get_char(i,1)&&board.get_char(i,0)==board.get_char(i,2))
                return true;
            }
            return false;
        }
        bool vertical(){
            for(int i=0;i<3;i++){
                if(board.get_char(0,i)==board.get_char(1,i)&&board.get_char(0,i)==board.get_char(2,i))
                return true;
            }
            return false;
        }
        bool diagonal(){
            if((board.get_char(0,0)==board.get_char(1,1)&&board.get_char(0,0)==board.get_char(2,2)) || 
            (board.get_char(0,2)==board.get_char(1,1)&&board.get_char(0,2)==board.get_char(2,0)))
                return true;
            return false;    
        }
    public:
        //constructor
        Game(){}
        Game(string p1_name,char p1_symbol,string p2_name,char p2_symbol):p1(p1_name,p1_symbol),p2(p2_name,p2_symbol) {}
        //setters
        Game set_player1(string p1_name,char symbol){
            p1.set_name(p1_name);
            p1.set_symbol(symbol);
            return *this;
        }
        Game set_player2(string p_name,char symbol){
            p2.set_name(p_name);
            p2.set_symbol(symbol);
            return *this;
        }
        void Whole_game(){

            cout<<"********** TIC-TAC-TOE **********"<<endl;
            board.display();
            for(int i=0;i<9;i++){
                if(i==0||i%2==0){
                    bool val;
                    do{
                        val=board.set_board(p1.take_turn(),p1.get_symbol());
                    }while(val==false);
                    if(check_win()){
                        board.display();
                        cout<<p1.get_name()<<" has won the game"<<endl;
                        return;
                    }
                }
                else{
                    bool val;
                    do{
                        val=board.set_board(p2.take_turn(),p2.get_symbol());
                    }while(val==false);
                    if(check_win()){
                        board.display();
                        cout<<p2.get_name()<<" has won the game"<<endl;
                        return;
                    }

                }
                board.display();
            }
            cout<<"*********** DRAW **********"<<endl;

        }
        bool check_win(){
            if(horizontal() || vertical() || diagonal())
                return true;
            return false;    
        }

};
int main(){
    string n1,n2;
    char c1,c2;
    cout<<"Enter Player 1 Name : ";
    cin>>n1;
    cout << "enter Player 1 Symbol : ";
    cin>>c1;
    cout<<"Enter Player 2 Name : ";
    cin>>n2;
    cout << "enter Player 2 Symbol : ";
    cin>>c2;
    Game game(n1,c1,n2,c2);
    game.Whole_game();
}