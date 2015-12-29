function v = makeVPlate(voltage,numPerSide)
% makeVPlate  Make the voltage vector for a square plate.
%
% V=makeVPlate(voltage,numPerSide) Returns the vector V for a
%    square plate with a total of numPerSide^2 cells.  The
%    voltage is specified by the first argument.  The factor of
%    4*pi*epsilon_0 is included in the voltage vector (rather
%    than in the Zmn matrix).

numPerPlate = numPerSide^2;  % total number of cells on plate

v = repmat(voltage * 4.0 * pi * 8.854e-12,numPerPlate,1);

return;
