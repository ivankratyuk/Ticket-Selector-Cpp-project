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
