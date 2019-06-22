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

    void Error(const std::string & message, const std::string & title = "Error");
    void Dirty();

    void UpdateDiscoveredSymbolCount(bool);
    void UpdateContinueButtonVisible(int);

private slots:
    // User interaction methods
    void ButtonLoad();
    void ButtonSave();
    void ComboLevelChanged(int index);
    void SpinScarfLengthChanged(int value);
    void ComboCloakChanged(int index);
    void ComboSymbolChanged(int index);
    void CbHUB0changed(bool);
    void CbHUB1changed(bool);
    void CbHUB2changed(bool);
    void CbBB0changed(bool);
    void CbBB1changed(bool);
    void CbBB2changed(bool);
    void CbPD0changed(bool);
    void CbPD1changed(bool);
    void CbPD2changed(bool);
    void CbPD3changed(bool);
    void CbSC0changed(bool);
    void CbSC1changed(bool);
    void CbSC2changed(bool);
    void CbUG0changed(bool);
    void CbUG1changed(bool);
    void CbUG2changed(bool);
    void CbUG3changed(bool);
    void CbTOWER0changed(bool);
    void CbTOWER1changed(bool);
    void CbTOWER2changed(bool);
    void CbTOWER3changed(bool);


private:
    Ui::MainWindow *ui;

    // User-written code.
    // Tool
    SaveManager* saveManager;
    // Model
    Save* save;

    bool loading;
    bool dirty;

};

#endif // MAINWINDOW_H
