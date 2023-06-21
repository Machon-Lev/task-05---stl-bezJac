#pragma once
#include <string>
#include <map>
#include <Coordinate.h>

namespace IOUtilities {

    void fillMapsFromFile(std::map<std::string, Coordinate>& city_to_coordinates, std::map<Coordinate, std::string>& coordinates_to_city);
    std::string getCityNameInput(std::map<std::string, Coordinate>& cities);
    double  getRadiusInput();
    int getAlgorithmChoiceInput(const int number_of_functions);
    void printRersults(const std::map<double, std::string>& cities_maped_by_distance, const int cities_north_to_city_count);
};

