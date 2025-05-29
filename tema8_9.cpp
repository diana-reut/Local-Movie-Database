#include "tema8_9.h"
#include "MovieListWindow.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <qcombobox.h>
#include <QShortcut>

MainWindow::MainWindow(Service& service, int admin, QWidget* parent)
    : service(service), QMainWindow(parent), admin(admin)
{
    if (this->service.getAllMovies().empty()) { add_10_movies(); }

    // Central widget that will hold the layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    if (admin == 1) {
        addButton = new QPushButton("Add Movie");
        deleteButton = new QPushButton("Delete Movie");
        updateButton = new QPushButton("Update Movie");
        showGraphButton = new QPushButton("Show Movie Graph");
        undoButton = new QPushButton("Undo");
		redoButton = new QPushButton("Redo");
        //showMoviesButton = new QPushButton("Show Movies");

        showMoviesCombo = new QComboBox();
        showMoviesCombo->addItems({"Show Detailed", "Show Short"});

        
        QVBoxLayout* buttonLayout = new QVBoxLayout;
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(updateButton);
		buttonLayout->addWidget(showMoviesCombo);
		buttonLayout->addWidget(showGraphButton);
		buttonLayout->addWidget(undoButton);
		buttonLayout->addWidget(redoButton);

        //buttonLayout->addWidget(showMoviesButton);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addLayout(buttonLayout);

        // === Create update form ===
        updateLinkEdit = new QLineEdit();
        updateValueEdit = new QLineEdit();
        updateFieldCombo = new QComboBox();
        updateFieldCombo->addItems({ "Title", "Genre", "Year", "Likes" });
        confirmUpdateButton = new QPushButton("Confirm Update");

        QFormLayout* updateFormLayout = new QFormLayout();
        updateFormLayout->addRow("Link:", updateLinkEdit);
        updateFormLayout->addRow("Field:", updateFieldCombo);
        updateFormLayout->addRow("New Value:", updateValueEdit);

        // Wrap form and button in a layout
        QVBoxLayout* updateLayout = new QVBoxLayout();
        updateLayout->addLayout(updateFormLayout);
        updateLayout->addWidget(confirmUpdateButton);

        //  Wrap in a QWidget so we can hide/show 
        updateWidget = new QWidget();              //  create the container
        updateWidget->setLayout(updateLayout);     // set its layout
        updateWidget->hide();                      // hide by default

        mainLayout->addWidget(updateWidget);       // add to main layout
        centralWidget->setLayout(mainLayout);  // Attach layout to central widget


        new QShortcut(QKeySequence("Ctrl+Z"), this, SLOT(onUndo()));
		new QShortcut(QKeySequence("Ctrl+Y"), this, SLOT(onRedo()));

        connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddMovie);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteMovie);
        connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateMovie);
        connect(confirmUpdateButton, &QPushButton::clicked, this, &MainWindow::onConfirmUpdate);
        connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
        connect(redoButton, &QPushButton::clicked, this, &MainWindow::onRedo);
        //connect(showMoviesButton, &QPushButton::clicked, this, &MainWindow::onShowMoviesClicked);
        // === Show movies in a new window when combo box changes ===
        connect(showMoviesCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
            if (movieListWindow == nullptr) {
                movieListWindow = new MovieListWindow(this);
            }
            if (index == 0)
                movieListWindow->populateDetailed(this->service.getAllMovies());
            else
                movieListWindow->populateShort(this->service.getAllMovies());

            movieListWindow->show();
            movieListWindow->raise();
            movieListWindow->activateWindow();
            });

        connect(showGraphButton, &QPushButton::clicked, this, [this]() {
            if (movieGraphWindow == nullptr) {
                movieGraphWindow = new MovieGraphWindow(this->service.getAllMovies());
            }
            movieGraphWindow->show();
            movieGraphWindow->raise();
            movieGraphWindow->activateWindow();
            });

    }
    else {

        // Create the model and view
        moviesModel = new MoviesModel(service, this);
        moviesTableView = new QTableView();
        moviesTableView->setModel(moviesModel);

        // Style the table view
        moviesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        moviesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        moviesTableView->setAlternatingRowColors(true);

        // Create buttons
        QPushButton* browseButton = new QPushButton("Browse Movies");
        QPushButton* openFileButton = new QPushButton("Open Watchlist");
        deleteButton = new QPushButton("Delete Movie from Watchlist");
        showMoviesButton = new QPushButton("Show Watchlist");
        showGraphButton = new QPushButton("Show Watchlist Graph");
		showMoviesModel = new QPushButton("Show Movies Model");

        // Create layouts
        QVBoxLayout* buttonLayout = new QVBoxLayout();
        buttonLayout->addWidget(browseButton);
        buttonLayout->addWidget(openFileButton);
        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(showMoviesButton);
		buttonLayout->addWidget(showGraphButton);
		buttonLayout->addWidget(showMoviesModel);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->addLayout(buttonLayout);  // then add buttons
        

        // Connect signals
        connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteFromWatchlist);
        connect(openFileButton, &QPushButton::clicked, this, &MainWindow::onOpenFileClicked);

        connect(showMoviesButton, &QPushButton::clicked, this, [this]() {
            if (movieListWindow == nullptr) {
                movieListWindow = new MovieListWindow(this);
            }

            movieListWindow->populateDetailed(this->service.getWatchlist());
            movieListWindow->show();
            movieListWindow->raise();
            movieListWindow->activateWindow();
            });
        connect(showGraphButton, &QPushButton::clicked, this, [this]() {
            if (movieGraphWindow == nullptr) {
                movieGraphWindow = new MovieGraphWindow(this->service.getWatchlist());
            }
            movieGraphWindow->show();
            movieGraphWindow->raise();
            movieGraphWindow->activateWindow();
            });
		connect(showMoviesModel, &QPushButton::clicked, this, [this]() {
            if (moviesModel == nullptr) {
                moviesModel = new MoviesModel(this->service, this);
            }
            moviesTableView->setModel(moviesModel);
            moviesTableView->show();
            moviesTableView->raise();
            moviesTableView->activateWindow();
        });
    }
}

