#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	// Ensure at least one number is provided
	if (argc < 2)
	{
		std::cerr << "Error\n";
		return 1;
	}

	try
	{
		PmergeMe sorter;
		sorter.process(argc, argv);
	}
	catch (const std::exception& e)
	{
		// Catches bad inputs like negative numbers or alphabetical characters
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
