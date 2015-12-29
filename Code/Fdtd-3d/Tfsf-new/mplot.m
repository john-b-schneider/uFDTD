subplot(3,2,1)
raw2image('no-sphere.1',1,3)
title('(a) time-step 20, no scatterer')
xlabel('x location')
ylabel('z location')

subplot(3,2,2)
raw2image('sphere.1',1,3)
title('(b) time-step 20, with sphere')
xlabel('x location')
ylabel('z location')

subplot(3,2,3)
raw2image('no-sphere.3',1,3)
title('(c) time-step 40, no scatterer')
xlabel('x location')
ylabel('z location')

subplot(3,2,4)
raw2image('sphere.3',1,3)
title('(d) time-step 40, with sphere')
xlabel('x location')
ylabel('z location')

subplot(3,2,5)
raw2image('no-sphere.5',1,3)
title('(e) time-step 60, no scatterer')
xlabel('x location')
ylabel('z location')

subplot(3,2,6)
raw2image('sphere.5',1,3)
title('(f) time-step 60, with sphere')
xlabel('x location')
ylabel('z location')

print -depsc -adobecset -r300 tfsf-demo.eps
