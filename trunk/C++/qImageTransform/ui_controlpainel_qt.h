/********************************************************************************
** Form generated from reading ui file 'controlpainel_qt.ui'
**
** Created: Fri Mar 13 13:05:37 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONTROLPAINEL_QT_H
#define UI_CONTROLPAINEL_QT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPainel_qtClass
{
public:
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonDrawLineA;
    QPushButton *buttonClearLineA;
    QPushButton *buttonMaskLineA;
    QPushButton *buttonFilterLineA;
    QCheckBox *checkBoxShowMaskA;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *buttonDrawLineB;
    QPushButton *buttonClearLineB;
    QPushButton *buttonMaskLineB;
    QPushButton *buttonFilterLineB;
    QCheckBox *checkBoxShowMaskB;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonOpen;
    QPushButton *buttonSave;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonQuit;

    void setupUi(QWidget *ControlPainel_qtClass)
    {
        if (ControlPainel_qtClass->objectName().isEmpty())
            ControlPainel_qtClass->setObjectName(QString::fromUtf8("ControlPainel_qtClass"));
        ControlPainel_qtClass->resize(230, 413);
        groupBox = new QGroupBox(ControlPainel_qtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(100, 10, 121, 191));
        groupBox->setStyleSheet(QString::fromUtf8("background:rgb(170, 255, 127)"));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 101, 161));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonDrawLineA = new QPushButton(verticalLayoutWidget_2);
        buttonDrawLineA->setObjectName(QString::fromUtf8("buttonDrawLineA"));
        buttonDrawLineA->setFlat(false);

        verticalLayout_2->addWidget(buttonDrawLineA);

        buttonClearLineA = new QPushButton(verticalLayoutWidget_2);
        buttonClearLineA->setObjectName(QString::fromUtf8("buttonClearLineA"));

        verticalLayout_2->addWidget(buttonClearLineA);

        buttonMaskLineA = new QPushButton(verticalLayoutWidget_2);
        buttonMaskLineA->setObjectName(QString::fromUtf8("buttonMaskLineA"));

        verticalLayout_2->addWidget(buttonMaskLineA);

        buttonFilterLineA = new QPushButton(verticalLayoutWidget_2);
        buttonFilterLineA->setObjectName(QString::fromUtf8("buttonFilterLineA"));
        buttonFilterLineA->setAutoRepeat(true);

        verticalLayout_2->addWidget(buttonFilterLineA);

        checkBoxShowMaskA = new QCheckBox(verticalLayoutWidget_2);
        checkBoxShowMaskA->setObjectName(QString::fromUtf8("checkBoxShowMaskA"));

        verticalLayout_2->addWidget(checkBoxShowMaskA);

        groupBox_2 = new QGroupBox(ControlPainel_qtClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(100, 210, 121, 191));
        groupBox_2->setStyleSheet(QString::fromUtf8("background: rgb(255, 170, 127)"));
        verticalLayoutWidget_3 = new QWidget(groupBox_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 101, 161));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setMargin(11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        buttonDrawLineB = new QPushButton(verticalLayoutWidget_3);
        buttonDrawLineB->setObjectName(QString::fromUtf8("buttonDrawLineB"));
        buttonDrawLineB->setFlat(false);

        verticalLayout_5->addWidget(buttonDrawLineB);

        buttonClearLineB = new QPushButton(verticalLayoutWidget_3);
        buttonClearLineB->setObjectName(QString::fromUtf8("buttonClearLineB"));

        verticalLayout_5->addWidget(buttonClearLineB);

        buttonMaskLineB = new QPushButton(verticalLayoutWidget_3);
        buttonMaskLineB->setObjectName(QString::fromUtf8("buttonMaskLineB"));

        verticalLayout_5->addWidget(buttonMaskLineB);

        buttonFilterLineB = new QPushButton(verticalLayoutWidget_3);
        buttonFilterLineB->setObjectName(QString::fromUtf8("buttonFilterLineB"));
        buttonFilterLineB->setAutoRepeat(true);

        verticalLayout_5->addWidget(buttonFilterLineB);

        checkBoxShowMaskB = new QCheckBox(verticalLayoutWidget_3);
        checkBoxShowMaskB->setObjectName(QString::fromUtf8("checkBoxShowMaskB"));

        verticalLayout_5->addWidget(checkBoxShowMaskB);

        verticalLayoutWidget = new QWidget(ControlPainel_qtClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(6, 10, 87, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        buttonOpen = new QPushButton(verticalLayoutWidget);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));

        verticalLayout->addWidget(buttonOpen);

        buttonSave = new QPushButton(verticalLayoutWidget);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));

        verticalLayout->addWidget(buttonSave);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonQuit = new QPushButton(verticalLayoutWidget);
        buttonQuit->setObjectName(QString::fromUtf8("buttonQuit"));

        verticalLayout->addWidget(buttonQuit);


        retranslateUi(ControlPainel_qtClass);

        QMetaObject::connectSlotsByName(ControlPainel_qtClass);
    } // setupUi

    void retranslateUi(QWidget *ControlPainel_qtClass)
    {
        ControlPainel_qtClass->setWindowTitle(QApplication::translate("ControlPainel_qtClass", "ControlPainel_qt", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ControlPainel_qtClass", "Line A", 0, QApplication::UnicodeUTF8));
        buttonDrawLineA->setText(QApplication::translate("ControlPainel_qtClass", "Draw", 0, QApplication::UnicodeUTF8));
        buttonClearLineA->setText(QApplication::translate("ControlPainel_qtClass", "Clear", 0, QApplication::UnicodeUTF8));
        buttonMaskLineA->setText(QApplication::translate("ControlPainel_qtClass", "Mask", 0, QApplication::UnicodeUTF8));
        buttonFilterLineA->setText(QApplication::translate("ControlPainel_qtClass", "Filter", 0, QApplication::UnicodeUTF8));
        checkBoxShowMaskA->setText(QApplication::translate("ControlPainel_qtClass", "Show Mask", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ControlPainel_qtClass", "Line B", 0, QApplication::UnicodeUTF8));
        buttonDrawLineB->setText(QApplication::translate("ControlPainel_qtClass", "Draw", 0, QApplication::UnicodeUTF8));
        buttonClearLineB->setText(QApplication::translate("ControlPainel_qtClass", "Clear", 0, QApplication::UnicodeUTF8));
        buttonMaskLineB->setText(QApplication::translate("ControlPainel_qtClass", "Mask", 0, QApplication::UnicodeUTF8));
        buttonFilterLineB->setText(QApplication::translate("ControlPainel_qtClass", "Filter", 0, QApplication::UnicodeUTF8));
        checkBoxShowMaskB->setText(QApplication::translate("ControlPainel_qtClass", "Show Mask", 0, QApplication::UnicodeUTF8));
        buttonOpen->setText(QApplication::translate("ControlPainel_qtClass", "Open", 0, QApplication::UnicodeUTF8));
        buttonSave->setText(QApplication::translate("ControlPainel_qtClass", "Save", 0, QApplication::UnicodeUTF8));
        buttonQuit->setText(QApplication::translate("ControlPainel_qtClass", "Quit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ControlPainel_qtClass);
    } // retranslateUi

};

namespace Ui {
    class ControlPainel_qtClass: public Ui_ControlPainel_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPAINEL_QT_H
