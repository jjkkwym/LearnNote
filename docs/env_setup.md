# env setup

# wsl

some secure software may broken the wsl lxssmanager service start
to some this issue, in cmd prompt(admin), run the command:
sc config LxssManager start=auto

to let the LxssManager start automatically.

# udev

service udev start

wsl do not auto run some nenessary service at start,do it at /etc/wsl.conf manully
