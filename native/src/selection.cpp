#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define ARRAY_SIZE 60
#define MAX_VALUE 500
#define TOP_MARGIN 80
#define BOTTOM_MARGIN 60
#define LEFT_MARGIN 40
#define RIGHT_MARGIN 40
#define FRAME_DELAY_COMPARE 35
#define FRAME_DELAY_SWAP 60

void drawBars(int arr[], int n, int iIndex, int jIndex, int minIndex, int sortedUpto, int pass, long comparisons, long swaps, int *page)
{
    setactivepage(*page);
    cleardevice();

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(LEFT_MARGIN, 20, (char *)"Selection Sort Visualization");

    char info[160];
    sprintf(info, "Pass: %d   Comparisons: %ld   Swaps: %ld", pass, comparisons, swaps);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(LEFT_MARGIN, 52, info);

    int chartWidth = WINDOW_WIDTH - LEFT_MARGIN - RIGHT_MARGIN;
    int chartHeight = WINDOW_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN;
    int barWidth = chartWidth / n;
    if (barWidth < 2)
        barWidth = 2;

    for (int k = 0; k < n; k++)
    {
        int x1 = LEFT_MARGIN + k * barWidth;
        int x2 = x1 + barWidth - 1;
        if (x2 <= x1)
            x2 = x1 + 1;

        int barHeight = (arr[k] * chartHeight) / MAX_VALUE;
        int y1 = TOP_MARGIN + (chartHeight - barHeight);
        int y2 = TOP_MARGIN + chartHeight;

        if (k <= sortedUpto)
            setfillstyle(SOLID_FILL, GREEN);
        else if (k == minIndex)
            setfillstyle(SOLID_FILL, YELLOW);
        else if (k == iIndex || k == jIndex)
            setfillstyle(SOLID_FILL, RED);
        else
            setfillstyle(SOLID_FILL, CYAN);

        bar(x1, y1, x2, y2);
    }

    setcolor(LIGHTGRAY);
    line(LEFT_MARGIN, TOP_MARGIN + chartHeight, WINDOW_WIDTH - RIGHT_MARGIN, TOP_MARGIN + chartHeight);

    setvisualpage(*page);
    *page = 1 - *page;
}

void selectionSortVisual(int arr[], int n, int *page)
{
    long comparisons = 0;
    long swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        drawBars(arr, n, i, -1, minIndex, i - 1, i + 1, comparisons, swaps, page);
        delay(FRAME_DELAY_COMPARE);

        for (int j = i + 1; j < n; j++)
        {
            comparisons++;
            drawBars(arr, n, i, j, minIndex, i - 1, i + 1, comparisons, swaps, page);
            delay(FRAME_DELAY_COMPARE);

            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
                drawBars(arr, n, i, j, minIndex, i - 1, i + 1, comparisons, swaps, page);
                delay(FRAME_DELAY_COMPARE);
            }
        }

        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            swaps++;

            drawBars(arr, n, i, minIndex, minIndex, i, i + 1, comparisons, swaps, page);
            delay(FRAME_DELAY_SWAP);
        }
        else
        {
            drawBars(arr, n, i, -1, minIndex, i, i + 1, comparisons, swaps, page);
            delay(FRAME_DELAY_COMPARE);
        }
    }

    drawBars(arr, n, -1, -1, -1, n - 1, n - 1, comparisons, swaps, page);
}

int main()
{
    int arr[ARRAY_SIZE];
    int page = 0;

    srand((unsigned int)time(0));
    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = 20 + rand() % (MAX_VALUE - 20);

    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Visualization of Selection Sort - C Graphics", 40, 40);
    setbkcolor(BLACK);
    setactivepage(0);
    cleardevice();
    setactivepage(1);
    cleardevice();
    setvisualpage(0);

    selectionSortVisual(arr, ARRAY_SIZE, &page);

    setactivepage(page);
    setcolor(WHITE);
    outtextxy(LEFT_MARGIN, WINDOW_HEIGHT - 35, (char *)"Sorting complete. Press any key to close.");
    setvisualpage(page);

    getch();
    closegraph();
    return 0;
}
