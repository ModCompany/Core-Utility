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
        return injector.getBoolResult(symbol);
    }
    this.getStringResult = function(symbol){
        return String(injector.getStringResult(symbol));
    }
    this.getPointerResult = function(symbol){
        return injector.getPointerResult(symbol);
    }
    this.replace = function(table,symbol,replace){
        return injector.replace(table,symbol,replace);
    }
    this.free = function(){
        return injector.free();
    }
}