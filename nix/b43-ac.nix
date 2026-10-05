# Out-of-tree b43 with the BCM4360 AC-PHY port, built for one kernel (notes/115).
#   boot.extraModulePackages = [ (config.boot.kernelPackages.callPackage /home/gonsolo/bcm4360-acphy/nix/b43-ac.nix { }) ];
# Installs b43.ko into extra/, which depmod prefers over the in-tree b43; tools/b43_boot.sh insmods `modinfo -n b43`.
{ lib, stdenv, kernel }:

stdenv.mkDerivation {
  pname = "b43-ac";
  version = "0-${kernel.modDirVersion}";

  # Sources only: no objects/.ko from a previous in-tree build, so the hash is stable.
  src = builtins.path {
    name = "b43-ac-src";
    path = ./../b43-src;
    filter = path: type: type == "regular" && builtins.match ".*\\.[ch]|.*/Makefile" path != null;
  };

  nativeBuildInputs = kernel.moduleBuildDependencies;
  hardeningDisable = [ "pic" "format" ];

  makeFlags = kernel.makeFlags ++ [
    "KDIR=${kernel.dev}/lib/modules/${kernel.modDirVersion}/build"
    "INSTALL_MOD_PATH=$(out)"
  ];
  buildFlags = [ "all" ];
  installPhase = ''
    runHook preInstall
    install -D b43.ko $out/lib/modules/${kernel.modDirVersion}/extra/b43.ko
    runHook postInstall
  '';

  meta = {
    description = "b43 with the BCM4360 AC-PHY port (out of tree)";
    license = lib.licenses.gpl2Only;
    platforms = lib.platforms.linux;
  };
}
