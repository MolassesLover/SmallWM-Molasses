{
  description =
    "Molasses' fork of SmallWM, a lightweight floating window manager.";

  inputs = { nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable"; };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" ];

      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in {
      packages = forAllSystems (system:
        let
          pkgs = (import nixpkgs { inherit system; });
          smallwm = pkgs.callPackage misc/nix/smallwm-molasses.nix { };
        in {
          inherit smallwm;
          default = smallwm;
          devShell = pkgs.mkShell { inputsFrom = [ smallwm ]; };
        });
    };
}
