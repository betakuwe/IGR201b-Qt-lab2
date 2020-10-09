#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGraphicsItem>
#include <QColorDialog>
#include "shape.h"

/*
https://perso.telecom-paristech.fr/elc/qt/TP-Qt2.html
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createDrawBoard();
    this->createToolBar();
    this->statusBar();
    this->createConnections();

}

void MainWindow::setShape(const Shape &shape) {
    widthBox->setValue(shape.getPen().width());
    styleBox->setCurrentText(DrawBoard::penStyleToString[shape.getPen().style()]);
    insertModeBox->setCurrentText(shape.getShapeName());
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    if (QMessageBox::Yes ==
            QMessageBox::question(this,
                                  "Quit App",
                                  "Are you sure you want to quit?")) {
        event->accept();
    }
}

void MainWindow::createToolBar()
{
    widthBox = new QSpinBox(ui->toolBar);
    widthBox->setPrefix("Width ");
    widthBox->setMinimum(1);

    styleBox = new QComboBox(ui->toolBar);
    addItemsToComboBox(*styleBox, DrawBoard::stringToPenStyle);
    styleBox->setCurrentText("Solid Line");

    modeBox = new QComboBox(ui->toolBar);
    addItemsToComboBox(*modeBox, DrawBoard::stringToMode);
    modeBox->setCurrentText("Insert");

    insertModeBox = new QComboBox(ui->toolBar);
    addItemsToComboBox(*insertModeBox, DrawBoard::stringToInsertMode);
    insertModeBox->setCurrentText("Line");

    ui->toolBar->addWidget(widthBox);
    ui->toolBar->addWidget(styleBox);
    ui->toolBar->addWidget(modeBox);
    ui->toolBar->addWidget(insertModeBox);
}

void MainWindow::createDrawBoard()
{
    drawboard = new DrawBoard(this);
    drawboard->setMinimumSize(400, 400);
    this->setCentralWidget(drawboard);
}

void MainWindow::setWidth(const int width)
{
    drawboard->setWidth(width);
}

void MainWindow::setStyle(const QString &styleString)
{
    drawboard->setStyle(styleString);
}

void MainWindow::setMode(const QString &modeString)
{
    drawboard->setMode(modeString);
}

void MainWindow::setInsertMode(const QString &modeString)
{
    drawboard->setInsertMode(modeString);
}

void MainWindow::createConnections()
{
    QObject::connect(widthBox, SIGNAL(valueChanged(int)), this, SLOT(setWidth(int)));
    QObject::connect(styleBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setStyle(const QString&)));
    QObject::connect(modeBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setMode(const QString&)));
    QObject::connect(insertModeBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setInsertMode(const QString&)));
    QObject::connect(drawboard, SIGNAL(shapeSelected(const Shape&)), this, SLOT(setShape(const Shape&)));
}

template<typename Item>
void MainWindow::addItemsToComboBox(QComboBox &comboBox, std::map<QString, Item> &map) {
    for (typename std::map<QString, Item>::iterator it = map.begin();
         it != map.end(); ++it)
    {
        comboBox.addItem(it->first);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName{ QFileDialog::getOpenFileName(this, tr("Open File"), "./") };
    QFile file{ fileName };
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in{ &file };
        QVector<Shape*> shapes;
        in >> shapes;
        drawboard->setShapes(shapes);
        file.close();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName{ QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled") };
    QFile file{ fileName };
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out{ &file };
        out << drawboard->getShapes();
        file.close();
    }
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionPick_Color_triggered()
{
    drawboard->pickColor(QColorDialog::getColor(Qt::black, this));
}
