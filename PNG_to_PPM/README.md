# PNG to PPM

A program I have written to get familiar with pnm formats and image manipulation. This can be thought as an improvement to the BITMAP_to_ASCII experiment. Unlike that experiment this experiment can create ASCII art of pngs.

After this experiment I have written Image_Manipulator, which a much better structured program capable of greater things.

## This Program Can:
 -  Turn PNGs into PPM files. (using NETPBM)
 -  Read PPM files
 -  Grayscale read PPMs with average model or luminosity model
 -  Turn read PPM files into ASCII art and save as TXT files.
 -  Save read PPMs as PPMs.
 -  Turn PPMs into PNGs. (using NETPBM)

## Requierements to run

  -  Windows

## Program flow
  
1. Asks for the name of the png file to open.
    - Turns file into a ppm file using pngtopnm from NETPBM.
    - Reads the ppm file and saves the file as a variable of struct PNM.
2. Asks if the user wants to use grayscaling (either average model or luminosity model)
    - Should grayscaling be chosen, all values for each pixel are set to be same. e.g: for average model, a pixel with (R, G, B)=(60, 0, 0) would be set as (R, G, B)=(20, 20, 20).
3. Asks the user which ASCII gradient to use
    - a text file with name ASCII.txt is created and for each pixel's R value a char from the gradient is chosen and pushed to ASCII.txt.
4. The result after grayscaling is saved as a ppm file and then pnmtopng from NETPBM is called.
5. Asks if the user wants to start over.
