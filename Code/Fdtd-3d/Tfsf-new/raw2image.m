function raw2image(filename,z_norm,decades,cmap)
% raw2movie Creates a plot from a "raw" file.
%
% The absolute value of the data is used together with logarithmic
% scaling.  The user may specify one, two, or three arguments.
% raw2movie(filename,z_norm,decades,cmap) or
% raw2movie(filename,z_norm) or
% raw2movie(filename).
%
% filename = name of data file
% z_norm   = value used to normalize data, typically this
%            would be the maximum value.
%            Default value is 1.
% decades  = decades to be used in the display.  The normalized
%            data is assumed to vary between 1.0 and 10^(-decades)
%            so that after taking the log (base 10), the values
%            vary between 0 and -decades.  Default value is 3.
% cmap     = colormap to apply.
%
% raw file format:
% Raw files are assumed to consist of all floats (in binary
% format).  The first two elements specify the horizontal and vertical
% dimensions.  Then the data itself is given in English book-reading
% order, i.e., from the upper left corner of the image and then
% scanned left to right.

% set defaults if we have less than three arguments
if nargin < 4, cmap=jet(128); end
if nargin < 3, decades=3; end
if nargin < 2, z_norm=1.0; end

% open the first frame
fid = fopen(filename,'rb');
if fid == -1
  error(['raw2image: could not open data file ',filename])
end

% determine image size
size_x = fread(fid,1,'single');
size_y = fread(fid,1,'single');

% read data
data = flipud(transpose(...
    reshape(fread(fid,size_x*size_y,'single'),size_x,size_y)...
    ));

% plot the data
if decades ~= 0
  pcolor(log10(abs((data+realmin)/z_norm)))
  shading flat;
  axis equal;
  axis([1 size_x 1 size_y]);   
  caxis([-decades 0]);
  colormap(cmap);
%  colorbar
else
  pcolor(abs((data+realmin)/z_norm))
  shading flat;
  axis equal;
  axis([1 size_x 1 size_y]);   
  caxis([0 1]);
  colormap(cmap);
%  colorbar
end  
  
return;
