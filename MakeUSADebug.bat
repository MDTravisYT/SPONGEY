del out\*.* /s /y /e >nul
del /s /q CdBuild.USA.Debug
rmdir /s /q CdBuild.USA.Debug
@tools\make -r -f makefile.gfx VERSION=DEBUG TERRITORY=USA USER_NAME=CDBUILD
@tools\make -r -f makefile.gaz VERSION=DEBUG TERRITORY=USA USER_NAME=CDBUILD
ren cdbuild CdBuild.USA.Debug
pause