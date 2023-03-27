#pragma once

#include <map>
#include <functional>
#include <string_view>

#include "co/http.h"

namespace gd__ {
    struct httpServerConf {
        static constexpr char const * userSqlServerUrl {"http://localhost:9191"};
        static constexpr char const * userImgServerUrl {"http://localhost:9193"};
        static constexpr char const * logSqlServerUrl {"http://localhost:9192"};

        static std::map<std::string, std::function<void(http::Req const &, http::Res &)>> methods;

        static void httpOnReq(http::Req const &, http::Res &);
        static void onInsert(http::Req const &, http::Res &);
        static void onDelete(http::Req const &, http::Res &);
        static void onSelect(http::Req const &, http::Res &);
        static void onGetImg(http::Req const &, http::Res &);
        static void onAddImg(http::Req const &, http::Res &);
        static void onDelImg(http::Req const &, http::Res &);
        static void onInsertLog(http::Req const &, http::Res &);
        static void onGetLogByName(http::Req const &, http::Res &);
        static void onGetLogBySite(http::Req const &, http::Res &);
        static void onGetLogByTime(http::Req const &, http::Res &);

        static void addSuccessHeader(http::Res &);
        static void addFailedHeader(http::Res &, char const *);
        static void addResultHeader(http::Res &, http::Client &);
    };
}