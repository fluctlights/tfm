Primer comando que me ha funcionado, para generar un sistema completo, esta deprecated la funcion pero funciona:

build/ARM/gem5.opt -d m5out/estadisticas configs/deprecated/example/fs.py  \
--bootloader=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/boot.arm64 \
--disk-image=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/ubuntu-18.04-arm64-docker.img \
--dtb=/home/fluctlights/Escritorio/Repos/tfm/gem5/m5out/system.dtb \
--kernel=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/vmlinux.arm64 \
--num-cpus=4 --mem-type=LPDDR2_S4_1066_1x32 \
--mem-size=1GB \
--caches --l2cache --l2_size=512kB --l1i_size=16kB --l1d_size=16kB \
--cpu-clock=1.4GHz --sys-clock=1.4GHz \
--timesync


ESTO ME CREA UNA SESION CORRECTAMENTE CON:

./util/term/m5term <port> normalmente port es 3456 y me genera ademas puertos UART, que creo que se pueden usar


Revisar a ver si puedo sacar un bootloader para raspberry pi directamente sin tirar de genericos de gem5
CREO QUE ESO NO VA A PODER SER PERO SI PUEDO MIRAR FORMAS DE MODIFICAR EL COMPORTAMIENTO PARA QUE SEA MAS RAPIDO
HAY UN VIDEO DE UNO HACIENDO UNA RPI4 -> https://pierreay.github.io/reproduce-spectre-gem5/

TAMBIEN PUEDO MIRAR LA PARTE DE MODIFICACION DEL MENUCONFIG A VER QUE SACO:
https://blog.carreralinux.com.ar/2017/12/configurar-el-kernel-make-menuconfig/

