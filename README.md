# TSVParser v 1.1.0 🖋️
A simple and easy-to-use C++ TSV Parser, it can read TSV files, modify them, and export them.

For now, it only supports strings (that for a TSV Parser is probably enough) but I'll be working on adding more types if I have time.  
Everything is inside a single header file `tsvParser`, just download it, put it in your project, and you're good to go!

# Examples ⚙️
With TSVParser, you can access TSV files like they're two-dimensional arrays and add or remove rows and columns with `+=/-=` like they're strings:
```cpp
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
```
Result: 🫘
| Name | Age | Job |
|:--- |:--- |:--- |
| Frank Freeman | 45 | Nuclear Scientist |
| Mario Rossi | 32 | Bean Counter |

Of course, we can also load and export TSV files:
```cpp
tsv::File antherFileOfMine;

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

Since version `1.1.0`, TSV files have now support for numbers:
```cpp
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
```
Result: 🔢
| Integer | Decimal | Exponential |
|:--- |:--- |:--- |
| 4 | 4,44 | 2,3e+2 |

**NOTE**: In most spreadsheet editors, decimal numbers contain `,` and those who contain `.` are considerated text. So when converting to string/file, TSVWrapper will change all `.` contained in numbers to `,` for compatibility.

# License ⚖️
This library is under the MIT License, which means you can use this Parser for anything but I won't be liable for damages that this Parser could cause.
If you want to know more, you can check out the `LICENSE` file or the text written at the top of the `tsvParser.hpp` header.
