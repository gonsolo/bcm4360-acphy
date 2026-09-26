{ config, lib, pkgs, ... }:

# One-shot boot generation: the normal config, but wl is not loaded at boot;
# txtrace.sh loads it under kprobe tracing instead.
{
  imports = [ /etc/nixos/configuration.nix ];

  boot.blacklistedKernelModules = [ "wl" ];

  systemd.services.wl-tx-trace = {
    description = "Trace wl TX descriptors on BCM4360 (reverts boot default first)";
    wantedBy = [ "multi-user.target" ];
    after = [ "NetworkManager.service" "local-fs.target" ];
    path = with pkgs; [
      bash coreutils gnugrep gnused kmod procps iproute2 util-linux xz
      networkmanager iw iputils config.systemd.package
    ];
    serviceConfig = {
      Type = "simple";
      ExecStart = "${pkgs.bash}/bin/bash /home/gonsolo/bcm4360-acphy/txtrace.sh";
    };
  };
}
