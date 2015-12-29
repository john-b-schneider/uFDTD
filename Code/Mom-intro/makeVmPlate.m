function vm = makeVmPlate(voltage,numPerSide)
% makeVmPlate  Make the voltage vector for a square plate.
%
% vm=makeVmPlate(voltage,numPerSide) Returns the vector Vm for
%    a square plate with a total of numPerSide^2 cells.  The
%    voltage is specified by the first argument.  The factor of
%    4*pi*epsilon_0 is included in the voltage vector (rather
%    than in the Zmn matrix).

numPerPlate = numPerSide^2;  % total number of cells on plate

vm = repmat(voltage * 4.0 * pi * 8.854e-12,numPerPlate,1);

return;
