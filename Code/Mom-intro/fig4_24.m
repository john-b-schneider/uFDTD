% these commands are to generate the data which
% goes into the construction of Figure 4.24 (which
% is wrong).

separations=.1:.1:1;
ratios=zeros(length(separations),1);

numPerSide = 17;

count=1;
for s=separations
  [c an r] = capacitance(numPerSide,s);
  ratios(count) = r
  count = count+1;
end

plot(separations,ratios)
xlabel('separation/width (d/w)')
title('Corrected Fig. 4.24 of Iskander')   
ylabel('C/C_0')
axis([0 1 0 5])
