function [i, j, k] = mtoijk(m,numPerSide)
% MTOIJK Convert the global index to the local indices.
%
%   [i, j, k] = mtoijk(m,numPerSide) where m is the global index
%   and numPerSide is the number of elements along one side of the
%   plate.

numPerPlate = numPerSide^2;  % total number of segments per plate

k = floor((m-1)/(numPerPlate)) + 1;

m = m - numPerPlate*(k-1);

j = floor((m-1)/numPerSide) + 1;

i = mod(m-1,numPerSide) + 1;

return;
