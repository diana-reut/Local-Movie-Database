#include "MovieListWindow.h"
#include <QHeaderView>

MovieListWindow::MovieListWindow(QWidget *parent)
	: QMainWindow(parent), movieTable(new QTableWidget(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(movieTable);

    movieTable->setColumnCount(5);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Likes", "Link" });
    movieTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setLayout(layout);
    setWindowTitle("Movie List");
    movieTable->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(
                x1: 0, y1: 0,
                x2: 1, y2: 1,
                stop: 0 #6b8e23,
                stop: 1 #4169e1
            );
        }
    )");
    resize(700, 400);
}

void MovieListWindow::populateDetailed(const std::vector<Movie>& movies) {
    movieTable->setColumnCount(5);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Number of Likes", "Trailer"});
    movieTable->setRowCount(static_cast<int>(movies.size()));
    for (int i = 0; i < movies.size(); ++i) {
        movieTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movies[i].getTitle())));
        movieTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movies[i].getGenre())));
        movieTable->setItem(i, 2, new QTableWidgetItem(QString::number(movies[i].getYearOfRelease())));
        movieTable->setItem(i, 3, new QTableWidgetItem(QString::number(movies[i].getNumberOfLikes())));
        movieTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(movies[i].getTrailer())));
    }
    movieTable->setMinimumSize(700, 900);
}

void MovieListWindow::populateShort(const std::vector<Movie>& movies) {
    movieTable->setColumnCount(2);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genre" });
    movieTable->setRowCount(static_cast<int>(movies.size()));

    for (int i = 0; i < movies.size(); ++i) {
        movieTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movies[i].getTitle())));
        movieTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movies[i].getGenre())));
    }
	movieTable->setMinimumSize(300, 900);
}

MovieListWindow::~MovieListWindow()
{}
