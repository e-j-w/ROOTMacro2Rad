# ROOT macro to RadWare converter

Maintainer: Jonathan Williams


## Description

Code for converting [ROOT](https://root.cern.ch/) macro files (.C files generated using the File/Save option in a ROOT TBrowser) to spectra readable by [RadWare](https://radware.phy.ornl.gov/).

The code works by directly parsing the macro file - it does not rely on ROOT in any way, and so does not require a specific version of ROOT.


## Instructions

Use `make` to compile.  The code is then run from the command line:

```
rootmacro2rad /path/to/macro.C
```