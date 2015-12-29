function zmn = makeZmn(numPerSide,separation)
% makeZmn  Make the impedance matrix for the plates.
%
% zmn = makeZmn(numPerSide) Creates the impedance matrix for two
%    square plates where each basis function is a square pulse.  The
%    area of the basis function is (1/numPerSide)^2, i.e., each plate
%    is assumed to have unit area and is divided into numPerSide^2
%    square segments.  The plates are separated by 'separation' units.

del  = 1/numPerSide;        % length of the side of a segment
del2 = del^2;     
numPerPlate = numPerSide^2; % total number of elements on a plate

% Self term (exact).
self  =  2.0 * del * log((sqrt(2)+1)/(sqrt(2)-1));

zmn=zeros(2*numPerPlate);

% Since symmetric, only compute values for upper half of matrix.
% First, fill in diagonal terms.
for m=1:2*numPerPlate
  zmn(m,m) = self;
end
% Calculate off-diagonal terms in upper half.
for m=1:2*numPerPlate
  for n=m+1:2*numPerPlate
    [i j k]    = mtoijk(m,numPerSide);  % observation point
    [ip jp kp] = mtoijk(n,numPerSide);  % source point
    zmn(m,n)   = del2/...
	sqrt(((i-ip)^2 + (j-jp)^2)*del2 + (separation*(k-kp))^2);
  end
end

% Fill in lower half -- things are symmetric since all elements the
% same size.
for m=1:2*numPerPlate
  for n=m+1:2*numPerPlate
    zmn(n,m) = zmn(m,n);
  end
end

return;
