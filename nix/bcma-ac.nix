# bcma with Alessio Ferri's PMU/PLL patches for the BCM4352/BCM4360 (notes/167, 168), built for one kernel.
#   boot.extraModulePackages = [ (config.boot.kernelPackages.callPackage /home/gonsolo/bcm4360-acphy/nix/bcma-ac.nix { }) ];
# Installs bcma.ko into extra/, which depmod prefers over the in-tree bcma. Without the PLL patch the chip stays dead
# after a long suspend. Only patches 1-4 and 8 of his series: 5-7 change struct ssb_sprom, which b43 (built against
# the stock header) would then read at wrong offsets; add them when b43 is built against the same headers.
{ lib, stdenv, kernel }:

stdenv.mkDerivation {
  pname = "bcma-ac";
  version = "0-${kernel.modDirVersion}";
  inherit (kernel) src;

  # Unpack only the bcma driver and its public headers from the kernel tarball.
  unpackPhase = ''
    runHook preUnpack
    tar xf $src --strip-components=1 --wildcards '*/drivers/bcma' '*/include/linux/bcma' '*/include/linux/ssb' '*/include/linux/bcm47xx_sprom.h'
    runHook postUnpack
  '';
  patches = lib.sort (a: b: a < b) (map (n: ./bcma-patches + "/${n}") (builtins.attrNames (builtins.readDir ./bcma-patches)));

  preferLocalBuild = true;
  allowSubstitutes = false;

  nativeBuildInputs = kernel.moduleBuildDependencies;
  hardeningDisable = [ "pic" "format" ];

  # The patched chipcommon header (new CHIPST/PLL defines) must win over the kernel's copy.
  dontConfigure = true;
  buildPhase = ''
    runHook preBuild
    make -C ${kernel.dev}/lib/modules/${kernel.modDirVersion}/build M=$PWD/drivers/bcma modules \
      KCFLAGS="-include linux/types.h -include $PWD/include/linux/bcma/bcma_driver_chipcommon.h"
    runHook postBuild
  '';
  installPhase = ''
    runHook preInstall
    install -D drivers/bcma/bcma.ko $out/lib/modules/${kernel.modDirVersion}/extra/bcma.ko
    runHook postInstall
  '';

  meta = {
    description = "bcma with the BCM4352/BCM4360 PMU PLL init (out of tree)";
    license = lib.licenses.gpl2Only;
    platforms = lib.platforms.linux;
  };
}
