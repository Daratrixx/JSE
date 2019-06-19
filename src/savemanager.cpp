
#include "savemanager.h"

SaveManager::SaveManager() {

}

std::string SaveManager::GetDefaultSaveFilePath() {
    //SHGetFolderPath(CSIDL_MYDOCUMENTS)
    return "C:/Users/%USERNAME%/Documents/Journey/SAVE.BIN";
}

Save* SaveManager::LoadFile() {
    return LoadFile(GetDefaultSaveFilePath());
}

Save* SaveManager::LoadFile(const std::string & path) {
    std::cout << "Attenpting to open (read) file at " << path << std::endl;
    Save* output = new Save();
    Save& s = *output; // easier syntax
    try {

        saveFileRead.open(path, std::ifstream::in|std::ifstream::binary);

        if(!saveFileRead.is_open()) {
            std::cout << "Error: The save file was not opened. Check the path." << std::endl;
            saveFileRead.close();
            delete output;
            return null;
        }

        // read current journey state
        s.level = (ReadAtOffset(OFFSET_CURRENT_LEVEL));
        std::cout << "level " << s.level << std::endl; // debug
        s.scarfLength = (ReadAtOffset(OFFSET_SCARF_LENGTH));
        std::cout << "scarfLength " << s.scarfLength << std::endl; // debug
        s.symbol = (ReadAtOffset(OFFSET_CURRENT_SYMBOL));
        std::cout << "symbol " << s.symbol << std::endl; // debug
        s.cloak = (ReadAtOffset(OFFSET_CLOAK));
        std::cout << "cloak " << s.cloak << std::endl; // debug

        // read global journey data
        FLAG dsHUB = ReadAtOffset(OFFSET_FOUND_HUB);
        s.discoveredSymbolHUB0 = dsHUB & 0x1;
        s.discoveredSymbolHUB1 = dsHUB & 0x2;
        s.discoveredSymbolHUB2 = dsHUB & 0x4;
        FLAG dsBB = ReadAtOffset(OFFSET_FOUND_BB);
        s.discoveredSymbolBB0 = dsBB & 0x1;
        s.discoveredSymbolBB1 = dsBB & 0x2;
        s.discoveredSymbolBB2 = dsBB & 0x4;
        FLAG dsPD = ReadAtOffset(OFFSET_FOUND_PD);
        s.discoveredSymbolPD0 = dsPD & 0x1;
        s.discoveredSymbolPD1 = dsPD & 0x2;
        s.discoveredSymbolPD2 = dsPD & 0x4;
        s.discoveredSymbolPD3 = dsPD & 0x8;
        FLAG dsSC = ReadAtOffset(OFFSET_FOUND_SC);
        s.discoveredSymbolSC0 = dsSC & 0x1;
        s.discoveredSymbolSC1 = dsSC & 0x2;
        s.discoveredSymbolSC2 = dsSC & 0x4;
        FLAG dsUG = ReadAtOffset(OFFSET_FOUND_UG);
        s.discoveredSymbolUG0 = dsUG & 0x1;
        s.discoveredSymbolUG1 = dsUG & 0x2;
        s.discoveredSymbolUG2 = dsUG & 0x4;
        s.discoveredSymbolUG3 = dsUG & 0x8;
        FLAG dsTOWER = ReadAtOffset(OFFSET_FOUND_TOWER);
        s.discoveredSymbolTOWER0 = dsTOWER & 0x1;
        s.discoveredSymbolTOWER1 = dsTOWER & 0x2;
        s.discoveredSymbolTOWER2 = dsTOWER & 0x4;
        s.discoveredSymbolTOWER3 = dsTOWER & 0x8;
        //FLAG dsLEVEL09 = ReadAtOffset(OFFSET_FOUND_LEVEL09);
        //s.discoveredSymbolLEVEL090 = dsLEVEL09 & 0x1;
        //s.discoveredSymbolLEVEL091 = dsLEVEL09 & 0x2;
        //s.discoveredSymbolLEVEL092 = dsLEVEL09 & 0x4;
        //s.discoveredSymbolLEVEL093 = dsLEVEL09 & 0x8;

    } catch (std::exception e) {
        std::cout << "Exception loading save file: " << e.what() << std::endl;
        saveFileRead.close();
        delete output;
        return null;
    }
    return output;
}

char* SaveManager::ReadAtOffset(std::streampos offset, std::uint8_t size) {
    char* output = new char[size];

    saveFileRead.seekg(offset);
    saveFileRead.read(output,size);

    return output;
}

