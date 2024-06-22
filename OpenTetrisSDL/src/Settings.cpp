#include "Settings.h"

Settings::Settings() :
    videoSettings(),
    audioSettings(),
    keyboardSettings()
{}

Settings::~Settings() {}

bool Settings::LoadFromJson(const std::string& file) {
    std::ifstream inputFile(file);
    if (!inputFile.is_open()) {
        spdlog::warn("Settings file not found. Creating default settings file.");
        return SaveToJson(file);
    }

    Json::Value settingsJson;
    inputFile >> settingsJson;

    videoSettings.width = settingsJson["video"]["width"].asInt();
    videoSettings.height = settingsJson["video"]["height"].asInt();
    videoSettings.fullscreen = settingsJson["video"]["fullscreen"].asBool();
    videoSettings.verticalSyncEnabled = settingsJson["video"]["verticalSyncEnabled"].asBool();
    videoSettings.framerateLimit = settingsJson["video"]["framerateLimit"].asInt();
    videoSettings.antiAliasingLevel = settingsJson["video"]["antiAliasingLevel"].asInt();
    videoSettings.windowMode = settingsJson["video"]["windowMode"].asString();
    videoSettings.renderScaleQuality = settingsJson["video"]["renderScaleQuality"].asString();
    videoSettings.videoDriver = settingsJson["video"]["videoDriver"].asString();
    videoSettings.hardwareAcceleration = settingsJson["video"]["hardwareAcceleration"].asBool();

    audioSettings.volume = settingsJson["audio"]["volume"].asFloat();
    audioSettings.mute = settingsJson["audio"]["mute"].asBool();

    keyboardSettings.moveUpKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["moveUpKey"].asInt());
    keyboardSettings.moveLeftKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["moveLeftKey"].asInt());
    keyboardSettings.moveRightKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["moveRightKey"].asInt());
    keyboardSettings.moveDownKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["moveDownKey"].asInt());

    inputFile.close();

    return true;
}

bool Settings::SaveToJson(const std::string& file) {
    Json::Value settingsJson;

    settingsJson["video"]["width"] = videoSettings.width;
    settingsJson["video"]["height"] = videoSettings.height;
    settingsJson["video"]["fullscreen"] = videoSettings.fullscreen;
    settingsJson["video"]["verticalSyncEnabled"] = videoSettings.verticalSyncEnabled;
    settingsJson["video"]["framerateLimit"] = videoSettings.framerateLimit;
    settingsJson["video"]["antiAliasingLevel"] = videoSettings.antiAliasingLevel;
    settingsJson["video"]["windowMode"] = videoSettings.windowMode;
    settingsJson["video"]["renderScaleQuality"] = videoSettings.renderScaleQuality;
    settingsJson["video"]["videoDriver"] = videoSettings.videoDriver;
    settingsJson["video"]["hardwareAcceleration"] = videoSettings.hardwareAcceleration;

    settingsJson["audio"]["volume"] = audioSettings.volume;
    settingsJson["audio"]["mute"] = audioSettings.mute;

    settingsJson["keyboard"]["moveUpKey"] = static_cast<int>(keyboardSettings.moveUpKey);
    settingsJson["keyboard"]["moveLeftKey"] = static_cast<int>(keyboardSettings.moveLeftKey);
    settingsJson["keyboard"]["moveRightKey"] = static_cast<int>(keyboardSettings.moveRightKey);
    settingsJson["keyboard"]["moveDownKey"] = static_cast<int>(keyboardSettings.moveDownKey);

    std::ofstream outputFile(file);
    if (!outputFile.is_open()) {
        return false;
    }

    Json::StreamWriterBuilder writer;
    writer["indentation"] = "\t";
    outputFile << Json::writeString(writer, settingsJson);
    outputFile.close();

    return true;
}

void Settings::restartProgram() {
    this->SaveToJson();
    system("start OpenTetrisSDL.exe");
    exit(0);
}

std::string ButtonToString(Uint8 button) {
    const char* buttonName = SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
    return buttonName ? std::string(buttonName) : "Undefined";
}

std::string AxisToString(SDL_GameControllerAxis axis) {
    const char* axisName = SDL_GameControllerGetStringForAxis(axis);
    return axisName ? std::string(axisName) : "Undefined";
}
