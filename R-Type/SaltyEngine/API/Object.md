## Object

Base of all GameObject and Component  

Class in [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md)
###### Namespace [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) {

| Constructor / Destructor |
|------------------|
| `Object()` |
| `Object(const std::string &name)` |
| `virtual ~Object()` |

| Private attributs |
|------------------|
| `uid m_uid` |
| `const std::string &m_name` |

| Public Functions |   Information      |
|------------------|--------------------|
| `uid GetInstanceID() const` | Get the instance uid of this object. |
| `const std::string &GetName() const` | Ge the name of this object. |

###### }
