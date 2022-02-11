#include "virtualmachine.h"
#include "./ui_virtualmachine.h"

VirtualMachine::VirtualMachine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirtualMachine)
{
    ui->setupUi(this);

    this->connect(ui->actionQuit, &QAction::triggered, this, &QMainWindow::close);
    this->connect(ui->actionOpen, &QAction::triggered, this, &VirtualMachine::onActionOpen);
    this->connect(ui->actionNew, &QAction::triggered, this, &VirtualMachine::newVirtualMachine);
    this->connect(ui->pushButton, &QPushButton::clicked, this, &VirtualMachine::runMachine);
    this->connect(ui->pushButtonISO, &QPushButton::clicked, this, &VirtualMachine::chooseISO);
    this->connect(ui->actionMe, &QAction::triggered, this,
                  [](){ QMessageBox::about(nullptr, "关于", "本软件是为QEMU做的简易图形程序，图形界面使用Qt"); });
    this->connect(ui->actionQt, &QAction::triggered, this, [](){ QMessageBox::aboutQt(nullptr, "关于Qt"); });
    this->connect(ui->actionGet, &QAction::triggered, this,
                  [](){ QDesktopServices::openUrl(QUrl(QString::fromUtf8("https://gitee.com/oser_bilibili/virtual-machine"))); });

    if (!ifFound((char*)"qemu-img")) {
        QMessageBox::critical(this, "错误", "无法找到qemu-img!\n请检查是否安装QEMU");
        exit(1);
    }

    ui->label->setFont(QFont("KaiTi", 20));
    ui->pushButton->setFont(QFont("KaiTi", 20));

    this->setWindowTitle("虚拟机（基于QEMU）");

    this->setWindowIcon(QIcon(QString::fromUtf8(":/icon/1.png")));
    this->setFixedSize(800, 600);
}

VirtualMachine::~VirtualMachine()
{
    delete ui;
}

void VirtualMachine::onActionOpen() {
    imgFile = QFileDialog::getOpenFileName(this, "选择", ".", "File(*.*)");
    ui->label->setText(imgFile);
}

bool VirtualMachine::ifFound(char *file) {
    char *command = (char*)malloc((strlen(file) + 10)*sizeof(char));
    bool result;
#ifdef __linux__
    char copy[] = "which";
#else
#ifdef __WIN32
    char copy[] = "where";
#endif
#endif
    sprintf(command, "%s %s", copy, file);

    result = !system(command);
    free(command);

    return result;
}

void VirtualMachine::newVirtualMachine() {
    CreateMachineDialog dialog(&machine, this);

    if (!dialog.exec()) {
        createMachine();
    }
}

void VirtualMachine::createMachine() {
    QString command = QString::fromUtf8("qemu-img create -f ");
    command += (machine.format + QString::fromUtf8(" ") + machine.path + QString::fromUtf8("/") + machine.name + QString::fromUtf8(" ") + machine.size);
    QProcess p(0);
    p.start(command);
    p.waitForFinished();
}

void VirtualMachine::runMachine() {
    QString space = QString::fromUtf8(" ");
    QString command;

    if (ui->lineEditMenory->text().isEmpty()) {
        return;
    }

    if (!QString::compare(ui->pushButtonISO->text(), QString::fromUtf8("未选择镜像"))) {
        command = ui->lineEditRun->text() + space + QString::fromUtf8("-enable-kvm -usb -soundhw all -m ")\
                + ui->lineEditMenory->text() + space + imgFile;
    } else {
        command = ui->lineEditRun->text() + space + QString::fromUtf8("-enable-kvm -usb -soundhw all -m ")\
                + ui->lineEditMenory->text() + space + QString::fromUtf8(" -cdrom ") + ui->pushButtonISO->text() + space + imgFile;
    }

    QProcess::startDetached(command);

    if (ui->checkBox->isChecked()) {
        close();
    }
}

void VirtualMachine::chooseISO() {
    QString ISOFile = QFileDialog::getOpenFileName(this, "选择", ".", "ISO file(*.iso)");

    if (!ISOFile.isEmpty()) {
        ui->pushButtonISO->setText(ISOFile);
    }
}