#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSpinBox>
#include <QComboBox>
#include "drawboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setWidth(const int width);
    void setStyle(const QString &styleString);
    void setMode(const QString &modeString);
    void setInsertMode(const QString &insertModeString);
    void setShape(const Shape &shape);

    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionQuit_triggered();
    void on_actionPick_Color_triggered();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createToolBar();
    void createDrawBoard();
    void createConnections();

    template<typename Item>
    static void addItemsToComboBox(QComboBox &comboBox, std::map<QString, Item> &map);

    QSpinBox *widthBox;
    QComboBox *styleBox;
    QComboBox *modeBox;
    QComboBox *insertModeBox;

    DrawBoard *drawboard;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
