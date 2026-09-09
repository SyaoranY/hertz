#include <gtest/gtest.h>
#include <hertz/hertz.h>
#include <limits>
#include <sstream>

using hertz::Hertz;

TEST(HertzTest, DefaultConstructor) {
  hertz::Hertz h;
  EXPECT_EQ(h.numerator(), 0);
  EXPECT_EQ(h.denominator(), 1);
}

TEST(HertzTest, SingleParameterConstructor) {
  {
    hertz::Hertz h(5);
    EXPECT_EQ(h.numerator(), 5);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(0);
    EXPECT_EQ(h.numerator(), 0);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(-1);
    EXPECT_EQ(h.numerator(), -1);
    EXPECT_EQ(h.denominator(), 1);
  }
}

TEST(HertzTest, TwoParametersConstructor) {
  {
    hertz::Hertz h(3, 4);
    EXPECT_EQ(h.numerator(), 3);
    EXPECT_EQ(h.denominator(), 4);
  }
  {
    hertz::Hertz h(2, 4);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 2);
  }
  {
    hertz::Hertz h(0, 4);
    EXPECT_EQ(h.numerator(), 0);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(1, 1);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(-1, -1);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(-4, -1);
    EXPECT_EQ(h.numerator(), 4);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(-4, -4);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(4, 4);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(2, 1);
    EXPECT_EQ(h.numerator(), 2);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(7, 3);
    EXPECT_EQ(h.numerator(), 7);
    EXPECT_EQ(h.denominator(), 3);
  }
  {
    hertz::Hertz h(100, 5);
    EXPECT_EQ(h.numerator(), 20);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h(100, 30);
    EXPECT_EQ(h.numerator(), 10);
    EXPECT_EQ(h.denominator(), 3);
  }
}

TEST(HertzTest, SupportsInt64MinWithUnitDenominator) {
  constexpr auto min = std::numeric_limits<std::int64_t>::min();

  constexpr Hertz hertz{min, 1};

  static_assert(hertz.numerator() == min, "");
  static_assert(hertz.denominator() == 1, "");

  EXPECT_EQ(hertz.numerator(), min);
  EXPECT_EQ(hertz.denominator(), 1);
}

TEST(HertzTest, CopyAndMove) {
  { // copy ctor
    hertz::Hertz h1(100, 30);
    hertz::Hertz h2(h1);
    EXPECT_EQ(h2.numerator(), 10);
    EXPECT_EQ(h2.denominator(), 3);
  }
  { // move ctor
    hertz::Hertz h1(100, 30);
    hertz::Hertz h2(std::move(h1));
    EXPECT_EQ(h2.numerator(), 10);
    EXPECT_EQ(h2.denominator(), 3);
  }
  { // copy assign
    hertz::Hertz h1(100, 30);
    hertz::Hertz h2;
    h2 = h1;
    EXPECT_EQ(h2.numerator(), 10);
    EXPECT_EQ(h2.denominator(), 3);
  }
  { // move assign
    hertz::Hertz h1(100, 30);
    hertz::Hertz h2;
    h2 = std::move(h1);
    EXPECT_EQ(h2.numerator(), 10);
    EXPECT_EQ(h2.denominator(), 3);
  }
}

TEST(HertzTest, PrefixIncrement) {
  {
    hertz::Hertz h{0};
    hertz::Hertz& h2 = ++h;
    EXPECT_EQ(h2.numerator(), 1);
    EXPECT_EQ(h2.denominator(), 1);
    ++h;
    EXPECT_EQ(h2.numerator(), 2);
    EXPECT_EQ(h2.denominator(), 1);
  }
  {
    hertz::Hertz h{3, 4};
    hertz::Hertz& h2 = ++h;
    EXPECT_EQ(h2.numerator(), 7);
    EXPECT_EQ(h2.denominator(), 4);
    ++h;
    EXPECT_EQ(h2.numerator(), 11);
    EXPECT_EQ(h2.denominator(), 4);
  }
  {
    hertz::Hertz h{5, 2};
    hertz::Hertz& h2 = ++h;
    EXPECT_EQ(h2.numerator(), 7);
    EXPECT_EQ(h2.denominator(), 2);
    ++h;
    EXPECT_EQ(h2.numerator(), 9);
    EXPECT_EQ(h2.denominator(), 2);
  }
  {
    hertz::Hertz h{-3, 2};
    hertz::Hertz& h2 = ++h;
    EXPECT_EQ(h2.numerator(), -1);
    EXPECT_EQ(h2.denominator(), 2);
    ++h;
    EXPECT_EQ(h2.numerator(), 1);
    EXPECT_EQ(h2.denominator(), 2);
  }
}

