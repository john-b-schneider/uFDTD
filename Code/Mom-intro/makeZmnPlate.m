function zmn = makeZmnPlate(numPerSide)
% makeZmnPlate  Make the Zmn matrix for a square plate.
%
% zmn = makeZmnPlate(numPerSide) Creates the Zmn matrix for a
%    square plate where each basis function is a square pulse.
%    The area of the basis functions is (1/numPerSide)^2, i.e.,
%    the plate is assumed to have unit area and is divided into
%    numPerSide^2 square cells.

del  = 1/numPerSide;        % length of the side of a cell
del2 = del^2;               % area of a cell
numPerPlate = numPerSide^2; % total number of elements on a plate

% Place self term (exact Zmm term) along diagonal of matrix.
zmn = diag(...
    repmat(2.0*del*log((sqrt(2)+1)/(sqrt(2)-1)),numPerPlate,1)...
    );

% Calculate the off-diagonal terms.
for m=1:numPerPlate
  [i j] = m2ij(m,numPerSide);       % observation point
  for n=m+1:numPerPlate
    [ip jp]  = m2ij(n,numPerSide);  % source point
    zmn(m,n) = del/sqrt((i-ip)^2 + (j-jp)^2);
    zmn(n,m) = zmn(m,n);  % exploit symmetry to fill lower half
  end
end

return;
