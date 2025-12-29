% Copyright (C) 2013 Quan Wang <wangq10@rpi.edu>,
% Signal Analysis and Machine Perception Laboratory,
% Department of Electrical, Computer, and Systems Engineering,
% Rensselaer Polytechnic Institute, Troy, NY 12180, USA

function d = dtw(s, t, w)
    % DTW Dynamic Time Warping of two signals.
    %   D = DTW(S, T) returns the dynamic time warping distance between S and T.
    %   D = DTW(S, T, W) specifies the window parameter W.
    %
    %   Inputs:
    %       s: signal 1, size is ns*k, row for time, column for channel
    %       t: signal 2, size is nt*k, row for time, column for channel
    %       w: window parameter (optional, default: Inf)
    %          if s(i) is matched with t(j) then |i-j|<=w
    %
    %   Output:
    %       d: resulting DTW distance

    if nargin < 3
        w = Inf;
    end

    ns = size(s, 1);
    nt = size(t, 1);

    if size(s, 2) ~= size(t, 2)
        error('Error in dtw(): the dimensions of the two input signals do not match.');
    end

    % Adapt window size
    w = max(w, abs(ns - nt));

    %% Initialization
    D = zeros(ns + 1, nt + 1) + Inf; % cache matrix
    D(1, 1) = 0;

    %% Dynamic programming
    for i = 1:ns
        for j = max(i - w, 1):min(i + w, nt)
            cost = norm(s(i, :) - t(j, :));
            D(i + 1, j + 1) = cost + min([D(i, j + 1), D(i + 1, j), D(i, j)]);
        end
    end

    d = D(ns + 1, nt + 1);
end
