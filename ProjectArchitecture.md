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
│   ├── Conception
│   │   ├── ...
│   ├── Dependencies
|   |   ├── SFML
|   |   |   ├── Win
|   |   |   |   ├── include
|   |   |   |   ├── x86
|   |   |   |   |   ├── Debug
|   |   |   |   |   ├── Release
|   |   |   |   ├── x64
|   |   |   |   |   ├── Debug
|   |   |   |   |   ├── Release
|   |   |   ├── Linux
|   |   |   |   ├── include
|   |   |   |   ├── lib
|   |   ├── ...
│   ├── include
│   │   ├── ClientGame
│   │   ├── ClientRoom
|   |   ├── ServerGame
|   |   ├── ServerRoom
|   |   ├── ...
│   ├── R-Type
│   │   ├── ClientGame
│   │   ├── ClientRoom
|   |   ├── ServerGame
|   |   ├── ServerRoom
│   │   ├── ...
│   ├── src
│   │   ├── ClientGame
│   │   ├── ClientRoom
|   |   ├── Common
|   |   ├── ServerGame
|   |   ├── ServerRoom
|   |   ├── ...
│   ├── Tests
│   │   ├── Client
|   |   ├── Server
|   |   ├── ...
│   ├── README.md
```
### Ce qui fait un total de 7 dossiers à la racine:
* Assets
* Dependencies
* Conception
* include
* R-Type
* src
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
