#include "color.hpp"

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (r < kMinColorValue || r > kMaxColorValue || g < kMinColorValue || g > kMaxColorValue || b < kMinColorValue || b > kMaxColorValue) {
    throw std::runtime_error("color parameters are out of range");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}

