# VBinDiff - Visual Binary Diff

[Visual Binary Diff (VBinDiff)](https://www.cjmweb.net/vbindiff/)
displays files in hexadecimal and ASCII (or EBCDIC). It can also
display two files at once, and highlight the differences between them.
Unlike diff, it works well with large files (up to 4 GB).

VBinDiff was inspired by the Compare Files function of the [ProSel
utilities by Glen
Bredon](http://www.apple2.org.za/gswv/USA2WUG/Glen.Bredon.In.Memoriam/A2.Software/),
for the [Apple II](https://en.wikipedia.org/wiki/Apple_II). When I
couldn't find a similar utility for the PC, I wrote it myself.

The single-file mode was inspired by the LIST utility of [4DOS and
friends](http://jpsoft.com/take-command-windows-scripting.html). While
[less](http://www.greenwoodsoftware.com/less/) provides a good
line-oriented display, it has no equivalent to LIST's hex display.
(True, you can pipe the file through
[hexdump](http://linux.die.net/man/1/hexdump), but that's incredibly
inefficient on multi-gigabyte files.)

# Build

To build the code, see [the build instructions](./docs/build.md).

# Copyright and License

Visual Binary Diff is copyright 1995-2013 by Christopher J. Madsen

This program is free software; you can redistribute it and/or modify it under the terms of the [GNU General Public License](https://www.gnu.org/licenses/gpl.html) as published by the Free Software Foundation; either [version 2 of the License](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html), or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
