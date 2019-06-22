#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    saveManager(null),
    save(new Save()),
    loading(false),
    dirty(false)
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
    connect(ui->inputLevel, SIGNAL(currentIndexChanged(int)), this, SLOT (ComboLevelChanged(int)));
    connect(ui->inputScarfLength, SIGNAL(valueChanged(int)), this, SLOT (SpinScarfLengthChanged(int)));
    connect(ui->inputSymbol, SIGNAL(currentIndexChanged(int)), this, SLOT (ComboSymbolChanged(int)));
    connect(ui->inputCloak, SIGNAL(currentIndexChanged(int)), this, SLOT (ComboCloakChanged(int)));

    connect(ui->cbHUB0, SIGNAL (clicked(bool)), this, SLOT (CbHUB0changed(bool)));
    connect(ui->cbHUB1, SIGNAL (clicked(bool)), this, SLOT (CbHUB1changed(bool)));
    connect(ui->cbHUB2, SIGNAL (clicked(bool)), this, SLOT (CbHUB2changed(bool)));
    connect(ui->cbBB0, SIGNAL (clicked(bool)), this, SLOT (CbBB0changed(bool)));
    connect(ui->cbBB1, SIGNAL (clicked(bool)), this, SLOT (CbBB1changed(bool)));
    connect(ui->cbBB2, SIGNAL (clicked(bool)), this, SLOT (CbBB2changed(bool)));
    connect(ui->cbPD0, SIGNAL (clicked(bool)), this, SLOT (CbPD0changed(bool)));
    connect(ui->cbPD1, SIGNAL (clicked(bool)), this, SLOT (CbPD1changed(bool)));
    connect(ui->cbPD2, SIGNAL (clicked(bool)), this, SLOT (CbPD2changed(bool)));
    connect(ui->cbPD3, SIGNAL (clicked(bool)), this, SLOT (CbPD3changed(bool)));
    connect(ui->cbSC0, SIGNAL (clicked(bool)), this, SLOT (CbSC0changed(bool)));
    connect(ui->cbSC1, SIGNAL (clicked(bool)), this, SLOT (CbSC1changed(bool)));
    connect(ui->cbSC2, SIGNAL (clicked(bool)), this, SLOT (CbSC2changed(bool)));
    connect(ui->cbUG0, SIGNAL (clicked(bool)), this, SLOT (CbUG0changed(bool)));
    connect(ui->cbUG1, SIGNAL (clicked(bool)), this, SLOT (CbUG1changed(bool)));
    connect(ui->cbUG2, SIGNAL (clicked(bool)), this, SLOT (CbUG2changed(bool)));
    connect(ui->cbUG3, SIGNAL (clicked(bool)), this, SLOT (CbUG3changed(bool)));
    connect(ui->cbTOWER0, SIGNAL (clicked(bool)), this, SLOT (CbTOWER0changed(bool)));
    connect(ui->cbTOWER1, SIGNAL (clicked(bool)), this, SLOT (CbTOWER1changed(bool)));
    connect(ui->cbTOWER2, SIGNAL (clicked(bool)), this, SLOT (CbTOWER2changed(bool)));
    connect(ui->cbTOWER3, SIGNAL (clicked(bool)), this, SLOT (CbTOWER3changed(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete save;
    delete saveManager;
}

void MainWindow::LoadFile() {
    if(!saveManager) saveManager = new SaveManager();
    // ensure the destruction of the previous data context
    if(save) delete save;

    // ask the user to locate the file on their computer
    // TODO: first try to get a registry value (TODO: write that registry value upon successfully loading the file)
    // TODO: then try the default path before asking the user to locate the file
    auto path = QFileDialog::getOpenFileName(this,
                                     tr("Locate Journey save file (Documents/Journey)"), "/Documents/Journey", tr("Binary file (*.BIN)"));

    if(path == null || path == "null") {
        Error("Please indicate where the Journey save file is located on your computer. Click Load (ctrl+o)");
        return;
    }


    // get a new context from the path located
    save = saveManager->LoadFile(path.toStdString());

    // update view and editing context
    dirty = false;
    std::string title = "Journey Save Editor (" + path.toStdString() + ")";
    this->setWindowTitle(title.c_str());

    DisplaySaveData();
}
void MainWindow::SaveFile() {


    // ask the user to locate the file on their computer
    // TODO: first try to get a registry value (TODO: write that registry value upon successfully loading the file)
    // TODO: then try the default path before asking the user to locate the file
    auto path = QFileDialog::getOpenFileName(this,
                                     tr("Locate Journey save file (Documents/Journey)"), "/Documents/Journey", tr("Binary file (*.BIN)"));

    if(!saveManager->SaveFile(*save,path.toStdString())) {
        Error("An error occured while writing to the save file. The save file was not modified.");
        return;
    }

    // update context and view
    dirty = false;
    std::string title = "Journey Save Editor (" + path.toStdString() + ")";
    this->setWindowTitle(title.c_str());
}
void MainWindow::DisplaySaveData() {
    if(save == null) {
        Error("No data context to display. The file was not preoperly loaded.");
        return;
    }
    try {
        loading = true;
        // Set the general state values
        ui->labelContinueButtonVisibilityValue->setText(save->continueButtonVisible == VALUE_CONTINUE_TRUE ? "VISIBLE":"HIDDEN");
        ui->inputLevel->setCurrentIndex(std::max(ui->inputLevel->findData(save->level),0));
        ui->inputScarfLength->setValue(save->scarfLength);
        ui->inputSymbol->setCurrentIndex(std::max(ui->inputSymbol->findData(save->symbol),0));
        ui->inputCloak->setCurrentIndex(std::max(ui->inputCloak->findData(save->cloak),0));

        // Set the discovered symbol checkboxes values
        ui->labelDiscoveredSymbolCountValue->setText(NumberToString(save->discoveredSymbolCount).c_str());
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
        loading = false;
    } catch (std::exception e) {
        Error(e.what());
        loading = false;
    }
}

void MainWindow::Error(const std::string & message, const std::string & title) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title.c_str());
    msgBox.setText(message.c_str());
    msgBox.exec();
}

