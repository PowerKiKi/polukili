#!/bin/bash
PATH_POLUKILI=`dirname $0`
PATH_GRRLIB="$PATH_POLUKILI/../../grrlib"

# (inspired by "official instructions":http://devkitpro.org/wiki/Getting_Started/devkitPPC)

# Install system tools
sudo apt-get install git subversion

# Install devkitpro
echo "export DEVKITPRO=/opt/devkitpro" >> ~/.bashrc
echo "export DEVKITPPC=\$DEVKITPRO/devkitPPC" >> ~/.bashrc
bash
sudo mkdir -p $DEVKITPRO
sudo chmod 777 $DEVKITPRO
cd $DEVKITPRO/
wget http://switch.dl.sourceforge.net/project/devkitpro/devkitPPC/devkitPPC_r22-i686-linux.tar.bz2
tar -xvjf devkitPPC_r22-i686-linux.tar.bz2 
mkdir libogc
cd libogc/
wget http://switch.dl.sourceforge.net/project/devkitpro/libogc/libogc-1.8.5.tar.bz2
tar -xvjf libogc-1.8.5.tar.bz2 
wget http://switch.dl.sourceforge.net/project/devkitpro/libfat/libfat-ogc-1.0.7.tar.bz2
tar -xvjf libfat-ogc-1.0.7.tar.bz2
cd ..
mkdir -p examples/wii
cd examples/wii/
wget http://switch.dl.sourceforge.net/project/devkitpro/examples/wii/wii-examples-20100930.tar.bz2
tar -xvjf wii-examples-20100930.tar.bz2 
cd ..

# Install portlibs
mkdir -p $DEVKITPRO/portlibs/ppc
cd $DEVKITPRO/portlibs/ppc/
wget http://switch.dl.sourceforge.net/project/devkitpro/portlibs/mxml-2.6-ppc.tar.bz2
tar -xvjf mxml-2.6-ppc.tar.bz2 

# Install GRRLIB
mkdir -p $PATH_GRRLIB
svn checkout http://grrlib.googlecode.com/svn/trunk/ $PATH_GRRLIB
cd "$PATH_GRRLIB/GRRLIB"
make all install

# Compile polukili
cd $PATH_POLUKILI
make

