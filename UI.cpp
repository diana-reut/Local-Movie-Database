#include <iostream>
#include "movie.h"
#include "repository.h"
#include "service.h"
#include "ui.h"

using namespace std;

int openLink(const std::string& link) {
    const std::string link2 = "start \"\" \"" + link + "\"";
    const char* c_link = link2.c_str();
    system(c_link);
    return 0;
}

void UI::print_menu() {
    cout<<"Choose an option:\n";
    cout<<"1. Add a new movie.\n";
    cout<<"2. Delete a movie.\n";
    cout<<"3. Print all movies.\n";
    cout<<"4. Update movie.\n";
    cout<<"0. Exit\n";
}

void UI::add_movie() {
    string title;
    string genre;
    int year;
    int number_of_likes;
    string link;

    cout<<"Title of movie: ";
    cin.ignore( 1024, '\n' ) ;
    getline(cin, title);

    cout<<"Genre of movie: ";
    getline(cin, genre);

    cout<<"Year of movie: ";
    if (!(cin>>year)){
        throw InputException("Please enter a number!");
    }

    cout<<"Number of likes: ";
    if(!(cin>>number_of_likes)){
        throw InputException("Please enter a number!");
    }

    cout<<"Link: ";
    cin.ignore( 1024, '\n' ) ;
    getline(cin, link);

    Movie movie(title, genre, year, number_of_likes, link);
    this->service.add_movie(movie);
}

void UI::delete_movie() {
    string link;
    cout<<"Link: ";
    cin.ignore( 1024, '\n' );
    getline(cin, link);
    this->service.remove_movie(link);
}

void UI::print_all_movies() {
    std::vector<Movie> movies = this->service.getAllMovies();

    for (const Movie& movie : movies) {
        cout <<movie<<"\n";
    }
    cout<<"\n";
}

void UI::update_movie() {
    string link;
    cout<<"Link: ";
    cin.ignore( 1024, '\n' );
    getline(cin, link);
    int trial = this->service.search_movie(link);
    cout<<"What do you want to update?\n";
    cout<<"1. Title\n2. Genre\n3. Year of release\n4. Number of likes\n";
    int choice;
    if (!(cin>>choice)) {
        throw InputException("Choice must be a number!");
    }
    try {
        switch (choice) {
            case 1: {
                string title;
                cout<<"New title: ";
                cin.ignore( 1024, '\n' ) ;
                getline(cin, title);
                try {
                    this->service.update_movie_title(link, title);
                } catch (RepositoryException e) {
                    cout<<"\nUpdate movie title failed! Link not found...\n\n";
                }
                break;
            }
            case 2: {
                string genre;
                cout<<"New genre: ";
                cin.ignore( 1024, '\n' ) ;
                getline(cin, genre);
                try {
                    this->service.update_movie_genre(link, genre);
                } catch (RepositoryException e) {
                    cout<<"\nUpdate movie title failed! Link not found...\n\n";
                }
                break;
            }
            case 3: {
                int year;
                cout<<"Updated year: ";
                cin.ignore( 1024, '\n' ) ;
                if (!(cin>>year)) {
                    throw InputException("Please enter a number!");
                }
                try {
                    this->service.update_movie_year(link, year);
                } catch (RepositoryException e) {
                    cout<<"\nUpdate movie title failed! Link not found...\n\n";
                }
                break;
            }
            case 4: {
                int likes;
                cout<<"New number of likes: ";
                cin.ignore( 1024, '\n' ) ;
                if (!(cin>>likes)) {
                    throw InputException("Please enter a number!");
                }
                try {
                    this->service.update_movie_likes(link, likes);
                } catch (RepositoryException e) {
                    cout<<"\nUpdate movie title failed! Link not found...\n\n";
                }
                break;
            }
            default: {
                throw InputException("That is not a valid choice!");
            }
        }
    }catch (const std::exception& e) {}
}

void UI::add_10_movies() {
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
    this->service.add_movie(movie1);
    this->service.add_movie(movie2);
    this->service.add_movie(movie3);
    this->service.add_movie(movie4);
    this->service.add_movie(movie5);
    this->service.add_movie(movie6);
    this->service.add_movie(movie7);
    this->service.add_movie(movie8);
    this->service.add_movie(movie9);
    this->service.add_movie(movie10);
}


