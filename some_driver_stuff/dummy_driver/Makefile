#LINUXDIR := $(HOME)/embedded-linux-toolchain/linux      # Путь к каталогу ядра
# для целевого устройства, на котором будет работать модуль

#obj-m := dummy.o        # Будет вызвано правило сборки ядра, которое преобразует
# исходный файл dummy.c в модуль ядра dummy.ko. Модуль загрузится только в то ядро,
# вместе с которым он компилировался

#all:
#	$(MAKE) ARCH=x86_64 -C $(LINUXDIR) M=$(shell pwd) modules 
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -C $(LINUXDIR) M=$(shell pwd)
#clean: 
#	# $(MAKE) -C $(LINUXDIR) M=$(shell pwd) clean
#	make -C $(LINUXDIR) M=$(shell pwd) clean

obj-m := dummy_driver.o

# Путь к исходникам ядра для текущей системы
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

# Явное указание компилятора, который использовался для сборки ядра
CC := x86_64-linux-gnu-gcc-13

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) CC=$(CC) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean