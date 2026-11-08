#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void printUsage(const char* programName) {
    std::cout
        << "Usage: " << programName << " <command> [arguments]\n\n"
        << "Commands:\n"
        << "  create <filename>              Create a new empty file\n"
        << "  rename <old_name> <new_name>   Rename a file or directory\n"
        << "  delete <filename>              Delete a file\n";
}

int createFile(const fs::path& path) {
    std::error_code ec;

    if (fs::exists(path, ec)) {
        std::cerr << "Error: '" << path.string() << "' already exists; refusing to overwrite it.\n";
        return 1;
    }
    if (ec) {
        std::cerr << "Error checking path: " << ec.message() << '\n';
        return 1;
    }

    std::ofstream file(path);
    if (!file) {
        std::cerr << "Error: could not create '" << path.string()
                  << "'. Check the path and permissions.\n";
        return 1;
    }

    std::cout << "Created: " << path.string() << '\n';
    return 0;
}

int deleteFile(const fs::path& path) {
    std::error_code ec;

    if (!fs::exists(path, ec)) {
        std::cerr << "Error: '" << path.string() << "' does not exist.\n";
        return 1;
    }
    if (ec) {
        std::cerr << "Error checking path: " << ec.message() << '\n';
        return 1;
    }

    if (!fs::is_regular_file(path, ec)) {
        std::cerr << "Error: delete currently supports regular files only.\n";
        return 1;
    }
    if (ec) {
        std::cerr << "Error checking file type: " << ec.message() << '\n';
        return 1;
    }

    if (!fs::remove(path, ec)) {
        std::cerr << "Error: could not delete '" << path.string() << "'.\n";
        if (ec) std::cerr << ec.message() << '\n';
        return 1;
    }

    std::cout << "Deleted: " << path.string() << '\n';
    return 0;
}

int renamePath(const fs::path& oldPath, const fs::path& newPath) {
    std::error_code ec;

    if (!fs::exists(oldPath, ec)) {
        std::cerr << "Error: source '" << oldPath.string() << "' does not exist.\n";
        return 1;
    }
    if (ec) {
        std::cerr << "Error checking source: " << ec.message() << '\n';
        return 1;
    }

    if (fs::exists(newPath, ec)) {
        std::cerr << "Error: destination '" << newPath.string() << "' already exists.\n";
        return 1;
    }
    if (ec) {
        std::cerr << "Error checking destination: " << ec.message() << '\n';
        return 1;
    }

    fs::rename(oldPath, newPath, ec);
    if (ec) {
        std::cerr << "Rename failed: " << ec.message() << '\n';
        return 1;
    }

    std::cout << "Renamed '" << oldPath.string()
              << "' to '" << newPath.string() << "'.\n";
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    const std::string command = argv[1];

    if (command == "create") {
        if (argc != 3) {
            std::cerr << "Error: create requires one filename.\n";
            printUsage(argv[0]);
            return 1;
        }
        return createFile(argv[2]);
    }

    if (command == "delete") {
        if (argc != 3) {
            std::cerr << "Error: delete requires one filename.\n";
            printUsage(argv[0]);
            return 1;
        }
        return deleteFile(argv[2]);
    }

    if (command == "rename") {
        if (argc != 4) {
            std::cerr << "Error: rename requires an old name and a new name.\n";
            printUsage(argv[0]);
            return 1;
        }
        return renamePath(argv[2], argv[3]);
    }

    std::cerr << "Error: unknown command '" << command << "'.\n";
    printUsage(argv[0]);
    return 1;
}
