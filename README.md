# numpy.distutils-example
Small project to expore the numpy.distutils module to call Fortran from Python

To build:
python3 setup.py build_ext -i

To test:
```
python3
>>> import fmod
>>> print (fmod.fmod.fib (8))
```

To package:
```
pyinstaller main.py
```

To test packaged executable:
```
./dist/main/main
```

That's all folks!
