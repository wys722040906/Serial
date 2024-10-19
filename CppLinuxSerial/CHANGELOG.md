# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased

## [2.8.2] - 2024-06-02

- Fix bug where this project could not be added into another CMake file with `add_subdirectory()` correctly (thanks [alexg-k](https://github.com/alexg-k)).

## [v2.8.1] - 2023-12-16

- Added missing header include (thanks [Uglješa Lukešević](https://github.com/ukicomputers)).
- Added missing compare links to the CHANGELOG.

## [v2.8.0] - 2023-07-22

- Improved error checking in read/write commands. (thanks @meetgandhi-eic).

## [v2.7.2] - 2023-07-16

- Changed CICD runner from TravisCI to GitHub Actions.
- Fixed some spelling errors in the README (thanks @JensvanEsch).

## [v2.7.1] - 2023-03-16

- CMake config updated with exporting and generation of a CMake config file so that end users can simply do (thanks to https://github.com/borgmanJeremy for this contribution):

    ```cmake
    find_package(CppLinuxSerial REQUIRED)
    ...
    ...
    target_link_libraries(target CppLinuxSerial::CppLinuxSerial)
    ```

## [v2.7.0] - 2023-02-13

- `Read()` and `ReadBinary()` now append to the provided data containers (string or vector) rather than erase and write.
- Added `run.sh` bash script for running local serial port tests with connected Arduino Uno (see README). Updated local tests to write and read back data in both string and binary forms.

## [v2.6.0] - 2023-02-02

- `Read()` and `ReadBinary()` now throw exceptions if they detect that the serial device has been disconnected (thanks to [aldoshkind](https://github.com/aldoshkind) for helping with this one).
- Added Arduino testing instructions to the README.

## [v2.5.0] - 2022-11-12

- Replaced all tabs in code with spaces, which should fix the ugly code rendering in GitHub.
- Added ability to set/change both hardware and software flow control (thanks to [Vittorio Francescon](https://github.com/VFrancescon/) for helping with this one).
- Added some ready-to-run examples in the new `example/` directory.
- Added a section in the README on WSL (Windows Subsystem for Linux) usage.

## [v2.4.0] - 2022-02-12

- Added `Available()` method to return number of bytes ready to be read from the receive buffer (thanks lotricekCZ).
- Added CMake option for shared library (thanks lotricekCZ).

## [v2.3.0] - 2021-12-23

- Added support for setting the num. data bits.
- Added support for setting the parity.
- Added support for setting the num. stop bits.

## [v2.2.1] - 2021-12-06

- Fixed a build error by changing the branch cmake downloads googletest from master to main.

## [v2.2.0] - 2021-12-03

- ReadBinary() and WriteBinary() added to read/write raw data, instead of having to use strings (thanks to @RolandHughes for adding this).

## [v2.1.2] - 2021-07-01

- Removed download of gtest if tests are not built.
- Install headers correctly when used as a cmake submodule (FetchContent).

Big thanks to https://github.com/MadsAndreasen-Zoetis for these improvements.

## [v2.1.1] - 2021-04-05

- Fixed bug where `echo` was not being set correctly.

## [v2.1.0] - 2020-11-08

### Added
- Support for custom baud rates.
- Support for all standard UNIX baud rates.
- Improved Doxygen documentation.
- Improved README.md documentation.

### Removed
- Dependencies from the README, they weren't that useful and were not accurate anyway.

## [v2.0.3] - 2020-10-13

### Added
- Added example of how to use the library to the README.

### Fixed
- Fixed CMake not using C++14 by specifying `set(CMAKE_CXX_STANDARD 14)` rather than just `add_definitions(-std=c++14)`.

### Removed
- Removed all unit tests that were using virtual serial ports for testing, as these are broken due to a changing TravisCI OS environment. This needs fixing at a later date.

## [v2.0.2] - 2020-07-07

### Added
- Sphinx documentation.
- Unit tests for testing `SetTimeout()`.

### Fixed
- Serial port state is set to `CLOSED` on initialization.
- Fixed build commands in README.

## [v2.0.1] - 2017-11-27

### Fixed
- Fixed link to TravisCI image in README.

## [v2.0.0] - 2017-11-27

### Added
- Added CMake build support.
- Added basic, config and read/write unit tests using gtest.
- Improved read() performance due to removal of buffer creation on every call.
- TravisCI configuration file.
- Build script under `tools/`.

### Changed
- Updated serial port to use C++14.
- Changed library name from serial-port to CppLinuxSerial.
- Updated Doxygen comments.

## [v1.0.1] - 2014-05-21
 
### Changed
- Added ability to enable/disable echo with 'SerialPort::EnableEcho()'.

## [v1.0.0] - 2014-05-15

### Added
- Initial commit. serial-port-cpp library has basic functions up and running.

[Unreleased]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.8.2...HEAD
[v2.8.2]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.8.1...v2.8.2
[v2.8.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.8.0...v2.8.1
[v2.8.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.7.2...v2.8.0
[v2.7.2]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.7.1...v2.7.2
[v2.7.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.7.0...v2.7.1
[v2.7.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.6.0...v2.7.0
[v2.6.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.5.0...v2.6.0
[v2.5.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.4.0...v2.5.0
[v2.4.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.3.0...v2.4.0
[v2.3.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.2.1...v2.3.0
[v2.2.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.2.0...v2.2.1
[v2.2.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.1.2...v2.2.0
[v2.1.2]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.1.1...v2.1.2
[v2.1.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.1.0...v2.1.1
[v2.1.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.0.3...v2.1.0
[v2.0.3]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.0.2...v2.0.3
[v2.0.2]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.0.1...v2.0.2
[v2.0.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v2.0.0...v2.0.1
[v2.0.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v1.0.1...v2.0.0
[v1.0.1]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/v1.0.0...v1.0.1
[v1.0.0]: https://github.com/mbedded-ninja/CppLinuxSerial/compare/...v1.0.0
