/**
 * Copyright (C) 2013 Quan Wang <wangq10@rpi.edu>,
 * Signal Analysis and Machine Perception Laboratory,
 * Department of Electrical, Computer, and Systems Engineering,
 * Rensselaer Polytechnic Institute, Troy, NY 12180, USA
 */

/**
 * This is the C/MEX code of dynamic time warping of two signals.
 *
 * Compile:
 *     mex dtw_c.c
 *
 * Usage:
 *     d = dtw_c(s, t)  or  d = dtw_c(s, t, w)
 *     where s is signal 1, t is signal 2, w is window parameter.
 */

#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Calculate the Euclidean distance between two vectors at specific time steps.
 */
double vectorDistance(double *s, double *t, int ns, int nt, int k, int i, int j) {
    double result = 0;
    double ss, tt;
    int x;
    for (x = 0; x < k; x++) {
        ss = s[i + ns * x];
        tt = t[j + nt * x];
        result += ((ss - tt) * (ss - tt));
    }
    result = sqrt(result);
    return result;
}

/**
 * Core DTW implementation in C.
 */
double dtw_c(double *s, double *t, int w, int ns, int nt, int k) {
    double d = 0;
    int sizediff = abs(ns - nt);
    double **D;
    int i, j;
    int j1, j2;
    double cost, temp;

    if (w != -1) {
        if (w < sizediff) {
            w = sizediff; // adapt window size
        }
        if (w > ns && w > nt) {
            w = (ns > nt) ? ns : nt; // cap w to avoid overflow
        }
    }

    // Allocate memory for cost matrix D
    D = (double **)malloc((ns + 1) * sizeof(double *));
    for (i = 0; i < ns + 1; i++) {
        D[i] = (double *)malloc((nt + 1) * sizeof(double));
    }

    // Initialization
    for (i = 0; i < ns + 1; i++) {
        for (j = 0; j < nt + 1; j++) {
            D[i][j] = -1;
        }
    }
    D[0][0] = 0;

    // Dynamic programming
    for (i = 1; i <= ns; i++) {
        if (w == -1) {
            j1 = 1;
            j2 = nt;
        } else {
            j1 = (i - w > 1) ? (i - w) : 1;
            j2 = (i + w < nt) ? (i + w) : nt;
        }
        for (j = j1; j <= j2; j++) {
            cost = vectorDistance(s, t, ns, nt, k, i - 1, j - 1);

            temp = -1;
            // Check Up: D[i-1][j]
            if (D[i - 1][j] != -1) {
                temp = D[i - 1][j];
            }
            // Check Left: D[i][j-1]
            if (D[i][j - 1] != -1) {
                if (temp == -1 || D[i][j - 1] < temp) {
                    temp = D[i][j - 1];
                }
            }
            // Check Diagonal: D[i-1][j-1]
            if (D[i - 1][j - 1] != -1) {
                if (temp == -1 || D[i - 1][j - 1] < temp) {
                    temp = D[i - 1][j - 1];
                }
            }

            if (temp != -1) {
                D[i][j] = cost + temp;
            }
        }
    }

    d = D[ns][nt];

    // Free memory
    for (i = 0; i < ns + 1; i++) {
        free(D[i]);
    }
    free(D);

    return d;
}

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    double *s, *t;
    int w;
    int ns, nt, k;
    double *dp;

    /* Check for proper number of arguments */
    if (nrhs != 2 && nrhs != 3) {
        mexErrMsgIdAndTxt("MATLAB:dtw_c:invalidNumInputs", "Two or three inputs required.");
    }
    if (nlhs > 1) {
        mexErrMsgIdAndTxt("MATLAB:dtw_c:invalidNumOutputs", "dtw_c: One output required.");
    }

    /* Check to make sure w is a scalar */
    if (nrhs == 2) {
        w = -1;
    } else if (nrhs == 3) {
        if (!mxIsDouble(prhs[2]) || mxIsComplex(prhs[2]) || mxGetN(prhs[2]) * mxGetM(prhs[2]) != 1) {
            mexErrMsgIdAndTxt("MATLAB:dtw_c:wNotScalar", "dtw_c: Input w must be a scalar.");
        }

        /* Get the scalar input w */
        w = (int)mxGetScalar(prhs[2]);
    }

    /* Create a pointer to the input matrix s */
    s = mxGetPr(prhs[0]);

    /* Create a pointer to the input matrix t */
    t = mxGetPr(prhs[1]);

    /* Get the dimensions of the matrix input s */
    ns = (int)mxGetM(prhs[0]);
    k = (int)mxGetN(prhs[0]);

    /* Get the dimensions of the matrix input t */
    nt = (int)mxGetM(prhs[1]);
    if (mxGetN(prhs[1]) != k) {
        mexErrMsgIdAndTxt("MATLAB:dtw_c:dimNotMatch", "dtw_c: Dimensions of input s and t must match.");
    }

    /* Set the output pointer to the output matrix */
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);

    /* Create a C pointer to a copy of the output matrix */
    dp = mxGetPr(plhs[0]);

    /* Call the C subroutine */
    dp[0] = dtw_c(s, t, w, ns, nt, k);

    return;
}
