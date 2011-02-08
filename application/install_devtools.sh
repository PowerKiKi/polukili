#!/bin/bash
PATH_POLUKILI=`dirname $(readlink -f $0)`
PATH_GRRLIB="$PATH_POLUKILI/../../grrlib"
VERSION_DEVKITPPC=r22
VERSION_LIBOGC=1.8.6
VERSION_LIBFAT=1.0.8
VERSION_EXAMPLES=20100930
VERSION_MXML=2.6

# (inspired by "official instructions":http://devkitpro.org/wiki/Getting_Started/devkitPPC)

# Install system tools
sudo apt-get install git subversion

# Install devkitpro
DEVKITPRO=/opt/devkitpro
DEVKITPPC=$DEVKITPRO/devkitPPC
echo "export DEVKITPRO=$DEVKITPRO" >> ~/.bashrc
echo "export DEVKITPPC=$DEVKITPPC" >> ~/.bashrc
sudo mkdir -p $DEVKITPRO
sudo chmod 777 $DEVKITPRO
cd $DEVKITPRO/
wget http://switch.dl.sourceforge.net/project/devkitpro/devkitPPC/devkitPPC_$VERSION_DEVKITPPC-i686-linux.tar.bz2 || { echo "cannot download devkitppc $VERSION_DEVKITPPC !" ; exit  $?  ; }
tar -xvjf devkitPPC_$VERSION_DEVKITPPC-i686-linux.tar.bz2 
mkdir libogc
cd libogc/
wget http://switch.dl.sourceforge.net/project/devkitpro/libogc/libogc-$VERSION_LIBOGC.tar.bz2 || { echo "cannot download libogc $VERSION_LIBOGC !" ; exit  $?  ; }
tar -xvjf libogc-$VERSION_LIBOGC.tar.bz2 
wget http://switch.dl.sourceforge.net/project/devkitpro/libfat/libfat-ogc-$VERSION_LIBFAT.tar.bz2 || { echo "cannot download libfat $VERSION_LIBFAT !" ; exit  $?  ; }
tar -xvjf libfat-ogc-$VERSION_LIBFAT.tar.bz2
cd ..
mkdir -p examples/wii
cd examples/wii/
wget http://switch.dl.sourceforge.net/project/devkitpro/examples/wii/wii-examples-$VERSION_EXAMPLES.tar.bz2 || { echo "cannot download examples $VERSION_EXAMPLES !" ; exit  $?  ; }
tar -xvjf wii-examples-$VERSION_EXAMPLES.tar.bz2 
cd ..

# Install portlibs
mkdir -p $DEVKITPRO/portlibs/ppc
cd $DEVKITPRO/portlibs/ppc/
wget http://switch.dl.sourceforge.net/project/devkitpro/portlibs/mxml-$VERSION_MXML-ppc.tar.bz2 || { echo "cannot download mxml $VERSION_MXML !" ; exit  $?  ; }
tar -xvjf mxml-$VERSION_MXML-ppc.tar.bz2 

# Install GRRLIB
mkdir -p $PATH_GRRLIB
svn checkout http://grrlib.googlecode.com/svn/trunk/ $PATH_GRRLIB

# Compilation instruction 
echo "________________________________________________________________________"
echo "Installation completed !"
echo "Open a new terminal and run the following command:"
echo "cd $PATH_GRRLIB/GRRLIB && make all install && cd $PATH_POLUKILI && make"

