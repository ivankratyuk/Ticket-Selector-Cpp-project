#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::on_pushButtonFilter_clicked()
{
    QStringList AirLines;
    if (!ui->checkBoxGoFirst->isChecked() && !ui->checkBoxIndigo->isChecked() &&
        !ui->checkBoxSpaceJ->isChecked() && !ui->checkBoxVistara->isChecked() &&
        !ui->checkBox_AirInd->isChecked() && !ui->AirAsia->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Choose at leat one AirLine to filter");
    } else {
        if (ui->AirAsia->isChecked())
            AirLines.append("AirAsia");
        if (ui->checkBoxGoFirst->isChecked())
            AirLines.append("GO_FIRST");
        if (ui->checkBoxIndigo->isChecked())
            AirLines.append("Indigo");
        if (ui->checkBoxSpaceJ->isChecked())
            AirLines.append("SpaceJet");
        if (ui->checkBoxVistara->isChecked())
            AirLines.append("Vistara");
        if (ui->checkBox_AirInd->isChecked())
            AirLines.append("Air_India");

        emit AirLinesSignal(AirLines);
        close();
    }
}

