#pragma once
#include "repository.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

class TextFileRepository : public Repository {
private:
    std::string filename;

protected:
    virtual void saveToFile(const std::string& filename)
    {
        std::ofstream fout(filename); // Open file for writing
        if (!fout) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        for (const Movie& m : this->movies)
            fout << m;  // Use the overloaded << operator

    }

    // Load movies from file
    virtual void loadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin) {
            std::cerr << "Error opening the file for reading! " << std::endl;
            return;
        }
        std::string line;
        Movie m;
        while (fin>>m) {
            this->movies.push_back(m);
        }
    }

public:
    // Constructor with filename parameter
    explicit TextFileRepository(const std::string& filename) : filename(filename){
        loadFromFile(this->filename);
    }

    // Override addMovie to save after adding
    void addMovie(const Movie& movie) override {
        Repository::addMovie(movie);
        saveToFile(this->filename);
    }

    // Override removeMovie to save after removing
    void removeMovie(const std::string& link) override {
        Repository::removeMovie(link);
        saveToFile(this->filename);
    }

    // Override update methods to save after modification
    void updateMovieTitle(const std::string& link, const std::string& new_name) override {
        Repository::updateMovieTitle(link, new_name);
        saveToFile(this->filename);
    }

    void updateMovieGenre(const std::string& link, const std::string& new_genre) override {
        Repository::updateMovieGenre(link, new_genre);
        saveToFile(this->filename);
    }

    void updateMovieYear(const std::string& link, const int& year) override {
        Repository::updateMovieYear(link, year);
        saveToFile(this->filename);
    }

    void updateMovieLikes(const std::string& link, const int& likes) override {
        Repository::updateMovieLikes(link, likes);
        saveToFile(this->filename);
    }

    void open_file() const override {
    }
};