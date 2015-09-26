#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <QWidget>
#include <QStringList>
#include <QDir>
#include <string>

namespace Ui {
class Launcher;
}

class Launcher : public QWidget
{
    Q_OBJECT

public:
    explicit Launcher(bool multi, QWidget *parent = 0);
    ~Launcher();

private:
    QStringList readDirectory(QString dir);

private:
    Ui::Launcher *ui;

    QWidget *m_parent;
    QString m_currentMap;
    QStringList m_maps;

private slots:
  void returnHome();
  void enableButtonPlay();
  int  newRound(std::vector<int> &, const int, const int, const int) const;
  void launchGame1();
  void launchGame2();
};

#endif // LAUNCHER_HPP
