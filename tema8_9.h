#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tema8_9.h"
#include "MovieListWindow.h"
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qtextbrowser.h>
#include <qlabel>
#include "service.h"
#include <MovieGraphWindow.h>
#include <MoviesModel.h>

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Service& service, int admin, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_10_movies();
    void onAddMovie();
    void onDeleteMovie();
    void onUpdateMovie();
    void onConfirmUpdate();
    void onDeleteFromWatchlist();
    void onUndo();
    void onRedo();
	void openLink(const std::string& link);
    void onBrowseClicked();
	void browseMoviesInteractive(const std::vector<Movie>& movies);
    void onOpenFileClicked();

private:

    int admin;
    Service& service;

    MoviesModel* moviesModel;
    QTableView* moviesTableView;

    MovieListWindow* movieListWindow = nullptr;
    QWidget* tableWidgetContainer;
    MovieGraphWindow* movieGraphWindow = nullptr;
	QTableWidget* movieTable;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* showMoviesModel;
	QPushButton* showGraphButton;
    QLineEdit* updateLinkEdit;
    QComboBox* updateFieldCombo;
    QLineEdit* updateValueEdit;
    QPushButton* confirmUpdateButton;
	QWidget* updateWidget; 
    QPushButton* showMoviesButton;
    QComboBox* showMoviesCombo;
    
};
