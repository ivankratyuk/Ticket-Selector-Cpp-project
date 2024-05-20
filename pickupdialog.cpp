#include "pickupdialog.h"
#include "ui_pickupdialog.h"

PickUpDialog::PickUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PickUpDialog)
{
    ui->setupUi(this);
}

PickUpDialog::~PickUpDialog()
{
    delete ui;
}

void PickUpDialog::on_pushButtonCancel_clicked()
{
    close();
}


void PickUpDialog::on_pushButtonFind_clicked()
{
    QList<QStringList> parToFind{{"class"}, {}, {"Dep City"}, {"Dest City"}};

    if (ui->comboBoxDepCity->currentIndex() == 0 || ui->comboBoxDestCity->currentIndex() == 0)
    {
        QMessageBox::warning(this, "Warning", "Choose both cities");

    }

    else if (ui->comboBoxDepCity->currentIndex() == ui->comboBoxDestCity->currentIndex())
    {
        QMessageBox::warning(this, "Warning", "Can't choose same city");
    }
    else
    {
        // class
        if (!ui->radioButtonBus->isChecked() && !ui->radioButtonEco->isChecked()) {
            QMessageBox::warning(this, "Warning", "Choose ticket class");

        } else {
            if (ui->radioButtonBus->isChecked()) {
                parToFind[0][0] = "Business";
            } else if (ui->radioButtonEco->isChecked()) {
                parToFind[0][0] = "Economy";
            }

            // dep/dest city
            parToFind[2][0] = ui->comboBoxDepCity->currentText();
            parToFind[3][0] = ui->comboBoxDestCity->currentText();

            // time period
            if (!ui->checkBoxEarlMo->isChecked() && !ui->checkBoxMo->isChecked() && !ui->checkBoxAft->isChecked()
                && !ui->checkBoxEve->isChecked() && !ui->checkBoxNight->isChecked())
                QMessageBox::warning(this, "Warning", "Choose at leat one time period");
            else {
                if (ui->checkBoxEarlMo->isChecked())
                    parToFind[1].append("Early_Morning");
                if (ui->checkBoxMo->isChecked())
                    parToFind[1].append("Morning");
                if (ui->checkBoxAft->isChecked())
                    parToFind[1].append("Afternoon");
                if (ui->checkBoxEve->isChecked())
                    parToFind[1].append("Evening");
                if (ui->checkBoxNight->isChecked())
                    parToFind[1].append("Night");

                emit FindTicketsignal(parToFind);
                close();
            }
        }
    }
}

