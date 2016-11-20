## GameObject

Base of all GameObject

## Inheritence

```
        Object  
          |
          v
      GameObject
```
###### Namespace SaltyEngine {

| Constructor / Destructor |
|------------------|
| Object()         |
| Object(const std::string &name)  |
| virtual ~Object()  |

| Private attributs |
|------------------|
| uid m_uid |
| const std::string &m_name |

| Public Functions |   Information      |
|------------------|--------------------|
| `T AddComponent<T>`()	| Adds a component class named className to the game object. |
| `bool CompareTag(const std::string &tag)` |	Is this game object tagged with tag ? |
| `T GetComponent<T>`() |	Returns the component of Type type if the game object has one attached, null if it doesn't. |
| `T GetComponentInChildren<T>`() |	Returns the component of Type type in the GameObject or any of its children using depth first search.
| `T GetComponentInParent<T>()` | Returns the component of Type type in the GameObject or any of its parents. |
| `List<T> GetComponents<T>()`	| Returns all components of Type type in the GameObject.
| `List<T> GetComponentsInChildren<T>()`	| Returns all components of Type type in the GameObject or any of its children. |
| `List<T> GetComponentsInParent<T>()`	| Returns all components of Type type in the GameObject or any of its parents. |
| `SetActive(bool status)` | Activates/Deactivates the GameObject. |

###### }
