#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanIp>
using namespace std;

// function prototypes
void header();
void printmaze();
void printP(int PX, int PY);
void eraseP(int PX, int PY);

void printGhosts();
void ghostmovement();
void ghostmovement2();
void ghostmovement4();
void ghostmovement3();
int randomDirection();
void eraseGhost(int ghostX, int ghostY);

void movePDown();
void movePUp();
void movePLeft();
void movePRight();

void printscore();
void printHighScore();
void updateHighScore(int currentScore);

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

void gameover();

void printlives();
void ghostmovement();
void ghostmovement2();
void ghostmovement3();
void ghostmovement4();
void eraseGhost(int ghostX, int ghostY);
void printGhosts();
void collide();

void checkwin();

// global variables
int PX = 4, PY = 40; // player starting position
int ghost1X = 10, ghost1Y = 11;
int ghost2X = 18, ghost2Y = 25;
int ghost3X = 15, ghost3Y = 15;
int ghost4X = 4, ghost4Y = 20;
// keeps track of score
int Life = 5;
int score = 0;
int highestScore = 0; // global variable for highest score

int main()
{    
    system("cls");
    header();
    Sleep(2500);
    system("cls");
    printmaze();   // displaying the maze layout
    printHighScore(); // Display high score initially
    printP(PX, PY);   // Print

    while (true)
    {
        Sleep(200); // Slow down the game loop

        ghostmovement();  // ghosts move
        ghostmovement2(); // second ghost moves
        ghostmovement3(); // third ghost moves
        ghostmovement4(); // fourth ghost moves
        printscore();     // print the score
        printHighScore(); // display updated high score
        printlives();
        collide();
        gotoxy(85,10);
        cout<<"press ESC to quit the game"<<endl;
         
        // Check for collisions with ghosts
        // Player movement
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePDown();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {   system("cls");
         cout << "Thanks for playing PACMAN!";
        cout << "GAME OVER!";
            updateHighScore(score);
            return 0;}
        
    }
 }

// function definitions
void header(){
        cout << "\033[1;33m";  // Set text color to yellow

    cout << setw(50) << "  88888888ba      db         ,ad8888ba,   88b           d88         db         888b      88  \n";
    cout << setw(50) << "  88       8b    d88b       d8        8b  888b         d888        d88b        8888b     88  \n";
    cout << setw(50) << "  88      ,8P   d8'`8b     d8'            88`8b       d8'88       d8'`8b       88 `8b    88  \n";
    cout << setw(50) << "  88aaaaaa8P'  d8'  `8b    88             88 `8b     d8' 88      d8'  `8b      88  `8b   88  \n";
    cout << setw(50) << "  88          d8YaaaaY8b   88             88  `8b   d8'  88     d8YaaaaY8b     88   `8b  88  \n";
    cout << setw(50) << "  88         d8        8b  Y8,            88   `8b d8'   88    d8        8b    88    `8b 88  \n";
    cout << setw(50) << "  88        d8'        `8b  Y8a.    .a8P  88    `888'    88   d8'        `8b   88     `8888  \n";
    cout << setw(50) << "  88       d8'          `8b    Y8888Y   88       `8'     88  d8'          `8b  88      `888  \n";

    // Reset text color to default
    cout << "\033[0m";
    
}

void printmaze()
{
    // print the maze layout
    fstream file;
    file.open("maze.txt", ios::in); // Open the file in read mode

    // Check if the file is open
    if (!file)
    {
        cout << "Error opening the file!" << endl;
        return; // If the file can't be opened, exit the function
    }

    string line;
    // Read the maze layout line by line and display it
    while (getline(file, line))
    {
        system("COLOR 3");
        cout << line << endl; // Print each line of the maze
    }

    // Close the file after reading
    file.close();
}
void printlives()
{
    gotoxy(85, 16);
    // setting cursor at position
    cout << "\033[31mlives:\033[0m " << Life; // printing the score
    if (Life < 0)

    {
        updateHighScore(score); // update highest score before game over
        gameover();             // check for game over condition
    }
}

void printscore()
{
    gotoxy(85, 15);             // setting cursor at position
    cout << "\033[31mScore:\033[0m " << score; // printing the score
                                // Check for win condition (score reached 150)
    if (score >= 151)
    {
        updateHighScore(score);
        checkwin();
    }
}

void movePLeft()
{
    char nextLocation = getCharAtxy(PY - 1, PX);
    if (nextLocation == ' ' || nextLocation == '.' || nextLocation == '0')
    {
        eraseP(PX, PY);
        PY -= 1;
        printP(PX, PY);
        if (nextLocation == '.')
        {
            score = score + 1; // score increases when player eats dot
        }
        if (nextLocation == '0')
        {
            score = score + 10; // score increases when player eats dot
        }
    }
}
void movePRight()
{
    char nextLocation = getCharAtxy(PY + 1, PX);
    if (nextLocation == ' ' || nextLocation == '.' || nextLocation == '0') // player can move right
    {
        eraseP(PX, PY);
        PY += 1;
        printP(PX, PY);
        if (nextLocation == '.')
        {
            score = score + 1; // score increases when player eats dot
        }
        if (nextLocation == '0')
        {
            score = score + 10; // score increases when player eats dot
        }
    }
}

