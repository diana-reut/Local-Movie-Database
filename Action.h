#pragma once
#include <memory>
#include "movie.h"
#include "repository.h"

class Action
{
public:
	Action() {};
	virtual ~Action() {};
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
	Movie added_movie;
	Repository& repo;

public:
	ActionAdd(Repository& repo, const Movie& movie) :repo(repo), added_movie(movie) {}
	void executeUndo() override
	{
		repo.removeMovie(added_movie.getLink());
	}
	void executeRedo() override
	{
		repo.addMovie(added_movie);
	}
};

class ActionRemove : public Action
{
	Movie removed_movie;
	Repository& repo;

public:
	ActionRemove(Repository& repo, const Movie& movie) :repo(repo), removed_movie(movie) {}
	void executeUndo() override
	{
		repo.addMovie(removed_movie);
	}
	void executeRedo() override
	{
		repo.removeMovie(removed_movie.getLink());
	}
};

// Action for updating title (you already had this one)
class ActionUpdateTitle : public Action {
    std::string old_title;
    std::string new_title;
    std::string link;
    Repository& repo;

public:
    ActionUpdateTitle(Repository& repo, const std::string& link,
        const std::string& old_title, const std::string& new_title)
        : repo(repo), link(link), old_title(old_title), new_title(new_title) {
    }

    void executeUndo() override {
        repo.updateMovieTitle(link, old_title);
    }

    void executeRedo() override {
        repo.updateMovieTitle(link, new_title);
    }
};

// Action for updating genre
class ActionUpdateGenre : public Action {
    std::string old_genre;
    std::string new_genre;
    std::string link;
    Repository& repo;

public:
    ActionUpdateGenre(Repository& repo, const std::string& link,
        const std::string& old_genre, const std::string& new_genre)
        : repo(repo), link(link), old_genre(old_genre), new_genre(new_genre) {
    }

    void executeUndo() override {
        repo.updateMovieGenre(link, old_genre);
    }

    void executeRedo() override {
        repo.updateMovieGenre(link, new_genre);
    }
};

// Action for updating year of release
class ActionUpdateYear : public Action {
    int old_year;
    int new_year;
    std::string link;
    Repository& repo;

public:
    ActionUpdateYear(Repository& repo, const std::string& link,
        int old_year, int new_year)
        : repo(repo), link(link), old_year(old_year), new_year(new_year) {
    }

    void executeUndo() override {
        repo.updateMovieYear(link, old_year);
    }

    void executeRedo() override {
        repo.updateMovieYear(link, new_year);
    }
};

// Action for updating number of likes
class ActionUpdateLikes : public Action {
    int old_likes;
    int new_likes;
    std::string link;
    Repository& repo;

public:
    ActionUpdateLikes(Repository& repo, const std::string& link,
        int old_likes, int new_likes)
        : repo(repo), link(link), old_likes(old_likes), new_likes(new_likes) {
    }

    void executeUndo() override {
        repo.updateMovieLikes(link, old_likes);
    }

    void executeRedo() override {
        repo.updateMovieLikes(link, new_likes);
    }
};



