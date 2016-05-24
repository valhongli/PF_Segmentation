
if ~exist('pfsegment', 'file')
    mex -DMEX pfsegment.cpp
end

imgSrc = imread('emir.ppm');
figure;
subplot(1,2,1);imshow(imgSrc,[]);title('Source image');

sigma = 0.5;
k = 1000;
mim_z = 20;

segs = pfsegment(a,sigma,k,mim_z);
subplot(1,2,2);imshow(segs,[]);title('Segmentation result');
