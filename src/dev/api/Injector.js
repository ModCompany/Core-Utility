let InjectorJava = WRAP_JAVA("com.core.api.Injector");

function Injector(ptr){
    let injector = new InjectorJava(ptr);
    this.call = function(symbol){
        injector.call(symbol);
    }
    this.getInjector = function(){
        return injector;
    }
}