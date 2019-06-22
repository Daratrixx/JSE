#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

/*
 * File: savemanager.h
 *
 * Author: Daratrixx
 *
 * Contributors:
 *
 * Desciption:
 * This file defines the helper class responsible for locating, loading and saving the journey
 * save file.
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include "defines.h"
#include "save.h"

class SaveManager {

public:

    explicit SaveManager();
    ~SaveManager();

    // TODO: find a way to generate a path to the Document/Journey folder using %USERNAME%
    std::string GetDefaultSaveFilePath();

    // Loads the file from the path returned by GetDefaultSaveFilePath()
    Save* LoadFile();

    // Loads the file from the [path] given in parameter
    Save* LoadFile(const std::string & path);

    // Reads [size] bytes from the absolute [offset] within the currently opened [saveFileRead]
    char* ReadAtOffset(std::streampos offset, std::uint8_t size);
    NUMBER ReadAtOffset(std::streampos offset);

    // Saves the [save] data to the file at the path returned by GetDefaultSaveFilePath()
    bool SaveFile(const Save & save);

    // Saves the [save] data to the file at the [path] given in parameter
    bool SaveFile(const Save & save, const std::string & path);

    // Writes [size] bytes of [data] at the absolute [offset] within the currently opened [saveFileWrite]
    bool WriteAtOffset(char* data, std::streampos offset, std::uint8_t size);
    bool WriteAtOffset(NUMBER data, std::streampos offset);

private:

    // "clean globals" so the streams are not set in every parameter lists.
    std::ifstream* saveFileRead;
    std::fstream* saveFileWrite;

};

#endif // SAVEMANAGER_H
