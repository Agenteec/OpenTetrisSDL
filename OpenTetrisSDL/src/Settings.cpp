#include "Settings.h"


Settings::Settings():
	//videoSettings(),
	audioSettings(),
	keyboardSettings()
	//mouseSettings()
{
}

Settings::~Settings()
{
}

bool Settings::LoadFromJson(std::string file)
{
	std::ifstream inputFile(file);
	if (!inputFile.is_open()) {
		return false;
	}

	Json::Value settingsJson;
	inputFile >> settingsJson;

	/*videoSettings.videoMode.width = settingsJson["video"]["resolution_x"];
	videoSettings.videoMode.height = settingsJson["video"]["resolution_y"];
	videoSettings.fullscreen = settingsJson["video"]["fullscreen"];
	videoSettings.ñontext.antialiasingLevel = settingsJson["video"]["antialiasing_level"];*/

	audioSettings.volume = settingsJson["audio"]["volume"].asFloat();
	audioSettings.mute = settingsJson["audio"]["mute"].asBool();

	keyboardSettings.moveUpKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["move_up_key"].asInt());
	keyboardSettings.moveLeftKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["move_left_key"].asInt());
	keyboardSettings.moveRightKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["move_right_key"].asInt());
	keyboardSettings.moveDownKey = static_cast<SDL_KeyCode>(settingsJson["keyboard"]["move_down_key"].asInt());

	//mouseSettings.shootButton = static_cast<int>(settingsJson["mouse"]["shoot_button"]);

	inputFile.close();

	return true;
}

bool Settings::SaveToJson(std::string file)
{
	Json::Value settingsJson;

	/*settingsJson["video"]["resolution_x"] = videoSettings.videoMode.width; 
	settingsJson["video"]["resolution_y"] = videoSettings.videoMode.height;
	settingsJson["video"]["fullscreen"] = videoSettings.fullscreen;
	settingsJson["video"]["antialiasing_level"] = videoSettings.ñontext.antialiasingLevel;*/

	settingsJson["audio"]["volume"] = audioSettings.volume;
	settingsJson["audio"]["mute"] = audioSettings.mute;

	settingsJson["keyboard"]["move_up_key"] = static_cast<int>(keyboardSettings.moveUpKey);
	settingsJson["keyboard"]["move_left_key"] = static_cast<int>(keyboardSettings.moveLeftKey);
	settingsJson["keyboard"]["move_right_key"] = static_cast<int>(keyboardSettings.moveRightKey);
	settingsJson["keyboard"]["move_down_key"] = static_cast<int>(keyboardSettings.moveDownKey);

	//settingsJson["mouse"]["shoot_button"] = static_cast<int>(mouseSettings.shootButton);

	std::ofstream outputFile(file);
	if (!outputFile.is_open()) {
		return false;
	}

	Json::StreamWriterBuilder writer;
	writer["indentation"] = '\t';
	outputFile << Json::writeString(writer, settingsJson);
	outputFile.close();

	return true;
}

void Settings::restartProgram()
{
	this->SaveToJson();

	system("start OpenTetrisSDL.exe");

	exit(0);
}

