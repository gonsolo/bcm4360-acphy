{ config, lib, pkgs, ... }:

# One-shot cold-boot test generation: identical to /etc/nixos/configuration.nix
# except wl is absent, so our custom b43.ko is the first driver to touch the chip.
{
  imports = [ /etc/nixos/configuration.nix ];

  boot.blacklistedKernelModules = [ "wl" ];
  boot.extraModulePackages = lib.mkForce [ ];

  systemd.services.b43-coldboot-test = {
    description = "BCM4360 b43 cold-boot test (reverts boot default first)";
    wantedBy = [ "multi-user.target" ];
    after = [ "NetworkManager.service" "local-fs.target" ];
    path = with pkgs; [
      bash coreutils gnugrep gnused kmod procps iproute2 util-linux
      networkmanager config.systemd.package
    ];
    serviceConfig = {
      Type = "simple";
      ExecStart = "${pkgs.bash}/bin/bash /home/gonsolo/bcm4360-acphy/coldboot_test.sh";
    };
  };
}
