#pragma once

#include <QWidget>
#include "ui_MovieGraphWindow.h"
#include "Movie.h"
#include <QPainter.h>

class MovieGraphWindow : public QWidget
{
	Q_OBJECT

public:
    MovieGraphWindow(const std::vector<Movie>& movies, QWidget* parent = nullptr);
	~MovieGraphWindow();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<Movie> movies;
	Ui::MovieGraphWindowClass ui;
};
