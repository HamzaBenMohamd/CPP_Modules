#include <iostream>

class Base
{
	public:
		virtual void show() {}
};

class Derived : public Base
{
	public:
		void display()
		{
			std::cout << "Dynamic Cast Successful\n";
		}
};

int main()
{
	Base *ptr = new Derived();
	Derived *d_ptr = dynamic_cast<Derived*>(ptr);
	if (d_ptr)
		d_ptr->display();
	delete ptr;
	return 0;
}
