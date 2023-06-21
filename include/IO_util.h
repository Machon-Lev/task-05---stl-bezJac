#pragma once
#include <string>
#include <map>
#include <Coordinate.h>

/**
* @brief namespace is responsible for all IO tasks performed in main function
* includes reading from file.
*/
namespace IOUtilities {

    /**
     * @brief reads the data.txt files and stores its data into map containers.
     * @param city_to_coordinates map object - key: city's name, value: city's coordinates
     * @param coordinates_to_city map object - key: city's coordinates, value: city's name
     * @throws std::runtime_error if file cannot be processed
     */
    void fillMapsFromFile(std::map<std::string, Coordinate>& city_to_coordinates, std::map<Coordinate, std::string>& coordinates_to_city);

    /**
    * @brief gets input from user for city name.
    * @param cities map object to validate the city name input
    * @returns city name
    * @throws std::invalid_argument if input type is incorrect
    */
    std::string getCityNameInput(std::map<std::string, Coordinate>& cities);

    /**
    * @brief gets input from user for radius.
    * @returns radius value
    * @throws std::invalid_argument if input type is incorrect
    */
    double  getRadiusInput();

    /**
    * @brief gets input from user for distance algorithm to use.
    * @param number_of_functions number of possible algorithms to choose from
    * @returns ralgorithm choice value
    * @throws std::invalid_argument if input type is incorrect
    */
    int getAlgorithmChoiceInput(const int number_of_functions);

    /**
   * @brief prints the results of calculation executed in main function
   * @param cities_maped_by_distance map object- contains all cities within distance requested by user
   * @param cities_north_to_city_count number of cities that are northen to the input city
   */
    void printRersults(const std::map<double, std::string>& cities_maped_by_distance, const int cities_north_to_city_count);
};

