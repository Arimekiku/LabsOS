#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

float middle(float *arr)
{
    int i, length = sizeof(arr) / sizeof(arr[0]);
    float sum = 0;

    for (i = 0; i < length; i++)
    {
        sum += arr[i];
    }

    return sum / length;
}

int main()
{
    srand(time(0));

    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    float *arr = malloc(n);
    int i;

    printf("Generated array: ");

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 11 - 5;
        printf("%.2f ", arr[i]);
    }

    float middleValue = middle(arr);
    int count = 0, check = 0;
    float sum = 0;

    for (i = 0; i < n; i++)
    {
        if (middleValue < arr[i])
        {
            count += 1;
        }

        if (check == 1)
        {
            sum += fabs(arr[i]);
        }

        if (arr[i] < 0)
        {
            check = 1;
        }
    }

    printf("\n\nNumber of values greater than middle value: %d", count);
    printf("\nSum of abs values located after first negative element in array: %.2f", sum);
}