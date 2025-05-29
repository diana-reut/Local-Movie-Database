#include "repository.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include <vector>

void Repository::addMovie(const Movie& movie) {
    std::vector<Movie> movies = this->getAllMovies();
    for (const Movie& moviee : movies) {
        if (moviee.getLink() == movie.getLink()){
            throw RepositoryException("\nAdd movie failed! Link is already associated with another movie\n\n");
        }
    }
    this->movies.push_back(movie);
}

void Repository::removeMovie(const std::string& link) {
    std::vector<Movie> movies = this->getAllMovies();
    auto it = std::find_if(movies.begin(), movies.end(), [&link](const Movie& movie){return movie.getLink() == link;});
    if (it == movies.end())
        throw RepositoryException("\nMovie not found\n\n");
    erase(this->movies, *it);
}

void Repository::add_to_watchlist(const std::string &link) {
    std::vector<Movie> movies2 = this->getWatchlist();
    for (const Movie& moviee : movies2) {
        if (moviee.getLink() == link){
            throw RepositoryException("\nMovie already in watchlist\n\n");
        }
    }

    std::vector<Movie> movies = this->getAllMovies();
    for (const Movie& moviee : movies) {
        if (moviee.getLink() == link){
            this->watchlist.push_back(moviee);
            return;
        }
    }
    throw RepositoryException("\nMovie not found\n\n");
}

void Repository::remove_from_watchlist(const std::string& link) {
    std::vector<Movie> movies = this->getWatchlist();

    auto it = std::find_if(movies.begin(), movies.end(),[&link](const Movie& movie) {return movie.getLink() == link;});

    if (it != movies.end()) {
        erase(this->watchlist, *it);
        return;
    }
    throw RepositoryException("\nMovie not found\n\n");

}

const std::vector<Movie> & Repository::getWatchlist() const {
    return this->watchlist;
}

void Repository::updateMovieTitle(const std::string& link,const std::string& new_name) {
    int index = search_movie(link);
    this->movies[index].setTitle(new_name);
}

void Repository::updateMovieGenre(const std::string& link, const std::string &new_genre) {
    int index = search_movie(link);
    this->movies[index].setGenre(new_genre);
}

void Repository::updateMovieYear(const std::string& link, const int &year) {
    int index = search_movie(link);
    this->movies[index].setYearOfRelease(year);
}

void Repository::updateMovieLikes(const std::string& link, const int &likes) {
    int index = search_movie(link);
    this->movies[index].setNumberOfLikes(likes);
}

int Repository::search_movie(const std::string& link) const {
    std::vector<Movie> movies = this->getAllMovies();

    auto it = std::find_if(movies.begin(), movies.end(),
        [&link](const Movie& m) {
            return m.getLink() == link;
        });

    if (it != movies.end()) {
        return std::distance(movies.begin(), it);
    }
    throw RepositoryException("\nMovie not found\n\n");
}
int Repository::getMovieLikes(const int &index) {
    return this->movies[index].getNumberOfLikes();
}

// Get all movies - return a reference to the vector
const std::vector<Movie>& Repository::getAllMovies() const {
    return this->movies;  // Return the internal std::vector by reference
}

// Get a specific movie by index
Movie Repository::getMovie(int index) const {
    if (index >= 0 && index < this->movies.size()) {
        return this->movies[index];  // Return the movie at the specified index
    }
    throw std::out_of_range("Invalid movie index");
}
