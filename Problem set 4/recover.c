#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

// JPEG signature
BYTE jpeg_signature[] = {0xFF, 0xD8, 0xFF, 0xE0};

// Function to check for the start of a JPEG file
int is_jpeg_start(BYTE buffer[BLOCK_SIZE])
{
    return buffer[0] == jpeg_signature[0] && buffer[1] == jpeg_signature[1] && buffer[2] == jpeg_signature[2] &&
           (buffer[3] & 0xF0) == jpeg_signature[3];
}

int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s forensic_image\n", argv[0]);
        return 1;
    }

    // Open the forensic image file
    FILE *forensic_file = fopen(argv[1], "rb");
    if (forensic_file == NULL)
    {
        fprintf(stderr, "Could not open forensic image file.\n");
        return 1;
    }

    // Buffer to read blocks from the forensic image
    BYTE buffer[BLOCK_SIZE];

    // Counter for naming JPEG files
    int jpeg_count = 0;

    // File pointer for the current JPEG file
    FILE *jpeg_file = NULL;

    // Read the forensic image in blocks
    while (fread(buffer, 1, BLOCK_SIZE, forensic_file) == BLOCK_SIZE)
    {
        // Check for the start of a new JPEG
        if (is_jpeg_start(buffer))
        {
            // If a JPEG file is already open, close it
            if (jpeg_file != NULL)
            {
                fclose(jpeg_file);
            }

            // Create a new JPEG file
            char filename[12]; // Assuming a maximum of 3-digit number and ".jpg"
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg_file = fopen(filename, "wb");

            if (jpeg_file == NULL)
            {
                fprintf(stderr, "Could not create JPEG file.\n");
                fclose(forensic_file);
                return 1;
            }

            // Increment the JPEG file counter
            jpeg_count++;
        }

        // If a JPEG file is open, write the block to it
        if (jpeg_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg_file);
        }
    }

    // Close the last JPEG file
    if (jpeg_file != NULL)
    {
        fclose(jpeg_file);
    }

    // Close the forensic image file
    fclose(forensic_file);

    return 0;
}