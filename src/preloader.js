Callback.addCallback("CoreUtilityBoot", function(){
    let Boot = com.core.api.Boot;
    Boot.dir = __dir__;
    let value = __config__.get("cache_module");
    Boot.cache_module = value == null ? true : value;
});