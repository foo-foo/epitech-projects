#ifndef MAPEDITOR_HPP
#define MAPEDITOR_HPP

#include <QWidget>
#include <string>

namespace Ui {
class MapEditor;
}

class MapEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = 0);
    ~MapEditor();

private:
    Ui::MapEditor *ui;

    QWidget *m_parent;
    std::string m_content;

    bool fileExists(std::string fileName);

private slots:
    void returnHome();
    void saveButton();
    void loadButton();
};

#endif // MAPEDITOR_HPP
