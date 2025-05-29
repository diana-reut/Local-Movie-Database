#include "MoviesModel.h"
#include <qbrush.h>

MoviesModel::MoviesModel(Service& service, QObject* parent): QAbstractTableModel(parent), serv(service)
{
}

int MoviesModel::rowCount(const QModelIndex& parent) const
{
	return serv.getWatchlist().size();
}

int MoviesModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant MoviesModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	const auto& movie = serv.getWatchlist()[row];
	
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0: return QString::fromStdString(movie.getTitle());
		case 1: return QString::fromStdString(movie.getGenre());
		case 2: return movie.getYearOfRelease();
		case 3: return movie.getNumberOfLikes();
		case 4: return QString::fromStdString(movie.getTrailer());
		default: break;
		}
	}

	/*if (role == Qt::BackgroundRole) {
		if (row % 2 == 1) {
			QBrush brush{ QColor{255, 192, 203} };
			return brush;
		}
	}*/

	return QVariant();
}

QVariant MoviesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section)
		{
		case 0:
			return "Title";
		case 1:
			return "Genra";
		case 2:
			return "Year of release";
		case 3:
			return "Number of likes";
		case 4:
			return "Trailer link";
		default:
			break;
		}
	}
	return QVariant();
}

Qt::ItemFlags MoviesModel::flags(const QModelIndex& index) const
{
	int row = index.row();
	int col = index.column();

	if (col == 0 || col == 1 || col == 2 || col == 3)
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;

	return Qt::ItemFlags();
}

bool MoviesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	int row = index.row();
	int column = index.column();

	const auto& movie = serv.getWatchlist()[row];

	if (role == Qt::EditRole) {
		switch (column) {
		case 0: // Title
			serv.update_movie_title(movie.getTrailer(), value.toString().toStdString());
			break;
		case 1: // Genre
			serv.update_movie_genre(movie.getTrailer(), value.toString().toStdString());
			break;
		case 2: // Year of release
			serv.update_movie_year(movie.getTrailer(), value.toInt());
			break;
		case 3: // Number of likes
			serv.update_movie_likes(movie.getTrailer(), value.toInt());
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}
