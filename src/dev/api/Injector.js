let InjectorJava = WRAP_JAVA("com.core.api.Injector");

function Injector(ptr){
    let injector = new InjectorJava(ptr);
    this.call = function(symbol, args, table, virtual){
        injector.call(symbol, args||[], table||"", !!virtual);
        return this;
    }
    this.setArgsType = function(types){
        injector.setArgsType(types);
        return this;
    }
    this.getInjector = function(){
        return injector;
    }
    this.getIntResult = function(symbol, args, table, virtual){
        return Number(injector.getIntResult(symbol, args || [], table||"", !!virtual));
    }
    this.getFloatResult = function(symbol, args, table, virtual){
        return Number(injector.getFloatResult(symbol, args || [], table||"", !!virtual));
    }
    this.getBoolResult = function(symbol, args, table, virtual){
        return injector.getBoolResult(symbol, args || [], table||"", !!virtual);
    }
    this.getStringResult = function(symbol, args, table, virtual){
        return String(injector.getStringResult(symbol, args || [], table||"", !!virtual));
    }
    this.getPointerResult = function(symbol, args, table, virtual){
        return injector.getPointerResult(symbol, args || [], table||"", !!virtual);
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