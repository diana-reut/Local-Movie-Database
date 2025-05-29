#include "Validator.h"

void MovieValidator::validate_title(std::string title) {
    if (title.length() < 1)
        throw ValidatorException("Name cannot be NULL!\n");
}

void MovieValidator::validate_genre(std::string genre) {
    if (genre.length() < 1)
        throw ValidatorException("Name cannot be NULL!\n");
}

void MovieValidator::validate_year(int year) {
    if (year < 1800 || year > 2025)
        throw ValidatorException("Year incorrect!\n");
}

void MovieValidator::validate_likes(int likes) {
    if (likes < 0)
        throw ValidatorException("Likes number cannot be negative!\n");
}

void MovieValidator::validate_link(std::string link) {
    if (link.length() < 1) {
        throw ValidatorException("Link cannot be NULL!\n");
    }
}

void MovieValidator::validate_movie(Movie movie) {
    validate_title(movie.getTitle());
    validate_genre(movie.getGenre());
    validate_year(movie.getYearOfRelease());
    validate_likes(movie.getNumberOfLikes());
    validate_link(movie.getLink());
}

