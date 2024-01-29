# Poky with application

## Substring counting

Locate at `meta-app/recipes-app/substring-count`

## Build

Clone the project

```
$ git clone https://github.com/dungph/yocto-hacking.git -b substring-couting
```

Setup env

```
$ cd yocto-hacking
$ source oe-init-build-env
```

Add app layer to the build env

```
bitbake-layers add-layer ../meta-app
```

Add `substring-count` package and target machine to configuration at `conf/local.conf`:

```
MACHINE ?= "qemuarm64"
IMAGE_INSTALL:append = " substring-count"
```

Build image

```
$ bitbake code-image-minimal
```

Run the image using Qemu

```
# runqemu nographic qemuarm64
```

Run the application


```
$ echo "hello aaa bbbbbbbbbaaaa" > test.txt
$ substring-count test.txt "a"
```
    


