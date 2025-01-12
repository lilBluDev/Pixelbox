#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <optional>
#include <unordered_map>

class FileSystem {
public:
    FileSystem() = default;
    ~FileSystem() = default;

    bool fileExists(const std::string& path) const;
    bool directoryExists(const std::string& path) const;
    bool createDirectory(const std::string& path) const;
    bool deleteFile(const std::string& path) const;
    std::vector<std::string> listFiles(const std::string& directory) const;
    std::string readFile(const std::string& path) const;
    bool writeFile(const std::string& path, const std::string& content) const;
    void addPrefix(const std::string& prefix, const std::string& path);
    std::string resolvePath(const std::string& pathWithPrefix) const;

private:
    std::unordered_map<std::string, std::string> prefixMappings;
    std::optional<std::string> resolvePrefix(const std::string& pathWithPrefix) const;
};
