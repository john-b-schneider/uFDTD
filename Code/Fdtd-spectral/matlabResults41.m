clf

hold on
plot(nLambda,...
     real(exp(-j*pi*freqIndex/512.)'.*die(freqSlice)./inc(freqSlice)));
plot(nLambda,...
     imag(exp(-j*pi*freqIndex/512)'.*die(freqSlice)./inc(freqSlice)),'-.');
xlabel('Points per Wavelength');
ylabel('Transmission Coefficient, {\it T}(\omega)');
legend('Real part','Imaginary part');
axis([0 300 -1 1])
grid on
hold off

