package com.core.api.level.area;

public class TickingAreasManager {

    public static native boolean hasActiveAreas();
    public static native void addArea(int dimension,String name,int x,int y,int z,int range);
    public static native void addAreaB(int dimension, String name, int x,int y,int z, int xx,int yy,int zz);
    public static native void addEntityArea(int dimension, long uid);
    public static native int countStandaloneTickingAreas();
    public static native int countPendingAreas(int dimension);



}