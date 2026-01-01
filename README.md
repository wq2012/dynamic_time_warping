# Dynamic Time Warping (DTW)

[![View Dynamic Time Warping (DTW) on File Exchange](https://www.mathworks.com/matlabcentral/images/matlab-file-exchange.svg)](https://www.mathworks.com/matlabcentral/fileexchange/43156-dynamic-time-warping-dtw)
[![Octave application](https://github.com/wq2012/dynamic_time_warping/actions/workflows/octave.yml/badge.svg)](https://github.com/wq2012/dynamic_time_warping/actions/workflows/octave.yml)

![DTW Visualization](resources/dtw.jpg)

A high-performance implementation of the Dynamic Time Warping (DTW) algorithm for MATLAB and GNU Octave. This package provides both a native MATLAB implementation and a high-performance C/MEX implementation.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation & Compilation](#installation--compilation)
- [Usage](#usage)
- [Running Demo & Tests](#running-demo--tests)
- [Performance](#performance)
- [Copyright and Citation](#copyright-and-citation)

---

## Features

- **Standard DTW**: Compute the optimal alignment between two sequences.
- **Multidimensional**: Supports multi-channel signals (time-series).
- **Windowed DTW**: Supports Sakoe-Chiba band windowing for improved performance.
- **High Performance**: Includes a MEX implementation for significant speedup.
- **Automated Testing**: Comprehensive unit tests to ensure correctness and consistency.

## Requirements

- MATLAB or GNU Octave
- C compiler (for MEX compilation, e.g., GCC, Clang, or MSVC)

## Installation & Compilation

To use the high-performance MEX version, you need to compile the C source file. Run the following command in your MATLAB/Octave command window:

```matlab
cd code
mex dtw_c.c
```

## Usage

### MATLAB Version

```matlab
% s, t are ns*k and nt*k matrices (time steps by channels)
d = dtw(s, t);
d = dtw(s, t, w); % with window w
```

### MEX Version

```matlab
% Highly recommended for better performance
d = dtw_c(s, t);
d = dtw_c(s, t, w); % with window w
```

### Parameters

- `s`: First signal, size `[ns, k]`, where `ns` is time steps and `k` is channels.
- `t`: Second signal, size `[nt, k]`.
- `w`: Window parameter (optional). If `s(i)` is matched with `t(j)`, then `|i - j| <= w`.

## Running Demo & Tests

To see DTW in action and compare performance:
```matlab
cd code
demo_dtw
```

To run unit tests:
```matlab
cd code
test_dtw
```

## Performance

The C/MEX implementation is typically 10-50x faster than the native MATLAB implementation, especially for long sequences and multidimensional signals.

## Copyright and Citation

```
Copyright (C) 2012 Quan Wang <wangq10@rpi.edu>,
Signal Analysis and Machine Perception Laboratory,
Department of Electrical, Computer, and Systems Engineering,
Rensselaer Polytechnic Institute, Troy, NY 12180, USA
```

This software was developed as part of the following research. If you use this software in your research, please cite:

**Plain Text:**

> Quan Wang.
Exploiting Geometric and Spatial Constraints for Vision and Lighting Applications.
Ph.D. dissertation, Rensselaer Polytechnic Institute, 2014.

**BibTeX:**

```bibtex
@phdthesis{wang2014exploiting,
  title={Exploiting Geometric and Spatial Constraints for Vision and Lighting Applications},
  author={Quan Wang},
  year={2014},
  school={Rensselaer Polytechnic Institute},
}
```

---

Available on [MathWorks MATLAB Central](https://www.mathworks.com/matlabcentral/fileexchange/43156-dynamic-time-warping-dtw).