# File Manager (C++)

A small command-line file management utility written in C++ using the standard library, including `std::filesystem`.

## Features

- **Create** a new empty file.
- **Rename** an existing file or directory.
- **Delete** an existing regular file.
- Basic argument validation and readable error messages.
- Refuses to overwrite an existing destination when creating or renaming.

> Scope: this is a learning project and a lightweight CLI utility. It is not a full file manager. The delete command currently handles regular files only; it does not recursively delete directories.

## Requirements

- A C++17-compatible compiler (for example, GCC 8+).
- Linux, macOS, or another platform with C++17 filesystem support.

## Build

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic filemgr.cc -o filemgr
```

## Usage

```bash
./filemgr <command> [arguments]
```

### Create a file

```bash
./filemgr create notes.txt
```

### Rename a file or directory

```bash
./filemgr rename notes.txt project-notes.txt
```

### Delete a regular file

```bash
./filemgr delete project-notes.txt
```

### Show help

Run without arguments or with an invalid command:

```bash
./filemgr
```

## Safety notes

- `create` refuses to open an existing path, helping prevent accidental truncation.
- `rename` refuses when the destination path already exists.
- `delete` is limited to regular files and does not recursively remove directories.
- Use care with paths: commands act relative to the terminal's current working directory unless an absolute path is supplied.

## Project structure

```text
mytool/
├── filemgr.cc
├── README.md
└── .gitignore
```

## What I learned

This project is a practical exercise in:

- C++ command-line arguments (`argc` and `argv`)
- Functions and separation of responsibilities
- File streams (`std::ofstream`)
- Filesystem paths and operations (`std::filesystem`)
- Input validation and error handling

## Current limitations / possible future work

- Add a `list` command.
- Add file information such as size and last-modified time.
- Add directory creation and safer, explicitly confirmed directory removal.
- Add automated tests.

These are potential extensions, not features currently included.
