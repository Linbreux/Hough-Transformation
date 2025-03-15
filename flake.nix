{
  description = "Flake for building a Qt GUI program";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = { self, nixpkgs }: 
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      coreLib = pkgs.callPackage ./src/core/default.nix {};
      guiApp = pkgs.callPackage ./src/GUI/default.nix {
          inherit coreLib;
        };

    in{
      apps.${system}.default = {
        type = "app";
        program = "${guiApp}/bin/gui_program";
      };
      packages.${system}.default = pkgs.buildEnv {
        name = "combinedEnv";
        paths = [ guiApp ];  # Include the packages in the environment
      };
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = [
          pkgs.qt5.qtbase
          pkgs.qt5.qtquickcontrols2
          pkgs.qt5.qtquickcontrols
          pkgs.qt5.wrapQtAppsHook
          pkgs.gdb
          pkgs.bashInteractive
          pkgs.makeWrapper
          pkgs.just
          # Add other required Qt modules here
          #coreLib
          #guiApp
        ];
        nativeBuildInputs = [ pkgs.qt5.wrapQtAppsHook ];
        shellHook = ''
          export CMAKE_PREFIX_PATH="${pkgs.qt5.qtbase}/lib/cmake/Qt5:$CMAKE_PREFIX_PATH"
          bashdir=$(mktemp -d)
          makeWrapper "$(type -p bash)" "$bashdir/bash" "''${qtWrapperArgs[@]}"
          exec "$bashdir/bash"
        '';
      };
    };
}
