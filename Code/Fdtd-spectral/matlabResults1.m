clf

subplot(2,1,1)
hold on
plot(nLambda,abs(die(freqSlice)./inc(freqSlice)));
xlabel('Points per Wavelength');
ylabel('|{\it E^t_z}[{\it x}_1,\omega]/{\it E^i_z}[{\it x}_1,\omega]|');
title('(a) Normalized Transmitted Field vs. Discretization');
axis([0 300 0 1])
hold off

% Exponential has to be transposed to array conformal with others.
% Simply using ' (a prime) for transposition will yield the conjugat
% transpose.  Instead have to use .' (dot-prime) to get
% transposition without conjugation.
subplot(2,1,2)
hold on
plot(nLambda,...
     real(exp(j*pi*freqIndex/25.6).'.*die(freqSlice)./inc(freqSlice)));
plot(nLambda,...
     imag(exp(j*pi*freqIndex/25.6).'.*die(freqSlice)./inc(freqSlice)),'-.');
xlabel('Points per Wavelength');
ylabel('Transmission Coefficient, {\it T}(\omega)');
title('(b) Real and Imaginary Part of Transmission Coefficient');
legend('Real part','Imaginary part');
axis([0 300 -1 1])
grid on
hold off

