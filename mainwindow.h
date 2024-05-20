#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QList>
#include <QStringList>
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>
#include <QStandardItemModel>
#include <QLabel>
#include <QTableView>
#include <QSet>
#include <QAction>
#include <QDialog>
#include <QShortcut>
#include <QLineEdit>
#include <algorithm>
#include <functional>
#include <QChar>
#include <QFileDialog>
#include <QCoreApplication>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static QList<QStringList> DS;

    ~MainWindow();

private slots:
    void on_pushButtonPickUp_clicked();
    void on_comboBoxSort_currentIndexChanged(int order);
    void FindTicket(const QList<QStringList> &parameters);
    void Filter(const QStringList &AirLines);


    void on_pushButtonChooseAir_clicked();

    void on_pushButtonReset_clicked();

private:
    Ui::MainWindow *ui;

    void load_file();

};
#endif // MAINWINDOW_H
