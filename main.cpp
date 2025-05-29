#include <QApplication>
#include "tema8_9.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "tests.h"
#include <iostream>

#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "TextFileRepository.h"
#include <StartupDialog.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    test_all();


    ModeSelectionDialog modeDialog;
    if (modeDialog.exec() != QDialog::Accepted)
        return 0;

    Repository* repo = nullptr;
    int admin = 1;

    if (modeDialog.selectedMode == ModeSelectionDialog::User) {
        admin = 0;
        RepoSelectionDialog repoDialog;
        if (repoDialog.exec() != QDialog::Accepted)
            return 0;

        if (repoDialog.selectedRepoType == RepoSelectionDialog::CSV)
            repo = new CSVRepository("output.txt", "watchlist.csv");
        else
            repo = new HTMLRepository("output.txt", "watchlist.html");
    }
    else {
        repo = new TextFileRepository("output.txt");
    }

    Service service(*repo);
    MainWindow window(service, admin);
    window.show();
    
    int result = app.exec();
    delete repo;
    return result;
}
