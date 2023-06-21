#include <string>
#include <tuple>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>
#include <regex>
#include "Coordinate.h"
#include "IO_util.h"



std::vector < std::function<double(const Coordinate&, const Coordinate&)>> initializePredicates() {
	std::vector< std::function<double(const Coordinate&, const Coordinate&)>> distancePredicates = {
		[](const Coordinate& c1, const Coordinate& c2) {				// Euclidean distance calculation
			double dx = c2._x - c1._x;
			double dy = c2._y - c1._y;
			return std::sqrt(dx * dx + dy * dy);
		}
		, [](const Coordinate& c1, const Coordinate& c2) {			// Chebyshev distance calculation
			double dx = std::abs(c2._x - c1._x);
			double dy = std::abs(c2._y - c1._y);
			return std::max(dx, dy);
		},
		 [](const Coordinate& c1, const Coordinate& c2) {			// Manhattan distance calculation
			double dx = std::abs(c2._x - c1._x);
			double dy = std::abs(c2._y - c1._y);
			return dx + dy;
		}
	};
	return distancePredicates;
}





int main() {
	std::map<std::string, Coordinate> city_to_coordinates;
	std::map<Coordinate, std::string> coordinates_to_city;
	std::map<Coordinate, std::string> cities_within_radius;
	std::map<double, std::string> cities_within_radius_by_distance;
	Coordinate input_city_coordinates;

	std::string city_name;
	int algorithm_choice = -1;
	double radius = 0;
	int  cities_north_to_city_count = 0;
	auto distancePredicates = initializePredicates();
	size_t number_of_functions = distancePredicates.size();
	size_t result_length;

	try {
		IOUtilities::fillMapsFromFile(city_to_coordinates, coordinates_to_city);
		city_name = IOUtilities::getCityNameInput(city_to_coordinates);

		do {


			radius = IOUtilities::getRadiusInput();
			algorithm_choice = IOUtilities::getAlgorithmChoiceInput(number_of_functions);
			input_city_coordinates = city_to_coordinates[city_name];

			std::copy_if(coordinates_to_city.begin(), coordinates_to_city.end(), std::inserter(cities_within_radius, cities_within_radius.end()),
				[&distancePredicates, &input_city_coordinates, radius, algorithm_choice](const auto& pair) {
					return input_city_coordinates != pair.first && distancePredicates.at(algorithm_choice)(input_city_coordinates, pair.first) < radius;
				});

			std::transform(cities_within_radius.begin(), cities_within_radius.end(), std::inserter(cities_within_radius_by_distance, cities_within_radius_by_distance.end()),
				[&distancePredicates, algorithm_choice, input_city_coordinates](const auto& pair) {
					return std::make_pair(distancePredicates.at(algorithm_choice)(input_city_coordinates, pair.first), pair.second);
				});
			
			cities_north_to_city_count = std::count_if(coordinates_to_city.begin(), coordinates_to_city.end(),
				[&input_city_coordinates](const auto& pair) {
					return pair.first._y < input_city_coordinates._y;
				});



			IOUtilities::printRersults(cities_within_radius_by_distance, cities_north_to_city_count);

			cities_within_radius_by_distance.clear();
			cities_within_radius.clear();
			city_name = IOUtilities::getCityNameInput(city_to_coordinates);

		} while (city_name != "0");

		std::cout << "Bye";
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}

	return 0;
}
