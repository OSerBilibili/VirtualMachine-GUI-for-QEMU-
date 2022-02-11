#ifndef CREATEMACHINEDIALOG_H
#define CREATEMACHINEDIALOG_H

/**
 *@author 朱江宇
 */

#include "virtualmachinestruct.h"
#include <QDialog>
#include <QPushButton>

namespace Ui {
class CreateMachineDialog;
}

class CreateMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMachineDialog(VirtualMachineStruct *machine, QWidget *parent = nullptr);
    ~CreateMachineDialog();

    VirtualMachineStruct getMachine();

private:
    Ui::CreateMachineDialog *ui;
    VirtualMachineStruct *m_machine;

    void onButtonClicked();
};

#endif // CREATEMACHINEDIALOG_H