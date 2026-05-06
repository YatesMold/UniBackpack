// Author: Apostolos Chalis 2026 <achalis@csd.auth.gr>
// Co-Author: Ioannis Michadasis
#ifndef PROGRESSWINDOW_HPP
#define PROGRESSWINDOW_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>

class ProgressWindow : public QDialog {
    Q_OBJECT

public:
    explicit ProgressWindow(const QString &university, const QString &department, QWidget *parent = nullptr);

    void append_output(const QString &text);
    void set_finished(bool success);

private slots:
    void toggle_output();

private:
    QLabel      *status_label;
    QProgressBar *progress_bar;
    QPushButton  *show_more_button;
    QTextEdit    *output_view;
    bool         output_visible;
};

#endif // PROGRESSWINDOW_HPP