# env setup

# wsl

some secure software may broken the wsl lxssmanager service start
to some this issue, in cmd prompt(admin), run the command:
sc config LxssManager start=auto

to let the LxssManager start automatically.

# udev

service udev start

wsl do not auto run some nenessary service at start,do it at /etc/wsl.conf manully

# windows
用下面这个密匙可以将家庭中文版升级为家庭版。只能升级，无法用于激活。升级完成后就可以添加语言，并设为windows显示语言了。

YTMG3-N6DKC-DKB77-7M9GH-8HVX7