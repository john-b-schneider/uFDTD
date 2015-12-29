function v = makeV(voltage,numPerSide)
% makeV  Make the voltage vector for a pair of square plates.
%
% V=makeV(voltage,numPerSide)  Returns the vector V for two plates with
%    numPerSide^2 elements per plate.  The voltage on the bottom
%    plate is zero while the voltage on the upper plate is 'voltage'.

numPerPlate = numPerSide^2;

v = [repmat(0,numPerPlate,1)' ...
     repmat(voltage * 4.0 * pi * 8.854e-12,numPerPlate,1)']';

return;
