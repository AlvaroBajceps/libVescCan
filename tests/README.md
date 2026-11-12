# Codec tests

Run from the library root with a native GCC or Clang C11 toolchain:

```sh
cmake -S . -B build/tests -DLIBVESCCAN_BUILD_TESTS=ON
cmake --build build/tests
ctest --test-dir build/tests --output-on-failure
```

Tests cover literal STATUS_9 wire vectors, signed limits, rounding and truncation,
invalid inputs and unchanged outputs on rejection, generic SET_CONFIG/STATUS_13/
heartbeat payloads, reserved values, exact DLC checks, and MUX regression vectors.
Checks remain active in Release builds. Embedded consumers keep tests disabled by
default.
