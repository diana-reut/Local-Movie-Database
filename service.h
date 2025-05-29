#pragma once
#include "repository.h"
#include "Validator.h"
#include "Action.h"
#include <utility>

class Service {

private:
    Repository& repo;
    MovieValidator validator;
    std::vector<Action*> undoStack;
    std::vector<Action*> redoStack;

public:
    //constructor
    Service(Repository& repo) : repo(repo) {}
    //destructor
    ~Service() {}

    //function that adds a movie
    void add_movie(const Movie& movie);
    //function that removes a movie with the given link
    void remove_movie(const std::string& link);

    //function that adds a movie to the watchlist; it returns 0 if everything is ok, -1 if no such movie exist in the database and -2 if the movie is already in the watchlist
    void add_movie_to_watchlist(const std::string& link);
    //function that removes a movie from the watchlist; it returns 0 if it was successful and -1 if the movie is not found in the watchlist
    void remove_movie_from_watchlist(const std::string& link);
    //function that returns all movies from the watchlist as a dynamic vector
    const std::vector<Movie>& getWatchlist() const;
    //function that gives +1 like to the movie; it returns -1 if the movie is not found and 0 if it is found
    void rate_movie(const std::string& link);

    //updates a movies title
    void update_movie_title(const std::string& link, const std::string& new_name);
    //updates a movies genre
    void update_movie_genre(const std::string& link, const std::string& new_genre);
    //updates a movies year
    void update_movie_year(const std::string& link, const int& year);
    //update a movies number of likes
    void update_movie_likes(const std::string& link, const int& likes);

    //returns all the movies from the repo
    const std::vector<Movie>& getAllMovies() const;
    //getter for a movie with a given index
    Movie getMovie(int index) const;

    //function that searches for the movie with a given link
    int search_movie(const std::string& link) const;

    //function that returns the movies with a given genra from the repo as a dynamic vector
    std::vector<Movie> getAllMoviesWithGenra(const std::string& genre) const;

    void open_file() {
        this->repo.open_file();
    }
    
    void undo();
    void redo();
};
