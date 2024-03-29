#pragma once

namespace gd__ {
    struct httpHeaderConf {
        static constexpr char const * kOperation {"operation"};
        static constexpr char const * kResult {"result"};
        static constexpr char const * kReason {"reason"};

        static constexpr char const * kInsert {"insert"};
        static constexpr char const * kDelete {"delete"};
        static constexpr char const * kSelect {"select"};
        static constexpr char const * kGetImg {"getimg"};
        static constexpr char const * kAddImg {"addimg"};
        static constexpr char const * kDelImg {"delimg"};

        static constexpr char const * kInsertLog {"insertlog"};
        static constexpr char const * kGetLogByName {"getlogbyname"};
        static constexpr char const * kGetLogBySite {"getlogbysite"};
        static constexpr char const * kGetLogByTime {"getlogbytime"};

        static constexpr char const * kIdentify {"identify"};

        static constexpr char const * kSuccess {"success"};
        static constexpr char const * kFailed {"failed"};

        static constexpr char const * kName {"name"};
        static constexpr char const * kPhone {"phone"};
        static constexpr char const * kId {"id"};
        static constexpr char const * kImageSrc {"imagesrc"};
        static constexpr char const * kImg {"img"};
        static constexpr char const * kSite {"site"};
        static constexpr char const * kTime {"time"};

    };
}