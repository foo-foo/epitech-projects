#ifndef HOME_HPP
#define HOME_HPP

#include <QWidget>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private:
    Ui::Home *ui;
    QWidget *m_parent;

    QFont loadFont(int size);

private slots:
    void displayPlay1();
    void displayPlay2();
    void displayMapEditor();
    void displayOptions();
    void displayScores();
    void exitGame();
};

#endif // HOME_HPP
