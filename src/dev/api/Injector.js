let InjectorJava = WRAP_JAVA("com.core.api.Injector");

function Injector(ptr){
    let injector = new InjectorJava(ptr);
    this.call = function(symbol){
        injector.call(symbol);
    }
    this.getInjector = function(){
        return injector;
    }
    this.getIntResult = function(symbol){
        return Number(injector.getIntResult(symbol));
    }
    this.getFloatResult = function(symbol){
        return Number(injector.getFloatResult(symbol));
    }
    this.getBoolResult = function(symbol){
        return injector.getIntResult(symbol) == 1;
    }
    this.getStringResult = function(symbol){
        return String(injector.getFloatResult(symbol));
    }
    this.getPointerResult = function(symbol){
        return injector.getPointerResult(symbol);
    }
    this.free = function(){
        return injector.free();
    }
}