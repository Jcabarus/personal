#include <iostream>

int main()
{
  int miles;
  int km = (miles * 3) * 100;
  // Add your code below
  std::cout << "Enter distance in miles: ";
  std::cin >> miles;
  
  std::cout << "Distance in Miles -> Kilometers\n";
  std::cout << km << "\n";

  return 0;
}