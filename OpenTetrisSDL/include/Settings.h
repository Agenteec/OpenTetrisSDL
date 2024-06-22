#pragma once

#include "SDL.h"
#include <string>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "spdlog/spdlog.h"

class VideoSettings {
public:
    int width;
    int height;
    bool fullscreen;
    bool verticalSyncEnabled;
    int framerateLimit;
    int antiAliasingLevel;
    std::string windowMode; // "windowed", "fullscreen", "borderless"
    std::string renderScaleQuality; // "0", "1", "2"
    std::string videoDriver; // "direct3d", "opengl"
    bool hardwareAcceleration; // true for SDL_RENDERER_ACCELERATED, false for SDL_RENDERER_SOFTWARE

    VideoSettings() :
        width(800),
        height(600),
        fullscreen(false),
        verticalSyncEnabled(false),
        framerateLimit(60),
        antiAliasingLevel(0),
        windowMode("windowed"),
        renderScaleQuality("1"),
        videoDriver((SDL_GetCurrentVideoDriver()==nullptr?"undefined": SDL_GetCurrentVideoDriver())),
        hardwareAcceleration(true)
    {}

    bool operator==(const VideoSettings& other) const {
        return (width == other.width &&
            height == other.height &&
            fullscreen == other.fullscreen &&
            verticalSyncEnabled == other.verticalSyncEnabled &&
            framerateLimit == other.framerateLimit &&
            antiAliasingLevel == other.antiAliasingLevel &&
            windowMode == other.windowMode &&
            renderScaleQuality == other.renderScaleQuality &&
            videoDriver == other.videoDriver &&
            hardwareAcceleration == other.hardwareAcceleration);
    }

    friend std::ostream& operator<<(std::ostream& os, const VideoSettings& settings) {
        os << "Video Settings:" << std::endl;
        os << "Resolution: " << settings.width << "x" << settings.height << std::endl;
        os << "Fullscreen: " << (settings.fullscreen ? "Enabled" : "Disabled") << std::endl;
        os << "Vertical Sync: " << (settings.verticalSyncEnabled ? "Enabled" : "Disabled") << std::endl;
        os << "Framerate Limit: " << settings.framerateLimit << std::endl;
        os << "Anti-Aliasing Level: " << settings.antiAliasingLevel << std::endl;
        os << "Window Mode: " << settings.windowMode << std::endl;
        os << "Render Scale Quality: " << settings.renderScaleQuality << std::endl;
        os << "Video Driver: " << settings.videoDriver << std::endl;
        os << "Hardware Acceleration: " << (settings.hardwareAcceleration ? "Enabled" : "Disabled") << std::endl;
        return os;
    }
};

class AudioSettings {
public:
    float volume;
    bool mute;

    AudioSettings() :
        volume(1.0f),
        mute(false)
    {}

    friend std::ostream& operator<<(std::ostream& os, const AudioSettings& settings) {
        os << "Audio Settings:" << std::endl;
        os << "Volume: " << settings.volume << std::endl;
        os << "Mute: " << (settings.mute ? "Yes" : "No") << std::endl;
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
        os << "Move Up Key: " << SDL_GetKeyName(settings.moveUpKey) << std::endl;
        os << "Move Down Key: " << SDL_GetKeyName(settings.moveDownKey) << std::endl;
        os << "Move Left Key: " << SDL_GetKeyName(settings.moveLeftKey) << std::endl;
        os << "Move Right Key: " << SDL_GetKeyName(settings.moveRightKey) << std::endl;
        return os;
    }
};

class Settings {
public:
    Settings();
    ~Settings();

    VideoSettings videoSettings;
    AudioSettings audioSettings;
    KeyboardSettings keyboardSettings;

    bool LoadFromJson(const std::string& file = "settings.json");
    bool SaveToJson(const std::string& file = "settings.json");

    friend std::ostream& operator<<(std::ostream& os, const Settings& settings) {
        os << "All Settings:" << std::endl;
        os << settings.videoSettings << settings.audioSettings << settings.keyboardSettings << std::endl;
        return os;
    }

    void restartProgram();
};
