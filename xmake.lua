add_requires("libsdl")
add_rules("mode.debug", "mode.release")

set_languages("c++17")
add_includedirs("src")

target("ChessGame")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")
    add_packages("libsdl")
