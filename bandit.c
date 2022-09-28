#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int hasNumber(int number, int *arr)
{
    int count = 0, i;

    for (i = 0; i < sizeof(arr) / sizeof(arr[0]) + 1; i++)
    {
        if (arr[i] == number)
            count += 1;
    }

    return count;
}

void main()
{
    srand(time(0));

    int balance = 10000, bid = 1000, choice, i;

    printf(" YOUR BALANCE: %d\n\n", balance);
    while (1)
    {
        printf(" 1)Play\n 2)Change bid\n 3)Combinations\n 4)Quit\n\n CURRENT BID: %d\n\n MAKE A CHOICE: ", bid);

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            int combination[3];

            int multiplier = 1;
            balance -= bid;

            for (i = 0; i < 3; i++)
            {
                combination[i] = rand() % 8;
                printf(" %d ", combination[i]);
            }

            if ((hasNumber(5, combination) == 1 || hasNumber(7, combination) == 1) || (combination[2] == combination[1] && combination[1] == combination[0]))
            {
                multiplier = 2;
            }

            if (hasNumber(5, combination) == 2 || hasNumber(7, combination) == 2)
            {
                multiplier = 4;
            }

            if (hasNumber(5, combination) == 3)
            {
                multiplier = 55;
            }

            if (hasNumber(6, combination) == 3)
            {
                balance /= 2;
                printf("\n YOU LOST %d POINTS!!!\n\n", balance);

                break;
            }

            if (hasNumber(7, combination) == 3)
            {
                printf("\n YOU WIN!!!\n");
                exit(1);
            }

            if (multiplier == 1)
            {
                printf("\n TRY AGAIN!!!\n\n");
            }
            else
            {
                printf("\n YOU WON %d POINTS!!!\n\n", bid * multiplier);
                balance += bid * multiplier;
            }

            printf(" CURRENT BALANCE: %d\n\n", balance);
            break;
        case 2:
            printf("\n NEW BID: ");
            scanf("%d", &bid);
            printf("\n YOUR NEW BID: %d\n\n", bid);
            break;
        case 3:
            printf("\n MULTIPLIER X2: 000 111 222 333 444\n MULTIPLIER X2: 5XX 7XX\n MULTIPLIER X4: 55X 77X\n MULTIPLIER X55: 555\n PENALTY: 666\n JACKPOT: 777\n\n");
            break;
        case 4:
            exit(0);
        default:
            printf("\n Wrong command. Try again!\n\n");
            break;
        }

        if (balance == 0)
        {
            printf("\n YOU LOSE!!!\n");
            exit(-1);
        }
    }
}
