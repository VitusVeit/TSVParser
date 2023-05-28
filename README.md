# TSVParser v 1.0 🖋️
A simple and easy-to-use C++ TSV Parser, it can read TSV files, modify them, and export them.

For now, it only supports strings (that for a TSV Parser is probably enough) but I'll be working on adding more types if I have time.  
Everything is inside a single header file `tsvParser`, just download it, put it in your project, and you're good to go!

# Examples ⚙️
With TSVParser, you can access TSV files like they're two-dimensional arrays and add or remove rows and columns with `+=/-=` like they're strings:
```cpp
TSV myFile;

// You can create a row by a vector of strings.
myFile[0] = {"Name", "Age", "Job", "NA"};

myFile += Row({"Frank Freeman", "45", "Nuclear Scientist"});

// Or add them manually.
Row r1;

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
```
Result: 🫘
| Name | Age | Job |
|:--- |:--- |:--- |
| Frank Freeman | 45 | Nuclear Scientist |
| Mario Rossi | 32 | Bean Counter |

Of course, we can also load and export TSV files:
```cpp
TSV antherFileOfMine;

// You can open other files or read from strings with 'OpenFile' and 'OpenString'.
antherFileOfMine.OpenFile("test.tsv");

// Modify it a bit...
antherFileOfMine[3][0] = "Chocolate Bar";

// ...and also export it to a file or turn it into a string with 'ToFile' and 'ToString'!
antherFileOfMine.ToFile("shoppingList.tsv");
```
Result: 🍫
| Product | Quantity | Price |
|:--- |:--- |:---|
| Apple | 4 | 2,5 |
| Bread | 1 | 5 |
| Chocolate Bar | 5 | 1,2 |

# License ⚖️
This library is under the MIT License, which means you can use this Parser for anything but I won't be liable for damages that this Parser could cause.
If you want to know more, you can check out the `LICENSE` file or the text written at the top of the `tsvParser.hpp` header.
