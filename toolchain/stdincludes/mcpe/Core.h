#pragma once


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
}