#include "cartdialog.h"
#include "ui_cartdialog.h"

CartDialog::CartDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CartDialog)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStringList> to_show, ds = MainWindow::Cart;

    for (int c = 1; c < MainWindow::TicketsDS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::TicketsDS[0][c]);
        model->setHorizontalHeaderItem(c-1, item);
    }

    for (int r = 0; r < ds.length(); r++)
    {
        for (int c = 1; c < ds[0].length(); c++)
        {
            QStandardItem *item = new QStandardItem(ds[r][c]);
            model->setItem(r, c-1, item);
        }
    }
    ui->tableView->setModel(model);
}

CartDialog::~CartDialog()
{
    delete ui;
}

void CartDialog::on_pushButtonClear_clicked()
{
    MainWindow::Cart.clear();
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStringList> to_show, ds = MainWindow::Cart;

    for (int c = 1; c < MainWindow::TicketsDS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::TicketsDS[0][c]);
        model->setHorizontalHeaderItem(c-1, item);
    }

    for (int r = 0; r < ds.length(); r++)
    {
        for (int c = 1; c < ds[0].length(); c++)
        {
            QStandardItem *item = new QStandardItem(ds[r][c]);
            model->setItem(r, c-1, item);
        }
    }

    ui->tableView->setModel(model);

}

