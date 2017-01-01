mkdir build\Debug
mkdir Assets\Metas

set "cp=xcopy /d /y"

%cp% cmake-build-debug\R-Type\Common\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\GameClient\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\GameServer\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Network\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Parser\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Prefab\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Protocol\Game\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Protocol\Room\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\Protocol\Server\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\SaltyEngine\Debug\* build\Debug\
%cp% cmake-build-debug\R-Type\SFMLSaltyEngine\Debug\* build\Debug\
%cp% Dependencies\SFML\Win\x64\Debug\*.dll build\Debug\
%cp% cmake-build-debug\R-Type\Prefab\Debug\* Assets\Metas

cd cmake-build-debug\R-Type\GameClient

%cp% ..\Common\Debug\* .\Debug\
%cp% ..\Network\Debug\* .\Debug\
%cp% ..\Parser\Debug\* .\Debug\
%cp% ..\Prefab\Debug\* .\Debug\
%cp% ..\Protocol\Game\Debug\* .\Debug\
%cp% ..\Protocol\Room\Debug\* .\Debug\
%cp% ..\Protocol\Server\Debug\* .\Debug\
%cp% ..\SaltyEngine\Debug\* .\Debug\
%cp% ..\SFMLSaltyEngine\Debug\* .\Debug\
%cp% ..\..\..\Dependencies\SFML\Win\x64\Debug\*.dll .\Debug\
mklink /J .\Debug\Assets ..\..\..\Assets

cd ..\..\..

cd cmake-build-debug\R-Type\GameServer

%cp% ..\Common\Debug\* .\Debug\
%cp% ..\Network\Debug\* .\Debug\
%cp% ..\Parser\Debug\* .\Debug\
%cp% ..\Prefab\Debug\* .\Debug\
%cp% ..\Protocol\Game\Debug\* .\Debug\
%cp% ..\Protocol\Room\Debug\* .\Debug\
%cp% ..\Protocol\Server\Debug\* .\Debug\
%cp% ..\SaltyEngine\Debug\* .\Debug\
%cp% ..\SFMLSaltyEngine\Debug\* .\Debug\
%cp% ..\..\..\Dependencies\SFML\Win\x64\Debug\*.dll .\Debug\
mklink /J .\Debug\Assets ..\..\..\Assets

cd ..\..\..

mkdir build\Release

%cp% cmake-build-debug\R-Type\Common\Release\* build\Release\
%cp% cmake-build-debug\R-Type\GameClient\Release\* build\Release\
%cp% cmake-build-debug\R-Type\GameServer\Release\* build\Release\
%cp% cmake-build-debug\R-Type\Network\Release\* build\Release\
%cp% cmake-build-debug\R-Type\Parser\Release\* build\Release\
%cp% cmake-build-debug\R-Type\Prefab\Release\* build\Release\
%cp% cmake-build-debug\R-Type\Protocol\Game\Release\* build\Debug\
%cp% cmake-build-debug\R-Type\Protocol\Room\Release\* build\Debug\
%cp% cmake-build-debug\R-Type\Protocol\Server\Release\* build\Debug\
%cp% cmake-build-debug\R-Type\SaltyEngine\Release\* build\Release\
%cp% cmake-build-debug\R-Type\SFMLSaltyEngine\Release\* build\Release\

exit 0