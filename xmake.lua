set_languages("clatest", "cxxlatest")
add_rules("mode.debug", "mode.release")

if is_plat("linux") then
    add_syslinks("assimp", "stdc++fs", "pthread", "dl")
    on_config(function (target)
        local cxxflags = os.iorun("wx-config --cxxflags"):trim()
        target:add("cxxflags", table.unpack(string.split(cxxflags, " ")))
        
        local ldflags = os.iorun("wx-config --libs std,aui"):trim()
        target:add("ldflags", table.unpack(string.split(ldflags, " ")))
    end)

    add_defines("__WXGTK__")
else
    add_requires("nlohmann_json", "assimp")
end

target("SPETS")
    set_kind("binary")
    add_packages("nlohmann_json", "assimp")

    set_targetdir("bin")
    set_objectdir("build/obj")
    
    add_includedirs("src/")
    add_files( "src/**.cpp")

    if is_plat("windows") then
        add_headerfiles{ "src/**.h", "src/**.hpp" }
        local WX_ROOT = "D:/SDK/wx/3.3.1/"
        add_defines("__WXMSW__", "WXUSINGDLL", "_UNICODE", "wxMSVC_VERSION_AUTO", "wxMSVC_VERSION_ABI_COMPAT", "NDEBUG")
        add_includedirs(WX_ROOT .. "include/", WX_ROOT .. "lib/vc14x_x64_dll/mswu/")
        add_linkdirs(WX_ROOT .. "lib/vc14x_x64_dll/")
        add_files(WX_ROOT .. "include/wx/msw/wx.rc")
    end

    if is_plat("linux") then
        add_packages("wxwidgets")
        add_defines("__WXGTK__")
    end

