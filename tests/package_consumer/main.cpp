#include <hertz/hertz.h>
#include <iostream>

int main() {
  hertz::Hertz h;
  std::cout << h.numerator() << "/ " << h.denominator() << std::endl;
  return 0;
}