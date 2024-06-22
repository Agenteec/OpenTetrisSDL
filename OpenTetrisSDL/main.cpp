#include "Game.h"
#include <spdlog/spdlog.h>
int main(int argc, char* argv[]) {
    setlocale(0,"Russian");
    system("chcp 1251");
    std::shared_ptr<Settings> settings = std::make_shared<Settings>();
    settings->LoadFromJson();
    Game* game = new Game(settings);
    game->run();
    delete game;
    return 0;
}