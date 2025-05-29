#pragma once


class InputException : public std::exception {
private:
    const char* message;
public:
    explicit InputException(const char* message): message(message) {}
    const char* what() const noexcept override {return message;}
};

class UI {
private:
    Service service;
public:
    UI(Service service) : service(service) {}

    void add_10_movies();
    void update_movie();
    void print_all_movies();
    void delete_movie();
    void add_movie();
    void print_menu();
    void open_file();

    void work_with_user();
    void print_with_genre();
    void print_watchlist();
    void remove_from_watchlist();

    int run(int mode);
};
