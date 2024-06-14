/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *fileListWidget;
    QPushButton *selectFileButton;
    QPushButton *convertButton;
    QPushButton *saveButton;
    QPlainTextEdit *outputTextEdit;
    QLabel *fileCountLabel;
    QPushButton *clearButton;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 575);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        fileListWidget = new QListWidget(centralwidget);
        fileListWidget->setObjectName(QString::fromUtf8("fileListWidget"));
        fileListWidget->setGeometry(QRect(15, 51, 351, 371));
        QFont font1;
        font1.setPointSize(8);
        fileListWidget->setFont(font1);
        selectFileButton = new QPushButton(centralwidget);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));
        selectFileButton->setGeometry(QRect(21, 490, 171, 31));
        QFont font2;
        font2.setPointSize(10);
        selectFileButton->setFont(font2);
        convertButton = new QPushButton(centralwidget);
        convertButton->setObjectName(QString::fromUtf8("convertButton"));
        convertButton->setGeometry(QRect(201, 490, 171, 31));
        convertButton->setFont(font2);
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(410, 490, 171, 31));
        saveButton->setFont(font2);
        outputTextEdit = new QPlainTextEdit(centralwidget);
        outputTextEdit->setObjectName(QString::fromUtf8("outputTextEdit"));
        outputTextEdit->setGeometry(QRect(370, 50, 411, 371));
        outputTextEdit->setFont(font1);
        fileCountLabel = new QLabel(centralwidget);
        fileCountLabel->setObjectName(QString::fromUtf8("fileCountLabel"));
        fileCountLabel->setGeometry(QRect(30, 10, 131, 21));
        fileCountLabel->setFont(font);
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(590, 490, 171, 31));
        clearButton->setFont(font2);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(60, 440, 661, 23));
        progressBar->setValue(0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Convert_To_RGB565", nullptr));
        selectFileButton->setText(QApplication::translate("MainWindow", "Select File", nullptr));
        convertButton->setText(QApplication::translate("MainWindow", "Convert", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        fileCountLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
