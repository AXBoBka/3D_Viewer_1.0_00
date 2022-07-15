/********************************************************************************
** Form generated from reading UI file 'glview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLVIEW_H
#define UI_GLVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glView
{
public:

    void setupUi(QWidget *glView)
    {
        if (glView->objectName().isEmpty())
            glView->setObjectName(QString::fromUtf8("glView"));
        glView->resize(800, 600);

        retranslateUi(glView);

        QMetaObject::connectSlotsByName(glView);
    } // setupUi

    void retranslateUi(QWidget *glView)
    {
        glView->setWindowTitle(QCoreApplication::translate("glView", "glView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class glView: public Ui_glView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLVIEW_H
