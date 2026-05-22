#include "Location2D.h"
#include <stdio.h>
#include <stack>
#include <deque>
using namespace std;

#define MAZE_SIZE 6

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

char originalMap[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

void resetMap()
{
    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            map[i][j] = originalMap[i][j];
}

bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)
        return false;

    return map[r][c] == '0' || map[r][c] == 'x';
}

void BFS()
{
    resetMap();

    deque<Location2D> locDeque;
    locDeque.push_back(Location2D(1, 0));

    printf("\nBFS(deque) 추가 탐색 ==> ");

    while (!locDeque.empty())
    {
        Location2D here = locDeque.front();
        locDeque.pop_front();

        int r = here.row;
        int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x')
        {
            printf(" 미로 탐색 성공\n");
            return;
        }

        map[r][c] = '.';

        if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
        if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
        if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
        if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
    }

    printf("미로 탐색 실패\n");
}

int main()
{
    int ds_num;

    printf("데이터 구조 라이브러리 선택: 1)stack, 2)deque \n");
    scanf_s("%d", &ds_num);

    switch (ds_num)
    {
    case 1:
    {
        stack<Location2D> locStack;
        locStack.push(Location2D(1, 0));

        printf("DFS(stack) ==> ");

        while (!locStack.empty())
        {
            Location2D here = locStack.top();
            locStack.pop();

            int r = here.row;
            int c = here.col;

            printf("(%d,%d) ", r, c);

            if (map[r][c] == 'x')
            {
                printf(" 미로 탐색 성공\n");
                break;
            }

            map[r][c] = '.';

            if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
        }

        break;
    }

    case 2:
    {
        BFS();
        break;
    }

    default:
        printf("잘못 선택했습니다.\n");
        break;
    }

    BFS();

    return 0;
}