void movePUp()
{
    char nextLocation = getCharAtxy(PY, PX - 1);
    if (nextLocation == ' ' || nextLocation == '.' || nextLocation == '0')
    {
        eraseP(PX, PY);
        PX -= 1;
        printP(PX, PY);
        if (nextLocation == '.')
        {
            score = score + 1; // score increases when player eats dot
        }
        if (nextLocation == '0')
        {
            score = score + 10; // score increases when player eats dot
        }
    }
}

void movePDown()
{
    char nextLocation = getCharAtxy(PY, PX + 1);
    if (nextLocation == ' ' || nextLocation == '.' || nextLocation == '0')
    {
        eraseP(PX, PY);
        PX += 1;
        printP(PX, PY);
        if (nextLocation == '.')
        {
            score = score + 1;
            ; // score increases when player eats dot
        }
        if (nextLocation == '0')
        {
            score = score + 10; // score increases when player eats dot
        }
    }
}
void printP(int PX, int PY)
{
    gotoxy(PY, PX); // print the player at new position
    cout << "\033[33mP\033[0m";
}

void eraseP(int PX, int PY)
{
    gotoxy(PY, PX); // erase player from position
    cout << " ";
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize = {1, 1};
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moving cursor to position
}

int randomDirection()
{
    return rand() % 4; // random direction
}

void eraseGhost(int ghostX, int ghostY)
{
    gotoxy(ghostY, ghostX); // erasing ghost from current position
    cout << " ";
}

void printGhosts()
{
    gotoxy(ghost1Y, ghost1X); // print first ghost
    cout << "\033[31mA\033[0m";
    gotoxy(ghost2Y, ghost2X); // print second ghost
    cout << "\033[31mB\033[0m";
    gotoxy(ghost3Y, ghost3X); // print second ghost
    cout << "\033[31mC\033[0m";
    gotoxy(ghost4Y, ghost4X); // print second ghost
    cout << "\033[31mD\033[0m";
}

void ghostmovement()
{
    // ghosts move randomly or chase the player
    int directionX = 0, directionY = 0;
    int randomChance = rand() % 100;

    if (randomChance < 30) // ghost moves randomly 30% of the time
    {
        int direction = randomDirection();
        switch (direction)
        {
        case 0:
            directionX = -1;
            break; // move up
        case 1:
            directionX = 1;
            break; // move down
        case 2:
            directionY = -1;
            break; // move left
        case 3:
            directionY = 1;
            break; // move right
        }
    }
    else
    {
        // ghosts are chasing the player
        if (ghost1X < PX)
            directionX = 1; // move down
        else if (ghost1X > PX)
            directionX = -1; // move up

        if (ghost1Y < PY)
            directionY = 1; // move right
        else if (ghost1Y > PY)
            directionY = -1; // move left
    }

    int nextX = ghost1X + directionX;
    int nextY = ghost1Y + directionY;

    char originalChar = getCharAtxy(nextY, nextX); // checking if ghost can move

    if (originalChar == ' ' || originalChar == '.') // ghost can move
    {
        eraseGhost(ghost1X, ghost1Y);
        ghost1X = nextX;
        ghost1Y = nextY;
        printGhosts();

        if (originalChar == '.') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << ".";
        }
    }
}

