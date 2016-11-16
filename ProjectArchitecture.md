# Project Architecture

```
├── rtype/
│   ├── Assets
│   │   ├── Fonts
│   │   ├── IA
│   │   ├── Monsters
│   │   ├── Sounds
│   │   ├── Textures
│   │   ├── ...
│   ├── Dependencies
|   |   ├── SFML
|   |   |   ├── include
|   |   |   ├── x86
|   |   |   |   ├── Debug
|   |   |   |   ├── Release
|   |   |   ├── x64
|   |   |   |   ├── Debug
|   |   |   |   ├── Release
|   |   ├── ...
│   ├── include
│   │   ├── Client
|   |   ├── Server
|   |   ├── ...
│   ├── src
│   │   ├── Client
|   |   ├── Server
|   |   ├── ...
│   ├── R-Type
│   │   ├── Client
|   |   ├── Server
│   │   ├── ...
│   ├── Tests
│   │   ├── Client
|   |   ├── Server
|   |   ├── ...
│   ├── README.md
```
### Ce qui fait un total de 6 dossiers à la racine:
* Assets
* Dependencies
* include
* src
* R-Type
* Tests

# Dependencies
## :warning: Toutes les dépendances sont compréssées (zip, tar)
* {{Dependence}}
  * include
  * x86
    * Debug
    * Release
  * x64
    * Debug
    * Release