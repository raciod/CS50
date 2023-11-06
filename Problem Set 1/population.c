#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Enter starting population (must be >= 9): ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("Enter ending population (must be >= starting population): ");
    }
    while (end_size < start_size);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (start_size < end_size)
    {
        int births = start_size / 3;
        int deaths = start_size / 4;
        start_size = start_size + births - deaths;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);

    return 0;
}
