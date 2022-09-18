## 우마무스메 스타일 4과문 생성기

게임 이름, 회사 이름, 대표이사 이름을 입력하면 자동으로 4과문을 생성해줍니다.  
4과문은 화면에 표시되는 동시에 4과문.txt 라는 파일로 저장됩니다.

### 빌드 방법
CMake (3.13 이상), c++20 이상을 지원하는 컴파일러가 필요합니다.
```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --target ApologyPrinter
build/ApologyPrinter.exe # Windows
build/ApologyPrinter # *nix
```
또는 리포지토리 Release에 올라와 있는 exe 파일을 그대로 내려받아서 실행해도 됩니다.

### 실행 방법
화면에 나오는 순서대로 게임 이름, 회사 이름, 대표이사 이름을 입력하고 엔터를 치세요.  
