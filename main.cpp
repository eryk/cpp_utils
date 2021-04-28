#include <iostream>

#include "include/visit_struct/visit_struct.hpp"

struct my_type {
  int a;
  float b;
  std::string c;
};

VISITABLE_STRUCT(my_type, a, b, c);

void debug_print(const my_type &my_struct) {
  visit_struct::for_each(my_struct,
                         [](const char *name, const auto &value) {
                           auto field_type = typeid(value).name();
                           std::cerr << name << " " << field_type << ": " << value << std::endl;
                         });
}

int main() {
  my_type myType{5, 2.0, "eryk"};
  debug_print(myType);
  return 0;
}
