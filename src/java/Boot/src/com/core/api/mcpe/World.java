package com.core.api.mcpe;

import com.core.api.mcpe.level.LevelData;

public class World {
    native public static void setFlatGenerator(String json);
    native public static void addWorldToCache(String world_path);
    native public static void updateWorlds();

  
    native public static int getWorldsCount();
    native private static long _getLevelData(String maybe_uid);

    native public static void createLevel(String uid,String path);
    public static LevelData getLevelData(String uid){
        return new LevelData(_getLevelData(uid));
    }
}
