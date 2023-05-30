/*
	 _______ _______      __  _____                         
	|__   __/ ____\ \    / / |  __ \                        
	   | | | (___  \ \  / /  | |__) |_ _ _ __ ___  ___ _ __ 
	   | |  \___ \  \ \/ /   |  ___/ _` | '__/ __|/ _ \ '__|
	   | |  ____) |  \  /    | |  | (_| | |  \__ \  __/ |   
	   |_| |_____/    \/     |_|   \__,_|_|  |___/\___|_|   
	Version 1.0

	A simple and easy-to-use TSV Parser, it can read TSV files, modify them, and export them.

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
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

namespace tsv
{
	struct Column
	{
		bool IsNumber()
		{
			return IsNumber(value);
		}

		int GetNumber()
		{
			if (IsNumber()) return std::stoi(value);
			return 0;
		}

		double GetPreciseNumber()
		{
			if (IsNumber()) return std::stod(value);
			return 0;
		}

		std::string GetString()
		{
			if (IsNumber())
			{
				std::string copy(value);
			
				std::replace(copy.begin(), copy.end(), '.', ',');

				return copy;
			}
			return value;
		}

		void operator+=(int value)
		{
			if(IsNumber())
			{
				this->value = std::to_string(std::stod(this->value) + value);
				removeExtraZeros();
			}
		}

		void operator+=(double value)
		{
			if(IsNumber())
			{
				this->value = std::to_string(std::stod(this->value) + value);
				removeExtraZeros();
			}
		}

		void operator+=(std::string value)
		{
			if (IsNumber() && setDotPeriot(value))
			{
				this->value = std::to_string(std::stod(this->value) + std::stod(value));
				removeExtraZeros();
			}
			else this->value += value;
		}

		void operator-=(int value)
		{
			if (IsNumber())
			{
				this->value = std::to_string(std::stod(this->value) - value);
				removeExtraZeros();
			}
		}

		void operator-=(double value)
		{
			if (IsNumber())
			{
				this->value = std::to_string(std::stod(this->value) - value);
				removeExtraZeros();
			}
		}

		void operator-=(std::string value)
		{
			if (!IsNumber()) return;

			if (setDotPeriot(value))
			{
				this->value = std::to_string(std::stod(this->value) - std::stod(value));
				removeExtraZeros();
			}
		}

		void operator=(int value)
		{
			this->value = std::to_string(value);
		}

		void operator=(double value)
		{
			this->value = std::to_string(value);
			removeExtraZeros();
		}

		void operator=(std::string value)
		{
			setDotPeriot(value);
			
			this->value = value;

			if(IsNumber()) removeExtraZeros();
		}

		bool operator==(int otherValue)
		{
			if (IsNumber())
				return std::stod(this->value) == otherValue;
			return false;
		}

		bool operator==(double otherValue)
		{
			if (IsNumber())
				return std::stod(this->value) == otherValue;
			return false;
		}

		bool operator==(std::string otherValue)
		{
			return this->value == otherValue;
		}

		bool operator==(Column otherColumn) const
		{
			return this->value == otherColumn.value;
		}
	private:
		std::string value = "";

		// Check if a given string is a number, works with integer, decimal and exponential numbers.
		bool IsNumber(std::string string)
		{
			std::stringstream stream;

			stream << string;
			
			double num = 0;
			
			stream >> num;
			
			if (stream.good())
				return false;
			if (num == 0 && string[0] != 0)
				return false;

			return true;
		}

		// Removes extra zeros eg. 2.3200 -> 2.32.
		void removeExtraZeros()
		{
			if (!IsNumber()) return;
    
			// Check if string is exponential, if it is then don't remove extra zeros
			{			
				std::string copy(value);
				
				std::transform(copy.begin(), copy.end(),
				copy.begin(), ::tolower);
					
				if (copy.find('e') != std::string::npos) return;
			}

			value.erase(value.find_last_not_of('0') + 1, std::string::npos);
			value.erase(value.find_last_not_of('.') + 1, std::string::npos);
		}

		// Checks if the given string is a number or not.
		// Returns true if it is, otherwise false.
		bool setDotPeriot(std::string& string)
		{
			// 'string' is already a number and doesn't need any conversions.
			if (IsNumber(string)) return true;

			// No conversion for 'string' available.
			if (string.find(',') == std::string::npos) return false;

			std::string copy(string);
			
			std::replace(copy.begin(), copy.end(), ',', '.');

			// Conversion didn't work, 'string' is still a number.
			if (!IsNumber(copy)) return false;

			// Conversion worked, 'string' is now a C++ decimal number.
			string = copy;

			return true;
		}
	};

	struct Row
	{
		std::map<int, Column> Columns;

		Row(std::vector<std::string> columns = {})
		{
			for (std::string& s : columns)
			{
				*this += s;
			}
		}

		void operator+=(int column)
		{
			Columns[Columns.size()] = column;
		}

		void operator+=(double column)
		{
			Columns[Columns.size()] = column;
		}

		void operator+=(std::string column)
		{
			Columns[Columns.size()] = column;
		}

		void operator+=(Column column)
		{
			Columns[Columns.size()] = column;
		}

		void operator-=(int column)
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

		void operator-=(double column)
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

		void operator-=(Column column)
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

		// TODO: Add option to search for int, double and string.

		Column& operator[](int columnNumber)
		{
			return Columns[columnNumber];
		}

		bool operator==(const Row other) const
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

	struct File
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
					stream << Rows[i].Columns[i2].GetString();

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
			for(std::pair<const int, Row>& r : Rows)
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
}
