from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [
    Extension("monomial", ["monomial.pyx"], language="c++"),
    Extension("searching", ["searching.pyx"])
    ]

setup(
    name = 'Graph search tools',
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
    )
