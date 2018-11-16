# Dynamic Time Warping (DTW)

DTW is implemented in both Matlab and C/MEX. The C/MEX function is very fast.

The algorithm we use is the standard one from wiki:
* http://en.wikipedia.org/wiki/Dynamic_time_warping

There is a demo in the package. To use, just call:
```
d=dtw(s,t,w) or d=dtw_c(s,t,w)
```

This library is also available at MathWorks:
* https://www.mathworks.com/matlabcentral/fileexchange/43156-dynamic-time-warping-dtw

![dtw](resources/dtw.jpg)