#include <vector>
#include <fstream>

class Movie{
    public:
    Movie();
    Movie(int id, const std::string & title, const std::string & rating, const std::string & release_date, const std::string & description);
    Movie & operator<<(const std::string & input);
    int GetId() const;
    std::string GetTitle() const;
    std::string GetRating() const;
    std::string GetReleasedate() const;
    std::string GetDescription() const;

    private:
    int id_;
    std::string title_;
    std::string rating_;
    std::string release_date_;
    std::string description_;
};


std::ostream & operator<<(std::ostream & output, const Movie & input);
std::string Parse(const std::string & line, size_t & index);
void MovieToCsv (const std::vector<Movie> & movies, const std::string & file_name);
std::vector<Movie> CsvToMovie (const std::string & file_name);

