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
    QString imgFile;
    VirtualMachineStruct machine;

    void onActionOpen();
    void checkQemu();
    bool ifFound(char *file);
    void newVirtualMachine();
    void createMachine();
    void runMachine();
};
#endif // VIRTUALMACHINE_H