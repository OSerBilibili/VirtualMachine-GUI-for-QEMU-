#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

/**
 *@author 朱江宇
 */

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <QDesktopServices>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <QMessageBox>
#include <QDialog>
#include <QDir>
#include <QProcess>
#include "createmachinedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VirtualMachine; }
QT_END_NAMESPACE

class VirtualMachine : public QMainWindow
{
    Q_OBJECT

public:
    VirtualMachine(QWidget *parent = nullptr);
    ~VirtualMachine();

private:
    Ui::VirtualMachine *ui;
    QString imgFile; // .img文件
    VirtualMachineStruct machine; // 虚拟机配置

    void onActionOpen();
    bool ifFound(char *file); // 检测是否安装了QEMU
    void newVirtualMachine();
    void createMachine();
    void runMachine();
    void chooseISO();
};
#endif // VIRTUALMACHINE_H