<!--
  ~ Copyright 2022 NWChemEx-Project
  ~
  ~ Licensed under the Apache License, Version 2.0 (the "License");
  ~ you may not use this file except in compliance with the License.
  ~ You may obtain a copy of the License at
  ~
  ~ http://www.apache.org/licenses/LICENSE-2.0
  ~
  ~ Unless required by applicable law or agreed to in writing, software
  ~ distributed under the License is distributed on an "AS IS" BASIS,
  ~ WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ~ See the License for the specific language governing permissions and
  ~ limitations under the License.
-->

Utilities Repository
======================

[Documentation](https://nwchemex.github.io/Utilities/)

The C++ standard library as well as the STL are great for providing many of the
features one needs to write a code.  However, they leave much to be desired.
This library is intended to be our "Boost" in that it's a series of
extensions to the standard libraries for functionality we commonly want.

At the moment this functionality can be expressed as falling into one of three
sub libraries:

- IterTools: Classes designed to make iteration easier.  This includes base
             classes for writing your own iterators as well as classes for
             iterating over common situations such as:
             - All permutations of a sequence
             - All combinations of a sequence
- Mathematician : Math functionality beyond that of the STL including:
  - Binomial coefficients
  - Multinomial coefficients
- TypeTraits : Structs to make meta-template programming easier
  - Extended type intraspection (*i.e.* determining if a type has a member)

Building Utilities
--------------------

Utilities is built using [CMaize](https://github.com/CMakePP/CMaize). Building
Utilities can be accomplished by:

```bash
git clone https://github.com/NWChemEx/Utilities.git
cd Utilities
cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=<where/you/want/to/install/Utilities> \
                  -DCMAKE_TOOLCHAIN_FILE=<path/to/toolchain.cmake> # (Optional)
cd build
cmake --build .
#May need to run as an admin depending on where you are installing
cmake --build . --target install
```

Additional CMake parameters can be passed on the command line or in a toolchain
file, as represented in the above example. The unit tests for Utilities can be
built by passing `-DBUILD_TESTING=ON` to the first invocation of CMake, or by
adding `set(BUILD_TESTING ON)` in the toolchain file. Utilities uses the
[Catch2](https://github.com/catchorg/Catch2) framework for testing, and will
build it if not already present. If you wish to use an existing installation of
Catch2 and it is not being located by CMake configuration, setting `Catch2_ROOT`
to the location of the installation or adding that path to the
`CMAKE_PREFIX_PATH` should resolve the issue.
