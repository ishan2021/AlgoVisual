#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define ROWS 20
#define COLS 30
#define INF 999999

#define TOP_MARGIN 90
#define BOTTOM_MARGIN 40
#define LEFT_MARGIN 30
#define RIGHT_MARGIN 30

#define FRAME_DELAY_STEP 45
#define FRAME_DELAY_PATH 60

int grid[ROWS][COLS];
int visited[ROWS][COLS];
int distCost[ROWS][COLS];
int prevX[ROWS][COLS];
int prevY[ROWS][COLS];
int pathMask[ROWS][COLS];

void findMinNode(int *mx, int *my)
{
    int minVal = INF;
    *mx = -1;
    *my = -1;

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (!visited[y][x] && grid[y][x] == 0 && distCost[y][x] < minVal)
            {
                minVal = distCost[y][x];
                *mx = x;
                *my = y;
            }
        }
    }
}

void drawState(int currentX, int currentY, int pass, long settled, long relaxations, long updates, int *page)
{
    setactivepage(*page);
    cleardevice();

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(LEFT_MARGIN, 20, (char *)"Dijkstra Visualization");

    char info[196];
    sprintf(info, "Pass: %d   Settled: %ld   Relaxations: %ld   Distance Updates: %ld", pass, settled, relaxations, updates);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(LEFT_MARGIN, 52, info);

    int chartWidth = WINDOW_WIDTH - LEFT_MARGIN - RIGHT_MARGIN;
    int chartHeight = WINDOW_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN;
    int cellWidth = chartWidth / COLS;
    int cellHeight = chartHeight / ROWS;

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            int x1 = LEFT_MARGIN + x * cellWidth;
            int y1 = TOP_MARGIN + y * cellHeight;
            int x2 = x1 + cellWidth - 1;
            int y2 = y1 + cellHeight - 1;

            int color = WHITE;
            if (grid[y][x] == 1)
                color = DARKGRAY;
            else if (pathMask[y][x])
                color = GREEN;
            else if (y == 0 && x == 0)
                color = RED;
            else if (y == ROWS - 1 && x == COLS - 1)
                color = YELLOW;
            else if (x == currentX && y == currentY)
                color = LIGHTMAGENTA;
            else if (visited[y][x])
                color = LIGHTBLUE;
            else if (distCost[y][x] < INF)
                color = CYAN;

            setfillstyle(SOLID_FILL, color);
            bar(x1, y1, x2, y2);

            setcolor(BLACK);
            rectangle(x1, y1, x2, y2);
        }
    }

    setcolor(LIGHTGRAY);
    line(LEFT_MARGIN, TOP_MARGIN + chartHeight, WINDOW_WIDTH - RIGHT_MARGIN, TOP_MARGIN + chartHeight);

    setvisualpage(*page);
    *page = 1 - *page;
}

int main()
{
    int page = 0;
    srand((unsigned int)time(0));

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            grid[y][x] = (rand() % 5 == 0) ? 1 : 0;
            visited[y][x] = 0;
            distCost[y][x] = INF;
            prevX[y][x] = -1;
            prevY[y][x] = -1;
            pathMask[y][x] = 0;
        }
    }

    grid[0][0] = 0;
    grid[ROWS - 1][COLS - 1] = 0;
    distCost[0][0] = 0;

    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Visualization of Dijkstra - C Graphics", 40, 40);
    setbkcolor(BLACK);
    setactivepage(0);
    cleardevice();
    setactivepage(1);
    cleardevice();
    setvisualpage(0);

    long settled = 0;
    long relaxations = 0;
    long updates = 0;

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    for (int step = 1; step <= ROWS * COLS; step++)
    {
        int x, y;
        findMinNode(&x, &y);

        if (x == -1 || y == -1)
            break;

        visited[y][x] = 1;
        settled++;

        drawState(x, y, step, settled, relaxations, updates, &page);
        delay(FRAME_DELAY_STEP);

        if (x == COLS - 1 && y == ROWS - 1)
            break;

        for (int dir = 0; dir < 4; dir++)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && nx < COLS && ny >= 0 && ny < ROWS && grid[ny][nx] == 0 && !visited[ny][nx])
            {
                relaxations++;
                if (distCost[y][x] + 1 < distCost[ny][nx])
                {
                    distCost[ny][nx] = distCost[y][x] + 1;
                    prevX[ny][nx] = x;
                    prevY[ny][nx] = y;
                    updates++;
                }
            }
        }
    }

    int x = COLS - 1;
    int y = ROWS - 1;

    if (distCost[y][x] < INF)
    {
        while (!(x == 0 && y == 0))
        {
            pathMask[y][x] = 1;
            drawState(-1, -1, ROWS * COLS, settled, relaxations, updates, &page);
            delay(FRAME_DELAY_PATH);

            int px = prevX[y][x];
            int py = prevY[y][x];
            if (px == -1 || py == -1)
                break;

            x = px;
            y = py;
        }
        pathMask[0][0] = 1;
    }

    drawState(-1, -1, ROWS * COLS, settled, relaxations, updates, &page);

    setactivepage(page);
    setcolor(WHITE);
    if (distCost[ROWS - 1][COLS - 1] < INF)
        outtextxy(LEFT_MARGIN, WINDOW_HEIGHT - 26, (char *)"Path found. Press any key to close.");
    else
        outtextxy(LEFT_MARGIN, WINDOW_HEIGHT - 26, (char *)"No path found. Press any key to close.");
    setvisualpage(page);

    getch();
    closegraph();
    return 0;
}
