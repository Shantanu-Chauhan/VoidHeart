#pragma once

//#include "Hollow/Common.h"
#include "DungeonFloor.h"
#include "Hollow/Utils/Singleton.h"

namespace BulletHell
{
    class DungeonManager
    {
    private: 
        DungeonManager();
    public: 
        DungeonManager(const DungeonManager&) = delete;
        DungeonManager& operator= (const DungeonManager&) = delete;
        DungeonManager(DungeonManager&&) = delete;
        DungeonManager& operator=(DungeonManager&&) = delete;
        static DungeonManager& Instance();
    public:
        void Init();
        void Generate();
        void Regenerate();
        void Construct();
    	
        void SetSeed(unsigned seed);
        unsigned GetSeed();

        std::vector<DungeonFloor> GetFloors() const;
        DungeonFloor GetFloor(int index);
        void Print() const;
    private:

    public:

    private:
        std::vector<DungeonFloor> mFloors;
        unsigned mSeed;
    };
}