void MainWindow::Dirty() {
    if(!dirty) {
        dirty = true;
        setWindowTitle("* " + windowTitle());
    }
}


void MainWindow::UpdateDiscoveredSymbolCount(bool increased) {
    save->discoveredSymbolCount += increased ? 1 : -1;
    ui->labelDiscoveredSymbolCountValue->setText(NumberToString(save->discoveredSymbolCount).c_str());
}
void MainWindow::UpdateContinueButtonVisible(int level) {
    save->continueButtonVisible = IsContinueButtonVisible(*save);
    ui->labelContinueButtonVisibilityValue->setText(save->continueButtonVisible == VALUE_CONTINUE_TRUE ? "VISIBLE":"HIDDEN");
}


void MainWindow::ButtonLoad() {
    LoadFile();
}
void MainWindow::ButtonSave() {
    SaveFile();
}
void MainWindow::ComboLevelChanged(int index){
    if(loading) return;
    if(index > -1) {
        save->level = (ID)index;
        UpdateContinueButtonVisible(index);
        Dirty();
    }
}
void MainWindow::SpinScarfLengthChanged(int value){
    if(loading) return;
    save->scarfLength = (NUMBER)value;
}
void MainWindow::ComboCloakChanged(int index){
    if(loading) return;
    if(index > -1) {
        save->cloak = (ID)index;
        Dirty();
    }
}
void MainWindow::ComboSymbolChanged(int index){
    if(loading) return;
    if(index > -1) {
        save->symbol = (ID)index;
        Dirty();
    }
}
void MainWindow::CbHUB0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolHUB0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbHUB1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolHUB1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbHUB2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolHUB2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbBB0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolBB0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbBB1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolBB1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbBB2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolBB2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbPD0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolPD0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbPD1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolPD1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbPD2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolPD2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbPD3changed(bool checked){
    if(loading) return;
    save->discoveredSymbolPD3 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbSC0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolSC0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbSC1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolSC1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbSC2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolSC2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbUG0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolUG0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbUG1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolUG1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbUG2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolUG2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbUG3changed(bool checked){
    if(loading) return;
    save->discoveredSymbolUG3 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbTOWER0changed(bool checked){
    if(loading) return;
    save->discoveredSymbolTOWER0 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbTOWER1changed(bool checked){
    if(loading) return;
    save->discoveredSymbolTOWER1 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbTOWER2changed(bool checked){
    if(loading) return;
    save->discoveredSymbolTOWER2 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
void MainWindow::CbTOWER3changed(bool checked){
    if(loading) return;
    save->discoveredSymbolTOWER3 = checked;
    UpdateDiscoveredSymbolCount(checked);
    Dirty();
}
