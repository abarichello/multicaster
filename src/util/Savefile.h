#pragma once

#include <sol.hpp>
#include <string>

class Savefile {
public:
    Savefile();

    void loadSaveFile();
    void writeSaveFile();

    template <typename T>
    void setSaveData(std::string key, T data) {
        this->saveLuaState[TABLE_NAME][key] = data;
        this->writeSaveFile();
    }

    template <typename T>
    T getSaveData(std::string key) {
        return this->saveLuaState[TABLE_NAME][key];
    }

private:
    sol::state saveLuaState;
    const std::string TABLE_NAME = "save_table";
};
