{ pkgs ? import <nixpkgs> {}, ... }:

pkgs.mkShell {
  nativeBuildInputs = [
    # builder tools
    pkgs.cmake
    # Currently not using lldb, since it does not support intel assembly syntax
    pkgs.lldb
    pkgs.gdb

    # XXX: the order of include matters
    pkgs.clang-tools
    pkgs.clang # for clangd support

    # For generating compile_commands.json
    pkgs.bear

    pkgs.gtest
    pkgs.valgrind
  ];

  buildInputs = [
    # Dependencies
    # stdlib for C++
    pkgs.libcxx
    # Unit testing
    pkgs.cmocka
  ];

  # Optional compiler flags
  CXXFLAGS = "";

  # Path setup for includes
  CPATH = builtins.concatStringsSep ":" [
    (pkgs.lib.makeSearchPathOutput "dev" "include" [ pkgs.libcxx ])
    (pkgs.lib.makeSearchPath "resource-root/include" [ pkgs.clang ])
  ];
}

