#include <iostream>
#include <functional>

namespace poly
{
  //Функция
  //          _1     _2
  int plus(int a, int b) {
    return a + b;
  }
  //Функтор
  struct Plus {
    int operator()(int a, int b) {
      return plus(a, b);
    }
  };

  struct A {
    //foo(A &, int)
    void foo(int a) {
      std::cout << "call foo with " << a << "\n";
    }
  };
}

int main() {
  int x = 10;
  int y = -5;
  //x + y
  std::cout << poly::plus(x, y);

  //x + 5
  using namespace std::placeholders;

  //plus(5, _1) -> plus5(_1)
  std::function< int(int) > plus5 = std::bind(poly::plus, 5, _1);
  std::cout << "\n" << plus5(15);

  auto yaplus5 = std::bind(poly::plus, 5, _2);
  std::cout << "\n" << yaplus5(-100, 15);

  //f(x) = x + x
  auto f2x = std::bind(std::plus< int >{}, _1, _1);
  std::cout << "\n" << f2x(10);

  //f(x) = 2 * x
  auto yaf2x = std::bind(std::multiplies< int >{}, _1, 2);
  std::cout << "\n" << yaf2x(20);

  //g0(x, y) = x^2 + y * x
  //g1(x, y) = x^2 + y * x + y^2
  auto square = std::bind(std::multiplies< int >{}, _1, _1);
  auto g0 = std::bind(std::plus< int >{},
    square,
    std::bind(std::multiplies< int >{}, _2, _1)
  );
  auto g1 = std::bind(std::plus< int >{},
    g0,
    std::bind(square, _2)
  );
  std::cout << "\n" << g0(2, 3);
  std::cout << "\n" << g1(2, 3);

  //bind to method
  poly::A a;
  auto bindToMethod = std::bind(&poly::A::foo, std::ref(a), _1);

  bindToMethod(100);

  std::cout << "\n";
}
