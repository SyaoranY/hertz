# Hertz

A lightweight, header-only C++14 library for representing and manipulating frequency values as exact rational numbers.

```cpp
#include <hertz/hertz.h>

using hertz::Hertz;

Hertz refresh_rate{60};
Hertz fractional_rate{60000, 1001};
```

Unlike floating-point representations, `Hertz` stores frequencies as a normalized numerator and denominator, allowing fractional frequencies to be represented exactly.

## Features

* Exact rational frequency representation
* Automatic normalization
* Arithmetic and comparison operators
* Frequency literals: `mHz`, `Hz`, `kHz`, `MHz`, and `GHz`
* `floor`, `ceil`, and `round`
* Conversion from frequency to `std::chrono::duration`
* `constexpr` support
* Header-only
* C++14

## Requirements

* C++14 or later
* Linux
* GCC or Clang
* CMake 3.14 or later when using CMake

Hertz is developed and tested on Linux with GCC and Clang. Other platforms and compilers are not officially supported.

## Installation

### CMake FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    Hertz
    GIT_REPOSITORY https://github.com/SyaoranY/hertz.git
    GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(Hertz)

target_link_libraries(your_target PRIVATE Hertz::Hertz)
```

### Installed CMake package

Hertz can also be installed as a CMake package:

```bash
cmake -S . -B build
cmake --install build --prefix /path/to/install
```

Then use it from another project:

```cmake
find_package(Hertz 1 CONFIG REQUIRED)

target_link_libraries(your_target PRIVATE Hertz::Hertz)
```

If Hertz is installed to a custom prefix, pass it to CMake when configuring your project:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/install
```

### Manual

Hertz is header-only, so the `include` directory can also be added directly to your compiler's include path:

```cpp
#include <hertz/hertz.h>
```

## Usage

### Creating frequencies

An integer frequency can be constructed directly:

```cpp
using hertz::Hertz;

Hertz a{60};   // 60 Hz
Hertz b{-10};  // -10 Hz
```

Fractional frequencies are represented using a numerator and denominator:

```cpp
Hertz a{3, 2};         // 3/2 Hz
Hertz b{60000, 1001};  // 60000/1001 Hz
```

Values are automatically reduced to canonical form:

```cpp
Hertz value{6, 4};

// value.numerator()   == 3
// value.denominator() == 2
```

The denominator is kept positive and zero is represented as `0/1`.

### Frequency literals

Hertz provides literals for commonly used frequency units:

```cpp
using namespace hertz::literals;

auto slow       = 500_mHz;  // 1/2 Hz
auto refresh    = 60_Hz;    // 60 Hz
auto audio      = 48_kHz;   // 48,000 Hz
auto radio      = 100_MHz;  // 100,000,000 Hz
auto processor  = 3_GHz;    // 3,000,000,000 Hz
```

The supported literals are:

| Literal |       Unit |
| ------- | ---------: |
| `_mHz`  | millihertz |
| `_Hz`   |      hertz |
| `_kHz`  |  kilohertz |
| `_MHz`  |  megahertz |
| `_GHz`  |  gigahertz |

Literals use integral values. Fractional frequencies that cannot be expressed directly with a suitable unit can be represented using the rational constructor:

```cpp
Hertz{3, 2};         // 1.5 Hz
Hertz{60000, 1001};  // exact fractional frequency
```

Negative literals use the unary minus operator:

```cpp
using namespace hertz::literals;

auto a = -60_Hz;
auto b = -500_mHz;
```

### Arithmetic

Hertz values support addition and subtraction:

```cpp
Hertz a{3, 2};
Hertz b{1, 2};

auto sum = a + b;         // 2 Hz
auto difference = a - b;  // 1 Hz
```

A frequency can be multiplied or divided by an integer scalar:

```cpp
Hertz value{3, 2};

auto a = value * 2;  // 3 Hz
auto b = value / 3;  // 1/2 Hz
```

Multiplication is supported in both directions:

```cpp
auto a = Hertz{3, 2} * 2;
auto b = 2 * Hertz{3, 2};
```

Compound assignment is also supported:

