# Logging
Logging library from LBS R&D projects

## Getting Started

* Clone this repository

```sh
git clone ssh://git@bitbucket-ssh.vietmap.vn:7999/lbsrnd/vm-logging.git

```

* Build and install library

```sh
mkdir build && cd build
cmake ..
cmake --build . --parallel
sudo make install
```

* Build and install package

```sh
cmake ..
make package
sudo dpkg -i Logging-1.0.0-Linux.deb
```