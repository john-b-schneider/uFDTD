function [i, j] = m2ij(m,numPerSide)
% M2IJK Convert the global index m to the positional
%   indices i and j.
%
%   [i, j] = m2ij(m,numPerSide) where m is the global index
%   and numPerSide is the number of elements along one side of
%   the plate.

j = floor((m-1)/numPerSide) + 1;

i = m - numPerSide*(j-1);

return;
