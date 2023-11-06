#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit); // Updated function prototype
void decToBinary(int n, int binaryArray[]);

int main(void)
{
    // Input a string and store it in an array called charArray
    string input = get_string("Enter string: ");
    int length = strlen(input);

    char charArray[length + 1];
    strcpy(charArray, input);

    // For every character, find the ASCII value and store it in asciiArray
    int asciiArray[length + 1];
    for (int i = 0; i < length; i++)
    {
        asciiArray[i] = (int) charArray[i];
    }

    // For every ASCII value, convert to binary and store it in binaryArray
    int binaryArray[length + 1][9]; // 9 elements to store 8 bits + a sentinel -1

    for (int i = 0; i < length; i++)
    {
        decToBinary(asciiArray[i], binaryArray[i]);
        for (int j = 0; j < 8; j++)
        {
            print_bulb(binaryArray[i][j]);
        }
        printf("\n");
    }
}

// FUNCTIONS

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void decToBinary(int n, int binaryArray[])
{
    // Ensure the binary representation is 8 bits by padding with leading zeros
    for (int i = 0; i < 8; i++)
    {
        binaryArray[i] = (n >> (7 - i)) & 1; // Get the i-th bit from the left
    }
}