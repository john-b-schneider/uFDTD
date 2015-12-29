function simpleWaterfall(z,offset,scale)
%simpleWaterfall Waterfall plot from offset x-y plots.
%  simpleWaterfall(Z,OFFSET,SCALE) Plots each row of z where
%  successive plots are offset from each other by OFFSET
%  and each plot is scaled vertically by SCALE.

hold off            % release any previous plot
plot(scale*z(1,:))  % plot the first row
hold on             % hold the plot

for i=2:size(z,1)   % plot the remaining rows
  plot(scale*z(i,:) + offset*(i-1))
end

hold off            % release the plot

return
