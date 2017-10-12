#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAUSE() system("PAUSE");
void main () {
  int pix_x=300,pix_y=300;    // image dimns in pixels
  int image[pix_x][pix_y][3]; // first [] number here is total pixels of each color in
                              // my image, 3 is for //RGB values
  FILE *streamIn;
  FILE *num_img;//separate files for R,G and B components

  //opening 24bit image
  streamIn = fopen("BMP.bmp", "r"); // a bigger star in black and a smaller
                                          // star in blue (refer figure attached)
  num_img= fopen("pixels.txt","w");

  int byte;
  int i,j;
  for(i=0;i<54;i++) {
    byte = fgetc(streamIn);  // strip out BMP header-> for //24bit bmp image
  }

  // initiating with new "i" different from above

  for(i=0;i<pix_y;i++) {
    for(j=0;j<pix_x;j++) {
      image[i][j][2] = fgetc(streamIn);  // use BMP 24bit with no alpha channel
      image[i][j][1] = fgetc(streamIn);  // BMP uses BGR but we want RGB, grab //byte-by-byte
      image[i][j][0] = fgetc(streamIn);  // reverse-order array indexing fixes //RGB issue...
      // printing R, G and B components separately in a .txt format
      if ((j+1)==pix_x) {
        // incorporating nextline ('\n') to ensure alignment for edge pixels
        fprintf(num_img,"(%d ,%d ,%d  )\n",image[i][j][0],image[i][j][1],image[i][j][2]); // print R component
      }
      else {
        // for inner pixels, nextline(\n) not required
        fprintf(num_img,"(%d ,%d ,%d  )",image[i][j][0],image[i][j][1],image[i][j][2]); // R component
      }
    }
  }
}
