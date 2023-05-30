#include <iostream>
#include "../tsvParser.hpp"

int main()
{
    tsv::File myFile;

    myFile[0] = {"Integer", "Decimal", "Exponential"};

    // Create a row.
    tsv::Row r1;

    // You can add integer and double numbers directly.
    r1 += 4;
    r1 += 2.2;

    // Or add a string that follows the Google Sheets format or other spreadsheet editors.
    r1[1] += "2,24";

    // You add exponential numbers too, both directly and by string!
    r1 += 2.3e+2;
    r1[2] = "2.3e+2";

    // Add the row to the file.
    myFile += r1;

    std::cout << myFile.ToString() << '\n';
}