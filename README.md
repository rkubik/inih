# inih

inih is a simple .INI file parser written in C, released under the New BSD
license (see LICENSE). The original project home page is located at:

http://code.google.com/p/inih/

This fork adds ``cmake`` and ``debuild`` builds and some updates to the
``C++`` library (templating).

## Dependencies

- C++ compiler
- GNU/Linux OS
- cmake (>= 2.8)
- debuild (optional)

# Build

You can build and install with cmake or use debuild to create Debian packages.

1. cmake

In the root of the project.

    mkdir build
    cd build
    cmake ..
    make
    make install

2. debuild

In the root of the project.

    debuild -us -uc -b -j4
    debuild clean

Which will produce both the runtime and development Debian packages.

## Usage

    #include <iostream>
    #include <inicpp/INIReader.hpp>
    using namespace inicpp;

    int main()
    {
        INIReader reader("../examples/test.ini");

        if (reader.ParseError() < 0) {
            std::cerr << "Can't load 'test.ini'\n";
            return 1;
        }

        reader.Get<int>("protocol", "version", -1)

        return 0;
    }

## License

    The "inih" library is distributed under the New BSD license:

    Copyright (c) 2009, Brush Technology
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of Brush Technology nor the names of its contributors
        may be used to endorse or promote products derived from this software
        without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY BRUSH TECHNOLOGY ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL BRUSH TECHNOLOGY BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