```cpp
Hertz value{10};

value += Hertz{5};
value -= Hertz{2};
value *= 3;
value /= 2;
```

Prefix and postfix increment and decrement change the frequency by one hertz:

```cpp
Hertz value{3, 2};

++value;  // 5/2 Hz
value--;  // 3/2 Hz
```

Unary minus negates a frequency:

```cpp
auto value = -Hertz{3, 2};  // -3/2 Hz
```

### Comparison

Hertz values can be compared directly:

```cpp
Hertz{1, 2} == Hertz{2, 4};  // true
Hertz{3, 2} > Hertz{1};      // true
Hertz{-1} < Hertz{0};        // true
```

The following comparison operators are supported:

```text
==  !=  <  <=  >  >=
```

### Rounding

`floor`, `ceil`, and `round` convert a fractional frequency to an integer frequency.

```cpp
using hertz::ceil;
using hertz::floor;
using hertz::round;

Hertz value{3, 2};

floor(value);  // 1 Hz
ceil(value);   // 2 Hz
round(value);  // 2 Hz
```

`floor` rounds toward negative infinity:

```cpp
floor(Hertz{3, 2});   //  1 Hz
floor(Hertz{-3, 2});  // -2 Hz
```

`ceil` rounds toward positive infinity:

```cpp
ceil(Hertz{3, 2});    //  2 Hz
ceil(Hertz{-3, 2});   // -1 Hz
```

`round` rounds to the nearest integer, with halfway cases rounded away from zero:

```cpp
round(Hertz{3, 2});   //  2 Hz
round(Hertz{-3, 2});  // -2 Hz
```

### Period

The period corresponding to a frequency can be obtained with `period`.

By default, the result is returned in seconds as `std::chrono::duration<double>`:

```cpp
using hertz::period;

auto value = period(Hertz{2});

// std::chrono::duration<double>
// value.count() == 0.5
```

Fractional frequencies are supported naturally:

```cpp
auto value = period(Hertz{3, 2});

// 3/2 Hz -> 2/3 s
```

A specific `std::chrono::duration` type can be requested:

```cpp
#include <chrono>

auto value =
    period<std::chrono::milliseconds>(Hertz{60});

// value.count() == 16
```

Any `std::chrono::duration` type can be used:

```cpp
using DoubleMilliseconds =
    std::chrono::duration<double, std::milli>;

auto value =
    period<DoubleMilliseconds>(Hertz{60});

// value.count() ~= 16.6667
```

Custom duration periods are supported as well:

```cpp
using Tick =
    std::chrono::duration<double, std::ratio<1, 10>>;

auto value = period<Tick>(Hertz{4});

// 4 Hz -> 0.25 s
// one Tick = 0.1 s
// value.count() == 2.5
```

If the target duration uses an integral representation, fractional counts are truncated according to C++ integer conversion semantics:

```cpp
period<std::chrono::milliseconds>(Hertz{60}).count();
// 16
```

`period` requires a non-zero frequency.

### Output

Hertz values can be written directly to an output stream:

```cpp
#include <iostream>

std::cout << Hertz{5};
// 5 Hz

std::cout << Hertz{3, 2};
// 3/2 Hz
```

## Arithmetic Overflow

Hertz uses `std::int64_t` for its numerator and denominator.

Integer overflow is not checked. Intermediate and final arithmetic results are expected to be representable by `std::int64_t`.

Operations that violate this requirement are outside the supported contract.

This keeps Hertz lightweight and avoids introducing checked or arbitrary-precision integer arithmetic into the library.

## Building and Running Tests

Configure the project with tests enabled:

```bash
cmake -S . -B build \
    -DHERTZ_BUILD_TESTS=ON \
    -DCMAKE_CXX_STANDARD=14 \
    -DCMAKE_CXX_STANDARD_REQUIRED=ON \
    -DCMAKE_CXX_EXTENSIONS=OFF
```

Build:

```bash
cmake --build build
```

Run the tests:

```bash
ctest --test-dir build --output-on-failure
```

## License

Hertz is released under the MIT License. See [LICENSE](LICENSE) for details.
