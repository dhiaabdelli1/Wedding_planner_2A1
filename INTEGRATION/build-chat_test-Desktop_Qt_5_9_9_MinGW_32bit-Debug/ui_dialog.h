/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *uname;
    QLabel *passwordLabel;
    QLineEdit *passwd;
    QLabel *destinataireLabel;
    QLineEdit *recipient;
    QLabel *sujetLabel;
    QLineEdit *subjectLineEdit;
    QTextEdit *message;
    QHBoxLayout *horizontalLayout;
    QPushButton *annuler_mail;
    QPushButton *envoyer_dialog;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(581, 399);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        usernameLabel = new QLabel(Dialog);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        uname = new QLineEdit(Dialog);
        uname->setObjectName(QStringLiteral("uname"));

        formLayout->setWidget(0, QFormLayout::FieldRole, uname);

        passwordLabel = new QLabel(Dialog);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwd = new QLineEdit(Dialog);
        passwd->setObjectName(QStringLiteral("passwd"));

        formLayout->setWidget(1, QFormLayout::FieldRole, passwd);

        destinataireLabel = new QLabel(Dialog);
        destinataireLabel->setObjectName(QStringLiteral("destinataireLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, destinataireLabel);

        recipient = new QLineEdit(Dialog);
        recipient->setObjectName(QStringLiteral("recipient"));

        formLayout->setWidget(2, QFormLayout::FieldRole, recipient);

        sujetLabel = new QLabel(Dialog);
        sujetLabel->setObjectName(QStringLiteral("sujetLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, sujetLabel);

        subjectLineEdit = new QLineEdit(Dialog);
        subjectLineEdit->setObjectName(QStringLiteral("subjectLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, subjectLineEdit);


        verticalLayout->addLayout(formLayout);

        message = new QTextEdit(Dialog);
        message->setObjectName(QStringLiteral("message"));

        verticalLayout->addWidget(message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        annuler_mail = new QPushButton(Dialog);
        annuler_mail->setObjectName(QStringLiteral("annuler_mail"));

        horizontalLayout->addWidget(annuler_mail);

        envoyer_dialog = new QPushButton(Dialog);
        envoyer_dialog->setObjectName(QStringLiteral("envoyer_dialog"));

        horizontalLayout->addWidget(envoyer_dialog);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("Dialog", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("Dialog", "Password", Q_NULLPTR));
        destinataireLabel->setText(QApplication::translate("Dialog", "Destinataire", Q_NULLPTR));
        sujetLabel->setText(QApplication::translate("Dialog", "Sujet", Q_NULLPTR));
        annuler_mail->setText(QApplication::translate("Dialog", "Annuler", Q_NULLPTR));
        envoyer_dialog->setText(QApplication::translate("Dialog", "Envoyer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
