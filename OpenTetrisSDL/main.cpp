#include "Game.h"
#include <spdlog/spdlog.h>
int main(int argc, char* argv[]) {

    std::shared_ptr<Settings> settings = std::make_shared<Settings>();
    if (!settings->LoadFromJson())
        settings->SaveToJson();
    Game* game = new Game(settings);
    game->run();
    delete game;
    return 0;
}