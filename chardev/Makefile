obj-m += chardev.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/6.1.0-31-amd64/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.1.0-31-amd64/build M=$(PWD) clean