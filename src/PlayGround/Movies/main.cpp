#include "movies.hpp"
#include <iostream>
int main() {
    std::vector<Movie> test = CsvToMovie("movies.csv");
    std::cout << "first movie is " << test.at(0).GetTitle() << "\n" << "second movie is " << test.at(1).GetTitle() << "\n";
    return 0;
}