# Linux System And Netwrok Programming

![CI](https://github.com/tnsadithya/linux-sysnet-prog/actions/workflows/cmake-test.yml/badge.svg)
This is a structured C/C++ project scaffold to practice and test **Linux system programming** and **network programming** concepts using:

- ✅ CMake
- ✅ CppUTest for unit testing
- ✅ Pre-commit hooks for formatting (`clang-format`) and static analysis (`clang-tidy`)
- ✅ GitHub Actions for CI

## 🔧 Project Structure

├── include/ # Public headers
├── src/ # Implementation files
├── test/ # Unit tests (CppUTest)
├── build/ # CMake build directory
├── .clang-format
├── .clang-tidy
├── .pre-commit-config.yaml

## ✅ Build & Test

```bash
cmake -S . -B build
cmake --build build
cd build && ctest
```

## 🔁 Pre-commit Setup
```bash
pip install pre-commit
pre-commit install
pre-commit run --all-files
```
## 🚀 Features Implemented

- [x] Hostname retrieval (`get_hostname`)
- [ ] File I/O
- [ ] Process and Signals
- [ ] Socket Programming (TCP/UDP)
- [ ] Threads and Synchronization

---

## 📦 Continuous Integration

GitHub Actions is configured to:
- Install dependencies
- Build the project using CMake
- Run all unit tests on every push and pull request

CI config: `.github/workflows/cmake-test.yml`

---

## 📚 Reference Books

- *Hands-On System Programming with Linux* – Kaiwan Billimoria
- *The Linux Programming Interface* – Michael Kerrisk
- *Linux System Programming* – Robert Love
- *Unix Network Programming* – W. Richard Stevens
- *Hands-On Network Programming with C* – Lewis Van Winkle

