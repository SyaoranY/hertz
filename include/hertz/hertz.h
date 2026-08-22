#ifndef HERTZ_HERTZ_H_
#define HERTZ_HERTZ_H_

#include <assert.h>
#include <cstdint>
#include <ostream>

namespace hertz {

class Hertz final {
 public:
  constexpr Hertz() noexcept
    : numerator_(0)
    , denominator_(1) {}

  constexpr explicit Hertz(std::int64_t const frequency) noexcept
    : numerator_(frequency)
    , denominator_(1) {}

  constexpr Hertz(std::int64_t const numerator, std::int64_t const denominator) noexcept
    : numerator_(numerator)
    , denominator_(denominator) {
    normalize();
  }

  Hertz(Hertz const&) = default;
  Hertz(Hertz&&) noexcept = default;

  Hertz& operator=(Hertz const&) = default;
  Hertz& operator=(Hertz&&) noexcept = default;

  ~Hertz() = default;

  constexpr std::int64_t numerator() const noexcept { return numerator_; }

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

  constexpr Hertz& operator/=(std::int64_t const rhs) noexcept {
    denominator_ *= rhs;
    normalize();
    return *this;
  }

  constexpr Hertz& operator%=(std::int64_t rhs) noexcept {
    numerator_ %= rhs;
    return *this;
  }

 private:
  constexpr void normalize() noexcept {
    assert(denominator_ != 0);

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

constexpr Hertz operator/(Hertz const& lhs, std::int64_t const rhs) noexcept {
  Hertz result{lhs};
  result /= rhs;
  return result;
}

constexpr Hertz operator%(Hertz const& lhs, std::int64_t const rhs) noexcept {
  Hertz result{lhs};
  result %= rhs;
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

constexpr Hertz floor(Hertz const& hertz) noexcept {
  std::int64_t quotient = hertz.numerator() / hertz.denominator();
  std::int64_t remainder = hertz.numerator() % hertz.denominator();
  if (remainder < 0) {
    --quotient;
  }
  return Hertz(quotient);
}

constexpr Hertz ceil(Hertz const& hertz) noexcept {
  std::int64_t quotient = hertz.numerator() / hertz.denominator();
  std::int64_t remainder = hertz.numerator() % hertz.denominator();
  if (remainder > 0) {
    ++quotient;
  }
  return Hertz(quotient);
}

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
