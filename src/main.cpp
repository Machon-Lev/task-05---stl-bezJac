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

struct Coordinate {
	double _x;
	double _y;

	Coordinate() {}
	Coordinate(double x, double y) : _x(x), _y(y) {}

	bool operator<(const Coordinate& other) const {
		if (_x < other._x) {
			return true;
		}
		else if (_x > other._x) {
			return false;
		}
		else {
			return _y < other._y;
		}
	}

	bool operator!=(Coordinate other)
	{
		return _x != other._x && _y != other._y;
	}
};

void fillMapsFromFile(std::map<std::string, Coordinate>& city_to_coordinates, std::map<Coordinate, std::string>& coordinates_to_city) {
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


int main() {
	std::map<std::string, Coordinate> city_to_coordinates;
	std::map<Coordinate, std::string> coordinates_to_city;
	int algorithm_choice = -1;
	double radius = 0;
	size_t size;
	Coordinate input_city_coordinates;
	std::map<Coordinate, std::string> cities_within_radius;
	int  cities_north_count = 0;
	std::map<double, std::string> cities_within_radius_by_distance;
	std::string city_input;
	int i = 0;
	std::map<int, std::function<double(const Coordinate&, const Coordinate&)>> distancePredicates = {
	   {0, [](const Coordinate& c1, const Coordinate& c2) {				// Euclidean distance calculation
			double dx = c2._x - c1._x;
			double dy = c2._y - c1._y;
			return std::sqrt(dx * dx + dy * dy);
		}},
		{1, [](const Coordinate& c1, const Coordinate& c2) {			// Chebyshev distance calculation
			double dx = std::abs(c2._x - c1._x);
			double dy = std::abs(c2._y - c1._y);
			return std::max(dx, dy);
		}},
		{2, [](const Coordinate& c1, const Coordinate& c2) {			// Manhattan distance calculation
			double dx = std::abs(c2._x - c1._x);
			double dy = std::abs(c2._y - c1._y);
			return dx + dy;
		}}
	};

	try
	{
		fillMapsFromFile(city_to_coordinates, coordinates_to_city);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	std::cout << "Please enter selected city name (with line break after it):\n";
	std::getline(std::cin, city_input);
	do
	{
		while (city_to_coordinates.find(city_input) == city_to_coordinates.end()) {
			std::cout << "ERROR: " << city_input << " isn't found in the city list. Please try again.\n";
			std::getline(std::cin, city_input);
		}

		std::cout << "Please enter the wanted radius:\n";
		std::cin >> radius;
		while (radius < 0) {
			std::cout << "ERROR: radius value must be positive. Please try again.\n";
			std::cin >> radius;
		}

		std::cout << "Please enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
		std::cin >> algorithm_choice;
		while (algorithm_choice < 0 || algorithm_choice>2) {
			std::cout << "ERROR: norm value must be 0-2. Please try again.\n";
			std::cin >> algorithm_choice;
		}
		input_city_coordinates = city_to_coordinates[city_input];
		std::copy_if(coordinates_to_city.begin(), coordinates_to_city.end(), std::inserter(cities_within_radius, cities_within_radius.end()),
			[&distancePredicates, &input_city_coordinates, radius, algorithm_choice](const auto& pair) {
				return input_city_coordinates!= pair.first && distancePredicates.at(algorithm_choice)(input_city_coordinates, pair.first) < radius;
			});

		std::transform(cities_within_radius.begin(), cities_within_radius.end(), std::inserter(cities_within_radius_by_distance, cities_within_radius_by_distance.end()),
			[distancePredicates, algorithm_choice, input_city_coordinates](const auto& pair) {
				return std::make_pair(distancePredicates.at(algorithm_choice)(input_city_coordinates, pair.first), pair.second);
			});
		cities_north_count = std::count_if(coordinates_to_city.begin(), coordinates_to_city.end(),
			[&input_city_coordinates](const auto& pair) {
				return pair.first._y < input_city_coordinates._y;
			});


		std::cout << "Search result:" << std::endl;
		size = cities_within_radius.size();
		std::cout << size << ((size == 1) ? " city" : " cities") << " found in the given radius." << std::endl;
		std::cout << cities_north_count << ((cities_north_count == 1) ? " city" : " cities") << " are to the north of the selected city." << std::endl;
		std::cout << "City list:" << std::endl;

		std::transform(cities_within_radius_by_distance.begin(), cities_within_radius_by_distance.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
			[](const auto& pair) {
				return pair.second;
			});
		
		cities_within_radius_by_distance.clear();
		cities_within_radius.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter selected city name (with line break after it):\n";
		std::getline(std::cin, city_input);

	} while (city_input != "0");
	std::cout << "Bye";
	return 0;
}
