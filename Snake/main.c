#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>
#include <ctype.h>

#define Length 20
#define Line 10
#define SEC_PER_TICK 0.5

typedef struct {
	int x;
	int y;
} xy;

static int score;
static xy pos_food;
static xy snake[(Length-2)*(Line-2)];
static int gameover = 0;

xy generateFood() {
	//A random position generator for the food
	srand(time(NULL));
	xy temp;
	//Loop until the generated location is not in the snake
	int snakespot;
	do {
		temp.x = (rand() % (Length - 2)) + 1;
		temp.y = (rand() % (Line - 2)) + 1;
		
		snakespot = 0;
		for(int i=0;i<=score && snakespot == 0;i++) {
			if(temp.x == snake[i].x && temp.y == snake[i].y)
				snakespot = 1;
		}
	} while(snakespot == 1);
	
	return temp;
}

void addScore() {
	pos_food = generateFood();
	score++;
}

int thereIsAnother(int index) {
	/*
	 * If there is 2 snake locations in one spot (at game over) this function will return with 1,
	 * This helps at printing and detecting game over.
	*/
	for(int i=0;i<=score;i++) {
		if(i > index && snake[i].x == snake[index].x && snake[index].y == snake[i].y && i != index)
			return 1;
	}	
	return 0;
}

void setgameover() {
	printf("\nGame over!\nFinal score: %d\nPress R to restart the game!", score);
	gameover = 1;
}

void tick() {
	system("@cls||clear");	
	//Print
	//Goes trough every spot on the playfield (Length * Line)
	for(int i=0;i<Line;i++) {
		for(int j=0;j<Length;j++) {
			int foundSnake = 0;
			//If the current location is a snake location print 'O'
			for(int x=0;x<=score;x++) {
				if(snake[x].x == j && snake[x].y == i) {
					if(thereIsAnother(x) == 0)
						putchar('O');
					foundSnake = 1;
				}
			}
			/*	If the current location is not a snake location check 
			 * 	if it is food, a wall, or an empty space then print the right character. */
			if(foundSnake == 0) {
				if(j== pos_food.x && i == pos_food.y)
					putchar('%');
				else if(j == 0 || j == Length-1)
					putchar('|');
				else if(i == 0 || i == Line-1)
					putchar('&');
				else
					putchar(' ');
			}
		}
		putchar('\n');
	}
	//Collisions
	/*	If the snake's head is collides with food -> score +1
	 *	If the snake's head is collides with wall or the body -> game over */
	if(snake[0].x == pos_food.x && snake[0].y == pos_food.y)
		addScore();
	else if(snake[0].x == 0 || snake[0].x == Length-1 || snake[0].y == 0 || snake[0].y == Line-1)
		setgameover();
	else if(thereIsAnother(0))
		setgameover();
	//Print other things
	if(gameover == 0)
		printf("Score: %d\nMove the snake with W A S D", score);
}

void MoveSnake(char c) {
	if(gameover == 0) {
		xy temp = snake[0];
		switch(c) {
			case 'd':
				snake[0].x++;
			break;
			case 'a':
				snake[0].x--;
			break;
			case 's':
				snake[0].y++;
			break;
			case 'w':
				snake[0].y--;
			break;
		}
		
		//Move the body of the snake
		for(int i=1;i<=score;i++) {
			xy temp2 = snake[i];
			snake[i] = temp;
			temp = temp2;
		}
	}
}

void timer(char lastPressed) {
	//Loop every SEC_PER_TICK
	time_t start = clock();
	double delta;
	while(delta < SEC_PER_TICK) {
		//Check the elapsed time
		delta = ((double)clock()-(double)start)/CLOCKS_PER_SEC;
		if(delta >= SEC_PER_TICK) {
			char pressedBefore = lastPressed;
			//Input
			if(kbhit()) {
				lastPressed = tolower(getch());
			}
			//The user can't change the snake's direction to the opposite directly
			if((lastPressed == 'a' && pressedBefore == 'd') ||
				(lastPressed == 'd' && pressedBefore == 'a') ||
				(lastPressed == 'w' && pressedBefore == 's') ||
				(lastPressed == 's' && pressedBefore == 'w') ||
				(lastPressed != 's' && lastPressed != 'a' && lastPressed != 'd' && lastPressed != 'w' && gameover == 0)) {
					lastPressed = pressedBefore;
			}
			
			if(gameover == 0) {
				MoveSnake(lastPressed);
				tick();
			} else {
				if(lastPressed == 'r') {
					//Reset the game
					score = 0;
					snake[0].x = 1;
					snake[0].y = 1;
					lastPressed = 'd';
					gameover = 0;
					tick();
				}
			}
			//Start the timer again
			timer(lastPressed);		
		}
	}
}

int main() {
	pos_food = generateFood();
	score = 0;
	snake[0].x = 1;
	snake[0].y = 1;
	
	tick();
	timer('d');
	return 0;
}