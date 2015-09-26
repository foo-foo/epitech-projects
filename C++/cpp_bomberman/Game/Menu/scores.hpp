#ifndef SCORES_HPP
#define SCORES_HPP

#include <QWidget>

namespace Ui {
class Scores;
}

class Scores : public QWidget
{
    Q_OBJECT

public:
    explicit Scores(QWidget *parent = 0);
    ~Scores();

private:
    Ui::Scores *ui;

    QWidget *m_parent;

private slots:
    void returnHome();
};

#endif // SCORES_HPP
