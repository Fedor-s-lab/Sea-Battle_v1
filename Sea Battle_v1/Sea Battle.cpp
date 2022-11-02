#include <iostream>
#include "ShipPosition.h"
#include "Ship.h"
#include "Point.h"
#include <list>
using namespace std;
void createGamefield(char gf[10][10]);
void printGamefield(char gf[10][10], int num);
bool isEmpty(char gf[10][10], int x, int y);
bool checkPosition(int size, int x, int y, bool x_orient, char gf[10][10]);
list<ShipPosition> findPosition(char gf[10][10], int shipSize);
void addShip_Rand(char gf[10][10], int sizeShip);
int giveRand_Number(int size);
void fillGamefield(char gf[10][10]);
void newGame(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10]);
bool Player_PC_moves(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10]);
bool playerTurn(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10]);
bool pcTurn(char gf1[10][10]);
list<Point> findPosition_forPC(char gf_1[10][10]);
void newTurn(char gf_1[10][10], char gf_3[10][10], int numTurn);
bool victoryConditions(char gf_1[10][10], char gf_2[10][10]);
int main() {
    int flag = 2;
    char Gamefield_1[10][10], Gamefield_2[10][10], Gamefield_3[10][10];
    // field player         enemy field          player's turns field

    newGame(Gamefield_1, Gamefield_2, Gamefield_3);
    Player_PC_moves(Gamefield_1, Gamefield_2, Gamefield_3);
    system("pause");
    while (victoryConditions(Gamefield_1, Gamefield_2)) {
        newTurn(Gamefield_1, Gamefield_3, flag);
        Player_PC_moves(Gamefield_1, Gamefield_2, Gamefield_3);
        system("pause");
        flag++;
    }
    return 0;
}
void createGamefield(char gf[10][10]) {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gf[i][j] = '.';
        }
    }
}
void printGamefield(char gf[10][10], int num) {
    cout << num << ')' << endl << "   ";
    for (int i = 0; i < 10; i++) cout << i << ' ';
    cout << endl << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << "  ";
        for (int j = 0; j < 10; j++) {
            cout << gf[i][j] << ' ';

        }
        cout << endl;
    }
    cout << endl;
}
bool isEmpty(char gf[10][10], int x, int y) {
    if (x < 0 || x >= 10) return false;
    if (y < 0 || y >= 10) return false;
    return gf[x][y] != 'K';
}
bool checkPosition(int size, int x, int y, bool x_orient, char gf[10][10]) {
    if (x_orient) {
        if (x < 0 || x + size > 10) return false;
        for (int i = -1; i <= size; i++) {
            if (x + i < 0 || x + i >= 10) continue;
            for (int j = -1; j < 2; j++) {
                if (y + j < 0 || y + j >= 10) continue;
                if (!isEmpty(gf, x + i, y + j)) return false;
            }
        }
    }
    else {
        if (y < 0 || y + size > 10) return false;
        for (int i = -1; i <= size; i++) {
            if (y + i < 0 || y + i >= 10) continue;
            for (int j = -1; j < 2; j++) {
                if (x + j < 0 || x + j >= 10) continue;
                if (!isEmpty(gf, x + j, y + i)) return false;
            }
        }
    }
}
list<ShipPosition> findPosition(char gf[10][10], int shipSize) {
    list<ShipPosition> Pos;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (checkPosition(shipSize, i, j, true, gf)) {
                Pos.emplace_front(ShipPosition(i, j, true));
            }
            if (checkPosition(shipSize, i, j, false, gf)) {
                Pos.emplace_front(ShipPosition(i, j, false));
            }
        }
    }
    return Pos;
}
void addShip_Rand(char gf[10][10], int sizeShip) {
    list<ShipPosition> Pos = findPosition(gf, sizeShip);
    int num = giveRand_Number(Pos.size());
    for (int i = 0; i < num; i++) Pos.pop_front();
    int x = Pos.front().p.givePoint_x();
    int y = Pos.front().p.givePoint_y();
    if (Pos.front().x_orient) {
        for (int i = 0; i < sizeShip; i++) gf[x + i][y] = 'K';
    }
    else {
        for (int i = 0; i < sizeShip; i++) gf[x][y + i] = 'K';
    }
}
int giveRand_Number(int size) {
    srand(time(0));
    return (rand() % size);
}
void fillGamefield(char gf[10][10]) {
    for (int i = 0; i < 1; i++) addShip_Rand(gf, 4);
    for (int i = 0; i < 2; i++) addShip_Rand(gf, 3);
    for (int i = 0; i < 3; i++) addShip_Rand(gf, 2);
    for (int i = 0; i < 4; i++) addShip_Rand(gf, 1);
}
void newGame(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10]) {
    system("cls");
    cout << "1 move" << endl;
    cout << "New game. We're filling the fields!" << endl;
    createGamefield(gf_1);
    createGamefield(gf_2);
    createGamefield(gf_3);
    printGamefield(gf_1, 1);
    printGamefield(gf_2, 2);
    system("pause");
    fillGamefield(gf_1);
    system("pause"); // if you want to create two identical fields - comm this row
    fillGamefield(gf_2);
    system("cls");
    cout << "Your turn!" << endl;
    printGamefield(gf_1, 1);
    printGamefield(gf_3, 2);
}
bool Player_PC_moves(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10]) {
    while (playerTurn(gf_1, gf_2, gf_3)) {
        if (!victoryConditions(gf_1, gf_2)) {
            system("cls");
            cout << "You win!!!" << endl;
            return 1;
        }
         else {
            cout << endl << "Hit again" << endl;
            printGamefield(gf_3, 2);
        }
    }
    printGamefield(gf_3, 2);
    while (pcTurn(gf_1)) {
        if (!victoryConditions(gf_1, gf_2)) {
            system("cls");
            cout << "PC win!!!" << endl;
            return 1;
        }
        else {
            cout << endl << "PC hit again" << endl;
            printGamefield(gf_1, 1);
            printGamefield(gf_3, 3);
        }
    }
    printGamefield(gf_1, 1);
    printGamefield(gf_3, 3);
    return 0;
}
bool playerTurn(char gf_1[10][10], char gf_2[10][10], char gf_3[10][10])
{
    // . - field empty, not hitten
    // * - field empty, hitten
    // K - ship not hitten
    // X - ship hitten
    int x, y;
    cin >> x;
    cout << ' ';
    cin >> y;
    system("cls");
    printGamefield(gf_1, 1);
    if (x < 0 || y < 0 || x > 9 || y > 9) {
        cout << endl << "Wrong coordinates" << endl;
        return 1;
    }
    switch (gf_2[x][y]) {
    case'.':
        gf_2[x][y] = '*';
        gf_3[x][y] = '*';
        cout << endl << "You're missing" << endl;
        return 0;
    case'K':
        gf_2[x][y] = 'X';
        gf_3[x][y] = 'X';
        cout << endl << "You're hitting the ship" << endl;
        return 1;
    case'X':
        cout << endl << "This ship is already beaten" << endl;
        return 1;
    case'*':
        cout << endl << "This position is already beaten" << endl;
        return 1;
    default:
        cout << endl << "Unknown symbol";
        return 0;
    }
}
bool pcTurn(char gf_1[10][10]) {
    system("pause");
    system("cls");
    cout << "PC turn!" << endl;
    list<Point> Point = findPosition_forPC(gf_1);
    int num = giveRand_Number(Point.size());
    for (int i = 0; i < num; i++) Point.pop_front();
    int x = Point.front().givePoint_x();
    int y = Point.front().givePoint_y();
    switch (gf_1[x][y]) {
    case'.':
        gf_1[x][y] = '*';
        cout << endl << "PC's missing" << endl;
        return 0;
    case'K':
        gf_1[x][y] = 'X';
        cout << endl << "PC is hitting" << endl;
        return 1;
    default:
        cout << endl << "Unknown symbol";
        return 0;
    }
}
list<Point> findPosition_forPC(char gf_1[10][10]) {
    list<Point> Pos;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (gf_1[i][j] != '*' && gf_1[i][j] != 'X') {
                Pos.emplace_front(Point(i, j));
            }
        }
    }
    return Pos;
}
void newTurn(char gf_1[10][10], char gf_3[10][10], int numTurn) {
    system("cls");
    cout << numTurn << " move" << endl;
    cout << "Your turn!" << endl;
    printGamefield(gf_1, 1);
    printGamefield(gf_3, 2);
}
bool victoryConditions(char gf_1[10][10], char gf_2[10][10]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (gf_1[i][j] == 'K' && gf_2[i][j] == 'K') return 1;
        }
    }
    return 0;
}