#pragma once

#include <stl/string>

#define stl std::__ndk1
namespace Core {
    class Random {
        public:
        char filler[52];
        public:

        int nextInt();
        int nextInt(int);
        int nextInt(int,int);
        int nextIntInclusive(int,int);
        bool nextBoolean();
        float nextFloat();
        float nextFloat(float,float);
        void _setSeed(unsigned int);
        Random();
    };
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

