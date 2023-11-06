#include <cs50.h>
#include <stdio.h>

void half_pyramid(int n);

int main(void)
{
    int height;

    // Prompt the user for the height of the pyramid
    do
    {
        height = get_int("Enter the height of the pyramid (1-8): ");
    }
    while (height < 1 || height > 8);

    half_pyramid(height);
}

void half_pyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int spaces = n - i; spaces > 0; spaces--)
        {
            printf(" ");
        }

        for (int hashes = 1; hashes <= i; hashes++)
        {
            printf("#");
        }

        printf("\n");
    }
}
