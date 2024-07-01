#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

// "Group Members                   ID",
// "Nebil Rahmeto               UGR/25275/14",
// "Tekliye Tamiru              UGR/25614/14",
// "Mohammed Kasim              UGR/25433/14",
// "Abraham Yitbarek			UGR/26544/14"


const int WIDTH = 800;
const int HEIGHT = 600;
const int GRID_SIZE = 20;
int score;
bool levelPicked = false;

struct Point
{
    int x, y;
};

std::vector<Point> snake;
Point food;
int direction;
bool gameOver;
void Timer(int);
int speed = 200;

void InitGame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    snake.clear();
    Point p;
    p.x = 10;
    p.y = 10;
    snake.push_back(p);
    
    direction = GLUT_KEY_RIGHT;
    Point food;
    food.x = 15;
    food.y = 10;
    
    gameOver = false;
    score = 0;
    levelPicked = false;
    glutTimerFunc(speed, Timer, 0);
}

void DrawSquare(int x, int y)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}
void GameOver()
{
    string text = "GAME OVER!";
    string subtext = "Press F2 to play again!";
    glColor3f(1, 0, 0);
    glRasterPos2i(WIDTH / GRID_SIZE - 23, HEIGHT / GRID_SIZE - 15);
    for (int i = 0; i < text.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
    }
    glColor3f(1, 1, 1);
    glRasterPos2i(WIDTH / GRID_SIZE - 24.4, HEIGHT / GRID_SIZE - 17);
    for (int i = 0; i < subtext.size(); i++)
    {   
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, subtext.at(i));
    }
}
void Levels()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the snake
    string texts[] = {
        "PICK A LEVEL!",
        "1. EASY LEVEL",
        "2. MEDIUM LEVEL",
        "3. HARD LEVEL"};
    for (int i = 0; i < 4; i++)
    {
        string subtext = texts[i];
        glColor3f(1,1,0);   
        glRasterPos2i(WIDTH/GRID_SIZE - 24.4, HEIGHT / GRID_SIZE - 12 - (i*2));
        for (int j = 0; j < subtext.size(); j++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, subtext.at(j));
        }
    }
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (levelPicked) {
    // Draw the snake
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i=0; i<snake.size();i++)
    {
        Point p = snake[i];
		DrawSquare(p.x, p.y);
    }
    string text = "Score: ";
    glColor3f(1, 1, 0);
    glRasterPos2i(WIDTH / GRID_SIZE - 5, HEIGHT / GRID_SIZE - 2);
    for (int i = 0; i < text.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
    }
    // Draw the food
    glColor3f(1.0f, 0.0f, 0.0f);
    DrawSquare(food.x, food.y);

    if (gameOver)
    {
        GameOver();
    }
    } else {
        Levels();
    }
    glutSwapBuffers();
}

void Timer(int = 0)
{
    if (!gameOver && levelPicked)
    {
        Point next = snake.front();

        switch (direction)
        {
        case GLUT_KEY_UP:
            next.y++;
            break;
        case GLUT_KEY_DOWN:
            next.y--;
            break;
        case GLUT_KEY_LEFT:
            next.x--;
            break;
        case GLUT_KEY_RIGHT:
            next.x++;
            break;
        }

        // Check for collision with walls
        if (next.x < 0 || next.x >= WIDTH / GRID_SIZE || next.y < 0 || next.y >= HEIGHT / GRID_SIZE)
        {
            gameOver = true;
        }

        // Check for collision with self
        for (int i=0; i<snake.size();i++)
    {
        Point p = snake[i];
            if (p.x == next.x && p.y == next.y)
            {
                gameOver = true;
            }
        }

        if (!gameOver)
        {
            snake.insert(snake.begin(), next);

            // Check for food
            if (next.x == food.x && next.y == food.y)
            {
                food.x = rand() % (WIDTH / GRID_SIZE);
                food.y = rand() % (HEIGHT / GRID_SIZE);
				
                score += 1;
                speed -= 6;
            }
            else
            {
                snake.pop_back();
            }

            glutPostRedisplay();
        }

        glutTimerFunc(speed, Timer, 0);
    }
    else
    {
        glutPostRedisplay();
    }
}

void Keyboard(int key, int, int)
{
    if (!gameOver)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            if (direction != GLUT_KEY_DOWN)
            {
                direction = key;
            }
            break;
        case GLUT_KEY_DOWN:
            if (direction != GLUT_KEY_UP)
            {
                direction = key;
            }
            break;
        case GLUT_KEY_LEFT:
            if (direction != GLUT_KEY_RIGHT)
            {
                direction = key;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (direction != GLUT_KEY_LEFT)
            {
                direction = key;
            }
            break;
        }
    }
    else
    {
        if (key == GLUT_KEY_F2)
        {
            InitGame();
        }
    }
}
void selectLevel(unsigned char key, int x, int y)
{
    if (!levelPicked) {
    switch (key)
    {
    case '1':
        speed = 200;
        levelPicked = true;
        glutTimerFunc(speed,Timer,0);
        break;
    case '2':
        speed = 150;
        levelPicked = true;
        glutTimerFunc(speed,Timer,0);

        break;
    case '3':
        speed = 100;
        levelPicked = true;
        glutTimerFunc(speed,Timer,0);

        break;
    default:
        break;
    }
    }
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake Game");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH / GRID_SIZE, 0, HEIGHT / GRID_SIZE, -1, 1);
    InitGame();
    glutDisplayFunc(Display);
    glutSpecialFunc(Keyboard);
    glutKeyboardFunc(selectLevel);

    glutMainLoop();
    return 0;
}