TEST(HertzTest, PostfixIncrement) {
  {
    hertz::Hertz h{0};
    hertz::Hertz h2 = h++;
    EXPECT_EQ(h2.numerator(), 0);
    EXPECT_EQ(h2.denominator(), 1);
    EXPECT_EQ(h.numerator(), 1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h{3, 4};
    hertz::Hertz h2 = h++;
    EXPECT_EQ(h2.numerator(), 3);
    EXPECT_EQ(h2.denominator(), 4);
    EXPECT_EQ(h.numerator(), 7);
    EXPECT_EQ(h.denominator(), 4);
  }
  {
    hertz::Hertz h{5, 2};
    hertz::Hertz h2 = h++;
    EXPECT_EQ(h2.numerator(), 5);
    EXPECT_EQ(h2.denominator(), 2);
    EXPECT_EQ(h.numerator(), 7);
    EXPECT_EQ(h.denominator(), 2);
  }
  {
    hertz::Hertz h{-3, 2};
    hertz::Hertz h2 = h++;
    EXPECT_EQ(h2.numerator(), -3);
    EXPECT_EQ(h2.denominator(), 2);
    EXPECT_EQ(h.numerator(), -1);
    EXPECT_EQ(h.denominator(), 2);
  }
}

TEST(HertzTest, PrefixDecrement) {
  {
    hertz::Hertz h{0};
    hertz::Hertz& h2 = --h;
    EXPECT_EQ(h2.numerator(), -1);
    EXPECT_EQ(h2.denominator(), 1);
    --h;
    EXPECT_EQ(h2.numerator(), -2);
    EXPECT_EQ(h2.denominator(), 1);
  }
  {
    hertz::Hertz h{3, 4};
    hertz::Hertz& h2 = --h;
    EXPECT_EQ(h2.numerator(), -1);
    EXPECT_EQ(h2.denominator(), 4);
    --h;
    EXPECT_EQ(h2.numerator(), -5);
    EXPECT_EQ(h2.denominator(), 4);
  }
  {
    hertz::Hertz h{5, 2};
    hertz::Hertz& h2 = --h;
    EXPECT_EQ(h2.numerator(), 3);
    EXPECT_EQ(h2.denominator(), 2);
    --h;
    EXPECT_EQ(h2.numerator(), 1);
    EXPECT_EQ(h2.denominator(), 2);
  }
  {
    hertz::Hertz h{-3, 2};
    hertz::Hertz& h2 = --h;
    EXPECT_EQ(h2.numerator(), -5);
    EXPECT_EQ(h2.denominator(), 2);
    --h;
    EXPECT_EQ(h2.numerator(), -7);
    EXPECT_EQ(h2.denominator(), 2);
  }
}

TEST(HertzTest, PostfixDecrement) {
  {
    hertz::Hertz h{0};
    hertz::Hertz h2 = h--;
    EXPECT_EQ(h2.numerator(), 0);
    EXPECT_EQ(h2.denominator(), 1);
    EXPECT_EQ(h.numerator(), -1);
    EXPECT_EQ(h.denominator(), 1);
  }
  {
    hertz::Hertz h{3, 4};
    hertz::Hertz h2 = h--;
    EXPECT_EQ(h2.numerator(), 3);
    EXPECT_EQ(h2.denominator(), 4);
    EXPECT_EQ(h.numerator(), -1);
    EXPECT_EQ(h.denominator(), 4);
  }
  {
    hertz::Hertz h{5, 2};
    hertz::Hertz h2 = h--;
    EXPECT_EQ(h2.numerator(), 5);
    EXPECT_EQ(h2.denominator(), 2);
    EXPECT_EQ(h.numerator(), 3);
    EXPECT_EQ(h.denominator(), 2);
  }
  {
    hertz::Hertz h{-3, 2};
    hertz::Hertz h2 = h--;
    EXPECT_EQ(h2.numerator(), -3);
    EXPECT_EQ(h2.denominator(), 2);
    EXPECT_EQ(h.numerator(), -5);
    EXPECT_EQ(h.denominator(), 2);
  }
}

TEST(HertzTest, AdditionAssignment) {
  {
    hertz::Hertz lhs{1, 2};
    hertz::Hertz const rhs{1, 3};
    lhs += rhs;
    EXPECT_EQ(lhs, hertz::Hertz(5, 6));
  }
  {
    hertz::Hertz lhs{1, 4};
    hertz::Hertz const rhs{1, 4};
    lhs += rhs;
    EXPECT_EQ(lhs, hertz::Hertz(1, 2));
  }
  {
    hertz::Hertz lhs{3, 2};
    hertz::Hertz const zero{0};
    lhs += zero;
    EXPECT_EQ(lhs, hertz::Hertz(3, 2));
  }
  {
    hertz::Hertz lhs{1, 2};
    hertz::Hertz const rhs{1, 2};
    hertz::Hertz& result = (lhs += rhs);
    EXPECT_EQ(lhs, hertz::Hertz(1, 1));
    EXPECT_EQ(&result, &lhs);
  }
  {
    hertz::Hertz lhs{3, 4};
    hertz::Hertz const rhs{-1, 4};
    lhs += rhs;
    EXPECT_EQ(lhs, hertz::Hertz(1, 2));
  }
}

TEST(HertzTest, SubstractionAssignment) {
  Hertz lhs{5, 6};
  Hertz const rhs{1, 3};

  Hertz& result = (lhs -= rhs);

  EXPECT_EQ(lhs, Hertz(1, 2));
  EXPECT_EQ(&result, &lhs);
}

TEST(HertzTest, MultiplicationAssignment) {
  Hertz value{2, 3};

  Hertz& result = (value *= 6);

  EXPECT_EQ(value, Hertz(4, 1));
  EXPECT_EQ(&result, &value);
}

TEST(HertzTest, DivisionAssignment) {
  Hertz value{4, 3};

  Hertz& result = (value /= 2);

  EXPECT_EQ(value, Hertz(2, 3));
  EXPECT_EQ(&result, &value);
}

TEST(HertzTest, Addition) {
  const Hertz lhs{1, 2};
  const Hertz rhs{1, 3};

  const Hertz result = lhs + rhs;

  EXPECT_EQ(result, Hertz(5, 6));
  EXPECT_EQ(lhs, Hertz(1, 2));
  EXPECT_EQ(rhs, Hertz(1, 3));
}

TEST(HertzTest, Substraction) {
  const Hertz lhs{5, 6};
  const Hertz rhs{1, 3};

  const Hertz result = lhs - rhs;

  EXPECT_EQ(result, Hertz(1, 2));
  EXPECT_EQ(lhs, Hertz(5, 6));
  EXPECT_EQ(rhs, Hertz(1, 3));
}

TEST(HertzTest, Multiplication) {
  {
    const Hertz value{2, 3};

    const Hertz result = value * 6;

    EXPECT_EQ(result, Hertz(4, 1));
    EXPECT_EQ(value, Hertz(2, 3));
  }
  {
    const Hertz value{2, 3};

    const Hertz result = 6 * value;

    EXPECT_EQ(result, Hertz(4, 1));
    EXPECT_EQ(value, Hertz(2, 3));
  }
}

TEST(HertzTest, Division) {
  const Hertz value{4, 3};

  const Hertz result = value / 2;

  EXPECT_EQ(result, Hertz(2, 3));
  EXPECT_EQ(value, Hertz(4, 3));
}

TEST(HertzTest, Comparision) {
  const Hertz half{1, 2};
  const Hertz equivalent_half{2, 4};
  const Hertz two_thirds{2, 3};

  EXPECT_EQ(half, equivalent_half);
  EXPECT_NE(half, two_thirds);

  EXPECT_LT(half, two_thirds);
  EXPECT_LE(half, equivalent_half);
  EXPECT_LE(half, two_thirds);

  EXPECT_GT(two_thirds, half);
  EXPECT_GE(equivalent_half, half);
  EXPECT_GE(two_thirds, half);
}

TEST(HertzTest, UnaryMinus) {
  EXPECT_EQ(-Hertz(60), Hertz(-60));
  EXPECT_EQ(-Hertz(-60), Hertz(60));

  EXPECT_EQ(-Hertz(3, 2), Hertz(-3, 2));
  EXPECT_EQ(-Hertz(-3, 2), Hertz(3, 2));

  EXPECT_EQ(-Hertz(0), Hertz(0));

  constexpr Hertz value{3, 2};
  constexpr Hertz result = -value;

  static_assert(result.numerator() == -3, "");
  static_assert(result.denominator() == 2, "");

  EXPECT_EQ(result, Hertz(-3, 2));
}

TEST(HertzTest, Floor) {
  {
    Hertz h{0};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{0});
  }
  {
    Hertz h{1, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{0});
  }
  {
    Hertz h{3, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{1});
  }
  {
    Hertz h{4, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{2});
  }
  {
    Hertz h{7, 3};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{2});
  }
  {
    Hertz h{-1, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{-1});
  }
  {
    Hertz h{-3, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{-2});
  }
  {
    Hertz h{-4, 2};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{-2});
  }
  {
    Hertz h{-7, 3};
    Hertz h2 = hertz::floor(h);
    EXPECT_EQ(h2, Hertz{-3});
  }
}

