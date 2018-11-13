#include "tcp_ip_server.h"
#include "base_handler.h"
#include "time_handler.h"
#include "game_handler.h"
#include "set_handler.h"

int main() {
    NeosFunGame *pGame = new NeosFunGame();

    TCPIPServer *pServer = new TCPIPServer();
    // pServer->registerHandler(new BaseHandler(pGame));
    pServer->registerHandler(new TimeHandler(pGame));
    pServer->registerHandler(new SetHandler(pGame));

    // cast example
    GameHandler *pGameHandler = new GameHandler(pGame);
    BaseHandler *pGameLikeBaseHandler = static_cast<BaseHandler *>(pGameHandler);
    pServer->registerHandler(pGameLikeBaseHandler);

    int nPort = 3333;
    pServer->start(nPort); // will wait finish
}