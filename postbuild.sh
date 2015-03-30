#! /bin/bash


## Create resource file (.rcc)
rcc --compress 2 -binary /home/heebum/Documents/AhnLab/V3LC/01_PreResearch/02_qt/13_Beyond_compare/resource/resource.qrc -o /home/heebum/Documents/AhnLab/V3LC/01_PreResearch/02_qt/13_Beyond_compare/resource/resource.rcc

## copy .rcc to build path
mkdir  resource
cp /home/heebum/Documents/AhnLab/V3LC/01_PreResearch/02_qt/13_Beyond_compare/resource/resource.rcc ./resource/resource.rcc
