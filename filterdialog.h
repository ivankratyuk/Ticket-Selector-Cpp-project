#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

signals:
    void AirLinesSignal(const QStringList &AirLines);

private slots:
    void on_pushButtonFilter_clicked();

private:
    Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
