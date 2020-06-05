# ROOT macro to RadWare converter

Maintainer: Jonathan Williams


## Description

Code for converting [ROOT](https://root.cern.ch/) macro files (.C files generated using the File/Save option in a ROOT TBrowser) to spectra readable by [RadWare](https://radware.phy.ornl.gov/).

The code works by directly parsing the macro file - it does not depend on ROOT in any way, and so does not require a specific version of ROOT.


## Instructions

Use `make` to compile.  The code is then run from the command line:

```
rootmacro2rad /path/to/macro.C
```

Extra conversion options are available.  These include:

|**Option**|**Description**|
|:---:|:---:|
| `-offset NUMBER` | offset the starting channel by the specified number of channels, useful for studying data beyond the 4096 channel limit allowed by RadWare |
| `-yoffset NUMBER` | same as `-offset`, except on the y-axis, for 2D histograms |
| `-rebin NUMBER` | rebin/contract the output spectra by the specified integer factor (applied after `-offset` and `-yoffset`) |

So for example, to convert a histogram in the file `sample_macros/Segment0.C`, rebinning the result by a factor of 2, you would run:

```
rootmacro2rad sample_macros/Segment0.C -rebin 2
```