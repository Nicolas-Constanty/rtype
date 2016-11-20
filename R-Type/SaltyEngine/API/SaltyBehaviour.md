## Behaviour

Behaviours are Components that can be enabled or disabled.

## Inheritence
Class in [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) / inherits from :
[Behaviour](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/R-Type/SaltyEngine/API/Behaviour.md)
```
        Object  
          |
          v
      Component
          |
          v
      Behaviour
          |
          v
    SaltyBehaviour
```

###### Namespace [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) {

| Constructor / Destructor |
|------------------|
| `Behaviour()` |
| `Behaviour(const std::string &name)` |
| `virtual ~Behaviour()` |

| Private attributs |
|------------------|
| `uid m_uid` |
| `const std::string &m_name` |

| Public Functions |   Information      |
|------------------|--------------------|
| `uid GetInstanceID() const` | Get the instance uid of this object. |
| `const std::string &GetName() const` | Ge the name of this object. |

###### }
