#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pickupdialog.h"
#include "filterdialog.h"

QList<QStringList> MainWindow::DS;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_file(); //load csv to a global array

    QStandardItemModel *model = new QStandardItemModel(this);

    // Setting up headers
    for (int c = 1; c < MainWindow::DS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::DS[0][c]);
        model->setHorizontalHeaderItem(c-1, item);
    }

    // Setting up the whole table
    for (int row = 1; row < MainWindow::DS.length(); row++)
    {
        for(int col = 1; col < MainWindow::DS[row].length(); col++)
        {
            QStandardItem *item = new QStandardItem(MainWindow::DS[row][col]);
            model->setItem(row-1, col-1, item);
        }
    }
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonPickUp_clicked()
{
    PickUpDialog *pickUpDialog = new PickUpDialog(this);
    connect(pickUpDialog, &PickUpDialog::FindTicketsignal, this, &MainWindow::FindTicket);

    pickUpDialog->show();
}

void MainWindow::load_file()
{
    MainWindow::DS.clear();
    QString path = ":/resource/Clean_Dataset.csv";
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        qDebug() << "Can't open the file";
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QString cell;

    while (!in.atEnd())
    {
        QStringList row;
        cell.clear();

        for (int i = 0; i < line.length(); ++i)
        {
            QChar letter = line[i];
            if (letter == ',')
            {
                row.append(cell);
                cell.clear();
                continue;
            }

            cell += letter;

        }

        row.append(cell);
        MainWindow::DS.append(row);
        line = in.readLine();
    }
    file.close();
}

void MainWindow::on_comboBoxSort_currentIndexChanged(int order)
{
    QList<QStringList> d;

    QAbstractItemModel *model = ui->tableView->model();
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    // Extracting data from the model
    for (int row = 0; row < rowCount; ++row) {
        QStringList rowList;
        for (int column = 0; column < columnCount; ++column) {
            QModelIndex index = model->index(row, column);
            QString cellText = model->data(index).toString();
            rowList.append(cellText);
        }
        d.append(rowList);
    }

    // Sorting based on the order
    if (order == 0 || order == 1) {
        std::sort(d.begin(), d.end(), [order](const QStringList& list1, const QStringList& list2) {

            int value1 = list1[9].toInt();
            int value2 = list2[9].toInt();
            return order == 0 ? value1 < value2 : value1 > value2;
        });
    }
    else if (order == 2 || order == 3) {
        std::sort(d.begin(), d.end(), [order](const QStringList& list1, const QStringList& list2) {

            int value1 = list1[10].toInt();
            int value2 = list2[10].toInt();
            return order == 2 ? value1 < value2 : value1 > value2;
        });
    }

    QStandardItemModel *newModel = new QStandardItemModel(rowCount, columnCount, this);

    for (int column = 0; column < columnCount; ++column) {
        QString headerText = model->headerData(column, Qt::Horizontal).toString();
        newModel->setHeaderData(column, Qt::Horizontal, headerText);
    }

    for (int row = 0; row < rowCount; ++row) {
        const QStringList &rowList = d.at(row);
        for (int column = 0; column < rowList.size(); ++column) {
            QStandardItem *item = new QStandardItem(rowList.at(column));
            newModel->setItem(row, column, item);
        }
    }

    ui->tableView->setModel(newModel);
}

void MainWindow::FindTicket(const QList<QStringList> &parameters)
{
    QList<QStringList> d = MainWindow::DS, sortedD;
    for (int r = 0; r < d.length(); ++r)
    {
        if (d[r][3] == parameters[2][0] && d[r][7] == parameters[3][0] && d[r][8] == parameters[0][0] && parameters[1].contains(d[r][4]))
        {
            sortedD.append(d[r]);
        }
    }

    QStandardItemModel *model = new QStandardItemModel();

    // Setting up headers
    for (int c = 1; c < MainWindow::DS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::DS[0][c]);
        model->setHorizontalHeaderItem(c-1, item);
    }

    // Setting up the whole table
    for (int row = 1; row < sortedD.length(); row++)
    {
        for(int col = 1; col < sortedD[row].length(); col++)
        {
            QStandardItem *item = new QStandardItem(sortedD[row][col]);
            model->setItem(row-1, col-1, item);
        }
    }
    ui->tableView->setModel(model);

}

void MainWindow::Filter(const QStringList &AirLines)
{
    QList<QStringList> d, sortedDs;

    QAbstractItemModel *model = ui->tableView->model();
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    // Extracting data from the model
    for (int row = 0; row < rowCount; ++row) {
        QStringList rowList;
        for (int column = 0; column < columnCount; ++column) {
            QModelIndex index = model->index(row, column);
            QString cellText = model->data(index).toString();
            rowList.append(cellText);
        }
        d.append(rowList);
    }

    for (int i = 0; i < d.length(); ++i)
    {
        if (AirLines.contains(d[i][0]))
            sortedDs.append(d[i]);
    }

    QStandardItemModel *newModel = new QStandardItemModel();

    // Setting up headers
    for (int c = 1; c < MainWindow::DS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::DS[0][c]);
        newModel->setHorizontalHeaderItem(c-1, item);
    }

    // Setting up the whole table
    for (int row = 0; row < sortedDs.length(); row++)
    {
        for(int col = 0; col < sortedDs[row].length(); col++)
        {
            QStandardItem *item = new QStandardItem(sortedDs[row][col]);
            newModel->setItem(row, col, item);
        }
    }

    ui->tableView->setModel(newModel);
}

void MainWindow::on_pushButtonChooseAir_clicked()
{
    FilterDialog *filterDialog = new FilterDialog(this);
    connect(filterDialog, &FilterDialog::AirLinesSignal, this, &MainWindow::Filter);

    filterDialog->show();
}


void MainWindow::on_pushButtonReset_clicked()
{
    load_file();
    QStandardItemModel *model = new QStandardItemModel(this);

    // Setting up headers
    for (int c = 1; c < MainWindow::DS[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::DS[0][c]);
        model->setHorizontalHeaderItem(c-1, item);
    }

    // Setting up the whole table
    for (int row = 1; row < MainWindow::DS.length(); row++)
    {
        for(int col = 1; col < MainWindow::DS[row].length(); col++)
        {
            QStandardItem *item = new QStandardItem(MainWindow::DS[row][col]);
            model->setItem(row-1, col-1, item);
        }
    }
    ui->tableView->setModel(model);
}

