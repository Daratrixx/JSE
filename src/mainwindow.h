#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * File: mainwindow.h
 *
 * Author: Daratrixx
 *
 * Contributors:
 *
 * Desciption:
 * This file describes the class of the main window of the application.
 * It uses a SaveManager object to abstract the interractions with the actual save file.
 * A Save object is used as a datacontext. It is first loaded via the SaveManager,
 * and can then be edited via the interface. Finally, the SaveManager can commit the changes
 * into the actual file on the HDD.
 *
 */

#include <QMainWindow>
#include "defines.h"
#include "savemanager.h"
#include "save.h"

// Qt-generated code. Partial declaration within the Ui namespace.
namespace Ui {
    class MainWindow;
}

// Qt-generated code. Actual definition of the class.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // User-written code
    // High level methods
    void LoadFile();
    void SaveFile();
    void DisplaySaveData();

private slots:
    // User interaction methods
    void ButtonLoad();
    void ButtonSave();


private:
    Ui::MainWindow *ui;

    // User-written code.
    // Model
    Save* save;
    // Tool
    SaveManager saveManager;

};

#endif // MAINWINDOW_H
