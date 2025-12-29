% test_dtw.m - Unit tests for Dynamic Time Warping

function test_dtw()
    fprintf('Running DTW unit tests...\n');

    % Compile MEX version if needed
    if exist('dtw_c', 'file') ~= 3
        fprintf('Compiling MEX version for testing...\n');
        mex dtw_c.c;
    end

    % Define test cases
    test_cases = {
        % s, t, w, expected_dist (approx)
        rand(10, 2), rand(10, 2), 100, -1; % Large window
        [1 2 3]', [1 2 3]', 100, 0;       % Identical signals
        [1 2 3]', [2 3 4]', 100, 2;       % Simple shift (cost is 2, not sqrt(3))
        [1 2 3]', [1 1 2 2 3 3]', 100, 0; % Time stretching
        [1 0 1]', [0 1 0]', 100, 2;       % Different shapes
    };

    num_passed = 0;
    num_tests = size(test_cases, 1);

    for i = 1:num_tests
        s = test_cases{i, 1};
        t = test_cases{i, 2};
        w = test_cases{i, 3};
        expected = test_cases{i, 4};

        % Run both versions
        d_m = dtw(s, t, w);
        d_c = dtw_c(s, t, w);

        % Consistency check
        if abs(d_m - d_c) > 1e-10
            fprintf('Test %d FAILED: Matlab and C versions differ (%f vs %f)\n', i, d_m, d_c);
            continue;
        end

        % Accuracy check (if expected is not -1)
        if expected ~= -1 && abs(d_m - expected) > 1e-4
            fprintf('Test %d FAILED: Distance mismatch (Got %f, Expected %f)\n', i, d_m, expected);
            continue;
        end

        num_passed = num_passed + 1;
        fprintf('Test %d PASSED\n', i);
    end

    fprintf('\nUnit tests complete: %d/%d passed.\n', num_passed, num_tests);

    if num_passed == num_tests
        fprintf('All tests passed successfully.\n');
    else
        error('Some tests FAILED.');
    end
end
