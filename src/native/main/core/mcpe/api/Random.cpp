#include <innercore_callbacks.h>
#include <java.h>
#include <level/api/Random.h>

export(jint,mcpe_api_Random_nextIntPointer,jlong pointer, jint max) {
        return (jint) ((Random*) pointer)->nextInt(max);
}
