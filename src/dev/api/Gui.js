var Gui = {
    animationDestroy(x, y, z, speed){
        GlobalContext.getClientInstance().renderDestroyBlock(x, y, z, speed || 1);
    }
};