#pragma once
#include <string>
#include <ostream>

class Movie {

private:

    std::string title;
    std::string genre;
    int year_of_release;
    int number_of_likes;
    std::string link;


public:

    // Default constructor
    Movie() {
        // Set default values
        this->title = "Unknown Title";
        this->genre = "Unknown Genre";
        this->year_of_release = 0;
        this->number_of_likes = 0;
        this->link =  "Unknown Link";
    }

    //constructor
    Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string link)
        : title(title), genre(genre), year_of_release(year_of_release), number_of_likes(number_of_likes), link(link) {}

    // Overload operator<< to print the Movie object
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);

    friend std::ifstream& operator>>(std::ifstream& is, Movie& m);

    Movie(const Movie&) = default;

    //copy constructor of the movie
    bool operator==(const Movie& other) const {
        return this->title == other.title &&
               this->genre == other.genre &&
               this->year_of_release == other.year_of_release &&
               this->number_of_likes == other.number_of_likes &&
               this->link == other.link;
    }

    //function that returns the link
    std::string getLink() const {return this->link;}
    //functions that returns the year of release
    int getYearOfRelease() const {return this->year_of_release;}
    //function that returns the number of likes
    int getNumberOfLikes() const {return this->number_of_likes;}
    //function that returns the genre
    std::string getGenre() const {return this->genre;}
    //function that returns the title
    std::string getTitle() const {return this->title;}
    std::string getTrailer() const { return this->link; }

    void setTitle(std::string title) {this->title = title;}
    void setGenre(std::string genre) {this->genre = genre;}
    void setYearOfRelease(int year) {this->year_of_release = year;}
    void setNumberOfLikes(int number_of_likes) {this->number_of_likes = number_of_likes;}
};
