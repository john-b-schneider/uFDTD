% these commands are to generate the data essentially
% corresponds to Figure 4.24 of Iskander except here 
% the plates are offset from each other by a tenth a unit

separations=.1:.1:1;
ratios=zeros(length(separations),1);

numPerSide = 17;

count=1;
for s=separations
  [c an r] = capacitanceOffset(numPerSide,s);
  ratios(count) = r
  count = count+1;
end

plot(separations,ratios)
xlabel('separation/width (d/w)')
title('Similar to Fig. 4.24 of Iskander but with plate offset')
ylabel('C/C_0')
axis([0 1 0 5])
