#include "save.h"
#include <iostream>
#include <string>

NUMBER CountDiscoveredSymbol(const Save & s) {
    return (s.discoveredSymbolHUB0 ? 1 : 0) + (s.discoveredSymbolHUB1 ? 1 : 0) + (s.discoveredSymbolHUB2 ? 1 : 0)
        + (s.discoveredSymbolBB0 ? 1 : 0) + (s.discoveredSymbolBB1 ? 1 : 0) + (s.discoveredSymbolBB2 ? 1 : 0)
        + (s.discoveredSymbolPD0 ? 1 : 0) + (s.discoveredSymbolPD1 ? 1 : 0) + (s.discoveredSymbolPD2 ? 1 : 0) + (s.discoveredSymbolPD3 ? 1 : 0)
        + (s.discoveredSymbolSC0 ? 1 : 0) + (s.discoveredSymbolSC1 ? 1 : 0) + (s.discoveredSymbolSC2 ? 1 : 0)
        + (s.discoveredSymbolUG0 ? 1 : 0) + (s.discoveredSymbolUG1 ? 1 : 0) + (s.discoveredSymbolUG2 ? 1 : 0) + (s.discoveredSymbolUG3 ? 1 : 0)
        + (s.discoveredSymbolTOWER0 ? 1 : 0) + (s.discoveredSymbolTOWER1 ? 1 : 0) + (s.discoveredSymbolTOWER2 ? 1 : 0) + (s.discoveredSymbolTOWER3 ? 1 : 0);
}

FLAG IsContinueButtonVisible(const Save & s) {
    return (s.level == VALUE_LEVEL_HUB || s.level ==  VALUE_LEVEL_CREDITS || s.level == VALUE_LEVEL_CREDITS1 || s.level == VALUE_LEVEL_CREDITS2)
            ? VALUE_CONTINUE_FALSE : VALUE_CONTINUE_TRUE;
}

std::string NumberToString(NUMBER n) {
    std::string output = "";
    if(n < 10) {
        char val = '0' + n;
        output+= val;
    } else {
        while(n > 0) {
            char val = '0' + n % 10;
            output = val + output;
            n = n / 10;
        }
    }
    //if(n > -10 && n < 0) return "-" + (char)('0' + n);
    return output;
}
