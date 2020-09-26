#!/bin/bash

#variables
# Make colorcoding available for everyone
Black='\[\e[0;30m\]'        # Black
Red='\[\e[0;31m\]'          # Red
Green='\[\e[0;32m\]'        # Green
Yellow='\[\e[0;33m\]'       # Yellow
Blue='\[\e[0;34m\]'         # Blue
Purple='\[\e[0;35m\]'       # Purple
Cyan='\[\e[0;36m\]'         # Cyan
White='\[\e[0;37m\]'        # White
NC="\[\e[m\]"               # Color Reset

# needed for read -a
IFS=' '
#packages to install
packages="graphviz doxygen"

# functions
get_os () {
    which zypper &> /dev/null && os="opensuse"
    which pacman &> /dev/null && os="archlinux"
    which dnf &> /dev/null && os="fedora"
    which apt-get &> /dev/null && os="debian"
}

get_cmd_install () {
    os=get_os
    case "$os" in
        opensuse) echo "sudo zypper -y install";;
        archlinux) echo "sudo pacman --noconfirm -S";;
        fedora) echo "sudo dnf -y install";;
        debian) echo "sudo apt-get -y install";;
    esac
}

install_package () {
    package_name=$1
    [[ -z "$cmd_install" ]] && cmd_install=$(get_cmd_install)
    sudo $cmd_install $package_name
}

install_loop () {
  # splits the $args string into an array using IFS variable set before
  read -a array <<< "$packages"

  # -> for (int i = 0; i < array.length; i++)
  for i in "${array[@]}"
  do
    install_package "$i"
  done
}


# script
install_loop