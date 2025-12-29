% Copyright (C) 2013 Quan Wang <wangq10@rpi.edu>,
% Signal Analysis and Machine Perception Laboratory,
% Department of Electrical, Computer, and Systems Engineering,
% Rensselaer Polytechnic Institute, Troy, NY 12180, USA

% This is a demo showing the use of our dynamic time warping package.
% We provide both Matlab version and C/MEX version.
% The C/MEX version is much faster and highly recommended.

clear;
clc;
close all;

% Compile the MEX version
fprintf('Compiling MEX version...\n');
mex dtw_c.c;

% Generate sample signals
fprintf('Generating sample signals...\n');
a = rand(500, 3);
b = rand(520, 3);
w = 50;

% Run Matlab version
fprintf('Running Matlab version...\n');
tic;
d1 = dtw(a, b, w);
t1 = toc;

% Run C/MEX version
fprintf('Running C/MEX version...\n');
tic;
d2 = dtw_c(a, b, w);
t2 = toc;

% Display results
fprintf('\n--- Results ---\n');
fprintf('Using Matlab version: distance = %f, time = %f s\n', d1, t1);
fprintf('Using C/MEX version:  distance = %f, time = %f s\n', d2, t2);
fprintf('Speedup: %.2fx\n', t1 / t2);

