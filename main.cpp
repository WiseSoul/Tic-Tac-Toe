#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
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

void AI_move_Easy(void)
{
	int i, j;
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++)
			if (matrix[i][j] == ' ') break;
		if (matrix[i][j] == ' ') break;
	}

	if (i*j == 9)
		cout << "draw\n";
	else
		matrix[i][j] = playerTwoSymbol;
}

void disp_matrix(void) //matrix display
{
	int t;
    cout << endl;

	for (t = 0; t<3; t++)
	{

		cout << " " << char(matrix[t][0]) << " | " << char(matrix[t][1]) << " | " << char(matrix[t][2]);

		if (t != 2)
			cout << "\n---|---|---\n";
	}
	cout << endl << endl;
}

char check(void) //used for identifying winner
{
	int i;

	for (i = 0; i<3; i++)  /* check rows */
		if (matrix[i][0] == matrix[i][1] &&
			matrix[i][0] == matrix[i][2]) return matrix[i][0];

	for (i = 0; i<3; i++)  /* check columns */
		if (matrix[0][i] == matrix[1][i] &&
			matrix[0][i] == matrix[2][i]) return matrix[0][i];

	/* test diagonals */
	if (matrix[0][0] == matrix[1][1] &&
		matrix[1][1] == matrix[2][2])
		return matrix[0][0];

	if (matrix[0][2] == matrix[1][1] &&
		matrix[1][1] == matrix[2][0])
		return matrix[0][2];

	return ' ';
}

bool vulnerabil(int mat[3][3])
{
	char a, b, c, d, e, f, g, h, i;
	a = mat[0][0], b = mat[0][1], c = mat[0][2];
	d = mat[1][0], e = mat[1][1], f = mat[1][2];
	g = mat[2][0], h = mat[2][1], i = mat[2][2];
	if ((a == playerOneSymbol && b == playerOneSymbol && c != playerTwoSymbol) || (b == playerOneSymbol && c == playerOneSymbol && a != playerTwoSymbol) || (a == playerOneSymbol && c == playerOneSymbol && b != playerTwoSymbol))
	{
		row = 1; return true;
	}
	if ((d == playerOneSymbol && e == playerOneSymbol && f != playerTwoSymbol) || (e == playerOneSymbol && f == playerOneSymbol && d != playerTwoSymbol) || (d == playerOneSymbol && f == playerOneSymbol && e != playerTwoSymbol))
	{
		row = 2; return true;
	}
	if ((g == playerOneSymbol && h == playerOneSymbol && i != playerTwoSymbol) || (h == playerOneSymbol && i == playerOneSymbol && g != playerTwoSymbol) || (g == playerOneSymbol && i == playerOneSymbol && h != playerTwoSymbol))
	{
		row = 3; return true;
	}
	if ((a == playerOneSymbol && d == playerOneSymbol && g != playerTwoSymbol) || (d == playerOneSymbol && g == playerOneSymbol && a != playerTwoSymbol) || (a == playerOneSymbol && g == playerOneSymbol && d != playerTwoSymbol))
	{
		column = 1; return true;
	}
	if ((b == playerOneSymbol && e == playerOneSymbol && h != playerTwoSymbol) || (e == playerOneSymbol && h == playerOneSymbol && b != playerTwoSymbol) || (b == playerOneSymbol && h == playerOneSymbol && e != playerTwoSymbol))
	{
		column = 2; return true;
	}
	if ((c == playerOneSymbol && f == playerOneSymbol && i != playerTwoSymbol) || (f == playerOneSymbol && i == playerOneSymbol && c != playerTwoSymbol) || (c == playerOneSymbol && i == playerOneSymbol && f != playerTwoSymbol))
	{
		column = 3; return true;
	}
	if ((a == playerOneSymbol && e == playerOneSymbol && i != playerTwoSymbol) || (e == playerOneSymbol && i == playerOneSymbol && a != playerTwoSymbol) || (a == playerOneSymbol && i == playerOneSymbol && e != playerTwoSymbol))
	{
		diagonal = 1; return true;
	}
	if ((g == playerOneSymbol && e == playerOneSymbol && c != playerTwoSymbol) || (e == playerOneSymbol && c == playerOneSymbol && g != playerTwoSymbol) || (g == playerOneSymbol && c == playerOneSymbol && e != playerTwoSymbol))
	{
		diagonal = 2; return true;
	}
	return false;
}

