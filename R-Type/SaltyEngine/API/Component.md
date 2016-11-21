## Component

Base class for everything attached to GameObjects.

## Inheritence
Class in [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) / inherits from :
[Object](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/R-Type/SaltyEngine/API/Object.md)
```
        Object  
          |
          v
      Component
```
###### Namespace SaltyEngine {

| Constructor / Destructor              |
|---------------------------------------|
| `Component()`                         |
| `Component(const std::string &name)`  |
| `virtual ~Component()`                |

| Public attributs         |
|--------------------------|
| `GameObject *gameObject` |
| `std::string &tag`       |
| `Transform *transform`   |


| Public Functions |   Information      |
|------------------|--------------------|
| `bool CompareTag(const std::string &tag)` |	Is this game object tagged with tag ? |
| `T GetComponent<T>()` |	Returns the component of Type type if the game object has one attached, null if it doesn't. |
| `T GetComponentInChildren<T>()` |	Returns the component of Type type in the GameObject or any of its children using depth first search.
| `T GetComponentInParent<T>()` | Returns the component of Type type in the GameObject or any of its parents. |
| `List<T> GetComponents<T>()`	| Returns all components of Type type in the GameObject.
| `List<T> GetComponentsInChildren<T>()`	| Returns all components of Type type in the GameObject or any of its children. |
| `List<T> GetComponentsInParent<T>()`	| Returns all components of Type type in the GameObject or any of its parents. |

###### }
