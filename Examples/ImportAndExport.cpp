#include <iostream>
#include "../tsvParser.hpp"

int main()
{
    tsv::File antherFileOfMine;

    // You can open other files or read from strings with 'OpenFile' and 'OpenString'.
    antherFileOfMine.OpenFile("test.tsv");

    // Modify it a bit...
    antherFileOfMine[3][0] = "Chocolate Bar";

    // ...and also export it to a file or turn it into a string with 'ToFile' and 'ToString'!
    antherFileOfMine.ToFile("shoppingList.tsv");
}