#include <map>
#include <functional>
#include <string_view>
#include <iostream>

#include "httpServerConf.h"
#include "httpHeaderConf.h"

#include "co/co.h"
#include "co/co/pool.h"
#include "co/http.h"
#include "co/json.h"
#include "co/fs.h"
#include "co/fastring.h"

namespace gd__ {
    std::map<std::string, std::function<void(http::Req const &, http::Res &)>> httpServerConf::methods {
        {httpHeaderConf::kInsert, onInsert},
        {httpHeaderConf::kDelete, onDelete},
        {httpHeaderConf::kSelect, onSelect},
        {httpHeaderConf::kGetImg, onGetImg},
        {httpHeaderConf::kAddImg, onAddImg},
        {httpHeaderConf::kDelImg, onDelImg},
        {httpHeaderConf::kInsertLog, onInsertLog},
        {httpHeaderConf::kGetLogByName, onGetLogByName},
        {httpHeaderConf::kGetLogBySite, onGetLogBySite},
        {httpHeaderConf::kGetLogByTime, onGetLogByTime}
    };

    void httpServerConf::httpOnReq(http::Req const & req, http::Res & res) {  
        res.set_status(200);

        if (req.is_method_post()) {
            if (std::string_view(req.header(httpHeaderConf::kOperation)).empty()) {
                addFailedHeader(res, "wrong operation");
            } else {
                methods[req.header(httpHeaderConf::kOperation)](req, res);
            }
        } else if (req.is_method_get()){
            onGetImg(req, res);
        }else {
            addFailedHeader(res, "wrong method");
        }
    }

    void httpServerConf::onInsert(http::Req const & req, http::Res & res) {
        http::Client cli(userSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));

        cli.post("/", req.body(), req.body_size());

        addResultHeader(res, cli);
    }

    void httpServerConf::onDelete(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kName)).empty()) {
            addFailedHeader(res, "no name option");

            return;
        }

        http::Client cli(userSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kName, req.header(httpHeaderConf::kName));

        cli.post("/", "");

        addResultHeader(res, cli);
    }

    void httpServerConf::onSelect(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kName)).empty()) {
            addFailedHeader(res, "no name option");

            return;
        }

        http::Client cli(userSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kName, req.header(httpHeaderConf::kName));

        cli.post("/", "");

        addResultHeader(res, cli);

        res.set_body(cli.body());
    }   

    void httpServerConf::onAddImg(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kImageSrc)).empty()) {
            addFailedHeader(res, "no imagesrc option");

            return;
        }

        http::Client cli(userSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kImageSrc, req.header(httpHeaderConf::kImageSrc));

        cli.post("/", req.body(), req.body_size());

        addResultHeader(res, cli);
    }

    void httpServerConf::onDelImg(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kImageSrc)).empty()) {
            addFailedHeader(res, "no imagesrc option");

            return;
        }

        http::Client cli(userSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kImageSrc, req.header(httpHeaderConf::kImageSrc));

        cli.post("/", "");

        addResultHeader(res, cli);
    }

    void httpServerConf::onGetImg(http::Req const & req, http::Res & res) {
        http::Client cli(userImgServerUrl);

        cli.get(req.url().c_str());

        res.set_status(cli.status());

        // * add the following header for http client testing.
        res.add_header("content-type", "image/png");

        res.set_body(cli.body());
    }

    void httpServerConf::onInsertLog(http::Req const & req, http::Res & res) {
        http::Client cli(logSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));

        cli.post("/", req.body(), req.body_size());

        addResultHeader(res, cli);
    }

    void httpServerConf::onGetLogByName(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kName)).empty()) {
            addFailedHeader(res, "no name option");

            return;
        }

        http::Client cli(logSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kName, req.header(httpHeaderConf::kName));

        cli.post("/", "");

        addResultHeader(res, cli);

        res.set_body(cli.body());
    }

    void httpServerConf::onGetLogBySite(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kSite)).empty()) {
            addFailedHeader(res, "no site option");

            return;
        }

        http::Client cli(logSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kSite, req.header(httpHeaderConf::kSite));

        cli.post("/", "");

        addResultHeader(res, cli);

        res.set_body(cli.body());
    }

    void httpServerConf::onGetLogByTime(http::Req const & req, http::Res & res) {
        if (std::string_view(req.header(httpHeaderConf::kTime)).empty()) {
            addFailedHeader(res, "no time option");

            return;
        }

        http::Client cli(logSqlServerUrl);

        cli.add_header(httpHeaderConf::kOperation, req.header(httpHeaderConf::kOperation));
        cli.add_header(httpHeaderConf::kTime, req.header(httpHeaderConf::kTime));

        cli.post("/", "");

        addResultHeader(res, cli);

        res.set_body(cli.body());
    }

    void httpServerConf::addSuccessHeader(http::Res & res) {
        res.add_header(
            httpHeaderConf::kResult,
            httpHeaderConf::kSuccess
        );

        res.add_header("content-type", "application/json");

        res.add_header(
            "Access-Control-Allow-Origin",
            "*"
        );

        res.add_header(
            "Access-Control-Allow-Headers",
            "*"
        );
        res.add_header(
            "Access-Control-Expose-Headers",
            "*"
        );
    }

    void httpServerConf::addFailedHeader(http::Res & res, char const * reason) {
        res.add_header(
            httpHeaderConf::kResult,
            httpHeaderConf::kFailed
        );

        res.add_header(
            httpHeaderConf::kReason,
            reason
        );

        res.add_header(
            "Access-Control-Allow-Origin",
            "*"
        );

        res.add_header(
            "Access-Control-Allow-Headers",
            "*"
        );

        res.add_header(
            "Access-Control-Expose-Headers",
            "*"
        );
    }

    void httpServerConf::addResultHeader(http::Res & res, http::Client & cli) {
        res.add_header(httpHeaderConf::kResult, cli.header(httpHeaderConf::kResult));

        if (std::string_view(cli.header(httpHeaderConf::kResult)) == httpHeaderConf::kFailed) {
            res.add_header(httpHeaderConf::kReason, cli.header(httpHeaderConf::kReason));
        }

        res.add_header(
            "Access-Control-Allow-Origin",
            "*"
        );

        res.add_header(
            "Access-Control-Allow-Headers",
            "*"
        );

        res.add_header(
            "Access-Control-Expose-Headers",
            "*"
        );
    }
}