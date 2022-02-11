#include "createmachinedialog.h"
#include "ui_createmachinedialog.h"

CreateMachineDialog::CreateMachineDialog(VirtualMachineStruct *machine, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateMachineDialog),
    m_machine(machine)
{
    ui->setupUi(this);

    connect(ui->pushButtonYes, &QPushButton::clicked, this, &CreateMachineDialog::onButtonClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &QDialog::close);

    this->setWindowTitle("新建虚拟机");
}

CreateMachineDialog::~CreateMachineDialog()
{
    delete ui;
}

void CreateMachineDialog::onButtonClicked() {
    if (!ui->lineEditFormat->text().isEmpty() &&
            !ui->lineEditName->text().isEmpty() &&
            !ui->lineEditSize->text().isEmpty()) {
        m_machine->name = ui->lineEditName->text();

        m_machine->size = ui->lineEditSize->text();

        m_machine->format = ui->lineEditFormat->text();

        m_machine->path = ui->lineEditPath->text();
    }

    close();
}