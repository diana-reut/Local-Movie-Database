#include "MovieGraphWindow.h"


MovieGraphWindow::MovieGraphWindow(const std::vector<Movie>& movies, QWidget* parent)
    : QWidget(parent), movies(movies) {
    setWindowTitle("Movie Likes Graph");
    resize(600, 400);
}

void MovieGraphWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int graphWidth = width() - 100;
    int graphHeight = height() - 100;
    int originX = 50;
    int originY = height() - 50;

    // Draw axes
    painter.drawLine(originX, originY, originX + graphWidth, originY); // X-axis
    painter.drawLine(originX, originY, originX, originY - graphHeight); // Y-axis

    if (movies.empty()) return;

    // Find max value (e.g. likes)
    int maxValue = 0;
    for (const Movie& m : movies) {
        if (m.getNumberOfLikes() > maxValue)
            maxValue = m.getNumberOfLikes();
    }

    int barCount = movies.size();
    int spacing = 10;
    int barWidth = (graphWidth - spacing * (barCount + 1)) / barCount;

    int x = originX + spacing;

    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);

    for (const Movie& m : movies) {
        int barHeight = static_cast<int>((static_cast<double>(m.getNumberOfLikes()) / maxValue) * graphHeight);

        // Draw bar
        QRect barRect(x, originY - barHeight, barWidth, barHeight);
        painter.setBrush(Qt::blue);
        painter.drawRect(barRect);

        // Draw label below bar
        QString title = QString::fromStdString(m.getTitle());
        QRect textRect(x, originY + 5, barWidth, 20);
        painter.drawText(textRect, Qt::AlignCenter, title);

        // Draw likes count above bar
        QString likeStr = QString::number(m.getNumberOfLikes());
        painter.drawText(x, originY - barHeight - 5, likeStr);

        x += barWidth + spacing;
    }
    setMinimumSize(1200, 500);
}


MovieGraphWindow::~MovieGraphWindow()
{
}