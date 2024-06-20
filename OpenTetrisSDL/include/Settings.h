#pragma once

#include <fstream>
#include "SDL.h"
#include "json/json.h"


std::string KeyToString(SDL_KeyCode key);
std::string ButtonToString(Uint8 button);
std::string AxisToString(SDL_GameControllerAxis axis);

//class VideoSettings {
//public:
//    sf::VideoMode videoMode;
//    sf::ContextSettings ñontext;
//    bool fullscreen;
//    bool verticalSyncEnabled;
//    int framerateLimit;
//
//
//    VideoSettings() :
//        videoMode(800, 600),
//        fullscreen(false),
//        verticalSyncEnabled(false),
//        framerateLimit(0)
//    {}
//
//    bool operator==(const VideoSettings& other) const
//    {
//        return ((fullscreen == other.fullscreen)
//            && (verticalSyncEnabled == other.verticalSyncEnabled)
//            && (framerateLimit == other.framerateLimit)
//            && (videoMode.height == other.videoMode.height)
//            && (videoMode.width == other.videoMode.width));
//    }
//
//    bool ApplySettings(sf::RenderWindow& window)
//    {
//#pragma region Video settings
//        window.create(videoMode, L"Simple Strategy", fullscreen ? sf::Style::Fullscreen : sf::Style::Default, ñontext);
//        window.setFramerateLimit(framerateLimit);
//        window.setVerticalSyncEnabled(verticalSyncEnabled);
//#pragma endregion
//
//        return true;
//    }
//    friend std::ostream& operator<<(std::ostream& os, const VideoSettings& settings) {
//        os << "Video Settings:" << std::endl;
//        os << "Resolution: " << settings.videoMode.width << "x" << settings.videoMode.height << std::endl;
//        os << "Fullscreen: " << (settings.fullscreen ? "Enabled" : "Disabled") << std::endl;
//        os << "Vertical Sync: " << (settings.verticalSyncEnabled ? "Enabled" : "Disabled") << std::endl;
//        os << "Framerate Limit: " << settings.framerateLimit << std::endl;
//        return os;
//    }
//};

class AudioSettings {
public:
    float volume;
    bool mute;

    AudioSettings() :
        volume(1.f),
        mute(false)
    {}

    friend std::ostream& operator<<(std::ostream& os, const AudioSettings& settings) {
        os << "Audio Settings:" << std::endl;
        os << "Volume: " << settings.volume << std::endl;
        os << "Mute: " << (settings.mute ? "Yes" : "No") << std::endl;
        // Add other audio settings if needed
        return os;
    }
};

class KeyboardSettings {
public:
    SDL_KeyCode moveUpKey;
    SDL_KeyCode moveDownKey;
    SDL_KeyCode moveLeftKey;
    SDL_KeyCode moveRightKey;

    KeyboardSettings() :
        moveUpKey(SDLK_w),
        moveDownKey(SDLK_s),
        moveLeftKey(SDLK_a),
        moveRightKey(SDLK_d)
    {}

    friend std::ostream& operator<<(std::ostream& os, const KeyboardSettings& settings) {
        os << "Keyboard Settings:" << std::endl;
        os << "Move Up Key: " << KeyToString(settings.moveUpKey) << std::endl;
        os << "Move Down Key: " << KeyToString(settings.moveDownKey) << std::endl;
        os << "Move Left Key: " << KeyToString(settings.moveLeftKey) << std::endl;
        os << "Move Right Key: " << KeyToString(settings.moveRightKey) << std::endl;
        return os;
    }
};

//class MouseSettings {
//public:
//    Uint8 shootButton;
//
//    MouseSettings() :
//        shootButton(SDL_BUTTON_LEFT)
//    {}
//
//    friend std::ostream& operator<<(std::ostream& os, const MouseSettings& settings) {
//        os << "Mouse Settings:" << std::endl;
//        os << "Shoot Button: " << ButtonToString(settings.shootButton) << std::endl;
//        return os;
//    }
//};

class Settings
{
public:
    Settings();
    ~Settings();

    //VideoSettings videoSettings;
    AudioSettings audioSettings;
    KeyboardSettings keyboardSettings;
    //MouseSettings mouseSettings;

    bool LoadFromJson(std::string file = "settings.json");
    bool SaveToJson(std::string file = "settings.json");
    //bool ApplySettings(sf::RenderWindow& window);

    friend std::ostream& operator<<(std::ostream& os, const Settings& settings) {
        os << "All Settings:" << std::endl;
        os /*<< settings.videoSettings*/ << settings.audioSettings << settings.keyboardSettings /*<< settings.mouseSettings*/ << std::endl;
        return os;
    }

    void restartProgram();

private:
};