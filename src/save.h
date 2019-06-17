#ifndef SAVE_H
#define SAVE_H

/*
 * File: save.h
 *
 * Author: Daratrixx
 *
 * Contributors:
 *
 * Desciption:
 * This class define the model used by the editor. The file is parsed into this format by the SaveManager.
 * The model can then be modified by the user interface, and the SaveManager can write it back into the file.
 *
 */

#include "defines.h"

struct Save {

    // current journey
    ID level;
    NUMBER scarfLength;
    ID symbol;
    ID cloak;

    // global settings
    FLAG discoveredSymbolHUB0;
    FLAG discoveredSymbolHUB1;
    FLAG discoveredSymbolHUB2;
    FLAG discoveredSymbolBB0;
    FLAG discoveredSymbolBB1;
    FLAG discoveredSymbolBB2;
    FLAG discoveredSymbolPD0;
    FLAG discoveredSymbolPD1;
    FLAG discoveredSymbolPD2;
    FLAG discoveredSymbolPD3;
    FLAG discoveredSymbolSC0;
    FLAG discoveredSymbolSC1;
    FLAG discoveredSymbolSC2;
    FLAG discoveredSymbolUG0;
    FLAG discoveredSymbolUG1;
    FLAG discoveredSymbolUG2;
    FLAG discoveredSymbolUG3;
    FLAG discoveredSymbolTOWER0;
    FLAG discoveredSymbolTOWER1;
    FLAG discoveredSymbolTOWER2;
    FLAG discoveredSymbolTOWER3;
    FLAG discoveredSymbolLEVEL090;
    FLAG discoveredSymbolLEVEL091;
    FLAG discoveredSymbolLEVEL092;
    FLAG discoveredSymbolLEVEL093;

};

#endif // SAVE_H
