#ifndef COLOR_H
#define COLOR_H
#include <stdexcept>
#include <cmath>
class Color {
public:
  Color() = default;
  Color(int r, int g, int b);
  int Red() const { return red_; }
  int Green() const { return green_; }
  int Blue() const { return blue_; };
  

private:
  int red_ = 0;
  int green_ = 0;
  int blue_ = 0;
  static const int kMaxColorValue = 255;
  static const int kMinColorValue = 0;
};

bool operator==(const Color& rhs, const Color& lhs);


#endif