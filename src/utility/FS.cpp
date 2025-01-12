#include "utility/FS.h"
#include <iostream>
#include <fstream>
#include <string>

bool FileSystem::fileExists(const std::string& path) const {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

bool FileSystem::directoryExists(const std::string& path) const {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool FileSystem::createDirectory(const std::string& path) const {
    try {
        if (!directoryExists(path)) {
            std::filesystem::create_directory(path);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
    return false;
}

bool FileSystem::deleteFile(const std::string& path) const {
    try {
        if (fileExists(path)) {
            std::filesystem::remove(path);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
    return false;
}

std::vector<std::string> FileSystem::listFiles(const std::string& directory) const {
    std::vector<std::string> fileList;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (std::filesystem::is_regular_file(entry)) {
                fileList.push_back(entry.path().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing files: " << e.what() << std::endl;
    }
    return fileList;
}

std::string FileSystem::readFile(const std::string& path) const {
    std::ifstream file(path);
    if (file.is_open()) {
        return std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    }
    std::cerr << "Error reading file: " << path << std::endl;
    return "";
}

bool FileSystem::writeFile(const std::string& path, const std::string& content) const {
    std::ofstream file(path);
    if (file.is_open()) {
        file << content;
        return true;
    }
    std::cerr << "Error writing to file: " << path << std::endl;
    return false;
}

void FileSystem::addPrefix(const std::string& prefix, const std::string& path) {
    prefixMappings[prefix] = path;
}

std::string FileSystem::resolvePath(const std::string& pathWithPrefix) const {
    auto resolvedPrefix = resolvePrefix(pathWithPrefix);
    if (resolvedPrefix.has_value()) {
        return resolvedPrefix.value() + pathWithPrefix.substr(pathWithPrefix.find("://") + 3);
    }
    return pathWithPrefix; 
}

std::optional<std::string> FileSystem::resolvePrefix(const std::string& pathWithPrefix) const {
    for (const auto& [prefix, directory] : prefixMappings) {
        if (pathWithPrefix.find(prefix) == 0) {
            return directory; 
        }
    }
    return std::nullopt; 
}
