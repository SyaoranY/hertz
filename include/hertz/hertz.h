#ifndef HERTZ_HERTZ_H_
#define HERTZ_HERTZ_H_

#include <assert.h>
#include <cstdint>
#include <ostream>

namespace hertz {

/**
 * @brief Represents a frequency in hertz as an exact rational value.
 *
 * Hertz stores a frequency as a signed 64-bit numerator and denominator.
 * Values are automatically normalized to their reduced form, with the
 * denominator always kept positive.
 *
 * Arithmetic overflow is not checked. Intermediate and final arithmetic
 * results are expected to be representable by std::int64_t.
 */
class Hertz final {
 public:
  /**
   * @brief Constructs a zero-frequency value.
   */
  constexpr Hertz() noexcept
    : numerator_(0)
    , denominator_(1) {}

  /**
   * @brief Constructs an integer frequency.
   *
   * @param frequency Frequency in hertz.
   */
  constexpr explicit Hertz(std::int64_t const frequency) noexcept
    : numerator_(frequency)
    , denominator_(1) {}

  /**
   * @brief Constructs a rational frequency.
   *
   * The value is automatically reduced to its canonical form. If the
   * denominator is negative, the sign is moved to the numerator.
   *
   * @param numerator Numerator of the frequency value.
   * @param denominator Denominator of the frequency value.
   *
   * @pre denominator != 0
   */
  constexpr Hertz(std::int64_t const numerator, std::int64_t const denominator) noexcept
    : numerator_(numerator)
    , denominator_(denominator) {
    assert(denominator != 0);
    normalize();
  }

  Hertz(Hertz const&) = default;
  Hertz(Hertz&&) noexcept = default;

  Hertz& operator=(Hertz const&) = default;
  Hertz& operator=(Hertz&&) noexcept = default;

  ~Hertz() = default;

  /**
   * @brief Returns the numerator of the normalized frequency value.
   *
   * @return The numerator.
   */
  constexpr std::int64_t numerator() const noexcept { return numerator_; }

  /**
   * @brief Returns the denominator of the normalized frequency value.
   *
   * @return The positive denominator.
   */
  constexpr std::int64_t denominator() const noexcept { return denominator_; }

  constexpr Hertz& operator++() noexcept {
    numerator_ += denominator_;
    return *this;
  }

  constexpr Hertz operator++(int) noexcept {
    Hertz temp{*this};
    ++(*this);
    return temp;
  }

  constexpr Hertz& operator--() noexcept {
    numerator_ -= denominator_;
    return *this;
  }

  constexpr Hertz operator--(int) noexcept {
    Hertz temp{*this};
    --(*this);
    return temp;
  }

  constexpr Hertz& operator+=(Hertz const& rhs) noexcept {
    numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
    denominator_ *= rhs.denominator_;
    normalize();
    return *this;
  }

  constexpr Hertz& operator-=(Hertz const& rhs) noexcept {
    numerator_ = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
    denominator_ *= rhs.denominator_;
    normalize();
    return *this;
  }

  constexpr Hertz& operator*=(std::int64_t const rhs) noexcept {
    numerator_ *= rhs;
    normalize();
    return *this;
  }

  /**
   * @brief Divides the frequency by an integer scalar.
   *
   * @param rhs Divisor.
   *
   * @pre rhs != 0
   */
  constexpr Hertz& operator/=(std::int64_t const rhs) noexcept {
    assert(rhs != 0);
    denominator_ *= rhs;
    normalize();
    return *this;
  }

 private:
  /**
   * @brief Normalizes the internal rational representation.
   *
   * Reduces the numerator and denominator by their greatest common divisor,
   * keeps the denominator positive, and canonicalizes zero as 0/1.
   *
   * @pre denominator_ != 0
   */
  constexpr void normalize() noexcept {
    if (numerator_ == 0) {
      denominator_ = 1;
      return;
    }

    std::int64_t divisor = gcd(numerator_, denominator_);
    numerator_ /= divisor;
    denominator_ /= divisor;

    if (denominator_ < 0) {
      numerator_ = -numerator_;
      denominator_ = -denominator_;
    }
  }

  static constexpr std::int64_t gcd(std::int64_t a, std::int64_t b) noexcept {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;

    while (b != 0) {
      std::int64_t temp = a % b;
      a = b;
      b = temp;
    }
    return a;
  }

