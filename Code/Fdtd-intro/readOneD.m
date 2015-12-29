function z = readOneD(basename)
%readOneD(BASENAME) Read 1D data from a series of frames.
%  [Z,dataLength,nFrames] = readOneD(BASENAME) Data
%  is read from a series of data files all which have 
%  the common base name given by the string BASENAME, 
%  then a dot, then a frame index (generally starting
%  with zero).  Each frame corresponds to one row of Z.

% read the first frame and establish length of data
nFrames=0;
filename = sprintf('%s.%d',basename,nFrames);
nFrames=nFrames+1;
if exist(filename,'file')
  z = dlmread(filename,'\n');
  dataLength = length(z);
else
  return;
end

% loop through other frames and break out of loop
% when next frame does not exist
while 1
  filename = sprintf('%s.%d',basename,nFrames);
  nFrames=nFrames+1;
  if exist(filename,'file')
    zTmp = dlmread(filename,'\n');
    if length(zTmp) ~= dataLength  % check length matches
      error('Frames have different sizes.')
      break;
    end
    z = [z zTmp]; % append new data to z 
  else
    break;
  end
end

% reshape z to appropriate dimensions
z = reshape(z,dataLength,nFrames-1);
z=z';

return;