bool castigator(int mat[3][3])
{
	char a, b, c, d, e, f, g, h, i;
	a = mat[0][0], b = mat[0][1], c = mat[0][2];
	d = mat[1][0], e = mat[1][1], f = mat[1][2];
	g = mat[2][0], h = mat[2][1], i = mat[2][2];
	if ((a == playerTwoSymbol && b == playerTwoSymbol && c != playerOneSymbol) || (b == playerTwoSymbol && c == playerTwoSymbol && a != playerOneSymbol) || (a == playerTwoSymbol && c == playerTwoSymbol && b != playerOneSymbol))
	{
		row = 1;
		return true;
	}
	if ((d == playerTwoSymbol && e == playerTwoSymbol && f != playerOneSymbol) || (e == playerTwoSymbol && f == playerTwoSymbol && d != playerOneSymbol) || (d == playerTwoSymbol && f == playerTwoSymbol && e != playerOneSymbol))
	{
		row = 2;
		return true;
	}
	if ((g == playerTwoSymbol && h == playerTwoSymbol && i != playerOneSymbol) || (h == playerTwoSymbol && i == playerTwoSymbol && g != playerOneSymbol) || (g == playerTwoSymbol && i == playerTwoSymbol && h != playerOneSymbol))
	{
		row = 3;
		return true;
	}
	if ((a == playerTwoSymbol && d == playerTwoSymbol && g != playerOneSymbol) || (d == playerTwoSymbol && g == playerTwoSymbol && a != playerOneSymbol) || (a == playerTwoSymbol && g == playerTwoSymbol && d != playerOneSymbol))
	{
		column = 1;
		return true;
	}
	if ((b == playerTwoSymbol && e == playerTwoSymbol && h != playerOneSymbol) || (e == playerTwoSymbol && h == playerTwoSymbol && b != playerOneSymbol) || (b == playerTwoSymbol && h == playerTwoSymbol && e != playerOneSymbol))
	{
		column = 2;
		return true;
	}
	if ((c == playerTwoSymbol && f == playerTwoSymbol && i != playerOneSymbol) || (f == playerTwoSymbol && i == playerTwoSymbol && c != playerOneSymbol) || (c == playerTwoSymbol && i == playerTwoSymbol && f != playerOneSymbol))
	{
		column = 3;
		return true;
	}
	if ((a == playerTwoSymbol && e == playerTwoSymbol && i != playerOneSymbol) || (e == playerTwoSymbol && i == playerTwoSymbol && a != playerOneSymbol) || (a == playerTwoSymbol && i == playerTwoSymbol && e != playerOneSymbol))
	{
		diagonal = 1;
		return true;
	}
	if ((g == playerTwoSymbol && e == playerTwoSymbol && c != playerOneSymbol) || (e == playerTwoSymbol && c == playerTwoSymbol && g != playerOneSymbol) || (g == playerTwoSymbol && c == playerTwoSymbol && e != playerOneSymbol))
	{
		diagonal = 2;
		return true;
	}
	return false;


}

bool terminat(int mat[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (mat[i][j] == ' ')
				return false;
		}
	}
	return true;
}

int empty_c(int r)
{
	for (int i = 0; i < 3; ++i)
	{
		if (matrix[r][i] == ' ')
			return i;
	}
}

int empty_r(int c)
{
	for (int i = 0; i < 3; ++i)
	{
		if (matrix[i][c] == ' ')
			return i;
	}
}

void reset()
{
	row = 0;
	column = 0;
	diagonal = 0;
}

void assignSymbols(bool multiplayer) {
    bool isUserX = genRand();

    if (isUserX) {
        playerOneSymbol = 'X';
        playerTwoSymbol = 'O';
    }else {
        playerTwoSymbol = 'X';
        playerOneSymbol = 'O';
    }

	cout<<(multiplayer?"Player 1 is ":"You are ")<<"playing as : "<<playerOneSymbol<<'\n';
	if (multiplayer) {
		cout<<"Player 2 is playing as : "<<playerTwoSymbol<<'\n';
	}
}
