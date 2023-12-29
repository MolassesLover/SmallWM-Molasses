{ lib, stdenv, cmake, ninja, fetchFromGitHub, xorg, xorgserver, pkg-config
, libX11, libXext, libXrandr }:

stdenv.mkDerivation (finalAttrs: {
  pname = "smallwm-molasses";
  version = "1.0.0";

  src = ./.;

  nativeBuildInputs = [ cmake ninja ];
  buildInputs = [ libX11 libXext libXrandr ];

})
