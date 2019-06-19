#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    save(null)
{
    ui->setupUi(this);

    // Set a limit to the scarf length.
    ui->inputScarfLength->setRange(0x0,0x1E);

    // Initialize the values for the cloak combo box
    ui->inputCloak->addItem("Red first run",VALUE_CLOAK_1RED);
    ui->inputCloak->addItem("Red second run",VALUE_CLOAK_2RED);
    ui->inputCloak->addItem("Red third run",VALUE_CLOAK_3RED);
    ui->inputCloak->addItem("Red fourth run",VALUE_CLOAK_4RED);
    ui->inputCloak->addItem("White second run",VALUE_CLOAK_2WHITE);
    ui->inputCloak->addItem("White third run",VALUE_CLOAK_3WHITE);
    ui->inputCloak->addItem("White fourth run",VALUE_CLOAK_4WHITE);

    // Initialize the values for the level combo box
    ui->inputLevel->addItem("HUB",VALUE_LEVEL_HUB);
    ui->inputLevel->addItem("Broken bridges",VALUE_LEVEL_BB);
    ui->inputLevel->addItem("Pink desert",VALUE_LEVEL_PD);
    ui->inputLevel->addItem("Sunken city",VALUE_LEVEL_SC);
    ui->inputLevel->addItem("Underground",VALUE_LEVEL_UG);
    ui->inputLevel->addItem("Tower",VALUE_LEVEL_TOWER);
    ui->inputLevel->addItem("Snow",VALUE_LEVEL_SNOW);
    ui->inputLevel->addItem("Paradise",VALUE_LEVEL_PARADISE);
    ui->inputLevel->addItem("Credits",VALUE_LEVEL_CREDITS);
    ui->inputLevel->addItem("Level 09",VALUE_LEVEL_LEVEL09);
    ui->inputLevel->addItem("Credits 1",VALUE_LEVEL_CREDITS1);
    ui->inputLevel->addItem("Credits 2",VALUE_LEVEL_CREDITS2);

    // TODO: Initialize the values for the symbol combo box

    // connect events
    connect(ui->buttonLoad, SIGNAL (released()), this, SLOT (ButtonLoad()));
    connect(ui->buttonSave, SIGNAL (released()), this, SLOT (ButtonSave()));
    connect(ui->inputLevel, SIGNAL (currentIndexChanged()), this, SLOT (ComboLevelChanged()));
    connect(ui->inputScarfLength, SIGNAL (valueChanged()), this, SLOT (SpinScarfLengthChanged()));
    connect(ui->inputSymbol, SIGNAL (currentIndexChanged()), this, SLOT (ComboCloakChanged()));
    connect(ui->inputCloak, SIGNAL (currentIndexChanged()), this, SLOT (ComboSymbolChanged()));

    connect(ui->cbHUB0, SIGNAL (clicked()), this, SLOT (CbHUB0changed()));
    connect(ui->cbHUB1, SIGNAL (clicked()), this, SLOT (CbHUB1changed()));
    connect(ui->cbHUB2, SIGNAL (clicked()), this, SLOT (CbHUB2changed()));
    connect(ui->cbBB0, SIGNAL (clicked()), this, SLOT (CbBB0changed()));
    connect(ui->cbBB1, SIGNAL (clicked()), this, SLOT (CbBB1changed()));
    connect(ui->cbBB2, SIGNAL (clicked()), this, SLOT (CbBB2changed()));
    connect(ui->cbPD0, SIGNAL (clicked()), this, SLOT (CbPD0changed()));
    connect(ui->cbPD1, SIGNAL (clicked()), this, SLOT (CbPD1changed()));
    connect(ui->cbPD2, SIGNAL (clicked()), this, SLOT (CbPD2changed()));
    connect(ui->cbPD3, SIGNAL (clicked()), this, SLOT (CbPD3changed()));
    connect(ui->cbSC0, SIGNAL (clicked()), this, SLOT (CbSC0changed()));
    connect(ui->cbSC1, SIGNAL (clicked()), this, SLOT (CbSC1changed()));
    connect(ui->cbSC2, SIGNAL (clicked()), this, SLOT (CbSC2changed()));
    connect(ui->cbUG0, SIGNAL (clicked()), this, SLOT (CbUG0changed()));
    connect(ui->cbUG1, SIGNAL (clicked()), this, SLOT (CbUG1changed()));
    connect(ui->cbUG2, SIGNAL (clicked()), this, SLOT (CbUG2changed()));
    connect(ui->cbUG3, SIGNAL (clicked()), this, SLOT (CbUG3changed()));
    connect(ui->cbTOWER0, SIGNAL (clicked()), this, SLOT (CbTOWER0changed()));
    connect(ui->cbTOWER1, SIGNAL (clicked()), this, SLOT (CbTOWER1changed()));
    connect(ui->cbTOWER2, SIGNAL (clicked()), this, SLOT (CbTOWER2changed()));
    connect(ui->cbTOWER3, SIGNAL (clicked()), this, SLOT (CbTOWER3changed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadFile() {
    // ensure the destruction of the previous data context
    if(save) delete save;

    // ask the user to locate the file on their computer
    // TODO: first try to get a registry value (TODO: write that registry value upon successfully loading the file)
    // TODO: then try the default path before asking the user to locate the file
    auto path = QFileDialog::getOpenFileName(this,
                                     tr("Locate Journey save file (Documents/Journey)"), "/Documents/Journey", tr("Binary file (*.BIN)"));

    // get a new context from the path located
    save = saveManager.LoadFile(path.toStdString());
}
void MainWindow::SaveFile() {


    // ask the user to locate the file on their computer
    // TODO: first try to get a registry value (TODO: write that registry value upon successfully loading the file)
    // TODO: then try the default path before asking the user to locate the file
    auto path = QFileDialog::getOpenFileName(this,
                                     tr("Locate Journey save file (Documents/Journey)"), "/Documents/Journey", tr("Binary file (*.BIN)"));

    if(saveManager.SaveFile(*save,path.toStdString())) {
        delete save;
        save = null;
    }
}
void MainWindow::DisplaySaveData() {
    if(save == null) {
        QMessageBox msgBox;
        msgBox.setText("No data context to display. The file was not preoperly loaded.");
        msgBox.exec();
        return;
    }
    try {
        // Set the general state values
        ui->inputLevel->setCurrentIndex(std::max(ui->inputLevel->findData(save->level),0));
        ui->inputScarfLength->setValue(save->scarfLength);
        ui->inputSymbol->setCurrentIndex(std::max(ui->inputSymbol->findData(save->symbol),0));
        ui->inputCloak->setCurrentIndex(std::max(ui->inputCloak->findData(save->cloak),0));

        // Set the discovered symbol checkboxes values
        ui->cbHUB0->setCheckState(save->discoveredSymbolHUB0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbHUB1->setCheckState(save->discoveredSymbolHUB1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbHUB2->setCheckState(save->discoveredSymbolHUB2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbBB0->setCheckState(save->discoveredSymbolBB0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbBB1->setCheckState(save->discoveredSymbolBB1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbBB2->setCheckState(save->discoveredSymbolBB2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbPD0->setCheckState(save->discoveredSymbolPD0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbPD1->setCheckState(save->discoveredSymbolPD1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbPD2->setCheckState(save->discoveredSymbolPD2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbPD3->setCheckState(save->discoveredSymbolPD3 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbSC0->setCheckState(save->discoveredSymbolSC0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbSC1->setCheckState(save->discoveredSymbolSC1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbSC2->setCheckState(save->discoveredSymbolSC2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbUG0->setCheckState(save->discoveredSymbolUG0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbUG1->setCheckState(save->discoveredSymbolUG1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbUG2->setCheckState(save->discoveredSymbolUG2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbUG3->setCheckState(save->discoveredSymbolUG3 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbTOWER0->setCheckState(save->discoveredSymbolTOWER0 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbTOWER1->setCheckState(save->discoveredSymbolTOWER1 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbTOWER2->setCheckState(save->discoveredSymbolTOWER2 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
        ui->cbTOWER3->setCheckState(save->discoveredSymbolTOWER3 ? Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    } catch (std::exception e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void MainWindow::ButtonLoad() {
    LoadFile();
}
void MainWindow::ButtonSave() {
    SaveFile();
}
void MainWindow::ComboLevelChanged(int index){
    if(index > -1) {
        save->level = (ID)index;
    }
}
void MainWindow::SpinScarfLengthChanged(int value){
    save->level = (NUMBER)value;
}
void MainWindow::ComboCloakChanged(int index){
    if(index > -1) {
        save->cloak = (ID)index;
    }
}
void MainWindow::ComboSymbolChanged(int index){
    if(index > -1) {
        save->symbol = (ID)index;
    }
}
void MainWindow::CbHUB0changed(bool checked){
    save->discoveredSymbolHUB0 = checked;
}
void MainWindow::CbHUB1changed(bool checked){
    save->discoveredSymbolHUB1 = checked;
}
void MainWindow::CbHUB2changed(bool checked){
    save->discoveredSymbolHUB2 = checked;
}
void MainWindow::CbBB0changed(bool checked){
    save->discoveredSymbolBB0 = checked;
}
void MainWindow::CbBB1changed(bool checked){
    save->discoveredSymbolBB1 = checked;
}
void MainWindow::CbBB2changed(bool checked){
    save->discoveredSymbolBB2 = checked;
}
void MainWindow::CbPD0changed(bool checked){
    save->discoveredSymbolPD0 = checked;
}
void MainWindow::CbPD1changed(bool checked){
    save->discoveredSymbolPD1 = checked;
}
void MainWindow::CbPD2changed(bool checked){
    save->discoveredSymbolPD2 = checked;
}
void MainWindow::CbPD3changed(bool checked){
    save->discoveredSymbolPD3 = checked;
}
void MainWindow::CbSC0changed(bool checked){
    save->discoveredSymbolSC0 = checked;
}
void MainWindow::CbSC1changed(bool checked){
    save->discoveredSymbolSC1 = checked;
}
void MainWindow::CbSC2changed(bool checked){
    save->discoveredSymbolSC2 = checked;
}
void MainWindow::CbUG0changed(bool checked){
    save->discoveredSymbolUG0 = checked;
}
void MainWindow::CbUG1changed(bool checked){
    save->discoveredSymbolUG1 = checked;
}
void MainWindow::CbUG2changed(bool checked){
    save->discoveredSymbolUG2 = checked;
}
void MainWindow::CbUG3changed(bool checked){
    save->discoveredSymbolUG3 = checked;
}
void MainWindow::CbTOWER0changed(bool checked){
    save->discoveredSymbolTOWER0 = checked;
}
void MainWindow::CbTOWER1changed(bool checked){
    save->discoveredSymbolTOWER1 = checked;
}
void MainWindow::CbTOWER2changed(bool checked){
    save->discoveredSymbolTOWER2 = checked;
}
void MainWindow::CbTOWER3changed(bool checked){
    save->discoveredSymbolTOWER3 = checked;
}
