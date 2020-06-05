#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define S4K   4096

//internal histograms
double hist[S4K];
double hist2[S4K][S4K];

//other globals
int rebinFactor;
int startBinOffset, startBinOffsetY;