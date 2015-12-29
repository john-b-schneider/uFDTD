% Set the number of cells per side of the plate.
numPerSide = 10;

% Generate voltage vector assuming unit voltage on plate.
vm  = makeVPlate(1,numPerSide);  

% Calculate the Zmn matrix.
zmn = makeZmnPlate(numPerSide);

% Solve for the basis-function coefficients.
an = zmn \ vm;

% Calculate the total charge on plate.
del=1.0/numPerSide;  %%% length along a side of segment
charge = sum(an)*del^2;

%%% Plot coefficient of all basis functions.
figure(1)
plot(an)
title('Fig. 1: Charge vs. Basis Function Number, Aligned Plates, \Delta=1/10')
xlabel('Basis Function Number')
ylabel('Charge [Coulombs]')

%%% Create a 2D array of coefficients of basis functions on
%%% plate and plot it using a surface plot.
top = reshape(an(numPerSide1^2+1:end),numPerSide,numPerSide);
x1=del/2:del:1.0-del/2;  %%% x location of center of cells
y1=del/2:del:1.0-del/2;  %%% y location of center of cells
figure(2)
surf(x1,y1,top)
title('Fig. 2: Charge vs. Position on Plate, Aligned Plates, \Delta=1/10')
xlabel('Displacement from edge')
ylabel('Displacement from edge')
zlabel('Charge [Coulombs]')

