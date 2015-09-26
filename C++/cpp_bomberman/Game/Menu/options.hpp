#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QWidget>
#include <string>
#include <vector>

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private:
    Ui::Options *ui;
    QWidget *m_parent;
    std::vector<std::string> m_keysP1;
    std::vector<std::string> m_keysP2;
    bool m_sound;
    std::string m_nbIa;
    std::string m_levelIa;
    int m_bonusValue;

    QFont loadFont(int size);
    std::string listKeys(std::vector<std::string> keys);

private slots:
    void returnHome();
    void saveChanges();
    void changeLabelValue(int value);
};

#endif // OPTIONS_HPP
