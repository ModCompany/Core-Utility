let TickingAreasManagerJava = WRAP_JAVA("com.core.api.level.area.TickingAreasManager");
var TickingAreasManager = {
    hasActiveAreas(){
        return TickingAreasManagerJava.hasActiveAreas() == 1;
    },
    addArea(dimension, name, x,y,z,range){
        TickingAreasManagerJava.addArea(dimension,name,x,y,z,range)
    },
    addAreaPostions(dimension, name, x, y, z, xx, yy, zz){
        TickingAreasManagerJava.addAreaPostions(dimension, name, x, y, z, xx, yy, zz);
    },
    addEntityArea(dimension, ent){
        TickingAreasManagerJava.addEntityArea(dimension, ent);
    },
    countStandaloneTickingAreas(){
        return Number(TickingAreasManagerJava.countStandaloneTickingAreas());
    },
    countPendingAreas(dimension){
        return Number(TickingAreasManagerJava.countPendingAreas(dimension));
    }
};