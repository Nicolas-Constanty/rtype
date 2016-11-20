## Object

Base of all GameObject and Component

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
| uid GetInstanceID() const | Get the instance uid of this object. |
| const std::string &GetName() const | Ge the name of this object. |

###### }
