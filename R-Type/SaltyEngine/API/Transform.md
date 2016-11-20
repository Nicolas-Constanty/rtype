## Transform

Position, rotation and scale of an object.
###### :warning: `Transform is a typedef for BaseTransform<Vector>`
`Vector` is a typedef of `Vector3` by default, define `GAME2D` and `Vector` become a typedef of `Vector2`.

## Inheritence
Class in [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) / inherits from : [Component](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/R-Type/SaltyEngine/API/Component.md)
```
        Object  
          |
          v
      Component
          |
          v
      Transform
```

###### Namespace [SaltyEngine](https://github.com/Nicolas-Constanty/rtype/blob/feature/SaltyEngine/SaltyEnfineFeatures.md) {

| Public attributs |
|------------------|
| `T rotation` |
| ``T localRotation`` |
| ``T position`` |
| ``T localPosition`` |
| ``BaseTransform<T> *m_parent`` |
| ``std::vector<BaseTransform<T> *>	m_children`` |
| ``SaltyBehavior				*m_attach`` |

| Constructor / Destructor                                    |
|-------------------------------------------------------------|
| `BaseTransform()`                                               |
| `BaseTransform(const std::string &name)`                        |
| `BaseTransform(SaltyBehavior *sb)`                          |
| `BaseTransform(SaltyBehavior *sb, const std::string &name)` |
| `virtual ~BaseTransform()`                                  |

| Public Functions |   Information                                            |
|------------------|----------------------------------------------------------|
| `uid GetInstanceID() const` | Get the instance uid of this object.          |
| `const std::string &GetName() const` | Ge the name of this object.          |
| `void DetachChildren()` | Unparents all children.                           |
| `BaseTransform<T> *Find(const std::string &name) const` | Finds a child by name and returns it. |
| `BaseTransform<T> * GetChild(size_t index) const` | Returns a transform child by index.         |
| `bool IsChildOf(BaseTransform<T> *parent) const` | Is this transform a child of parent?         |
| `void Rotate(const T & eulerAngles)` | Applies a rotation of eulerAngles.z degrees around the z axis, eulerAngles.x degrees around the x axis, and eulerAngles.y degrees around the y axis (in that order). |
| `void RotateAround(const T & point, const T & axis, float angle)` | Rotates the transform about axis passing through point in world coordinates by angle degrees. |
| `void SetParent(BaseTransform<T> * parent)`| Set the parent of the transform. |
| `void Translate(const T & translation)` | Moves the transform in the direction and distance of translation. |

###### }
