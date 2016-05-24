/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"

#ifdef MEX
#include "mex.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  if (nrhs != 4 || nlhs != 1) {
	mexErrMsgTxt("usage: segs = segment(img,sigma, k, min)\n");
  }
  
  if (mxGetClassID(prhs[0]) != mxUINT8_CLASS || mxGetNumberOfDimensions(prhs[0]) != 3) {
    mexErrMsgTxt("'img' should be a 3D array of type UINT8.");  
  }

  float sigma = mxGetScalar(prhs[1]);
  float k = mxGetScalar(prhs[2]);
  int   min_size = mxGetScalar(prhs[3]);
  
  const mwSize *d = mxGetDimensions(prhs[0]);
  int h = d[0];
  int w = d[1];
  unsigned char *ptr = (unsigned char*)mxGetPr(prhs[0]);
  	
  printf("%dx%d image.\n", w, h); 
  image<rgb> input(w, h, false);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
    	input.access[y][x].r = ptr[x * h + y            ];
    	input.access[y][x].g = ptr[x * h + y + w * h    ];
    	input.access[y][x].b = ptr[x * h + y + w * h * 2];    	
    }
  }
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(&input, sigma, k, min_size, &num_ccs); 
  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");
  
  mwSize dim[3];
  dim[0] = seg->height();
  dim[1] = seg->width();
  dim[2] = 3;
  plhs[0] = mxCreateNumericArray(3, dim, mxUINT8_CLASS, mxREAL);
  ptr = (unsigned char*)mxGetPr(plhs[0]);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {    
    	ptr[x * h + y            ] = seg->access[y][x].r;
    	ptr[x * h + y + w * h    ] = seg->access[y][x].g;
    	ptr[x * h + y + w * h * 2] = seg->access[y][x].b;    	
    }
  }
}

#else

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
    return 1;
  }
  
  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);
	
  printf("loading input image.\n");
  image<rgb> *input = loadPPM(argv[4]);
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  savePPM(seg, argv[5]);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;
}

#endif
