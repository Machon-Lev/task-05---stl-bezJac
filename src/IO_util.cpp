#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Coordinate.h"
#include <map>
#include "IO_util.h"
#include <vector>
#include <regex>

void IOUtilities::fillMapsFromFile(std::map<std::string, Coordinate>& city_to_coordinates, std::map<Coordinate, std::string>& coordinates_to_city) {
	double x, y;
	std::string city;
	std::vector<std::string> coordTokens;
	std::regex reg("-");
	std::ifstream inputFile("data.txt");
	if (!inputFile.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	std::string line;
	while (std::getline(inputFile, line)) {
		city = line;

		std::getline(inputFile, line);
		std::istringstream iss(line);
		std::copy(std::sregex_token_iterator(line.begin(), line.end(), reg, -1),
			std::sregex_token_iterator(),
			std::back_inserter(coordTokens));

		x = std::stod(coordTokens[0]);
		y = std::stod(coordTokens[1]);

		Coordinate coordinate = Coordinate(x, y);
		city_to_coordinates[city] = coordinate;
		coordinates_to_city[coordinate] = city;
		coordTokens.clear();
	}

	// Close the file
	inputFile.close();



}

std::string IOUtilities::getCityNameInput(std::map<std::string, Coordinate>& cities)
{
	std::string city;
	do
	{
		std::cout << "Please enter selected city name (with line break after it):\n";
		std::getline(std::cin, city);
		if(city != "0" && cities.find(city) == cities.end())
			std::cout << "ERROR: " << city << " isn't found in the city list. Please try again.\n";
	} while (city != "0" && cities.find(city) == cities.end());
	return city;

}

int IOUtilities::getAlgorithmChoiceInput(const int number_of_functions)
{
	std::string input;
	int algorithm_choice;
	do
	{
		std::cout << "Please enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
		std::getline(std::cin, input);
		std::istringstream iss(input);
		if (!(iss >> algorithm_choice))
			throw std::invalid_argument("Algorithm number must be a digits only.");
		if (algorithm_choice < 0 || algorithm_choice>number_of_functions)
			std::cout << "ERROR: norm value must be 0-2. Please try again.\n";
	} while (algorithm_choice < 0 || algorithm_choice>2);
	return algorithm_choice;
}


double IOUtilities::getRadiusInput() {
	std::string input;
	double radius;
	do
	{
		std::cout << "Please enter the wanted radius:\n";
		std::getline(std::cin, input);
		std::istringstream iss(input);
		if (!(iss >> radius))
			throw std::invalid_argument("Algorithm number must be a digits only.");
		if (radius < 0)
			std::cout << "ERROR: radius value must be positive. Please try again.\n";
	} while (radius < 0);
	return radius;
}


void IOUtilities::printRersults(const std::map<double, std::string>& cities_maped_by_distance,const int cities_north_to_city_count)
{
	std::cout << "Search result:" << std::endl;
	int result_length = cities_maped_by_distance.size();
	std::cout << result_length << ((result_length == 1) ? " city" : " cities") << " found in the given radius." << std::endl;
	std::cout << cities_north_to_city_count << ((cities_north_to_city_count == 1) ? " city" : " cities") << " are to the north of the selected city." << std::endl;
	std::cout << "City list:" << std::endl;

	std::transform(cities_maped_by_distance.begin(), cities_maped_by_distance.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
		[](const auto& pair) {
			return pair.second;
		});
	std::cout << std::endl;
}