void MainWindow::add_10_movies() {
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

void MainWindow::onAddMovie() {
    QString title = QInputDialog::getText(this, "Add Movie", "Title:");
    if (title.isEmpty()) return;

    QString genre = QInputDialog::getText(this, "Add Movie", "Genre:");
    if (genre.isEmpty()) return;

    int year = QInputDialog::getInt(this, "Add Movie", "Year:", 2000, 1800, 2100);
    int likes = QInputDialog::getInt(this, "Add Movie", "Likes:", 0);

    QString link = QInputDialog::getText(this, "Add Movie", "Trailer Link:");

    try {
        service.add_movie(Movie(title.toStdString(), genre.toStdString(), year, likes, link.toStdString()));
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onDeleteMovie() {
    QString link = QInputDialog::getText(this, "Delete Movie", "Trailer Link:");

    try { int index = this->service.search_movie(link.toStdString()); }
    catch (RepositoryException){
        QMessageBox::warning(this, "Delete Movie", "Movie not found.");
        return;
    }

    try {
        service.remove_movie(link.toStdString());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onUpdateMovie() {
    // Show the update form
    updateWidget->show();
}

void MainWindow::onConfirmUpdate() {
    QString link = updateLinkEdit->text();
    QString field = updateFieldCombo->currentText();
    QString newValue = updateValueEdit->text();

    try {
        if (field == "Title") {
            service.update_movie_title(link.toStdString(), newValue.toStdString());
        }
        else if (field == "Genre") {
            service.update_movie_genre(link.toStdString(), newValue.toStdString());
        }
        else if (field == "Year") {
            service.update_movie_year(link.toStdString(), newValue.toInt());
        }
        else if (field == "Likes") {
            service.update_movie_likes(link.toStdString(), newValue.toInt());
        }
        updateWidget->hide();  // Hide the form after updating
        updateLinkEdit->clear();
        updateValueEdit->clear();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onDeleteFromWatchlist()
{
    QString link = QInputDialog::getText(this, "Delete Movie", "Trailer Link:");

    try { int index = this->service.search_movie(link.toStdString()); }
    catch (RepositoryException) {
        QMessageBox::warning(this, "Delete Movie", "Movie not found.");
        return;
    }
    try {
        // First remove the movie
        service.remove_movie_from_watchlist(link.toStdString());
        moviesModel->refreshModel();

        // Ask if user wants to rate the movie (simple yes/no)
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Rate Movie",
            "Do you want to rate this movie?",
            QMessageBox::Yes | QMessageBox::No
        );

        if (reply == QMessageBox::Yes) {
            // Just call rate_movie with the link (no rating value needed)
            service.rate_movie(link.toStdString());
            QMessageBox::information(this, "Success", "Movie rated and removed from watchlist!");
        }
        else {
            QMessageBox::information(this, "Success", "Movie removed from watchlist!");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onUndo()
{
	try {
		service.undo();
		QMessageBox::information(this, "Undo", "Last action undone successfully.");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Undo Error", e.what());
	}
}

void MainWindow::onRedo()
{
	try {
		service.redo();
		QMessageBox::information(this, "Redo", "Last undone action redone successfully.");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Redo Error", e.what());
	}
}

void MainWindow::openLink(const std::string& link) {
    const std::string link2 = "start \"\" \"" + link + "\"";
    const char* c_link = link2.c_str();
    system(c_link);
}

void MainWindow::onBrowseClicked() {
    // Get genre filter
    bool ok;
    QString genre = QInputDialog::getText(this, "Browse Movies",
        "Enter genre (leave blank for all):",
        QLineEdit::Normal, "", &ok);
    if (!ok) return;

    // Get movies from service
    auto movies = genre.isEmpty()
        ? service.getAllMovies()
        : service.getAllMoviesWithGenra(genre.toStdString());

    if (movies.empty()) {
        QMessageBox::information(this, "No Movies", "No movies found.");
        return;
    }

    // Create dialog for browsing
    browseMoviesInteractive(movies);
}

void MainWindow::browseMoviesInteractive(const std::vector<Movie>& movies) {
    int currentIndex = 0;
    bool browsing = true;

    while (browsing && !movies.empty()) {
        const Movie& movie = movies[currentIndex];

        // Show movie info
        QString info = QString("Title: %1\nGenre: %2\nYear: %3\nLikes: %4")
            .arg(QString::fromStdString(movie.getTitle()))
            .arg(QString::fromStdString(movie.getGenre()))
            .arg(movie.getYearOfRelease())
            .arg(movie.getNumberOfLikes());

        // Open trailer automatically
        openLink(movie.getLink());

        // Create custom dialog
        QDialog dialog(this);
        QVBoxLayout layout(&dialog);

        QLabel infoLabel(info);
        QPushButton btnAdd("Add to Watchlist");
        QPushButton btnNext("Next Movie");
        QPushButton btnStop("Stop Browsing");

        layout.addWidget(&infoLabel);
        layout.addWidget(&btnAdd);
        layout.addWidget(&btnNext);
        layout.addWidget(&btnStop);

        // Connect buttons
        QObject::connect(&btnAdd, &QPushButton::clicked, [&] {
            try {
                service.add_movie_to_watchlist(movie.getLink());
                moviesModel->refreshModel();
                QMessageBox::information(this, "Success", "Added to watchlist!");
            }
            catch (const std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
            });

        QObject::connect(&btnNext, &QPushButton::clicked, [&] {
            currentIndex = (currentIndex + 1) % movies.size();
            dialog.close();
            });

        QObject::connect(&btnStop, &QPushButton::clicked, [&] {
            browsing = false;
            dialog.close();
            });

        dialog.exec();
    }
}

void MainWindow::onOpenFileClicked()
{
    try {
        service.open_file();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

MainWindow::~MainWindow()
{}
