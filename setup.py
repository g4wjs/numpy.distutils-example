from __future__ import division, absolute_import, print_function

from numpy.distutils.core import Extension

fmod = Extension (name = 'fmod',
	sources = ['fmod.f90', 'threaded_fib.c'])

if __name__ == "__main__":
	from numpy.distutils.core import setup
	setup (name = 'fmod example',
		desrciption = 'Fortran module useable in Python',
		author = "Bill Somerville",
		ext_modules = [fmod]
		)
