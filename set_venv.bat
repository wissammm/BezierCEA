@if [%VIRTUAL_ENV%] == [] (
    python -m venv .venv
    pip install conan~=1.0
    pip install cmake
    .venv\Scripts\Activate.bat
)