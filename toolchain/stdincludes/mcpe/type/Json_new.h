#pragma once
#include <stl/string>
#define stl std::__ndk1

namespace Json {
    class Reader;
    class Value;
    class StaticString {
        public:
        explicit StaticString(const char *czstring) : c_str_(czstring) {}
        operator const char *() const { return c_str_; }
        const char *c_str() const { return c_str_; }

        private:
        const char *c_str_;
    };

    class Reader {
        public:

        char filler[256];
        Reader();
        bool parse(stl::string const&,Value&,bool);
        ~Reader();
    };

    class Value{        
        public:
        char filler[256];
        Value(int);
        Value(StaticString const&);
        Value(){};
        Value(stl::string const& text){
            Reader reader;
            reader.parse(text,*this,true);
        };

        void clear();
        stl::string toStyledString() const;
    };


};
