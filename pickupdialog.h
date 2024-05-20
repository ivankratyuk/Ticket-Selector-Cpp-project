#ifndef PICKUPDIALOG_H
#define PICKUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class PickUpDialog;
}

class PickUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PickUpDialog(QWidget *parent = nullptr);
    ~PickUpDialog();

signals:
    void FindTicketsignal(const QList<QStringList> &parameters);

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonFind_clicked();

private:
    Ui::PickUpDialog *ui;
};

#endif // PICKUPDIALOG_H
