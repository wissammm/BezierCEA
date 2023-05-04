@if [%VIRTUAL_ENV%] == [] (
    python -m venv .venv
    .venv\Scripts\Activate.bat
    pip install conan~=1.0
    pip install cmake
)