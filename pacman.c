#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'X' 
#define POWER_UP 'P'
 
int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
char board[HEIGHT][WIDTH]; 
int food = 0; 
int curr = 0; 
int powerUps = 0;
int powerUpActive = 0;
int lives = 3;
void initialize() 
{ 
	int i,j;
	// Putting Walls as boundary in the Game 
	for (i = 0; i < HEIGHT; i++) 
	{ 
		for (j = 0; j < WIDTH; j++) 
		{ 
			if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1) 
			{ 
				board[i][j] = WALL; 
			} 
			else
				board[i][j] = EMPTY; 
		} 
	} 

	// Putting Walls inside the Game 
	int count = 50; 
	while (count != 0) 
	{ 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 
		if (board[i][j] != WALL && board[i][j] != PACMAN) 
		{ 
			board[i][j] = WALL; 
			count--; 
		} 
	} 

	int val = 5; 
	while (val--) 
	{ 
		int row = (rand() % (HEIGHT + 1)); 
		for (j = 3; j < WIDTH - 3; j++) 
		{ 
			if (board[row][j] != WALL && board[row][j] != PACMAN) 
			{ 
				board[row][j] = WALL; 
			} 
		} 
	} 

	// Putting Demons in the Game 
	count = 10; 
	while (count != 0) 
	{ 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 
		if (board[i][j] != WALL && board[i][j] != PACMAN) 
		{ 
			board[i][j] = DEMON; 
			count--; 
		} 
	} 
	
	//Putting Power-ups in the Game
	int powerUpCount = 5;
	while(powerUpCount != 0)
	{
		int i = (rand() % (HEIGHT + 1));
		int j = (rand() % (WIDTH + 1));
		if(board[i][j] != WALL && board[i][j] != PACMAN && board[i][j] != FOOD && board[i][j] != DEMON && board[i][j] != POWER_UP)
		{
			board[i][j] = POWER_UP;
			powerUpCount--;
		}
	}

	// Cursor at Center 
	pacman_x = WIDTH / 2; 
	pacman_y = HEIGHT / 2; 
	board[pacman_y][pacman_x] = PACMAN; 

	// Points Placed 
	for (i = 0; i < HEIGHT; i++) 
	{ 
		for (j = 0; j < WIDTH; j++) 
		{ 
			if (i % 2 == 0 && j % 2 == 0 && board[i][j] != WALL && board[i][j] != DEMON && board[i][j] != PACMAN) 
			{ 

				board[i][j] = FOOD; 
				food++; 
			} 
		} 
	} 
} 

void draw() 
{ 
	int i,j;
	// Clear screen 
	system("cls"); 

	// Drawing All the elements in the screen 
	for (i = 0; i < HEIGHT; i++) 
	{ 
		for (j = 0; j < WIDTH; j++) 
		{ 
			printf("%c", board[i][j]); 
		} 
		printf("\n"); 
	} 
	printf("Score: %d\n", score); 
	printf("Lives: %d\n",lives);
} 

// Function enables to move the Cursor 
void move(int move_x, int move_y) 
{ 
	int x = pacman_x + move_x; 
	int y = pacman_y + move_y; 
	if (board[y][x] != WALL) 
	{ 
		if (board[y][x] == FOOD) 
		{ 
			score++; 
			food--; 
			curr++; 
			if (food == 0) 
			{ 
				res = 2; 
				return; 
			} 
		} 
		else if (board[y][x] == DEMON) 
		{ 
			lives--;
			if(lives == 0)
			{
				res = 1;
				return;
			}
		} 
		else if (board[pacman_y + move_y][pacman_x + move_x] == POWER_UP)
        {
        	powerUps++;
        	powerUpActive = 1; // Set flag to indicate power-up is active
        	board[pacman_y + move_y][pacman_x + move_x] = EMPTY; // Remove the power-up from the board
    	}
	
    	// Double the score if the flag is set
    	if (powerUpActive)
    	{
        	score *= 2;
           	powerUpActive = 0; // Reset the flag when power-up duration expires
        }
    	board[pacman_y][pacman_x] = EMPTY; 
		pacman_x = x; 
		pacman_y = y; 
		board[pacman_y][pacman_x] = PACMAN; 
	} 
} 

// Main Function 
int main() 
{ 
	initialize(); 
	char ch; 
	food -= 35; 
	int totalFood = food; 
	// Instructions to Play 
	printf(" Use buttons for u(up), l(left) , r(right) and d(down)\nAlso, Press q for quit\n"); 
	printf("Enter Y to continue: \n"); 
	ch = getch(); 
	if (ch != 'Y' && ch != 'y') 
	{ 
		printf("Exit Game! "); 
		return 1; 
	} 

	while (1) 
	{ 
		draw(); 
		printf("Total Food count: %d\n", totalFood); 
		printf("Total Food eaten: %d\n", curr); 
		if (res == 1) 
		{ 
			// Clear screen 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: %d\n", score); 
                                           printf("Food Eaten:%d\n",curr);
			return 1; 
		} 
		if (res == 2) 
		{ 
			// Clear screen 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
                                           printf("Food Eaten:%d\n",curr);
			return 1; 
		} 

		// Taking the Input from the user 
		ch = getch(); 

		// Moving According to the 
		// input character 
		switch (ch) 
		{ 	
			case 'u': 
				move(0, -1); 
				break; 
			case 'd': 
				move(0, 1); 
				break; 
			case 'l': 
				move(-1, 0); 
				break; 
			case 'r': 
				move(1, 0); 
				break; 
			case 'q': 
				printf("Game Over! Your Score: %d\n", score); 
                                                          printf("Food Eaten:%d\n",curr);
				return 0; 
		} 
	} 
}
