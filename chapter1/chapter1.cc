#include "Sales_item.h"

int main()
{
  Sales_item	book;

  std::cout << "Input format: ISBN Units_Sold Unit_Price" << std::endl;
  while (std::cin >> book)
  {
    std::cout << "Result:" << std::endl;
    std::cout << book << std::endl;
  }
  std::cout << "read EOF, exit" << std::endl;
  return (0);
}
