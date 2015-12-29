function [c_mom, an, ratio] = capacitance(numPerSide,separation)
% capacitance Calculate the capacitance of square parallel plates
%    using the method of moments.
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

del=1/numPerSide;  % width of a single cell

t0 = cputime;  % time the following operations
% create forcing function (unit voltage on top plate)
vm  = makeV(1,numPerSide);  
% calculate the Zmn matrix
zmn = makeZmn(numPerSide,separation);
% report how long it took to do the previous two operations 
cputime-t0  

% solve for the basis-function coefficients
an = zmn \ vm;

% calculate the capacitance by finding the total charge on the
% upper plate
c_mom = del^2*sum(an((numPerPlate+1):end));

% ratio of MoM capacitance to the capacitance formula derived by
% ignoring the fringing field
ratio = c_mom/(8.854e-12/separation);

return;