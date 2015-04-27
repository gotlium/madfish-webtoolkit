To compile WebToolkit from source, you have to install [cmake](http://www.cmake.org/).

1. Check out code from svn:
```
svn checkout http://madfish-webtoolkit.googlecode.com/svn/trunk/ WebApps
```

2. Create build folder:
```
mkdir WebAppsBuild
cd WebAppsBuild
```

3. Invoke cmake.

For Windows (Visual Studio 2008)
```
cmake -G "Visual Studio 9 2008" ..\WebApps
```

For Unix-like systems (by default it will use Unix makefiles, and that is ok)
```
cmake ../WebApps                                         #Debug version
cmake -DCMAKE_BUILD_TYPE=Release ../WebApps              #Release version
cmake -DCMAKE_BUILD_TYPE=Release -DDOCS=YES ../WebApps   #Release version with documentation
```

4. Build.

  * For Windows: open generated Visual Studio solution, and run build.
  * For Linux: just run make.

5. For FileServer and RatioProxy you should put their data files in the executable's folder (you should find them in the Data folders). For example, for RatioProxy you should put RatioProxy.exe and RatioProxy.conf into one folder for it to work.