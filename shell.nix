# Please Note I have a very limited understanding of the inner workings
# of certain things here I am just using what I have seen necessary for
# my application feel free to argue or change that as much as you please

{ pkgs ? import <nixpkgs> {} }:

let
  # use nixos-rebuild to get the system config
  systemConfig = (import <nixpkgs/nixos> {}).config;
  kernelPackages = systemConfig.boot.kernelPackages;
in

pkgs.mkShell {
  packages = with pkgs; [
    gcc
    cmake

    stdenv.cc
    stdenv.cc.cc

    raylib
  ];

  nativeBuildInputs = with pkgs; [
    #?  compiler
    gcc

    #? Build System
    cmake

    #*Libraries
      #?  GUI
      raylib

      #?  Testing
      gtest
      coreutils-prefixed

    #?LSP
    clang-tools #it has clangd
   ];

# running:  gcc main.cpp -lraylib -lstdc++ -o main

}