mkdir NovaPx/
cd NovaPx
cp ../../cmake-build-release-msys2/NovaPx.exe .
cp ../../assets/test.png .
windeployqt --release NovaPx.exe
cp $(ldd NovaPx.exe | grep mingw64 | cut -d \( -f1 | cut -d \> -f2) .
rm -fr iconengines/
rm -fr imageformats/
rm -fr styles/
rm -fr translations/
rm -f Qt5Svg.dll #Why is this even grabbed, nothing uses it :I
cd ..
zip -r NovaPx-1.2.0.zip NovaPx
