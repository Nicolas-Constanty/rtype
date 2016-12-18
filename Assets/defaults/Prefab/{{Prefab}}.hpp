#ifdef _WIN32
#ifdef {{PREFAB}}_EXPORTS
    #define {{PREFAB}}_API __declspec(dllexport)
    #else
        #define {{PREFAB}}_API __declspec(dllimport)
    #endif
#else
#define {{PREFAB}}_API
#endif

#ifndef {{PREFAB}}_HPP_
#define {{PREFAB}}_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class {{Prefab}} : public SaltyEngine::GameObject
{
public:
{{Prefab}}();
virtual ~{{Prefab}}();
};

SaltyEngine::Object const *GetObjectPrefab();
}

#endif