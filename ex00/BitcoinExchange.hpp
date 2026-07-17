#pragma once

#include <string>
#include <ctime>
#include <map>

#define DATAFILENAME "data.csv"

class BitcoinExchange {
	public:
		BitcoinExchange(const char *input_file_name, const char *data_file_name);
		~BitcoinExchange();


		
		class BadInputException : public std::exception {
			std::string error_msg;
			public:
				BadInputException();
				BadInputException(std::string date);
				BadInputException(float value);
				virtual ~BadInputException() throw();
 				virtual const char *what() const throw();
		};

		private:
			BitcoinExchange();
			BitcoinExchange(const BitcoinExchange &other);
			BitcoinExchange &operator=(const BitcoinExchange &other);
			
			struct s_input {
				std::string date;
				float				value;
			};

			s_input	_input;
			std::map<std::string, float> _input_map;
			std::map<std::string, float> _data_map;

			void getInputMap(const char *filename);
			void getDataMap(const char *filename);
			void dateValidation();
			void valueValidation(std::string value_str);
};

