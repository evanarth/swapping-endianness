# swapping-endianness
several byte manipulations for changing the endianness of numbers

endianness (big-endian and little-endian) are an annoying artifact of computer's having decades of history.
when multiple bytes are used to describe a single number, do we start from the smallest digit, or the biggest?
C/C++, Python, and Perl favor big-endian, and Fortran and Matlab favor little-endian. 
here are a few implimentations of swapping the endianness of varying readability and efficiency.
