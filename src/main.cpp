/* cmd snake v4.2.0 */

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

string TITLE (" snake v4.2.0 ");
const int TITLE_LEN = TITLE.length();

bool quit = false;
bool game_over;
bool invisible_walls;

const int WIDTH  = 24;
const int HEIGHT = 20;
const int BOARDW = WIDTH - 2;
const int BOARDH = HEIGHT - 2;
int x, y, fx, fy, tlen, score;
int tx[WIDTH*HEIGHT], ty[WIDTH*HEIGHT];
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup()
{
    system("color 0A");
    invisible_walls = true;
    game_over = false;
    score = 0;
    tlen = 2;
    dir = STOP;
    x = BOARDW / 2;
    y = BOARDH / 2;
    for (int i = 0; i < tlen; i++)
    {
        tx[i] = x;
        ty[i] = y + i + 1;
    }
    fx = rand() % BOARDW + 1;
    fy = rand() % BOARDH + 1;
}

void Draw()
{
    system("cls||clear");
    cout << endl;
    cout << "\t" << char(201); // ╔
    cout << TITLE;
    for (int j = TITLE_LEN + 1; j < WIDTH; j++)
        cout << char(205); // ═
    cout << char(187) << endl; // ╗

    for (int i = 0; i < BOARDH+1; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                cout << "\t" << char(186); // ║
            if (j == x && i == y)
                cout << "@";
            else if (j == fx && i == fy)
                cout << "X";
            else
            {                
                bool print = false;
                for (int k = 0; k < tlen; k++)
                {
                    if (tx[k] == j && ty[k] == i)
                    {
                        if (k == tlen-1)
                        {
                            if (tx[k-1] == tx[k])
                                cout << "|" ;
                            else if (ty[k-1] == ty[k])
                                cout << "-";
                        }
                        else
                            cout << "o";
                        print = true;
                    }
                };
                if (!print)
                    cout << " ";
            }

            if (j == BOARDW)
                cout << char(186); // ║
        }
        cout << endl;
    }

    cout << "\t" << char(200); // ╚
    string score_str = " score: " + to_string(score) + " ";
    cout << score_str;
    for (int j = score_str.length() + 1; j < WIDTH; j++)
        cout << char(205); // ═
    cout << char(188); // ╝
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                if (dir == RIGHT)
                    break;
                dir = LEFT;
                break;
            case 'w':
                if (dir == DOWN)
                    break;
                dir = UP;
                break;
            case 'd':
                if (dir == LEFT)
                    break;
                dir = RIGHT;
                break;
            case 's':
                if (dir == UP || dir == STOP)
                    break;
                dir = DOWN;
                break;
            case 'x':
                game_over = true;
                break;
            default:
                dir = STOP;
        }
    }
}

void Logic()
{
    int prev_x = tx[0], prev_y = ty[0];
    int prev_x2, prev_y2;

    tx[0] = x;
    ty[0] = y;

    for (int i = 1; i < tlen; i++)
    {
        prev_x2 = tx[i];
        prev_y2 = ty[i];
        tx[i]   = prev_x;
        ty[i]   = prev_y;
        prev_x  = prev_x2;
        prev_y  = prev_y2;
    }

    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    if (invisible_walls)
    {
        if (x < 0) x = BOARDW;
        else if (x > BOARDW) x = 0;
        if (y < 0) y = BOARDH;
        else if (y > BOARDH) y = 0;
    }
    else if (x < 0 || x > BOARDW || y < 0 || y > BOARDH)
            game_over = true;

    for (int i = 1; i < tlen; i++)
        if (tx[i] == x && ty[i] == y)
            game_over = true;

    if (x == fx && y == fy)
    {
        fx = rand() % BOARDW + 1;
        fy = rand() % BOARDH + 1;
        score += 1;
        tlen += 1;        
    }
}

int main()

{
    while (!quit)
    {
        Setup();
        Draw();

        while (dir == STOP)
            Input();

        while (!game_over)
        {
            Draw();
            Input();
            Logic();
            Sleep(20);
        }

        cout << endl << endl << "\tgame over" << endl;

        while (true)
        {
            cout << endl << "play again? (y/n): ";
            char response;
            cin >> response;
            if (response == char(110))
            {
                quit = true;
                break;
            }
            else if (response == char(121))
            {
                break;
            }
            else
                cout << endl << "not valid input" << endl;
        }
            
    }

    return 0;
}