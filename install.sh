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
packages="graphviz doxygen gcovr"

# functions
install_package () {
  printf "Installing ${Yellow}"$package_name"${NC} ..."
  package_name="$1"
  which zypper &> /dev/null && sudo zypper -y install "$package_name"
  which pacman &> /dev/null && sudo pacman --noconfirm -S "$package_name"
  which dnf &> /dev/null && sudo dnf -y install "$package_name"
  which apt-get &> /dev/null && sudo apt-get -y install "$package_name"
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
