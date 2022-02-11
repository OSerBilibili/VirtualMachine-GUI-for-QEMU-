#ifndef VIRTUALMACHINESTRUCT_H
#define VIRTUALMACHINESTRUCT_H

/**
 *@author 朱江宇
 */

#include <QString>

struct VirtualMachineStruct {
    QString size; // 大小
    QString name; // 名称
    QString format; // 格式
    QString path; // 路径
};

#endif // VIRTUALMACHINESTRUCT_H