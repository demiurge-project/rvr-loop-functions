# README
rvr-loop-functions
=====================

This package contains the source for unified handling of loop
fonctions to assess performances in automatic design methods.
It also contains the specific implementation of loop functions for
missions from different AutoMoDe related studies.

All useful information about the AutoMoDe package, including
installation and utilization instructions, are regrouped in the
following technical report ([techrep](#bibliography)). Please cite
this report if you any ARGoS3-AutoMoDe-rvr related package.

## Package content
- `loop-functions/` contains all sources for loop functions for
    specific missions from different AutoMoDe related studies.
- `src/` contains the core source files and mother class from which
    all loop functions are derived.

## Installation
### Dependencies
- [ARGoS3](https://github.com/ilpincy/argos3) (3.0.0-beta48)
- [argos3-rvr](https://github.com/demiurge-project/argos3-rvr)

### Compiling and installing
    $ git clone https://github.com/demiurge-project/rvr-loop-functions.git
    $ cd rvr-loop-functions
    $ mkdir build
    $ cmake ..
    $ make
    $ sudo make install

Once compiled and installed the shared library and header files
are installed in the system.

If you do not have root access off what to install in a your local
argos distribution folder use (if your argos installation is located
in `~/argos-dist`):

    $ cmake .. -DCMAKE_INSTALL_PREFIX=~/argos-dist
    $ make
    $ make install

### How to use
This package is meant to be used as a library to allow unified
definition of loop functions for performance assessment for different
automatic design methods. It is used in AutoMoDe, Evostick and other
automatic design methods (see [references](#bibliography)).

## References
### Bibliography

- [techrep] Kegeleirs, M., Todesco, R., Garzon Ramos, D., Legarda Herranz, G., Birattari, M. (2022).Mercator: hardware and software architecture for experiments in swarm SLAM. Technical report TR/IRIDIA/2022-012, IRIDIA, Université libre de Bruxelles, Belgium.
- [chocolate] Francesca, G., Brambilla, M., Brutschy, A., Garattoni, L., Miletitch, R., Podevijn, G., ... & Mascia, F. (2015). AutoMoDe-Chocolate: automatic design of control software for robot swarms. Swarm Intelligence, 9(2-3), 125-152.
- [gianduja] Hasselmann K., Robert F., Birattari M. (2018) Automatic Design of Communication-Based Behaviors for Robot Swarms. In: Dorigo M., Birattari M., Blum C., Christensen A., Reina A., Trianni V. (eds) Swarm Intelligence. ANTS 2018. Lecture Notes in Computer Science, vol 11172. Springer, Cham
