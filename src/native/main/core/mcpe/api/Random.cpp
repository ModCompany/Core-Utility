#include <innercore_callbacks.h>
#include <java.h>
#include <Core.h>

export(jint,mcpe_api_Random_nextIntPointer,jlong pointer, jint max) {
        return (jint) ((Core::Random*) pointer)->nextInt(max);
}
