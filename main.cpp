#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


bool genRand() {
 /* initialize random seed: */
  srand (time(NULL));

  /* generate secret number between 1 and 10: */
  int val = rand() % 2;

  return val == 1;
}

char playerOneSymbol;
char playerTwoSymbol;

int matrix[3][3];

int row, column, diagonal;

int empty_r(int c);
int empty_c(int r);

bool vulnerabil(int mat[3][3]);
bool castigator(int mat[3][3]);
bool terminat(int mat[3][3]);

char check(void);
void init_matrix(void);
void player_move(bool isPlayerOne);
void AI_move_Easy(void);
void AI_move_Hard(void);
void disp_matrix(void);
void assignSymbols(bool multiplayer);
void playGame(bool multiplayer, int difficulty);

void reset();

int scoreboard[3];


void playGame(bool multiplayer, int difficulty)
{

    while(true) {
		disp_matrix();
		player_move(true);
        if (check() != ' ') break;

        if (terminat(matrix)) //nu avem un castigator si nu sunt spatii deschise.
		{
			disp_matrix();
			cout << endl;
			cout << "It's a draw!\n\n";

			break;
		}

        if (multiplayer) {
            disp_matrix();
            player_move(false);
        } else {
            difficulty == 1 ? AI_move_Hard() : AI_move_Easy();
        }

        /* cauta castigator din nou*/
        if (check() != ' ') break; /* daca este gasit...*/


		reset();

	}

    if (check() == playerOneSymbol){ cout<<endl;
        cout <<(multiplayer ? "Player1 won!\n" : "Player won!\n\n");

        cout<<(multiplayer ? "Scoreboard: Player1 wins: ":" Scoreboard: Player wins: ")<<++scoreboard[0];

        cout<<(multiplayer ? " Player2 wins: " : " AI wins: ")<<scoreboard[1]<<endl;

    } else if (check() == playerTwoSymbol) { cout<<endl;
       cout <<(multiplayer ? "Player2 won!\n" : "Player won!\n\n");

        cout<<(multiplayer ? "Scoreboard: Player2 wins: ":" Scoreboard: Player wins: ")<<++scoreboard[1];

        cout<<(multiplayer ? " Player1 wins: " : " AI wins: ")<<scoreboard[0]<<endl;

	}

}

int main(void)
{
	char c;
	bool CONTINUE = true;
	bool select;
	bool multiplayer;

	bool isFirstGame = true;
	bool previousMode = false;

	cout << "Tic Tac Toe Game" << endl;
	cout << "       made by Patras Silviu" <<"\n\n";

	do {

    previousMode = multiplayer;

    cout<<"Press 0 for Singleplayer \nPress 1 for Multiplayer"<<endl;
    cin>>multiplayer;


    if (isFirstGame == false && previousMode != multiplayer) {
        scoreboard[0] = scoreboard[1] = 0;
    }

    isFirstGame = false;

    assignSymbols(multiplayer);


    init_matrix();

    if (multiplayer == false) {
        cout << "Select your difficulty:\nPress 0 for Easy\nPress 1 for Hard\n";
        cin >> select;
    }

    playGame(multiplayer, select);

    /*final positions */
    disp_matrix();

    cout << "Play again? Y/N" << endl; cin >> c;

	if (c == 'N' || c == 'n')
		CONTINUE = false;

    reset();

	}while(CONTINUE);

	return 0;
}


void init_matrix(void) //matrix intitialisation
{
	int i, j;

	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) matrix[i][j] = ' ';
}


void player_move(bool isPlayerOne)
{

	int x, y;

	char sign = isPlayerOne?playerOneSymbol:playerTwoSymbol;

	cout <<(isPlayerOne?"Player 1":"Player 2")<<"'s turn to enter X,Y coordinates for his move: ";
	cin >> x >> y;

	x--; y--;

	if (matrix[x][y] != ' ') {
		cout << "Invalid move, try again.\n";
		player_move(isPlayerOne);
		return;
	}

    matrix[x][y] = sign;
}


