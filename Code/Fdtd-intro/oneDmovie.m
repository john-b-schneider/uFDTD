function reel = oneDmovie(basename,y_min,y_max)
% oneDmovie Create a movie from data file with a common base
%    name which contain 1D data.
%
% basename = common base name of all files
% y_min    = minimum value used for all frames
% y_max    = maximum value used for all frames
%
% reel = movie which can be played with a command such as:
%          movie(reel,10)
%    This would play the movie 10 times.  To control the frame
%    rate, add a third argument specifying the desired rate.

% open the first frame (i.e., first data file).
frame=1;
filename = sprintf('%s.%d',basename,frame);
fid = fopen(filename,'rt');

% to work around rendering bug under Mac OS X see:
% <www.mathworks.com/support/solutions/
%  data/1-VW0GM.html?solution=1-VW0GM>
figure; set(gcf,'Renderer', 'zbuffer');

% provided fid is not -1, there is another file to process
while fid ~= -1
  data=fscanf(fid,'%f');    % read the data
  plot(data)                % plot the data
  axis([0 length(data) y_min y_max]) % scale appropriately
  reel(frame) = getframe;   % capture the frame for the movie

  % construct the next file name and try to open it
  frame=frame+1;
  filename = sprintf('%s.%d',basename,frame);
  fid = fopen(filename,'rb');
end


