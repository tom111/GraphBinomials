from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(ext_modules=[Extension(
                       "graphtool",                 # name of extension
                       ["graphtool.pyx"], #  our Cython source
                       libraries=["graphbinomial"],
                       library_dirs=["../"],
                       language="c++")],  # causes Cython to create C++ source
      cmdclass={'build_ext': build_ext})
