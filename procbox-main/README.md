# procbox
procbox is library to control the amount of memory used by a process

## build
```
$ make
```

## Usage
```
$ LD_PRELOAD=$PWD/libprocbox.so program
```

### Example
```
$ LD_PRELOAD=$PWD/libprocbox.so ls
```
 
