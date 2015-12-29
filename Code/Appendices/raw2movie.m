function reel = raw2movie(basename,z_norm,decades)
% raw2movie Creates a movie from "raw" files with a common base
%      name. 
%
% The absolute value of the data is used together with
% logarithmic scaling.  The user may specify one, two, or
% three arguments.
% raw2movie(basename,z_norm,decades) or
% raw2movie(basename,z_norm) or
% raw2movie(basename):
% basename = common base name for all files
% z_norm   = value used to normalize all frames, typically this
%         would be the maximum value for all the frames.
%         Default value is 1.
% decades  = decades to be used in the display.  The normalized
%         data is assumed to vary between 1.0 and 10^(-decades)
%         so that after taking the log (base 10), the values
%         vary between 0 and -decades.  Default value is 3.
%
% return value:
% reel = movie which can be played with a command such as:
%          movie(reel,10)
%        pcolor() is used to generate the frames.
%
% raw file format:
% The raw files are assumed to consist of all floats (in
% binary format).  The first two elements specify the horizontal
% and vertical dimensions.  Then the data itself is given in
% English book-reading order, i.e., from the upper left corner
% of the image and then scanned left to right.  The frame number
% is assumed to start at zero.

% set defaults if we have less than three arguments
if nargin < 3, decades=3; end
if nargin < 2, z_norm=1.0; end

% open the first frame
frame=0;
filename = sprintf('%s.%d',basename,frame);
fid = fopen(filename,'rb');

if fid == -1
  error(['raw2movie: initial frame not found: ',filename])
end

% to work around rendering bug under Mac OS X implementation.
figure; set(gcf,'Renderer', 'zbuffer');

% provided fid is not -1, there is another file to process
while fid ~= -1
  size_x = fread(fid,1,'single');
  size_y = fread(fid,1,'single');

  data = flipud(transpose(...
           reshape(...
             fread(fid,size_x*size_y,'single'),size_x,size_y)...
	 ));

  % plot the data
  if decades ~= 0
    pcolor(log10(abs((data+realmin)/z_norm)))
    shading flat; axis equal;
    axis([1 size_x 1 size_y]); caxis([-decades 0]); colorbar
  else
    pcolor(abs((data+realmin)/z_norm))
    shading flat; axis equal;
    axis([1 size_x 1 size_y]); caxis([0 1]); colorbar
  end
  
  % capture the frame for the movie (Matlab wants index to start
  % at 1, not zero, hence the addition of one to the frame)
  reel(frame+1) = getframe;

  % construct the next file name and try to open it
  frame=frame+1;
  filename = sprintf('%s.%d',basename,frame);
  fid = fopen(filename,'rb');

end
