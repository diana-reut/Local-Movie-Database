#pragma once

#include <QMainWindow>
#include "ui_MovieListWindow.h"
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include "MovieListWindow.h"
#include "Movie.h"

class MovieListWindow : public QMainWindow
{
	Q_OBJECT

public:
	MovieListWindow(QWidget *parent = nullptr);

	void populateDetailed(const std::vector<Movie>& movies);
	void populateShort(const std::vector<Movie>& movies);

	~MovieListWindow();

private:
	Ui::MovieListWindowClass ui;

	QTableWidget* movieTable;
};
