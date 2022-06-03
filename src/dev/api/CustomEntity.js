var CustomEntityJava = WRAP_JAVA("com.core.api.entity.CustomEntity");

var EntityRegister = {
    setHandlerTick(name, func){
        CustomEntityJava.setHandlerTick(name, func);
    }
};