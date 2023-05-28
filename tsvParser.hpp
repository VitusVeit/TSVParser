/*
     _______ _______      __  _____                         
    |__   __/ ____\ \    / / |  __ \                        
       | | | (___  \ \  / /  | |__) |_ _ _ __ ___  ___ _ __ 
       | |  \___ \  \ \/ /   |  ___/ _` | '__/ __|/ _ \ '__|
       | |  ____) |  \  /    | |  | (_| | |  \__ \  __/ |   
       |_| |_____/    \/     |_|   \__,_|_|  |___/\___|_|   
    Version 1.0

    A simple and easy-to-use C++ TSV Parser, it can read TSV files, modify them, and export them.

	This library is under the MIT License

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct Row
{
	std::map<int, std::string> Columns;

	Row(std::vector<std::string> columns = {})
	{
		for (std::string& s : columns)
		{
			*this += s;
		}
	}

	void operator+=(std::string column)
	{
		Columns[Columns.size()] = column;
	}

	void operator-=(std::string column)
	{
		for(auto& n : Columns)
		{
			if (n.second == column)
			{
				Columns.erase(n.first);
				return;
			}
		}
	}

	std::string& operator[](int columnNumber)
	{
		return Columns[columnNumber];
	}

	bool operator==(Row other)
	{
		return this->Columns == other.Columns;
	}	

	void operator=(std::vector<std::string> columns)
	{
		Columns.clear();

		for (std::string& s : columns)
		{
			*this += s;
		}
	}
};

struct TSV
{
	std::map<int, Row> Rows;

	void OpenString(std::string string)
	{
		std::istringstream inputStream(string);

		std::string line;

		while (std::getline(inputStream, line, '\n'))
		{
			Row newLine;

			std::string buffer = "";

			for (auto c : line)
			{
				if (c == '\t')
				{
					newLine += buffer;
					buffer.clear();
				}
				else
					buffer += c;
			}

			newLine += buffer;

			Rows[Rows.size()] = newLine;
		}
	}

	void OpenFile(std::string path)
	{
		std::ifstream file(path);

		if (!file.is_open()) return;

		std::stringstream stream;

		file >> stream.rdbuf();

		OpenString(stream.str());
		
		file.close();
	}

	std::string ToString()
	{
		std::stringstream stream;

		for (int i = 0; i < Rows.size(); i++)
		{
			int columnsSize = 1;

			for(auto& n : Rows[i].Columns)
			{
				if (n.first > 0)
					columnsSize = n.first + 1;
			}

			for (int i2 = 0; i2 < columnsSize; i2++)
			{
				stream << Rows[i].Columns[i2];

				if (i2 == columnsSize - 1 && i != Rows.size() - 1) stream << '\n';
				else if (i2 != columnsSize - 1) stream << '\t';
			}
		}

		return stream.str();
	}

	void ToFile(std::string path)
	{
		std::ofstream file(path);
		
		file << ToString();
		
		file.close();
	}

	void operator+=(Row row)
	{
		Rows[Rows.size()] = row;
	}

	void operator-=(Row row)
	{
		for(auto& r : Rows)
		{
			if (r.second == row)
			{
				Rows.erase(r.first);
				return;
			}
		}
	}

	Row& operator[](int rowNumber)
	{
		return Rows[rowNumber];
	}
};
