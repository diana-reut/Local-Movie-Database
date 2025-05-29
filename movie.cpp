#include "movie.h"
#include <sstream>  // for std::getline with delimiters
#include <string>
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Movie& m)
{
    //ostream works with ofstream and others
    os << m.title << "," << m.genre << "," << m.year_of_release << "," << m.number_of_likes << "," << m.link << "\n";
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Movie& m)
{
    std::getline(is, m.title, ',');
    std::getline(is, m.genre, ',');
    is >> m.year_of_release;
    is.ignore();
    is >> m.number_of_likes;
    is.ignore();
    std::getline(is, m.link);
    return is;
}
