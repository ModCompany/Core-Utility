#pragma once

#include <string>

#define stl std
namespace Core {
    struct Path {
        stl::string path;
        Path(stl::string path) : path(path){}
    };

    class FilePathManager {
        public:

    };

    class FileSystem {
        public:
        void deleteDirectoryAndContentsRecursively(Path const&);
        void deleteDirectoryContentsRecursively(Path const&);
        void deleteEmptyDirectory(Path const&);
        void deleteFile(Path const&);
        bool fileExists(Path const&);
        bool isValidPath(Path const&);
        bool isRelativePath(Path const&);
        bool directoryExists(Path const&);
        bool fileOrDirectoryExists(Path const&);

        void renameDirectory(Path const&,Path const&);
        void renameFile(Path const&,Path const&);
        void copyDirectoryAndContentsRecursivelyWithLimit(Path const&,Path const&);
        void createDirectoryRecursively(Path const&);
        void createDirectoryForFile(Path const&);

    };

    class FileSystemImpl : public FileSystem {
        public:
    };
}

