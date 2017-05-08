pkg load image;

m = imread('IMG_0315.JPG');
imshow(m(:,:,2))
line([100 100], [100 200],'color','r')
m2 = m(100:300, 200:500, :)
imshow(m2)

function r = scale(k, image)
	r = image .* k;
endfunction

imshow(scale(0.5, m))
%plot(m(100, :))
%g = rgb2gray(m);
%imshow(g)
