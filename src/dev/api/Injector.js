let InjectorJava = WRAP_JAVA("com.core.api.Injector");

function Injector(ptr){
    let injector = new InjectorJava(ptr);
    this.call = function(symbol, args){
        injector.call(symbol, args);
        return this;
    }
    this.setArgsType = function(types){
        injector.setArgsType(types);
        return this;
    }
    this.getInjector = function(){
        return injector;
    }
    this.getIntResult = function(symbol, args){
        return Number(injector.getIntResult(symbol, args));
    }
    this.getFloatResult = function(symbol, args){
        return Number(injector.getFloatResult(symbol, args));
    }
    this.getBoolResult = function(symbol, args){
        return injector.getBoolResult(symbol, args);
    }
    this.getStringResult = function(symbol, args){
        return String(injector.getStringResult(symbol, args));
    }
    this.getPointerResult = function(symbol, args){
        return injector.getPointerResult(symbol, args);
    }
    this.replace = function(table,symbol,replace){
        return injector.replace(table,symbol,replace);
    }
    this.free = function(){
        return injector.free();
    }

}

test = function(a){
    return InjectorJava.test(a);
}