TEST(HertzTest, Ceil) {
  {
    Hertz h{0};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{0});
  }
  {
    Hertz h{1, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{1});
  }
  {
    Hertz h{3, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{2});
  }
  {
    Hertz h{4, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{2});
  }
  {
    Hertz h{7, 3};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{3});
  }
  {
    Hertz h{-1, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{0});
  }
  {
    Hertz h{-3, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{-1});
  }
  {
    Hertz h{-4, 2};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{-2});
  }
  {
    Hertz h{-7, 3};
    Hertz h2 = hertz::ceil(h);
    EXPECT_EQ(h2, Hertz{-2});
  }
}

TEST(HertzTest, Round) {
  // Zero
  EXPECT_EQ(hertz::round(Hertz{0}), Hertz{0});

  // Exact integers
  EXPECT_EQ(hertz::round(Hertz{2}), Hertz{2});
  EXPECT_EQ(hertz::round(Hertz{-2}), Hertz{-2});

  // Positive values
  EXPECT_EQ(hertz::round(Hertz{1, 4}), Hertz{0}); //  0.25 ->  0
  EXPECT_EQ(hertz::round(Hertz{1, 2}), Hertz{1}); //  0.50 ->  1
  EXPECT_EQ(hertz::round(Hertz{3, 4}), Hertz{1}); //  0.75 ->  1

  EXPECT_EQ(hertz::round(Hertz{5, 4}), Hertz{1}); //  1.25 ->  1
  EXPECT_EQ(hertz::round(Hertz{3, 2}), Hertz{2}); //  1.50 ->  2
  EXPECT_EQ(hertz::round(Hertz{7, 4}), Hertz{2}); //  1.75 ->  2

  // Negative values
  EXPECT_EQ(hertz::round(Hertz{-1, 4}), Hertz{0});  // -0.25 ->  0
  EXPECT_EQ(hertz::round(Hertz{-1, 2}), Hertz{-1}); // -0.50 -> -1
  EXPECT_EQ(hertz::round(Hertz{-3, 4}), Hertz{-1}); // -0.75 -> -1

  EXPECT_EQ(hertz::round(Hertz{-5, 4}), Hertz{-1}); // -1.25 -> -1
  EXPECT_EQ(hertz::round(Hertz{-3, 2}), Hertz{-2}); // -1.50 -> -2
  EXPECT_EQ(hertz::round(Hertz{-7, 4}), Hertz{-2}); // -1.75 -> -2

  // boundary
  EXPECT_EQ(round(Hertz{49, 100}), Hertz{0}); //  0.49 ->  0
  EXPECT_EQ(round(Hertz{51, 100}), Hertz{1}); //  0.51 ->  1

  EXPECT_EQ(round(Hertz{-49, 100}), Hertz{0});  // -0.49 ->  0
  EXPECT_EQ(round(Hertz{-51, 100}), Hertz{-1}); // -0.51 -> -1
}

