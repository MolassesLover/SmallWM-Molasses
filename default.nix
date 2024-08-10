{ pkgs ? import <nixpkgs> { } }:
pkgs.callPackage ./misc/nix/smallwm-molasses.nix { }
