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
#define FRAME_DELAY_SWAP 55

void drawBars(int arr[], int n, int currentA, int currentB, int sortedFrom, int pass, long comparisons, long swaps, int *page)
{
    setactivepage(*page);
    cleardevice();

    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(LEFT_MARGIN, 20, (char *)"Bubble Sort Visualization");

    char info[128];
    sprintf(info, "Pass: %d   Comparisons: %ld   Swaps: %ld", pass, comparisons, swaps);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(LEFT_MARGIN, 52, info);

    int chartWidth = WINDOW_WIDTH - LEFT_MARGIN - RIGHT_MARGIN;
    int chartHeight = WINDOW_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN;
    int barWidth = chartWidth / n;
    if (barWidth < 2)
        barWidth = 2;

    for (int i = 0; i < n; i++)
    {
        int x1 = LEFT_MARGIN + i * barWidth;
        int x2 = x1 + barWidth - 1;
        if (x2 <= x1)
            x2 = x1 + 1;

        int barHeight = (arr[i] * chartHeight) / MAX_VALUE;
        int y1 = TOP_MARGIN + (chartHeight - barHeight);
        int y2 = TOP_MARGIN + chartHeight;

        if (i >= sortedFrom)
            setfillstyle(SOLID_FILL, GREEN);
        else if (i == currentA || i == currentB)
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

void bubbleSortVisual(int arr[], int n, int *page)
{
    long comparisons = 0;
    long swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int swappedThisPass = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            drawBars(arr, n, j, j + 1, n - i, i + 1, comparisons, swaps, page);
            delay(FRAME_DELAY_COMPARE);

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swaps++;
                swappedThisPass = 1;

                drawBars(arr, n, j, j + 1, n - i, i + 1, comparisons, swaps, page);
                delay(FRAME_DELAY_SWAP);
            }
        }

        if (!swappedThisPass)
            break;
    }

    drawBars(arr, n, -1, -1, 0, n - 1, comparisons, swaps, page);
}

int main()
{
    int arr[ARRAY_SIZE];
    int page = 0;

    srand((unsigned int)time(0));
    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = 20 + rand() % (MAX_VALUE - 20);

    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Visualization of Bubble Sort - C Graphics", 40, 40);
    setbkcolor(BLACK);
    setactivepage(0);
    cleardevice();
    setactivepage(1);
    cleardevice();
    setvisualpage(0);

    bubbleSortVisual(arr, ARRAY_SIZE, &page);

    setactivepage(page);
    setcolor(WHITE);
    outtextxy(LEFT_MARGIN, WINDOW_HEIGHT - 35, (char *)"Sorting complete. Press any key to close.");
    setvisualpage(page);

    getch();
    closegraph();
    return 0;
}