TEST(PeriodTest, ReturnsDurationDoubleByDefault) {
  constexpr Hertz hertz{2};

  static_assert(std::is_same<decltype(hertz::period(hertz)), std::chrono::duration<double>>::value, "");

  auto const result = hertz::period(hertz);

  EXPECT_DOUBLE_EQ(result.count(), 0.5);
}

TEST(PeriodTest, ConvertsFractionalFrequencyToDefaultPeriod) {
  constexpr Hertz hertz{3, 2};

  auto const result = hertz::period(hertz);

  EXPECT_DOUBLE_EQ(result.count(), 2.0 / 3.0);
}

TEST(PeriodTest, ConvertsExactlyToIntegralMilliseconds) {
  constexpr Hertz hertz{4};

  auto const result = hertz::period<std::chrono::milliseconds>(hertz);

  EXPECT_EQ(result.count(), 250);
}

TEST(PeriodTest, TruncatesIntegralMillisecondsTowardZero) {
  constexpr Hertz hertz{60};

  auto const result = hertz::period<std::chrono::milliseconds>(hertz);

  EXPECT_EQ(result.count(), 16);
}

TEST(PeriodTest, ConvertsFractionalFrequencyToIntegralMilliseconds) {
  constexpr Hertz hertz{3, 2};

  auto const result = hertz::period<std::chrono::milliseconds>(hertz);

  EXPECT_EQ(result.count(), 666);
}

