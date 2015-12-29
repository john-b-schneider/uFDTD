% Set the number of cells per side of the plate.
numPerSide = 20;

% Generate voltage vector assuming unit voltage on plate.
vm  = makeVmPlate(1,numPerSide);  

% Calculate the Zmn matrix.
zmn = makeZmnPlate(numPerSide);

% Solve for the basis-function coefficients.
an = zmn \ vm;

% Calculate the total charge on plate.
del=1.0/numPerSide;  %%% width of a cell
charge = sum(an)*del^2;

%%%
% Plot coefficients of all basis functions.
figure(1)
plot(an)      %%% show as a connected curve
hold
plot(an,'.')  %%% show the discrete values
title(...
  strcat('Charge vs. Basis Function Number, \Delta=1/',...
	  num2str(numPerSide)));
xlabel('Basis Function Number')
ylabel('Charge density [Coulombs/m^2]')

% Create a 2D array of coefficients of basis functions on
% plate and plot it using a surface plot.
plate = reshape(an,numPerSide,numPerSide);
x1=del/2:del:1.0-del/2;  %%% x location of center of cells
y1=del/2:del:1.0-del/2;  %%% y location of center of cells
figure(2)
surf(x1,y1,plate)
title(...
  strcat('Charge vs. Position on Plate, \Delta=1/',...
	  num2str(numPerSide)));
xlabel('Displacement from edge')
ylabel('Displacement from edge')
zlabel('Charge density [Coulombs/m^2]')
