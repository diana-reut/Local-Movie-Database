#pragma once
#include <string>

#include "repository.h"
#include "TextFileRepository.h"

class HTMLRepository : public TextFileRepository {
private:
    std::string watchlist_filename;

    std::string parseTagContent(const std::string& line) {
        size_t start = line.find("<td>") + 4;
        size_t end = line.find("</td>");
        if (start == std::string::npos || end == std::string::npos || end <= start) return "";
        return line.substr(start, end - start);
    }

    std::string parseHrefLink(const std::string& line) {
        size_t href_pos = line.find("href=\"");
        if (href_pos == std::string::npos) return "";

        size_t start = href_pos + 6;  // length of href="
        size_t end = line.find("\"", start);
        if (end == std::string::npos) return "";

        return line.substr(start, end - start);
    }

protected:
    // Load movies from file
    void loadFromFile(const std::string& filename) override {
        std::ifstream fin(filename);
        if (!fin) {
            throw RepositoryException("Error opening file for reading!\n");
        }

        std::string line;
        watchlist.clear();

        while (std::getline(fin, line)) {
            // Skip the header row
            if (line.find("<tr>") != std::string::npos) {
                std::getline(fin, line);  // Title
                if (line.find("<td>Title</td>") != std::string::npos) {
                    // This is the header row; skip the next 5 lines (genre, year, likes, link, </tr>)
                    for (int i = 0; i < 5; ++i) std::getline(fin, line);
                    continue;
                }

                // Parse movie row
                std::string title = parseTagContent(line);
                std::getline(fin, line);  // Genre
                std::string genre = parseTagContent(line);
                std::getline(fin, line);  // Year
                int year = std::stoi(parseTagContent(line));
                std::getline(fin, line);  // Likes
                int likes = std::stoi(parseTagContent(line));
                std::getline(fin, line);  // Link
                std::string link = parseHrefLink(line);

                watchlist.emplace_back(title, genre, year, likes, link);
            }
        }
    }


    void saveToFile(const std::string& filename) override
    {
        std::ofstream fout(filename); // Open file for writing
        if (!fout) {
            throw RepositoryException("Error opening file for writing!\n");
        }

        fout<<"<!DOCTYPE html>\n";
        fout<<"<html>\n";
        fout<<"<head>\n";
        fout<<"    <title>Watchlist</title>\n";
        fout<<"</head>\n";
        fout<<"<body>\n";
        fout<<"<table border=\"1\">\n";
        fout<<"    <tr>\n";
        fout<<"        <td>Title</td>\n";
        fout<<"        <td>Genre</td>\n";
        fout<<"        <td>Year</td>\n";
        fout<<"        <td>Likes</td>\n";
        fout<<"        <td>Link</td>\n";
        fout<<"    </tr>\n";
        for (const Movie& m : this->watchlist) {
            fout<<"    <tr>\n";
            fout<<"        <td>"<<m.getTitle()<<"</td>\n";
            fout<<"        <td>"<<m.getGenre()<<"</td>\n";
            fout<<"        <td>"<<m.getYearOfRelease()<<"</td>\n";
            fout<<"        <td>"<<m.getNumberOfLikes()<<"</td>\n";
            fout<<"        <td><a href=\""<<m.getLink()<<"\">Link</a></td>";
            fout<<"    </tr>\n";
        }
        fout<<"</table>\n";
        fout<<"</body>\n";
        fout<<"</html>\n";
    }

public:
    // Constructor with filename parameter
    explicit HTMLRepository(const std::string& filename, const std::string& watchlist_filename) : TextFileRepository(filename), watchlist_filename(watchlist_filename) {
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


