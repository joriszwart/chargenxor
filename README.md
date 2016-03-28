chargenxor
==========

**chargenxor** is a simple tool to transform (XOR) your custom CBM font using
the default charset ROM to make it more compressible.



Usage
-----

````bash
$ chargenxor <customfont> <outputfile>
````

A file called `chargen` containing the default charset ROM should be available
in the current directory.



Sample transformation code
--------------------------

````6510
                sei
                lda #$33                ; bank chargen in
                sta $01

                ldx #0
copyfont        lda $d000,x
                eor customfont,x
                sta $2000,x
                lda $d100,x
                eor customfont,x
                sta $2100,x
                inx
                bne copyfony

                lda #$37                ; default banks (basic / kernal / IO)
                sta $01
                cli
````



Version history
---------------


Version | Notes
--------|-----------------------------------------------
    1.0 | Initial version.
