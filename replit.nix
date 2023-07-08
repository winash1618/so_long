{ pkgs }: {
	deps = [
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
    pkgs.xorg.libX11
    pkgs.xorg.libXext
    pkgs.libbsd
    pkgs.nmap
	];
}