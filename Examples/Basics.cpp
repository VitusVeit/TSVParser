#include <iostream>
#include "../tsvParser.hpp"

int main()
{
    tsv::File myFile;

    // You can create a row by a vector of strings.
    myFile[0] = {"Name", "Age", "Job", "NA"};

    myFile += tsv::Row({"Frank Freeman", "45", "Nuclear Scientist"});

    // Or add them manually.
    tsv::Row r1;

    r1 += "Mario Rossi";
    r1 += "25";

    myFile += r1;

    myFile[2] += "Bean Counter";

    // You can also access individual columns given their rows.
    myFile[2][1] = "32";

    // You can remove a specific value from a row.
    myFile[0] -= "NA";

    // Use 'ToString' to convert the TSV class to a text format.
    std::cout << myFile.ToString() << '\n';
}