TEST(PeriodTest, ConvertsToFloatingPointMilliseconds) {
  using DoubleMilliseconds = std::chrono::duration<double, std::milli>;

  constexpr Hertz hertz{60};

  auto const result = hertz::period<DoubleMilliseconds>(hertz);

  EXPECT_DOUBLE_EQ(result.count(), 1000.0 / 60.0);
}

TEST(PeriodTest, ConvertsToMicroseconds) {
  constexpr Hertz hertz{60};

  auto const result = hertz::period<std::chrono::microseconds>(hertz);

  EXPECT_EQ(result.count(), 16666);
}

TEST(PeriodTest, ConvertsToNanoseconds) {
  constexpr Hertz hertz{4};

  auto const result = hertz::period<std::chrono::nanoseconds>(hertz);

  EXPECT_EQ(result.count(), 250000000);
}

TEST(PeriodTest, ConvertsToCustomIntegralDuration) {
  using HundredMilliseconds = std::chrono::duration<int, std::ratio<1, 10>>;

  constexpr Hertz hertz{4};

  auto const result = hertz::period<HundredMilliseconds>(hertz);

  // 4 Hz -> 0.25 s
  // one tick = 0.1 s
  // 0.25 / 0.1 = 2.5 -> 2
  EXPECT_EQ(result.count(), 2);
}

TEST(PeriodTest, ConvertsToCustomFloatingPointDuration) {
  using HundredMilliseconds = std::chrono::duration<double, std::ratio<1, 10>>;

  constexpr Hertz hertz{4};

  auto const result = hertz::period<HundredMilliseconds>(hertz);

  EXPECT_DOUBLE_EQ(result.count(), 2.5);
}

TEST(PeriodTest, ConvertsNegativeFrequency) {
  constexpr Hertz hertz{-4};

  auto const result = hertz::period<std::chrono::milliseconds>(hertz);

  EXPECT_EQ(result.count(), -250);
}

TEST(PeriodTest, TruncatesNegativeIntegralDurationTowardZero) {
  constexpr Hertz hertz{-60};

  auto const result = hertz::period<std::chrono::milliseconds>(hertz);

  EXPECT_EQ(result.count(), -16);
}

TEST(PeriodTest, DefaultPeriodIsConstexpr) {
  constexpr Hertz hertz{2};

  constexpr auto result = hertz::period(hertz);

  static_assert(result.count() == 0.5, "");

  EXPECT_DOUBLE_EQ(result.count(), 0.5);
}

TEST(PeriodTest, IntegralPeriodIsConstexpr) {
  constexpr Hertz hertz{4};

  constexpr auto result = hertz::period<std::chrono::milliseconds>(hertz);

  static_assert(result.count() == 250, "");

  EXPECT_EQ(result.count(), 250);
}

TEST(PeriodTest, FractionalFrequencyConversionIsConstexpr) {
  constexpr Hertz hertz{3, 2};

  constexpr auto result = hertz::period<std::chrono::milliseconds>(hertz);

  static_assert(result.count() == 666, "");

  EXPECT_EQ(result.count(), 666);
}

