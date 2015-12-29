% commands used to generate the waterfall plot
% of the dielectric interface
z=readOneD('sim');
simpleWaterfall(z,1,2);
axis([0 200 0 45])
xlabel('Space [spatial index]')
ylabel('Time [frame number]')
