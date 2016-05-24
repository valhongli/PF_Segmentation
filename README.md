# PF_Segmentation

Efficient Graph-Based Image Segmentation 
Pedro F. Felzenszwalb and Daniel P. Huttenlocher 
International Journal of Computer Vision, Volume 59, Number 2, September 2004 
http://people.cs.uchicago.edu/~pff/segment/

These two folders are codes for visual studio 2015 solution and matlab mex, respectively.

## 1. 
In folder VisualStudio, Debug and Release are 32 bit files, x64 are 64 bit files.
Use: under windows command line, run EGSeg.exe sigma k min_z input output
Here, input must be ppm image file (contains one example file) and output also must be ppm file.
For example, you can try this one: EGSeg.exe 0.5 1000 20 emir.ppm out.ppm.
Then, you can get the segmented result out.ppm image.

## 2.
In folder Matlab_C++, you can simply run demo.m to compile the c++ file and get and segmentation.

Have fun!!!