void UI::print_with_genre() {

    std::vector<Movie> movies;
    std::string genre;
    std::cout << "Enter Genre Name: ";
    cin.ignore(1024,'\n');
    getline(std::cin, genre);
    if (genre == "")
        movies = this->service.getAllMovies();
    else {
        movies = this->service.getAllMoviesWithGenra(genre);
    }

    cout<<"\n";
    if (movies.size() == 0) {
        std::cout << "No movies found!\n";
        return;
    }
    auto it = movies.begin();
    while (true) {
        const Movie& movie = *it;
        cout <<movie <<endl;
        openLink(movie.getLink());

        std::string add;
        do {
            std::cout<<"Add to watchlist? (yes/no)  ";
            getline(std::cin, add);
            if (add == "yes") {
                try {
                    this->service.add_movie_to_watchlist(movie.getLink());
                    std::cout<<"\nMovie successfully added to the watchlist\n\n";
                } catch (RepositoryException e){ std::cout << e.what();}
            }
        } while (add != "no" and add != "yes");

        std::string next;
        do {
            std::cout<<"See next movie? (yes/no)  ";
            getline(std::cin, next);
            if (next == "no") {
                return;
            }
        } while (next != "no" and next != "yes");
        it++;
        if (it == movies.end()) {
            it = movies.begin();
        }
    }
}

void UI::print_watchlist() {
    std::vector<Movie> movies = this->service.getWatchlist();

    cout<<"\n";
    for (const Movie& movie : movies) {
        cout <<movie <<endl;
    }
}

void UI::remove_from_watchlist() {
    string link;
    cout<<"Link of the movie you have watched: ";
    cin.ignore( 1024, '\n' );
    getline(cin, link);
    try {
        this->service.remove_movie_from_watchlist(link);
        std::string rate;
        do {
            std::cout<<"\nDo you want to rate the movie? (yes/no) ";
            getline(cin, rate);
            //cin.ignore( 1024, '\n' );
            if (rate == "yes") {
                this->service.rate_movie(link);
            }
        } while (rate != "no" and rate != "yes");
        std::cout<<"\nMovie successfully removed from the watchlist\n\n";
    }
    catch (RepositoryException e) {
        std::cout << e.what();
    }
}

void UI::open_file() {
    this->service.open_file();
}

void UI::work_with_user() {

    int choice = -1;
    while (choice != 0) {
        std::cout<<"Choose: \n";
        std::cout<<"1. See movies with genre\n";
        std::cout<<"2. Delete a movie\n";
        std::cout<<"3. See watchlist\n";
        std::cout<<"4. Open watchlist file\n";
        std::cout<<"0. EXIT\n";

        while (!(cin>>choice)) {
            cout<<"Invalid input!\n";
            cin.clear();
            cin.ignore(1024, '\n');
        }
        try {
            switch(choice) {
                case 1: {
                    print_with_genre();
                    break;
                }
                case 2: {
                    remove_from_watchlist();
                    break;
                }
                case 3: {
                    print_watchlist();
                    break;
                }
                case 4: {
                    open_file();
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout<<"Invalid input\n";
                    break;
                }
            }
        }catch (InputException& e) {cout<<e.what()<<"\n";}
        catch (ValidatorException& e) {cout<<e.what()<<"\n";}
        catch (RepositoryException& e) {cout<<e.what()<<"\n";}
    }

}

int UI::run(int mode){
    std::vector <Movie> movies = this->service.getAllMovies();
    if (movies.empty()) {add_10_movies();}

    if (mode == 2) {
        work_with_user();
        return 0;
    }
    if (mode != 1) {
        return 1;
    }
    int choice = -1;
    while (choice != 0) {
        print_menu();
        while (!(cin>>choice)) {
            cout<<"Invalid input!\n";
            cin.clear();
            cin.ignore(1024, '\n');
            print_menu();
        }
        try {
            switch(choice) {
                case 1: {
                    add_movie();
                    break;
                }
                case 2: {
                    delete_movie();
                    break;
                }
                case 3: {
                    print_all_movies();
                    break;
                }
                case 4: {
                    update_movie();
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout<<"Invalid input\n";
                    break;
                }
            }
        }catch  (InputException& e) {cout<<e.what()<<"\n";}
         catch (ValidatorException& e) {cout<<e.what()<<"\n";}
         catch (RepositoryException& e) {cout<<e.what()<<"\n";}
    }

    return 0;
}
