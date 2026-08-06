#include <gtest/gtest.h>
#include <hertz/hertz.h>

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
    hertz::Hertz h2(3, 4);
    EXPECT_EQ(h2.numerator(), 3);
    EXPECT_EQ(h2.denominator(), 4);
  }
  {
    hertz::Hertz h2(2, 4);
    EXPECT_EQ(h2.numerator(), 1);
    EXPECT_EQ(h2.denominator(), 2);
  }
  {
    hertz::Hertz h2(0, 4);
    EXPECT_EQ(h2.numerator(), 0);
    EXPECT_EQ(h2.denominator(), 1);
  }
  {
    hertz::Hertz h2(2, 1);
    EXPECT_EQ(h2.numerator(), 2);
    EXPECT_EQ(h2.denominator(), 1);
  }
  {
    hertz::Hertz h2(100, 5);
    EXPECT_EQ(h2.numerator(), 20);
    EXPECT_EQ(h2.denominator(), 1);
  }
  {
    hertz::Hertz h2(100, 30);
    EXPECT_EQ(h2.numerator(), 10);
    EXPECT_EQ(h2.denominator(), 3);
  }
}

