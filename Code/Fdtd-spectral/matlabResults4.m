incTime=dlmread('inc-8192-x4'); % incident field file
dieTime=dlmread('die-8192-x4'); % transmitted field file

inc=fft(incTime);  % take Fourier transforms
die=fft(dieTime);

nSteps=length(incTime);  % number of time steps
freqMin=1;    % minimum frequency index of interest
freqMax=500;  % maximum frequency of interest
freqIndex=freqMin:freqMax; % range of frequencies of interest
freqSlice=freqIndex+1; % correct for offset of 1 in matlab's indexing

courantNumber = 1;
nLambda=nSteps./freqIndex;  % points per wavelength of freq's of interest

clf
subplot(3,1,1)
hold on
plot(incTime(freqSlice),'-.');
plot(dieTime(freqSlice));
legend('Incident field','Transmitted field');
xlabel('Temporal Index');
ylabel('{\it E_z}[{\it x}_1,{\it t}]V/m');
title('(a) Temporal Fields');

subplot(3,1,2)
hold on
plot(freqIndex,abs(inc(freqSlice)),'-.');
plot(freqIndex,abs(die(freqSlice)));
legend('Incident field','Transmitted field');
xlabel('Frequency Index');
ylabel('|{\it E_z}[{\it x}_1,\omega]|');
title('(b) Transform vs. Frequency Index');
hold off

subplot(3,1,3)
hold on
plot(freqIndex,abs(die(freqSlice)./inc(freqSlice)));
xlabel('Frequency Index');
ylabel('|{\it E^t_z}[{\it x}_1,\omega]/{\it E^i_z}[{\it x}_1,\omega]|');
title('(c) Normalized Transmitted Field vs. Frequency Index');
hold off

