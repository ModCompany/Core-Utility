var CustomEntityJava = WRAP_JAVA("com.core.api.entity.CustomEntity");

var CustomEntity = {
    setHandlerTick(name, func){
        CustomEntityJava.setHandlerTick(name, func);
    }
};