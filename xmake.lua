set_languages("clatest", "cxxlatest")

add_rules "mode.debug"
add_rules "mode.release"

add_requires("nlohmann_json", "assimp")

target "SPETS"
    set_kind "binary" 
    
    add_packages("nlohmann_json", "assimp")

    if is_mode("debug") then 
        set_basename "SPETS_debug_$(arch)"
    else
        set_basename "SPETS"
    end

    set_targetdir "bin"
    set_objectdir "build/obj"
    
    add_includedirs "src/"
    add_headerfiles{ "src/**.h", "src/**.hpp" }
    add_files{ "src/**.c", "src/**.cpp" }
target_end()
