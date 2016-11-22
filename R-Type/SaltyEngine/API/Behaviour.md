## Behaviour

Behaviours are Components that can be enabled or disabled.

## Inheritence
Class in [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) / inherits from :
[Component](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/R-Type/SaltyEngine/API/Component.md)
```
        Object  
          |
          v
      Component
          |
          v
      Behaviour
```

###### Namespace [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) {

| Constructor / Destructor |
|------------------|
| `Behaviour()` |
| `Behaviour(const std::string &name)` |
| `virtual ~Behaviour()` |

| Public attributs |
|------------------|
| ``bool enabled``	| Enabled Behaviours are Updated, disabled Behaviours are not. |

###### }
