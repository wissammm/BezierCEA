@call conan install %~dp0 --build=missing -s build_type=Debug -if %~dp0build
@call conan install %~dp0 --build=missing -s build_type=Release -if %~dp0build