  std::int64_t numerator_;
  std::int64_t denominator_;
};

constexpr Hertz operator+(Hertz const& lhs, Hertz const& rhs) noexcept {
  Hertz result{lhs};
  result += rhs;
  return result;
}

constexpr Hertz operator-(Hertz const& lhs, Hertz const& rhs) noexcept {
  Hertz result{lhs};
  result -= rhs;
  return result;
}

constexpr Hertz operator*(Hertz const& lhs, std::int64_t const rhs) noexcept {
  Hertz result{lhs};
  result *= rhs;
  return result;
}

constexpr Hertz operator*(std::int64_t const lhs, Hertz const& rhs) noexcept {
  Hertz result{rhs};
  result *= lhs;
  return result;
}

/**
 * @brief Divides a frequency by an integer scalar.
 *
 * @param lhs Frequency value.
 * @param rhs Divisor.
 *
 * @return The resulting frequency.
 *
 * @pre rhs != 0
 */
constexpr Hertz operator/(Hertz const& lhs, std::int64_t const rhs) noexcept {
  Hertz result{lhs};
  result /= rhs;
  return result;
}

constexpr bool operator==(Hertz const& lhs, Hertz const& rhs) noexcept {
  return lhs.numerator() == rhs.numerator() && lhs.denominator() == rhs.denominator();
}

constexpr bool operator!=(Hertz const& lhs, Hertz const& rhs) noexcept {
  return !(lhs == rhs);
}

constexpr bool operator<(Hertz const& lhs, Hertz const& rhs) noexcept {
  return lhs.numerator() * rhs.denominator() < rhs.numerator() * lhs.denominator();
}

constexpr bool operator<=(Hertz const& lhs, Hertz const& rhs) noexcept {
  return !(rhs < lhs);
}

constexpr bool operator>(Hertz const& lhs, Hertz const& rhs) noexcept {
  return rhs < lhs;
}

constexpr bool operator>=(Hertz const& lhs, Hertz const& rhs) noexcept {
  return !(lhs < rhs);
}

/**
 * @brief Rounds a frequency down to an integer frequency.
 *
 * Rounding is performed toward negative infinity.
 *
 * @param hertz Frequency value to round.
 *
 * @return The greatest integer frequency not greater than @p hertz.
 *
 * @par Examples
 * @code
 * floor(Hertz{3, 2})  == Hertz{1};
 * floor(Hertz{-3, 2}) == Hertz{-2};
 * @endcode
 */
constexpr Hertz floor(Hertz const& hertz) noexcept {
  std::int64_t quotient = hertz.numerator() / hertz.denominator();
  std::int64_t remainder = hertz.numerator() % hertz.denominator();
  if (remainder < 0) {
    --quotient;
  }
  return Hertz(quotient);
}

/**
 * @brief Rounds a frequency up to an integer frequency.
 *
 * Rounding is performed toward positive infinity.
 *
 * @param hertz Frequency value to round.
 *
 * @return The smallest integer frequency not less than @p hertz.
 *
 * @par Examples
 * @code
 * ceil(Hertz{3, 2})  == Hertz{2};
 * ceil(Hertz{-3, 2}) == Hertz{-1};
 * @endcode
 */
constexpr Hertz ceil(Hertz const& hertz) noexcept {
  std::int64_t quotient = hertz.numerator() / hertz.denominator();
  std::int64_t remainder = hertz.numerator() % hertz.denominator();
  if (remainder > 0) {
    ++quotient;
  }
  return Hertz(quotient);
}

/**
 * @brief Rounds a frequency to the nearest integer frequency.
 *
 * Halfway cases are rounded away from zero, matching the behavior of
 * std::round.
 *
 * @param hertz Frequency value to round.
 *
 * @return The nearest integer frequency.
 *
 * @par Examples
 * @code
 * round(Hertz{3, 2})  == Hertz{2};
 * round(Hertz{-3, 2}) == Hertz{-2};
 * @endcode
 */
constexpr Hertz round(Hertz const& hertz) noexcept {
  std::int64_t quotient = hertz.numerator() / hertz.denominator();
  std::int64_t remainder = hertz.numerator() % hertz.denominator();
  if (remainder > 0) {
    if (remainder >= hertz.denominator() - remainder) {
      ++quotient;
    }
  } else if (remainder < 0) {
    if (-remainder >= hertz.denominator() + remainder) {
      --quotient;
    }
  }
  return Hertz(quotient);
}

/**
 * @brief Writes a frequency value to an output stream.
 *
 * Integer frequencies are written as "n Hz". Fractional frequencies are
 * written as "n/d Hz".
 *
 * @param os Output stream.
 * @param value Frequency value to write.
 *
 * @return The output stream.
 *
 * @par Examples
 * @code
 * std::cout << Hertz{5};     // 5 Hz
 * std::cout << Hertz{3, 2};  // 3/2 Hz
 * @endcode
 */
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Hertz const& hertz) {
  os << hertz.numerator();
  if (hertz.denominator() != 1) {
    os << "/" << hertz.denominator();
  }
  os << " Hz";
  return os;
}

} // namespace hertz

#endif /* HERTZ_HERTZ_H_ */
