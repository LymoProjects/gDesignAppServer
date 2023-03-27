add_rules("mode.debug", "mode.release")

set_languages("c++latest")
 
target("gdAppServer")
    set_kind("binary")
    add_files(
        "./*.cxx",
        "src/*.cxx"
    )
 
    add_syslinks(
        "Advapi32",
        "Crypt32",
        "Wldap32",
        "User32"
    )

    add_links(
        "co",
        "libcurl",
        "libssl",
        "libcrypto"
    )

    add_includedirs(
        "include",
        "D:/Cds/Libs/coost/include" -- to include coost headers.,
    )

    add_linkdirs(
        "D:/Cds/Libs/coost/build/windows/x64/release", -- to find co.lib from coost.
        "D:/Cds/Libs/curl-7.88.1/build/artifacts/l/libcurl/7.87.0/a2ac3a70b1e948b1843919b4cbb41b7f/lib",
        "D:/Cds/Libs/openssl-3.0.8/build/artifacts/o/openssl/1.1.1-t/9458079689e342b58f2f2e8d4b2fb860/lib"
    )
target_end()

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

