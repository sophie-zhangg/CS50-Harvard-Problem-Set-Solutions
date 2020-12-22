#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//defines a byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // read in 512 byte chunks
    FILE *f = fopen(argv[1], "r");
    FILE *img;
    //checks if there is a forensic image
    if (argc != 2)
    {
        printf("Usage: recover [name of a forensic image]\n");
        return 1;
    }
    //create 512 size buffer array
    BYTE buffer[512];
    int file_count = 0;
    char filename[8];
    while (fread(buffer, 512, 1, f) == 1)
    {
        //checks if there is jpg in the buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer [2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close the previous image if there is one
            if (file_count > 0)
            {
                fclose(img);
            }
            //assign the jpg file name
            sprintf(filename, "%03i.jpg", file_count);
            //open a file w/ the file name
            img = fopen(filename, "w");
            //write in that file the image from the forensic
            fwrite(buffer, 512, 1, img);
            //add another file to the counter
            file_count++;
        }
        //if image is continued from the last buffer continue writing to the same array
        else if (file_count > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    //closes open files
    fclose(img);
    fclose(f);
    //success!!
    return 0;

}
