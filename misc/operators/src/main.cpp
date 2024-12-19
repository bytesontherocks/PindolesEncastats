#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace { 
  class Complex
  {
    public:
      explicit Complex(const float i, const float j) : m_i(i), m_j(j) {};

      float getI() const {return m_i;};
      float getJ() const {return m_j;};

    private:
      float m_i;
      float m_j;
  };
  inline Complex operator+(const Complex& rhs, const Complex& lhs) {
    return Complex{rhs.getI()+lhs.getI(), rhs.getJ()+lhs.getJ()};
  }
  inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "Real: " << c.getI() << ", Im: :" << c.getJ() << std::endl;
    return os;
  }
}

int main(int argc, char** argv)
{
  const auto c = Complex{2.3, 4.9};
  const auto cc = Complex{6.5, 5.5};

  std::cout << c + cc << std::endl;

  return EXIT_SUCCESS;
}