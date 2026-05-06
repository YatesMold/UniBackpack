// Author: Apostolos Chalis 2026 <achalis@csd.auth.gr>
// Co-Author: Ioannis Michadasis
#include "ProgressWindow.hpp"

ProgressWindow::ProgressWindow(const QString &university, const QString &department, QWidget *parent)
    : QDialog(parent), output_visible(false) {

    setWindowTitle("Installing packages");
    setMinimumWidth(500);

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    // Title
    QLabel *title = new QLabel(QString("Installing packages for <b>%1</b> - %2")
                               .arg(university, department), this);
    title->setWordWrap(true);
    main_layout->addWidget(title);

    // Status label
    status_label = new QLabel("Preparing...", this);
    main_layout->addWidget(status_label);

    // Progress bar
    progress_bar = new QProgressBar(this);
    progress_bar->setMinimum(0);
    progress_bar->setMaximum(0); // indeterminate/busy mode
    main_layout->addWidget(progress_bar);

    // Show more button
    show_more_button = new QPushButton("Show details ▼", this);
    main_layout->addWidget(show_more_button);

    // Output view (hidden by default)
    output_view = new QTextEdit(this);
    output_view->setReadOnly(true);
    output_view->setFontFamily("monospace");
    output_view->setMinimumHeight(200);
    output_view->setVisible(false);
    main_layout->addWidget(output_view);

    connect(show_more_button, &QPushButton::clicked, this, &ProgressWindow::toggle_output);

    adjustSize();
}

void ProgressWindow::toggle_output() {
    output_visible = !output_visible;
    output_view->setVisible(output_visible);
    show_more_button->setText(output_visible ? "Hide details ▲" : "Show details ▼");
    adjustSize();
}

void ProgressWindow::append_output(const QString &text) {
    output_view->append(text);
    status_label->setText("Installing...");
}

void ProgressWindow::set_finished(bool success) {
    progress_bar->setMaximum(100);
    progress_bar->setValue(100);

    if (success) {
        status_label->setText("✓ Installation complete!");
        progress_bar->setStyleSheet("QProgressBar::chunk { background-color: #4CAF50; }");
    } else {
        status_label->setText("✗ Installation failed.");
        progress_bar->setStyleSheet("QProgressBar::chunk { background-color: #f44336; }");
    }
}