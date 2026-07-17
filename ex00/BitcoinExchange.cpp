#include "BitcoinExchange.hpp"

#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { (void)other; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) { (void)other; return *this; }
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *input_file_name, const char *data_file_name) {
	getDataMap(data_file_name);
	getInputMap(input_file_name);
}

void BitcoinExchange::getDataMap(const char *filename) {
	std::ifstream dataFile(filename);
	std::string		line;
	if (!dataFile.is_open())
		throw std::runtime_error("could not open file.");
	if (!std::getline(dataFile, line))
		throw std::runtime_error("Data file is empty.");

	std::string	date_str;
	std::string	value_str;
	while (std::getline(dataFile, date_str, ',')) {
		if (dataFile.eof() || date_str.empty())
			break;
		std::getline(dataFile, value_str);
		std::istringstream(value_str) >> _input.value;
		_data_map.insert(std::make_pair(date_str, _input.value));
	}
}

void BitcoinExchange::getInputMap(const char *filename) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
		throw std::runtime_error("Input file couldn't be opened.");

	std::string line;
	std::string value_str;

	if (!std::getline(inputFile, line))
		throw std::runtime_error("Input File is empty.");
	if (line != "date | value")
		throw std::runtime_error("First line needs to be 'date | value'.");
	
	while (std::getline(inputFile, line)) {
		try {
			if (inputFile.eof())
				break;
			if (line.empty())
				continue;

			std::size_t pipe = line.find('|');
			if (pipe == std::string::npos)
				throw std::runtime_error("Missing '|'.");
			_input.date = line.substr(0, pipe);
			if (*(_input.date.end() - 1) != ' ')
				throw std::runtime_error("'|' needs to be surrounded by spaces.");

			dateValidation();

			value_str = line.substr(line.find('|') + 1, line.size());
			if (value_str[0] != ' ')
				throw std::runtime_error("'|' needs to be surrounded by spaces.");

			valueValidation(value_str);

			std::map<std::string, float>::iterator found;
			found = _data_map.lower_bound(_input.date);
			if (found->first != _input.date)	
				found--;
			
			std::cout << _input.date << " => " << _input.value << " = ";

			std::cout.setf(std::ios::fixed, std::ios::floatfield);
			std::cout.setf(std::ios::showpoint);
			std::cout.precision(2);
			std::cout << (found->second * _input.value) << std::endl;
			_input_map.clear();

		} catch (std::exception & e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::dateValidation() {	
	_input.date.erase(0, _input.date.find_first_not_of(" \t"));
	_input.date.erase(_input.date.find_last_not_of(" \t") + 1);

	std::string format = "####-##-##";
	if (_input.date.size() != format.size())
		throw BadInputException(_input.date);
	
	for (std::size_t i = 0; i < _input.date.size(); i++) {
		if (format[i] == '#' && !std::isdigit(static_cast<unsigned char>(_input.date[i])))
			throw BadInputException(_input.date);
		else if (format[i] != '#' && format[i] != _input.date[i])
			throw BadInputException(_input.date);
	}
	
	int		year, month, day;
	char 	c;
	std::istringstream(_input.date) >> year >> c >> month >> c >> day;
	
	std::tm	input = std::tm();
	input.tm_year = year - 1900;
	input.tm_mon = month - 1;
	input.tm_mday = day;

	std::time_t tmp = std::mktime(&input);
	if (tmp == -1)
		throw BadInputException(_input.date);
	std::tm *normalized = std::localtime(&tmp);
	if (!normalized)
		throw BadInputException(_input.date);

	if (normalized->tm_year != input.tm_year ||
			normalized->tm_mon != input.tm_mon || 
			normalized->tm_mday != input.tm_mday)
		throw BadInputException(_input.date);


	std::time_t current_time = std::time(&current_time);
	std::tm	max = *std::localtime(&current_time);

	std::tm min = std::tm();
	min.tm_mday = 2;
	min.tm_mon = 1 - 1;
	min.tm_year = 2009 - 1900;

	if (std::difftime(std::mktime(&min), tmp) > 0 ||
			std::difftime(std::mktime(&max), tmp) < 0)
		throw BadInputException(_input.date);
}

void BitcoinExchange::valueValidation(std::string value_str) {
	value_str.erase(0, value_str.find_first_not_of(" \t"));
	value_str.erase(value_str.find_last_not_of(" \t") + 1);

	bool has_value = false;
	for (std::size_t i = 0; i < value_str.size(); i++) {
		unsigned char c = static_cast<unsigned char>(value_str[i]); 
		if (std::isdigit(c))
			has_value = true;
		else if ((c == '-' || c == '+') && i + 1 == value_str.size() && std::isdigit(static_cast<unsigned char>(value_str[i + 1])))
			continue;
		else
			throw BadInputException(value_str);
	}
	if (!has_value)
		throw std::runtime_error("Missing value.");
	std::istringstream(value_str) >> _input.value;
	
	if (_input.value < 0 || _input.value > 1000)
		throw BadInputException(_input.value);
}


BitcoinExchange::BadInputException::~BadInputException() throw() {}
BitcoinExchange::BadInputException::BadInputException() : error_msg("bad input") {}
BitcoinExchange::BadInputException::BadInputException(std::string date) : error_msg("bad input => " + date) {}
BitcoinExchange::BadInputException::BadInputException(float value) : error_msg("bad input => ") {
	std::string value_str;
	std::ostringstream(value_str) << value;

	if (value < 0)
		error_msg = "not a positive number.";
	else if (value > 1000)
		error_msg = "too large a number.";

	error_msg.append(value_str);
}
const char *BitcoinExchange::BadInputException::what() const throw() {
	return error_msg.c_str();
}
