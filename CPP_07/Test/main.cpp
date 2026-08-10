#include <iostream>

template <typename T1, typename T2>
class Pair
{
  private:
    T1 first;
    T2 second;

  public:
    Pair()
    {
      this->first = 10;
      this->second = 20;
    }
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
  // this line will not work because it dones not know the datatype the attributes of the class will have!
  // Pair anonymos;
  // that's why you should specify the datatypes in the declaration like this:
  Pair<int, int> anonymos;
  anonymos.display();

  return 0;
}
