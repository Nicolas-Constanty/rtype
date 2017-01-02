# R-Type

Clone of the original R-Type game.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

#### Linux

```
sudo apt-get install libboost-dev
```

### Building

#### Linux

```
git clone https://github.com/Nicolas-Constanty/rtype.git
cd rtype && mkdir build && cd build && cmake .. && make && cd ..
```

#### Windows

```
git clone https://github.com/Nicolas-Constanty/rtype.git
cd rtype
```

End with an example of getting some data out of the system or using it for a little demo

## Deployment

### First go to the rtype folder. You need minimum 3 terminals (one for each executable)

ex :
```
cd $HOME/rtype/
```

* Start a RoomServer
* Start a RoomGameDispatcher
* Start [1-4] GameClient

### Exemple for 2 players:

ex Term1 :
```
./RoomServer
```

ex Term2 :
```
./RoomGameDispatcher
```

ex Term3 :
```
./GameClient
```

ex Term4 :
```
./GameClient
```

## Built With

* [SFML](http://www.sfml-dev.org/download-fr.php) - The graphic lib used
* [Boost/Variant](http://www.boost.org/doc/libs/1_60_0/doc/html/variant.html) - Boost variant is used for the pseudo Json parser

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Victor Gouet** - *Project Manager* - [Github](https://github.com/Gouet)
* **Quentin Gasparotto** - *Programmer server* - [Github](https://github.com/GasparQ)
* **Adrien Wery** - *Programmer server* - [Github](https://github.com/Adpa18)
* **Fernand Veyrier** - *Programmer client* - [Github](https://github.com/FernandVEYRIER)
* **Nicolas Constanty** - *Programmer GameEngine/GraphicUserInterface client* - [Github](https://github.com/Nicolas-Constanty)

See also the list of [contributors](https://github.com/Nicolas-Constanty/rtype/graphs/contributors) who participated in this project.

## Acknowledgments

* [SFML](http://www.sfml-dev.org/download-fr.php)
* [Boost/Variant](http://www.boost.org/doc/libs/1_60_0/doc/html/variant.html)
* [Coroutine](https://github.com/tonbit/coroutine)
* [GetOpt Windows](https://github.com/skandhurkat/Getopt-for-Visual-Studio/blob/master/getopt.h)
* [CMAKE Visual Studio RC 2017](https://blogs.msdn.microsoft.com/vcblog/2016/10/05/cmake-support-in-visual-studio/)
