#include "co/http.h"
#include "co/time.h"

#include "httpServerConf.h"

auto main() -> int {
    http::Server()
    .on_req(gd__::httpServerConf::httpOnReq)
    .start("127.0.0.1", 9190);

    while (true) {
        sleep::sec(100);
    }

    return 0;
}