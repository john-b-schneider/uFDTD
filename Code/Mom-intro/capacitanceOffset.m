function [c_mom, an, ratio] = capacitanceOffset(numPerSide,separation)
% capacitanceOffset Calculate the capacitance of square parallel plates
%    using the method of moments.  The top plate is shifted in the
%    xy plane relative to the bottom plate.
%
%  [c_mom, an, ratio]=capacitance(numPerSide,separation)  Returns
%    the capacitance of square parallel plates with unit area that
%    are separated by 'separation' (the separation distance is
%    normalized by the width of a plate).  There are numPerSide^2
%    pulse basis functions per plate.  Also returned are the 'an'
%    vector containing basis-function coefficients and the ratio of
%    the capacitance calculate using MoM to the capacitance given
%    by the standard parallel-plate equation.


% Number of cells per side of the plate.
numPerPlate=numPerSide^2;

del=1/numPerSide;

t0 = cputime;
vm = makeV(1,numPerSide);
zmn = makeZmnOffset(numPerSide,separation);
cputime-t0

an = zmn \ vm;

c_mom = del^2*sum(an((numPerPlate+1):end));

ratio = c_mom/(8.854e-12/separation);

return;