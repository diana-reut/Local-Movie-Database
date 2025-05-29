#include "repository.h"
#include "service.h"
#include <cassert>
#include <iostream>
#include <sstream>

#include "Comparator.h"


void test_comparator() {
    Movie movie1("The Matrix", "sci-fi", 1999, 31000, "https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
    Movie movie2("Spirited Away", "animation", 2001, 132000, "https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");
    Movie movie3("Pulp Fiction", "crime", 1994, 35000, "https://youtu.be/s7EdQ4FqbhY?si=c_G21Yopf_1GnNYN");
    Movie movie4("The Grand Budapest Hotel", "comedy", 2014, 1100, "https://youtu.be/mXRztrOK47I?si=ymEVFc-_TzCXrOLq");
    Movie movie5("Inception", "sci-fi", 2010, 160000, "https://youtu.be/YoHD9XEInc0?si=PQ92F6_aKXWS2oPs");
    Movie movie6("The Dark Knight", "action", 2008, 201000, "https://youtu.be/EXeTwQWrcwY?si=dPs1BcKeZ2jVEXCL");
    Movie movie7("The Social Network", "drama", 2010, 93000, "https://youtu.be/lB95KLmpLR4?si=-yrQXWUPl-fzeVri");
    Movie movie8("Fight Club", "drama", 1999, 27000, "https://youtu.be/qtRKdVHc-cE?si=pdUYxuPEECk0xSVy");
    Movie movie9("La La Land", "romance", 2016, 214000, "https://youtu.be/0pdqf4P9MB8?si=dZIxjG1y1quV4ZUk");
    Movie movie10("500 Days of Summer", "romance", 2009, 122000, "https://youtu.be/PsD0NpFSADM?si=8TxHCUEmk-ecgc5b");
    std::vector<Movie> movies;
    movies.push_back(movie1);
    movies.push_back(movie2);
    movies.push_back(movie3);
    movies.push_back(movie4);
    movies.push_back(movie5);
    movies.push_back(movie6);
    movies.push_back(movie7);
    movies.push_back(movie8);
    movies.push_back(movie9);
    movies.push_back(movie10);

    ComparatorAscendingByYear comp1;
    sort(movies, comp1);
    for (int i = 0; i < movies.size() - 1; i++) {
        assert(movies[i].getYearOfRelease() <= movies[i + 1].getYearOfRelease());
    }

    ComparatorDescendingByTitle comp2;
    sort(movies, comp2);
    for (int i = 0; i < movies.size() - 1; i++) {
        assert(movies[i].getTitle() >= movies[i + 1].getTitle());
    }

}
void test_watchlist() {
    Repository repository;
    Service service(repository);
    Movie movie1("The Matrix", "sci-fi", 1999, 31000, "https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
    Movie movie2("Spirited Away", "animation", 2001, 132000, "https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");
    Movie movie3("Spirited", "anime", 2000, 132000, "https://youtu.be/ByXuk9QqQkk?si=hU1x0mUICmrT");

    try {
        service.add_movie(movie1);
        service.add_movie(movie2) ;
        assert(true);
    } catch (RepositoryException e) {
        assert(false);
    }

    try {
        service.add_movie_to_watchlist("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
        assert(true);
    } catch (RepositoryException e) {assert(false);}
    try {
        service.add_movie_to_watchlist("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
        assert(false);
    } catch (RepositoryException e) {assert(true);}
    try {
        service.add_movie_to_watchlist("https://youtu.be/vKQi3bBA1=HYP9jVJPclJcDfCE");
        assert(false);
    } catch (RepositoryException e) {assert(true);}

    try {
        service.remove_movie_from_watchlist("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
        assert(true);
    } catch (RepositoryException e) {assert(false);}
    try {
        service.remove_movie_from_watchlist("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
        assert(false);
    } catch (RepositoryException e) {assert(true);}

    std::vector<Movie> dv = service.getWatchlist();
    assert(dv.empty());

    std::vector<Movie> dv2 = service.getAllMoviesWithGenra("animation");
    assert(dv2.size() == 1);

    try {
        service.rate_movie("https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");
        assert(true);
    } catch (RepositoryException e) {assert(false);}
    try {
        service.rate_movie("https://youtu.be/ByXuk9QqQkhU1x0mz8f1UICmrT");
        assert(false);
    } catch (RepositoryException e) {assert(true);}

    std::vector<Movie> dvv = service.getAllMoviesWithGenra("animation");
    assert(dvv[0].getNumberOfLikes() == 132001);
}

void test_all() {
    Repository repository;
    Service service(repository);
    Movie movie1("The Matrix", "sci-fi", 1999, 31000, "https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
    Movie movie2("Spirited Away", "animation", 2001, 132000, "https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");

    assert(movie1.getNumberOfLikes() == 31000);
    assert(movie1.getGenre() == "sci-fi");

    std::vector<Movie> dv2;
    dv2.push_back(movie1);
    dv2.push_back(movie2);
    assert(dv2.size() == 2);

    std::vector<Movie> dv22;
    dv22.push_back(movie2);
    dv22 = dv2;
    assert(dv22.size() == 2);

    dv22 = dv22;
    assert(dv22.size() == 2);

    try {
        service.add_movie(movie1);
        service.add_movie(movie2) ;
        assert(true);
    } catch (RepositoryException e) {
        assert(false);
    }

    try {
        service.add_movie(movie1);
        assert(false);
    } catch (RepositoryException e) {
        assert(true);
    }

    std::vector<Movie> dv = repository.getAllMovies();
    assert(movie1 == dv[0]);

    try
    {
        Movie m = repository.getMovie(-1);
    }catch (std::out_of_range&) {}


    std::ostringstream output;
    output << movie1;
    assert(output.str() == "The Matrix,sci-fi,1999,31000,https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE\n");

    assert(movie2 == service.getMovie(1));
    assert(dv.size() == 2);

    try {
        service.update_movie_genre("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE", "romance");
        service.update_movie_likes("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE", 2);
        service.update_movie_title("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE", "Ionela");
        service.update_movie_year("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE", 2000);
        assert(true);
    } catch (RepositoryException e) { assert(false);}

    Movie movie_for_test("Ionela", "romance", 2000, 2, "https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPclJcDfCE");
    assert(movie_for_test == service.getMovie(0));
    //std::cout<<movie_for_test;
    //std::cout<<service.getMovie(0);

    try {
        service.update_movie_genre("https://youtu.be/vKQi3bBA1y8?si=HYPclJcDfCE", "romance");
        assert(false);
    } catch (RepositoryException e) { assert(true);}
    try {
        service.update_movie_likes("https://youtu.be/vKQi3bBA1y8?si=HYPclJcDfCE", 2);
        assert(false);
    } catch (RepositoryException e) { assert(true);}
    try {
        service.update_movie_title("https://youtu.be/vKQi3bBA1y8?si=HYP9jVcDfCE", "Ionela");
        assert(false);
    } catch (RepositoryException e) { assert(true);}
    try {
        service.update_movie_year("https://youtu.be/vKQi3bBA1y8?si=HYP9jVJPcoCE", 2000);
        assert(false);
    } catch (RepositoryException e) { assert(true);}

    erase(dv,movie1);
    assert(dv.size() == 1);
    try {
        service.remove_movie("https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");
        assert(true);
    } catch (RepositoryException e) {assert(false);}
    try {
        service.remove_movie("https://youtu.be/ByXuk9QqQkk?si=hU1x0mz8f1UICmrT");
        assert(false);
    } catch (RepositoryException e) {assert(true);}

    test_watchlist();
    test_comparator();
    std::cout << "ALL TESTS PASSED" << std::endl;
}