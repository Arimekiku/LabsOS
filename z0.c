#include <stdio.h>
#include <math.h>
#include <malloc.h>

struct Vector2
{
    float x;
    float y;
};

struct point
{
    int mass;
    int pos;
    struct Vector2 coord;
};

struct point closerPointToAnotherPoint(struct point point1, struct point *points, int n)
{
    struct point closerPoint;
    int i;
    float dist = 10000000;

    for (i = 1; i < n; i++)
    {
        float curDist = sqrt(pow(point1.coord.x - points[i].coord.x, 2) + pow(point1.coord.y - points[i].coord.y, 2));

        if (curDist < dist)
        {
            dist = curDist;
            closerPoint = points[i];
        }
    }

    return closerPoint;
}

int main()
{
    int i, n, j;

    printf("Enter number of points: ");
    scanf("%d", &n);

    struct point points[100000];

    for (i = 0; i < n; i++)
    {
        float x, y;
        int mass;

        printf("\nEnter X-coordinate of %d point: ", i + 1);
        scanf("%f", &x);
        printf("Enter Y-coordinate of %d point: ", i + 1);
        scanf("%f", &y);
        printf("Enter mass of %d point: ", i + 1);
        scanf("%d", &mass);

        points[i].coord.x = x;
        points[i].coord.y = y;
        points[i].mass = mass;
        points[i].pos = i;
    }

    int numb = n - 1;

    for (i = 0; i < numb; i++)
    {
        struct point pointToDelete = closerPointToAnotherPoint(points[0], points, n);
        points[0].mass += pointToDelete.mass;

        for (j = pointToDelete.pos; j < n - 1; j++)
        {
            points[j] = points[j + 1];
            points[j].pos = j;
        }

        n--;
    }

    printf("\nMass of your point: %d", points[0].mass);
}