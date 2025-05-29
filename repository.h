#pragma once
#include "movie.h"
#include <vector>

class RepositoryException : public std::exception {

private:
    const char* msg_;

public:
    explicit RepositoryException(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }

};


class Repository {
protected:
    std::vector<Movie> movies;
    std::vector<Movie> watchlist;

public:

    //constructor
    Repository(){};
    //destructor
    virtual ~Repository() = default;

    //function that adds a movie to the repo
    virtual void addMovie(const Movie& movie);
    //function that removes a movie from the repo
    virtual void removeMovie(const std::string& link);

    //function that adds a movie to the watchlist
    virtual void add_to_watchlist(const std::string &link);
    //function that removes a movie from the repository
    virtual void remove_from_watchlist(const std::string& link);
    //function that returns all movies from the watchlist as a dynamic vector structure
    const std::vector<Movie>& getWatchlist() const;

    //function that updates a movies title
    virtual void updateMovieTitle(const std::string& link,const std::string& new_name);
    //function that updates a movies genre
    virtual void updateMovieGenre(const std::string& link,const std::string& new_genre);
    //function that updates a movies year
    virtual void updateMovieYear(const std::string& link,const int& year);
    //function that updates a movies number of likes
    virtual void updateMovieLikes(const std::string& link,const int& likes);

    int search_movie(const std::string& link) const;

    //function that returns the number of likes for a movie at a given index
    int getMovieLikes(const int& index);

    // Get all movies (returning a reference to the vector)
    const std::vector<Movie>& getAllMovies() const;

    // Get a specific movie by index
    Movie getMovie(int index) const;

    virtual void open_file() const {};
};

