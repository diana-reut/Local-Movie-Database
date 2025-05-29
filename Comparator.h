#pragma once
#include <algorithm>
#include <vector>

#include "movie.h"

template <typename T>
class Comparator{
public:
    virtual bool compare(T e1, T e2) = 0;
};

class ComparatorAscendingByYear: public Comparator<Movie> {
public:
    bool compare(Movie m1, Movie m2) override{
        return m1.getYearOfRelease() < m2.getYearOfRelease();
    }
};

class ComparatorDescendingByTitle: public Comparator<Movie> {
public:
    bool compare(Movie m1, Movie m2) override {
        return m1.getTitle() > m2.getTitle();
    }
};

inline void sort(std::vector<Movie>& movies, Comparator<Movie>& comparator) {
    std::sort(movies.begin(), movies.end(), [&comparator](const Movie& m1, const Movie& m2) {
                  return comparator.compare(m1, m2);
              });
}