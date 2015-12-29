function zmn = makeZmnSymmetry(halfNumPerSide)
% makeZmnSymmetry  Make the impedance matrix for a square plate
%    exploiting four-fold symmetry.
%
% ZMN = makeZmnSymmetry(halfNumPerSide) Creates the Zmn matrix
% for a square plate where each basis function is a square pulse.
% The area of each basis function is (1/(2*halfNumPerSide))^2,
% i.e., the plate is assumed to have unit area and is divided
% into (2*halfNumPerSide)^2 square segments.

numPerSide = 2*halfNumPerSide;
del        = 1/numPerSide;  % width of a basis function
del2       = del^2;
% total number of basis functions
numPerQuadrant = halfNumPerSide^2;

% Contribution to self term for a the cell in first quadrant.
self  =  2.0 * del * log((sqrt(2)+1)/(sqrt(2)-1));

% Fill in matrix with m and n ranging over upper half of matrix.
for m=1:numPerQuadrant
  [i j]    = m2ij(m,halfNumPerSide);   % observation point
  for n=m:numPerQuadrant
    [ip jp]  = m2ij(n,halfNumPerSide); % source point
    % calculate individual terms which are common to different
    % distance calculations
    xdiff1_2 = (i-ip)^2*del2;  
    xdiff2_2 = ((i+ip-1)*del - 1)^2;
    ydiff1_2 = (j-jp)^2*del2;
    ydiff2_2 = ((j+jp-1)*del - 1)^2;
    % calculate distances between observation point and
    % sources.
    rmn1 = sqrt(xdiff1_2 + ydiff1_2);
    rmn2 = sqrt(xdiff1_2 + ydiff2_2);
    rmn3 = sqrt(xdiff2_2 + ydiff2_2);
    rmn4 = sqrt(xdiff2_2 + ydiff1_2);
    if (m==n)
      zmn(m,n) = self + del2*(1/rmn2+1/rmn3+1/rmn4);
    else
      zmn(m,n) = del2*(1/rmn1+1/rmn2+1/rmn3+1/rmn4);
      % exploit symmetry to fill in lower half
      zmn(n,m) = zmn(m,n);
    end
  end
end

return;
