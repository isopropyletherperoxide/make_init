with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "myenv";
  buildInputs = [ libgit2 ];
}
