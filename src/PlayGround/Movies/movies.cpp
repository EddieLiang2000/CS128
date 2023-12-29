#include "movies.hpp"
Movie::Movie(): id_{0}, title_{""}, rating_{""}, release_date_{""},description_{""}{

}

Movie::Movie(int id, const std::string & title, const std::string & rating, const std::string & release_date, const std::string & description) :
id_{id}, title_{title}, rating_{rating}, release_date_{release_date},description_{description}{
    
}

int Movie::GetId() const {
    return id_;
}

std::string Movie::GetTitle() const {
    return title_;
}

std::string Movie::GetRating() const {
    return rating_;
}

std::string Movie::GetReleasedate() const{
    return release_date_;
}

std::string Movie::GetDescription() const {
    return description_;
}

Movie & Movie::operator<<(const std::string & input) {
    size_t index = 0;
    size_t & indexref = index;
    this->id_ = std::stoi(Parse(input, indexref));
    this->title_ = Parse(input,indexref);
    this->rating_ = Parse(input,indexref);
    this->release_date_ = Parse(input,indexref);
    this->description_ = Parse(input,indexref);
    return *this;
}

std::string Parse(const std::string & input, size_t & index) {
    std::string output;
    for (; index < input.length(); index++) {
        if (input[index] == ',' || input[index] == '\n') {
            break;
        }
        output += input[index];
    }
    index += 1;
    return output;
}

std::ostream & operator<<(std::ostream & output, const Movie & input) {
    return output << input.GetId() << "," << input.GetTitle() << "," << input.GetRating() << "," <<
        input.GetReleasedate() << "," << input.GetDescription() << "\n"; 
}

void MovieToCsv (const std::vector<Movie> & movies, const std::string & file_name) {
    std::ofstream ofs{file_name};
    for (unsigned int i = 0; i < movies.size(); ++i) {
        ofs << movies.at(i);
    }
}

std::vector<Movie> CsvToMovie (const std::string & file_name) {
    std::ifstream ifs{file_name};
    std::vector<Movie> output;
    for (std::string line; getline(ifs,line); line = "") {
        Movie element;
        element << line;
        output.push_back(element);
    }
    return output;
}