void ghostmovement2()
{

    int directionX = 0, directionY = 0;
    int randomChance = rand() % 100;

    if (randomChance < 25) // ghost moves randomly 30% of the time
    {
        int direction = randomDirection();
        switch (direction)
        {
        case 0:
            directionX = -1;
            break; // move up
        case 1:
            directionX = 1;
            break; // move down
        case 2:
            directionY = -1;
            break; // move left
        case 3:
            directionY = 1;
            break; // move right
        }
    }
    else
    {
        // ghosts are chasing the player
        if (ghost2X < PX)
            directionX = 1; // move down
        else if (ghost2X > PX)
            directionX = -1; // move up

        if (ghost2Y < PY)
            directionY = 1; // move right
        else if (ghost2Y > PY)
            directionY = -1; // move left
    }

    int nextX = ghost2X + directionX;
    int nextY = ghost2Y + directionY;

    char originalChar = getCharAtxy(nextY, nextX); // checking if ghost can move

    if (originalChar == ' ' || originalChar == '.' || originalChar == '0') // ghost can move
    {
        eraseGhost(ghost2X, ghost2Y);
        ghost2X = nextX;
        ;
        ghost2Y = nextY;
        printGhosts();

        if (originalChar == '.') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << ".";
        }
        if (originalChar == '0') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << "0";
        }
    }
}
void ghostmovement3()
{

    int directionX = 0, directionY = 0;
    int randomChance = rand() % 100;

    if (randomChance < 15) // ghost moves randomly 25% of the time
    {
        int direction = randomDirection();
        switch (direction)
        {
        case 0:
            directionX = -1;
            break; // move up
        case 1:
            directionX = 1;
            break; // move down
        case 2:
            directionY = -1;
            break; // move left
        case 3:
            directionY = 1;
            break; // move right
        }
    }
    else
    {
        // ghosts are chasing the player
        if (ghost3X < PX)
            directionX = 1; // move down
        else if (ghost3X > PX)
            directionX = -1; // move up

        if (ghost3Y < PY)
            directionY = 1; // move right
        else if (ghost3Y > PY)
            directionY = -1; // move left
    }

    int nextX = ghost3X + directionX;
    int nextY = ghost3Y + directionY;

    char originalChar = getCharAtxy(nextY, nextX); // checking if ghost can move

    if (originalChar == ' ' || originalChar == '.' || originalChar == '0') // ghost can move
    {
        eraseGhost(ghost3X, ghost3Y);
        ghost3X = nextX;
        ghost3Y = nextY;
        printGhosts();

        if (originalChar == '.') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << ".";
        }
        if (originalChar == '0') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << "0";
        }
    }
}

void ghostmovement4()
{

    int directionX = 0, directionY = 0;
    int randomChance = rand() % 100;

    if (randomChance < 10) // ghost moves randomly 30% of the time
    {
        int direction = randomDirection();
        switch (direction)
        {
        case 0:
            directionX = -1;
            break; // move up
        case 1:
            directionX = 1;
            break; // move down
        case 2:
            directionY = -1;
            break; // move left
        case 3:
            directionY = 1;
            break; // move right
        }
    }
    else
    {
        // ghosts are chasing the player
        if (ghost4X < PX)
            directionX = 1; // move down
        else if (ghost4X > PX)
            directionX = -1; // move up

        if (ghost4Y < PY)
            directionY = 1; // move right
        else if (ghost4Y > PY)
            directionY = -1; // move left
    }

    int nextX = ghost4X + directionX;
    int nextY = ghost4Y + directionY;

    char originalChar = getCharAtxy(nextY, nextX); // checking if ghost can move

    if (originalChar == ' ' || originalChar == '.' || originalChar == '0') // ghost can move
    {
        eraseGhost(ghost4X, ghost4Y);
        ghost4X = nextX;
        ghost4Y = nextY;
        printGhosts();

        if (originalChar == '.') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << ".";
        }
        if (originalChar == '0') // restoring dot if ghost eats it
        {
            gotoxy(nextY, nextX);
            cout << "0";
        }
    }
}

void gameover()
{
system("cls");
    gotoxy(88, 18);

    cout << "YOU LOST!!!"; // game ends here
    gotoxy(88, 19);
    cout << "press enter to continue" << endl;
    cin.get();
    
    system("cls");
    exit(0); // End the game when lives reach 0
   
}

void checkwin()
{

    gotoxy(88, 18);

    cout << "YOU WON!!!"; // game ends here
    cin.get();
    cout << "press enter to continue" << endl;
    system("cls");
    exit(0);
}
void printHighScore()
{
    fstream file("highscore.txt", ios::in);
    if (file.is_open())
    {
        file >> highestScore;
        file.close();
    }
    gotoxy(85, 11); // 4 lines above the score
    cout << "High Score: " << highestScore;
}
void updateHighScore(int currentScore)
{
    fstream file("highscore.txt", ios::in);
    int storedHighScore = 0;
    if (file.is_open())
    {
        file >> storedHighScore;
        file.close();
    }

    if (currentScore > storedHighScore)
    {
        fstream outFile("highscore.txt", ios::out);
        outFile << currentScore;
        outFile.close();
    }
}
void collide()
{
    if ((abs(PX - ghost1X) <= 1 && abs(PY - ghost1Y) <= 1) ||
        (abs(PX - ghost2X) <= 1 && abs(PY - ghost2Y) <= 1) ||
        (abs(PX - ghost3X) <= 1 && abs(PY - ghost3Y) <= 1) ||
        (abs(PX - ghost4X) <= 1 && abs(PY - ghost4Y) <= 1))
    {
        eraseP(PX, PY); // erase the player
        Life -= 1;      // decrease player lives
        if (Life >= 0)
        {
            gotoxy(85, 18);
            cout << "\033[31mOuch! Lives left!!\033[0m" << Life;
            Sleep(1000);
            gotoxy(85, 18);
            cout << "                                        ";
            eraseP(PX, PY); // erase the player                ;
            Sleep(2500);
            printP(PX, PY); // reset player
        }
    }
}