NUMBER SaveManager::ReadAtOffset(std::streampos offset) {
    char* data = ReadAtOffset(offset,1);

    NUMBER output = (NUMBER)*data;
    delete data;

    return output;
}

bool SaveManager::SaveFile(const Save & save) {
    return SaveFile(save, GetDefaultSaveFilePath());
}

bool SaveManager::SaveFile(const Save & save, const std::string & path) {
    std::cout << "Attenpting to open (write) file at " << path << std::endl;
    try {
        saveFileWrite.open(path,std::fstream::out|std::ifstream::binary);

        // write current journey data
        WriteAtOffset(save.level,OFFSET_CURRENT_LEVEL);
        WriteAtOffset(save.scarfLength,OFFSET_SCARF_LENGTH);
        WriteAtOffset(save.symbol,OFFSET_CURRENT_SYMBOL);
        WriteAtOffset(save.cloak,OFFSET_CLOAK);

        // write global journey data
        FLAG dsHUB =
                (save.discoveredSymbolHUB0 ? 0x1 : 0x0) |
                (save.discoveredSymbolHUB1 ? 0x2 : 0x0) |
                (save.discoveredSymbolHUB2 ? 0x4 : 0x0) ;
        WriteAtOffset(dsHUB,OFFSET_FOUND_HUB);
        FLAG dsBB =
                (save.discoveredSymbolBB0 ? 0x1 : 0x0) |
                (save.discoveredSymbolBB1 ? 0x2 : 0x0) |
                (save.discoveredSymbolBB2 ? 0x4 : 0x0) ;
        WriteAtOffset(dsBB,OFFSET_FOUND_BB);
        FLAG dsPD =
                (save.discoveredSymbolPD0 ? 0x1 : 0x0) |
                (save.discoveredSymbolPD1 ? 0x2 : 0x0) |
                (save.discoveredSymbolPD2 ? 0x4 : 0x0) |
                (save.discoveredSymbolPD3 ? 0x8 : 0x0) ;
        WriteAtOffset(dsPD,OFFSET_FOUND_PD);
        FLAG dsSC =
                (save.discoveredSymbolSC0 ? 0x1 : 0x0) |
                (save.discoveredSymbolSC1 ? 0x2 : 0x0) |
                (save.discoveredSymbolSC2 ? 0x4 : 0x0) ;
        WriteAtOffset(dsSC,OFFSET_FOUND_SC);
        FLAG dsUG =
                (save.discoveredSymbolUG0 ? 0x1 : 0x0) |
                (save.discoveredSymbolUG1 ? 0x2 : 0x0) |
                (save.discoveredSymbolUG2 ? 0x4 : 0x0) |
                (save.discoveredSymbolUG3 ? 0x8 : 0x0) ;
        WriteAtOffset(dsUG,OFFSET_FOUND_UG);
        FLAG dsTOWER =
                (save.discoveredSymbolTOWER0 ? 0x1 : 0x0) |
                (save.discoveredSymbolTOWER1 ? 0x2 : 0x0) |
                (save.discoveredSymbolTOWER2 ? 0x4 : 0x0) |
                (save.discoveredSymbolTOWER3 ? 0x8 : 0x0) ;
        WriteAtOffset(dsTOWER,OFFSET_FOUND_TOWER);
        //FLAG dsLEVEL09 =
        //        (save.discoveredSymbolLEVEL090 ? 0x1 : 0x0) |
        //        (save.discoveredSymbolLEVEL091 ? 0x2 : 0x0) |
        //        (save.discoveredSymbolLEVEL092 ? 0x4 : 0x0) |
        //        (save.discoveredSymbolLEVEL093 ? 0x8 : 0x0) ;
        //WriteAtOffset(dsLEVEL09,OFFSET_FOUND_LEVEL09);

        saveFileWrite.flush();
        return true;
    } catch (std::exception e) {
        std::cout << "Exception loading save file: " << e.what() << std::endl;
        saveFileWrite.close();
        return false;
    }
}

bool SaveManager::WriteAtOffset(char* data, std::streampos offset, std::uint8_t size) {
    saveFileWrite.seekp(offset);
    saveFileWrite.write(data,size);

    return true;
}

bool SaveManager::WriteAtOffset(NUMBER data, std::streampos offset) {
    return WriteAtOffset((char*)&data,offset,1);
}