std::string KeyToString(SDL_KeyCode key)
{
    switch (key)
    {
    case SDLK_UNKNOWN:         return "Unknown";
    case SDLK_a:               return "A";
    case SDLK_b:               return "B";
    case SDLK_c:               return "C";
    case SDLK_d:               return "D";
    case SDLK_e:               return "E";
    case SDLK_f:               return "F";
    case SDLK_g:               return "G";
    case SDLK_h:               return "H";
    case SDLK_i:               return "I";
    case SDLK_j:               return "J";
    case SDLK_k:               return "K";
    case SDLK_l:               return "L";
    case SDLK_m:               return "M";
    case SDLK_n:               return "N";
    case SDLK_o:               return "O";
    case SDLK_p:               return "P";
    case SDLK_q:               return "Q";
    case SDLK_r:               return "R";
    case SDLK_s:               return "S";
    case SDLK_t:               return "T";
    case SDLK_u:               return "U";
    case SDLK_v:               return "V";
    case SDLK_w:               return "W";
    case SDLK_x:               return "X";
    case SDLK_y:               return "Y";
    case SDLK_z:               return "Z";
    case SDLK_0:               return "Num0";
    case SDLK_1:               return "Num1";
    case SDLK_2:               return "Num2";
    case SDLK_3:               return "Num3";
    case SDLK_4:               return "Num4";
    case SDLK_5:               return "Num5";
    case SDLK_6:               return "Num6";
    case SDLK_7:               return "Num7";
    case SDLK_8:               return "Num8";
    case SDLK_9:               return "Num9";
    case SDLK_ESCAPE:          return "Escape";
    case SDLK_LCTRL:           return "LControl";
    case SDLK_LSHIFT:          return "LShift";
    case SDLK_LALT:            return "LAlt";
    case SDLK_LGUI:            return "LSystem";
    case SDLK_RCTRL:           return "RControl";
    case SDLK_RSHIFT:          return "RShift";
    case SDLK_RALT:            return "RAlt";
    case SDLK_RGUI:            return "RSystem";
    case SDLK_MENU:            return "Menu";
    case SDLK_LEFTBRACKET:     return "LBracket";
    case SDLK_RIGHTBRACKET:    return "RBracket";
    case SDLK_SEMICOLON:       return "Semicolon";
    case SDLK_COMMA:           return "Comma";
    case SDLK_PERIOD:          return "Period";
    case SDLK_QUOTE:           return "Quote";
    case SDLK_SLASH:           return "Slash";
    case SDLK_BACKSLASH:       return "Backslash";
    case SDLK_BACKQUOTE:       return "Tilde";
    case SDLK_EQUALS:          return "Equal";
    case SDLK_MINUS:           return "Hyphen";
    case SDLK_SPACE:           return "Space";
    case SDLK_RETURN:          return "Enter";
    case SDLK_BACKSPACE:       return "Backspace";
    case SDLK_TAB:             return "Tab";
    case SDLK_PAGEUP:          return "PageUp";
    case SDLK_PAGEDOWN:        return "PageDown";
    case SDLK_END:             return "End";
    case SDLK_HOME:            return "Home";
    case SDLK_INSERT:          return "Insert";
    case SDLK_DELETE:          return "Delete";
    case SDLK_KP_PLUS:         return "Add";
    case SDLK_KP_MINUS:        return "Subtract";
    case SDLK_KP_MULTIPLY:     return "Multiply";
    case SDLK_KP_DIVIDE:       return "Divide";
    case SDLK_LEFT:            return "Left";
    case SDLK_RIGHT:           return "Right";
    case SDLK_UP:              return "Up";
    case SDLK_DOWN:            return "Down";
    case SDLK_KP_0:            return "Numpad0";
    case SDLK_KP_1:            return "Numpad1";
    case SDLK_KP_2:            return "Numpad2";
    case SDLK_KP_3:            return "Numpad3";
    case SDLK_KP_4:            return "Numpad4";
    case SDLK_KP_5:            return "Numpad5";
    case SDLK_KP_6:            return "Numpad6";
    case SDLK_KP_7:            return "Numpad7";
    case SDLK_KP_8:            return "Numpad8";
    case SDLK_KP_9:            return "Numpad9";
    case SDLK_F1:              return "F1";
    case SDLK_F2:              return "F2";
    case SDLK_F3:              return "F3";
    case SDLK_F4:              return "F4";
    case SDLK_F5:              return "F5";
    case SDLK_F6:              return "F6";
    case SDLK_F7:              return "F7";
    case SDLK_F8:              return "F8";
    case SDLK_F9:              return "F9";
    case SDLK_F10:             return "F10";
    case SDLK_F11:             return "F11";
    case SDLK_F12:             return "F12";
    default:
        return "undefine";
    }
}

std::string ButtonToString(Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:       return "Left";
    case SDL_BUTTON_RIGHT:      return "Right";
    case SDL_BUTTON_MIDDLE:     return "Middle";
    case SDL_BUTTON_X1:         return "XButton1";
    case SDL_BUTTON_X2:         return "XButton2";
    default:
        return "Undefined";
    }
}

std::string AxisToString(SDL_GameControllerAxis axis)
{
    switch (axis)
    {
    case SDL_CONTROLLER_AXIS_LEFTX:        return "LeftX";
    case SDL_CONTROLLER_AXIS_LEFTY:        return "LeftY";
    case SDL_CONTROLLER_AXIS_RIGHTX:       return "RightX";
    case SDL_CONTROLLER_AXIS_RIGHTY:       return "RightY";
    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:  return "TriggerLeft";
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT: return "TriggerRight";
    default:
        return "Undefined";
    }
}
