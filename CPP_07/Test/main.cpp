#include <iostream>

template <typename T1, typename T2>
class Pair
{
  private:
    T1 first;
    T2 second;

  public:
    Pair(T1 a, T2 b)
    {
      this->first = a;
      this->second = b;
    }
    void display()
    {
      std::cout << "First: " << this->first << "; Second: " << this->second << '\n';
    }
};

int main()
{
  Pair person("John", 30);  // same as: Pair<string, int> person("John", 30);
  Pair score(51, 9.5); // same as: Pair<int, double> score(51, 9.5);

  person.display();
  score.display();
  return 0;
}
