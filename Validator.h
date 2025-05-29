#pragma once
#include <string>

#include "movie.h"

class ValidatorException : public std::exception {
private:
    const char* message;
public:
    explicit ValidatorException(const char* message): message(message) {}
    const char* what() const noexcept override {return message;}
};

class MovieValidator {
public:
    void validate_title(std::string title);
    void validate_genre(std::string genre);
    void validate_year(int year);
    void validate_likes(int likes);
    void validate_link(std::string link);

    void validate_movie(Movie movie);
};