TEST(HertzTest, StreamInsertion) {
  {
    std::ostringstream oss;
    Hertz h{0};
    oss << h;
    EXPECT_EQ(oss.str(), "0 Hz");
  }
  {
    std::ostringstream oss;
    Hertz h{2};
    oss << h;
    EXPECT_EQ(oss.str(), "2 Hz");
  }
  {
    std::ostringstream oss;
    Hertz h{-2};
    oss << h;
    EXPECT_EQ(oss.str(), "-2 Hz");
  }
  {
    std::ostringstream oss;
    Hertz h{1, 2};
    oss << h;
    EXPECT_EQ(oss.str(), "1/2 Hz");
  }
}

TEST(HertzLiteralTest, ConstructsMillihertz) {
  using namespace hertz::literals;

  constexpr auto value = 500_mHz;

  static_assert(value == Hertz{1, 2}, "");
  EXPECT_EQ(value, Hertz(1, 2));
}

TEST(HertzLiteralTest, ConstructsHertz) {
  using namespace hertz::literals;

  constexpr auto value = 60_Hz;

  static_assert(value == Hertz{60}, "");
  EXPECT_EQ(value, Hertz(60));
}

TEST(HertzLiteralTest, ConstructsKilohertz) {
  using namespace hertz::literals;

  constexpr auto value = 10_kHz;

  static_assert(value == Hertz{10'000}, "");
  EXPECT_EQ(value, Hertz(10'000));
}

TEST(HertzLiteralTest, ConstructsMegahertz) {
  using namespace hertz::literals;

  constexpr auto value = 100_MHz;

  static_assert(value == Hertz{100'000'000}, "");
  EXPECT_EQ(value, Hertz(100'000'000));
}

TEST(HertzLiteralTest, ConstructsGigahertz) {
  using namespace hertz::literals;

  constexpr auto value = 2_GHz;

  static_assert(value == Hertz{2'000'000'000}, "");
  EXPECT_EQ(value, Hertz(2'000'000'000));
}

TEST(HertzLiteralTest, NormalizesMillihertz) {
  using namespace hertz::literals;

  EXPECT_EQ(1000_mHz, 1_Hz);
  EXPECT_EQ(1500_mHz, Hertz(3, 2));
}

TEST(HertzLiteralTest, SupportsNegativeValues) {
  using namespace hertz::literals;

  EXPECT_EQ(-60_Hz, Hertz(-60));
  EXPECT_EQ(-500_mHz, Hertz(-1, 2));
}


namespace {

template<typename... Ts>
constexpr void ignore_unused(const Ts&...) noexcept {}

constexpr Hertz UsedInCompileTime(Hertz h) {
  h++;
  ++h;
  h--;
  --h;
  Hertz h2;
  h += h2;
  h -= h2;
  h *= 2;
  h /= 2;
  return h;
}

} // namespace

TEST(HertzTest, ConstexprTest) {
  constexpr Hertz h1;
  constexpr Hertz h2{0};
  constexpr Hertz h3{1, 2};
  constexpr std::int64_t n = h1.numerator();
  constexpr std::int64_t d = h1.denominator();
  constexpr Hertz h4 = h1 + h2;
  constexpr Hertz h5 = h1 - h2;
  constexpr Hertz h6 = h1 * 6;
  constexpr Hertz h7 = 6 * h1;
  constexpr Hertz h8 = h1 / 6;
  constexpr Hertz h10 = UsedInCompileTime(h1);
  constexpr bool b1 = (h1 == h2);
  constexpr bool b2 = (h1 != h2);
  constexpr bool b3 = (h1 < h2);
  constexpr bool b4 = (h1 <= h2);
  constexpr bool b5 = (h1 > h2);
  constexpr bool b6 = (h1 >= h2);

  constexpr Hertz h11 = hertz::floor(h1);
  constexpr Hertz h12 = hertz::ceil(h1);
  constexpr Hertz h13 = hertz::round(h1);
  constexpr auto p1 = hertz::period(h3);
  constexpr auto p2 = hertz::period<std::chrono::milliseconds>(h3);
  constexpr auto p3 = hertz::period<std::chrono::duration<double, std::milli>>(h3);

  ignore_unused(h1, h2, h3, h4, h5, h6, h7, h8, h10, b1, b2, b3, b4, b5, b6, n, d, h11, h12, h13, p1, p2, p3);
}