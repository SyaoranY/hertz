#include <gtest/gtest.h>
#include <hertz/hertz.h>
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

TEST(HertzTest, ModuloAssignment) {
  Hertz value{7, 2};

  Hertz& result = (value %= 2);

  EXPECT_EQ(value, Hertz(1, 2));
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

TEST(HertzTest, Modulo) {
  const Hertz value{7, 2};

  const Hertz result = value % 2;

  EXPECT_EQ(result, Hertz(1, 2));
  EXPECT_EQ(value, Hertz(7, 2));
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

TEST(HertzTest, Floor) {
  // TODO
}

TEST(HertzTest, Ceil) {
  // TODO
}

TEST(HertzTest, Round) {
  // TODO
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

namespace {

template <typename... Ts>
constexpr void ignore_unused(const Ts&...) noexcept
{
}

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
  h %= 2;
  return h;
}

}

TEST(HertzTest, ConstexprTest) {
  constexpr Hertz h1{0};
  constexpr Hertz h2{0};
  constexpr Hertz h3{1, 2};
  constexpr std::int64_t n = h1.numerator();
  constexpr std::int64_t d = h1.denominator();
  constexpr Hertz h4 = h1 + h2;
  constexpr Hertz h5 = h1 - h2;
  constexpr Hertz h6 = h1 * 6;
  constexpr Hertz h7 = 6 * h1;
  constexpr Hertz h8 = h1 / 6;
  constexpr Hertz h9 = h1 % 6;
  constexpr Hertz h10 = UsedInCompileTime(h1);
  constexpr bool b1 = (h1 == h2);
  constexpr bool b2 = (h1 != h2);
  constexpr bool b3 = (h1 < h2);
  constexpr bool b4 = (h1 <= h2);
  constexpr bool b5 = (h1 > h2);
  constexpr bool b6 = (h1 >= h2);

  ignore_unused(h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, b1, b2, b3, b4, b5, b6, n, d);
}