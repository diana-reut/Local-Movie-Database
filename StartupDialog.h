#pragma once
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

class ModeSelectionDialog : public QDialog {
    Q_OBJECT

public:
    enum AppMode { Admin, User };
    AppMode selectedMode = Admin;

    ModeSelectionDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Choose Application Mode");

        QRadioButton* adminRadio = new QRadioButton("Administrator");
        QRadioButton* userRadio = new QRadioButton("User");
        adminRadio->setChecked(true);

        QVBoxLayout* radioLayout = new QVBoxLayout;
        radioLayout->addWidget(adminRadio);
        radioLayout->addWidget(userRadio);
        QGroupBox* box = new QGroupBox("Select Mode");
        box->setLayout(radioLayout);

        QPushButton* nextButton = new QPushButton("Next");

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(box);
        layout->addWidget(nextButton);
        setLayout(layout);

        connect(nextButton, &QPushButton::clicked, this, [=]() {
            selectedMode = adminRadio->isChecked() ? Admin : User;
            accept();
            });
    }
};

class RepoSelectionDialog : public QDialog {
    Q_OBJECT

public:
    enum RepoType { CSV, HTML };
    RepoType selectedRepoType = CSV;

    RepoSelectionDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Choose Repository Type");

        QRadioButton* csvRadio = new QRadioButton("CSV");
        QRadioButton* htmlRadio = new QRadioButton("HTML");
        csvRadio->setChecked(true);

        QVBoxLayout* radioLayout = new QVBoxLayout;
        radioLayout->addWidget(csvRadio);
        radioLayout->addWidget(htmlRadio);
        QGroupBox* box = new QGroupBox("Select Repository");
        box->setLayout(radioLayout);

        QPushButton* okButton = new QPushButton("OK");

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(box);
        layout->addWidget(okButton);
        setLayout(layout);

        connect(okButton, &QPushButton::clicked, this, [=]() {
            selectedRepoType = csvRadio->isChecked() ? CSV : HTML;
            accept();
            });
    }
};
