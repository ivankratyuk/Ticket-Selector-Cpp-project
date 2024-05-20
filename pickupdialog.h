#ifndef PICKUPDIALOG_H
#define PICKUPDIALOG_H

#include <QDialog>

namespace Ui {
class PickUpDialog;
}

class PickUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PickUpDialog(QWidget *parent = nullptr);
    ~PickUpDialog();

private:
    Ui::PickUpDialog *ui;
};

#endif // PICKUPDIALOG_H
