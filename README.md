Analysis of Container Choices for City Coordinates Mapping and Distance Algorithms.

City Coordinates Mapping:
For storing the mapping of cities to their corresponding coordinates, I decided to use a std::map container.
The reason behind this choice is that it provides a convenient key-value structure, allowing me to access coordinates based on the city name efficiently. 
By using the city name as the key and the coordinates as the value, we can easily retrieve the coordinates for any given city.

Coordinates to City Mapping:
Similarly, I have opted for another std::map container to store the mapping of coordinates to cities.
This choice enables us to access the city name based on a given set of coordinates. 
By using coordinates as the key and the city name as the value, we can efficiently retrieve the city name corresponding to specific coordinates.
this container is needed for the search process, to find near cities (within the distance).

Distance Algorithms - Lambda expressions:
I chose to utilize a std::vector container.
The main reason for this decision is that the selection of distance algorithms is based on index values, rather than keys.
Since std::vector provides efficient random access by index, it proves to be a more suitable choice compared to a std::map in this scenario.

Cities Within Distance Search:
To implement the functionality of finding cities within a certain distance, I decided to copy the relevant data to a std::map container.
By doing so, we can take advantage of the inherent sorting capability of std::map, which organizes data based on keys. In this case,
the keys represent the distances, allowing us to store cities in order of their distance from a reference point.
This approach ensures that the retrieval of cities within a specific distance range is both efficient and straightforward.
