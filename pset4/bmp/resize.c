// Jordan Trevino
// starting from copy.c

/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale-factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // get factor to scale
    int n = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine new bfSize
    bf.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + (n * (bf.bfSize - sizeof(BITMAPFILEHEADER)) - sizeof(BITMAPINFOHEADER));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // change bitmapinfoheader info to scale
    bi.biSizeImage = bi.biSizeImage * n;
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding_in =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) / n) % 4) % 4;
    int padding_out =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

      // Iterate n times

      for (int x = 0; x < n; x++)
      {
          // iterate over pixels in scanline
          for (int j = 0; j < bi.biWidth / n; j++)
          {
              // temporary storage
              RGBTRIPLE triple;
              // read RGB triple from infile
              fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
              // write RGB triple to outfile many times depending on n
              for(int y = 0; y < n; y++)
              {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
              }
          }
        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding_out; k++)
        {
          fputc(0x00, outptr);
        }
      }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
