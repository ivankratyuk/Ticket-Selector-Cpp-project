#include "cartdialog.h"
#include "ui_cartdialog.h"
#include <QDesktopServices>

CartDialog::CartDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CartDialog)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStringList> to_show, ds = MainWindow::Cart;
    int Total = 0;

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
        Total += ds[r][10].toInt();
    }
    ui->tableView->setModel(model);
    QString total = QString::number(Total);
    ui->labelTotal->setText("Total:  " + total);

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
    int Total = 0;


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
        Total += ds[r][10].toInt();
    }

    ui->tableView->setModel(model);
    QString total = QString::number(Total);
    ui->labelTotal->setText("Total:  " + total);
}


void CartDialog::on_pushButtonCheck_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Ticket File", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) {
        QMessageBox::information(nullptr, "No File Selected", "No file selected to save tickets.");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Could not open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "Flight Tickets\n";
    out << "==============\n\n";


    int Total = 0;

    for (QStringList &ticket : MainWindow::Cart)
    {
        out << "Date  " << ticket[1] << '\n';
        out << "Airline  " << ticket[2] << '\t';
        out << "Flight No.  " << ticket[3] << '\n';
        out << "Departure city  " << ticket[5] << '\t';
        out << "Departure time  " << ticket[4] << '\n';
        out << "Arrival city  " << ticket[9] << '\t';
        out << "Arrival time  " << ticket[8] << '\n';
        out << "Flight duration  " << ticket[6] << '\n';
        out << "-----------------------------\n";
        Total += ticket[10].toInt();
    }

    out << "\nTotal sum: " << QString::number(Total) << '\n';
    file.close();

    QMessageBox::information(nullptr, "File Saved", "The tickets have been saved successfully.");

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

