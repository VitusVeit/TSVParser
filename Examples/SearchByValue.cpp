#include <iostream>
#include "../tsvParser.hpp"

int main()
{
	tsv::File f;

	f += {{"Name"}, {"Frank"}, {"Mario"}, {"Gordon"}};

	f += {{"Age"}, {22}, {44}, {55}};

	f += {{"Height"}, {5.6}, {4.89f}, {"32,22"}};

	std::cout << f["Height"][3].GetPreciseNumber() << '\n';
}
