#include <iostream>
#include <algorithm>
#include "service.h"

void Service::add_movie(const Movie& movie) {
    validator.validate_movie(movie);
    this->repo.addMovie(movie);
    ActionAdd* a = new ActionAdd(this->repo, movie);
    this->undoStack.push_back(a);
}

void Service::remove_movie(const std::string& link) {
    validator.validate_link(link);
    Movie movie = this->repo.getMovie(this->search_movie(link));
    this->repo.removeMovie(link);
    ActionRemove* action = new ActionRemove(this->repo, movie);
    this->undoStack.push_back(action);

}

void Service::add_movie_to_watchlist(const std::string &link) {
    validator.validate_link(link);
    this->repo.add_to_watchlist(link);
}

void Service::remove_movie_from_watchlist(const std::string& link) {
    validator.validate_link(link);
    this->repo.remove_from_watchlist(link);
}


const std::vector<Movie>& Service::getWatchlist() const {
    return this->repo.getWatchlist();
}

void Service::rate_movie(const std::string &link) {
    validator.validate_link(link);
    int index = search_movie(link);
    int likes = this->repo.getMovieLikes(index);
    likes++;
    this->repo.updateMovieLikes(link, likes);
}

void Service::update_movie_title(const std::string& link, const std::string& new_name) {
    validator.validate_link(link);
    validator.validate_title(new_name);
    Movie movie = this->repo.getMovie(this->search_movie(link));
    this->repo.updateMovieTitle(link, new_name);
	ActionUpdateTitle* action = new ActionUpdateTitle(this->repo, link, movie.getTitle(), new_name);    
	this->undoStack.push_back(action);
}

void Service::update_movie_genre(const std::string& link, const std::string& new_genre) {
    validator.validate_link(link);
    validator.validate_genre(new_genre);
    Movie movie = this->repo.getMovie(this->search_movie(link));
    this->repo.updateMovieGenre(link, new_genre);
	ActionUpdateGenre* action = new ActionUpdateGenre(this->repo, link, movie.getGenre(), new_genre);
    this->undoStack.push_back(action);
}
void Service::update_movie_year(const std::string& link, const int& year) {
    validator.validate_link(link);
    validator.validate_year(year);
    Movie movie = this->repo.getMovie(this->search_movie(link));
    this->repo.updateMovieYear(link, year);
	ActionUpdateYear* action = new ActionUpdateYear(this->repo, link, movie.getYearOfRelease(), year);
    this->undoStack.push_back(action);
}

void Service::update_movie_likes(const std::string &link, const int &likes) {
    validator.validate_link(link);
    validator.validate_likes(likes);
    Movie movie = this->repo.getMovie(this->search_movie(link));
    this->repo.updateMovieLikes(link, likes);
	ActionUpdateLikes* action = new ActionUpdateLikes(this->repo, link, movie.getNumberOfLikes(), likes);
    this->undoStack.push_back(action);
}


const std::vector<Movie>& Service::getAllMovies() const {
    return this->repo.getAllMovies();
}

Movie Service::getMovie(int index) const {
    return this->repo.getMovie(index);
}

int Service::search_movie(const std::string& link) const {
    return this->repo.search_movie(link);
}


std::vector<Movie> Service::getAllMoviesWithGenra(const std::string& genre) const {
    std::vector<Movie> movies = this->getAllMovies();
    std::vector<Movie> movies2;

    std::copy_if(movies.begin(), movies.end(), std::back_inserter(movies2),
        [&genre](const Movie& movie) {
            return movie.getGenre() == genre;
        });
    return movies2;
}

void Service::undo()
{
    if (this->undoStack.size() == 0)
        throw std::exception("No undo can be made\n");
    auto a = this->undoStack.back();
    undoStack.pop_back();
    a->executeUndo();
    this->redoStack.push_back(a);
}

void Service::redo()
{
    if (this->redoStack.empty())
        throw std::exception("No redo can be made\n");
    auto a = this->redoStack.back();
    redoStack.pop_back();
    a->executeRedo();
    this->undoStack.push_back(a);
}
