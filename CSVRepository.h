#pragma once
#include <fstream>

#include "TextFileRepository.h"

class CSVRepository : public TextFileRepository {
private:
    std::string watchlist_filename;
protected:
    // Load movies from file
    void loadFromFile(const std::string& filename) override
    {
        std::ifstream fin(filename);
        if (!fin) {
            throw RepositoryException("Error opening file for reading!\n");
        }
        std::string line;
        Movie m;
        while (fin>>m) {
            this->watchlist.push_back(m);
        }
    }

    void saveToFile(const std::string& filename) override
    {
        std::ofstream fout(filename); // Open file for writing
        if (!fout) {
            throw RepositoryException("Error opening file for writing!\n");
        }

        for (const Movie& m : this->watchlist) {
            fout<<m;
        }
    }

public:
    // Constructor with filename parameter
    explicit CSVRepository(const std::string& filename, const std::string& watchlist_filename) : TextFileRepository(filename), watchlist_filename(watchlist_filename) {
        //loadFromFile(this->watchlist_filename);
    }

    void add_to_watchlist(const std::string &link) override {
        TextFileRepository::add_to_watchlist(link);
        saveToFile(this->watchlist_filename);
    };
    void remove_from_watchlist(const std::string &link) override {
        TextFileRepository::remove_from_watchlist(link);
        saveToFile(this->watchlist_filename);
    };

    void open_file() const override {
        std::string command;
        command = "start \"\" \"" + this->watchlist_filename + "\"";
        system(command.c_str());
    }
};

