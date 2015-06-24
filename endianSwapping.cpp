/*
 *  Endian swapping - March 16, 2015
 *  
 *  this program swaps the endianness of numbers
 */


#include <stdio.h>
#include <stdlib.h>
#include <vector>

// -----------------------------------------------------------------------------
// print data

static void printHex( void* input, size_t numBytes ) {
    unsigned char* hexList = (unsigned char*) input;
    if (input == NULL) return;
    while ( numBytes > 0 ) {
        -- numBytes;
        printf("%02x ", hexList[numBytes]);
    }
    printf("\n");
}

// -----------------------------------------------------------------------------
// swap bytes (bit-shuffling)

// 32-bit int
int32_t swap_int32( int32_t val ) {
    
    // shuffle { a b c d } into { b a d c }
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
    
    // shuffle { b a d c } into { d c b a }
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

// 64-bit int
int64_t swap_int64( int64_t val ) {
    
    // shuffle { a b c d   e f g h } into { b a d c   f e h g }
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    
    // shuffle { b a c d   f e h g } into { d c b a   h g f e }
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    
    // shuffle { d c b a   h g f e } into { h g f e   d c b a }
    return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

// -----------------------------------------------------------------------------
// swap bytes (character arrays)

// 4-byte float
float ReverseFloat( const float inFloat ) {
    
    float retVal;
    
    // convert inputs to character arrays
    char *floatToConvert = ( char* ) & inFloat;
    char *returnFloat = ( char* ) & retVal;
    
    // swap the bytes into a temporary buffer
    returnFloat[0] = floatToConvert[3];
    returnFloat[1] = floatToConvert[2];
    returnFloat[2] = floatToConvert[1];
    returnFloat[3] = floatToConvert[0];
    
    return retVal;
}

// 8-byte float
double ReverseFloat64( const double inFloat ) {
    
    double retVal;
    
    // convert inputs to character arrays
    char *floatToConvert = ( char* ) & inFloat;
    char *returnFloat = ( char* ) & retVal;
    
    // swap the bytes into a temporary buffer
    returnFloat[0] = floatToConvert[7];
    returnFloat[1] = floatToConvert[6];
    returnFloat[2] = floatToConvert[5];
    returnFloat[3] = floatToConvert[4];
    returnFloat[4] = floatToConvert[3];
    returnFloat[5] = floatToConvert[2];
    returnFloat[6] = floatToConvert[1];
    returnFloat[7] = floatToConvert[0];
    
    return retVal;
}

// -----------------------------------------------------------------------------
// general-case character swaps

static void reverseHex ( void* input, size_t numBytes ) {
    
    // output if no input, or if input can't have endianness
    if (input == NULL || numBytes < 2) return;
    
    // cast input as a character / hexidecimal list
    unsigned char* hexList = (unsigned char*) input;
    unsigned char tmp;
    
    // swap the bytes
    for (int i = 0; i < numBytes/2; i++) {
        tmp = hexList[i];
        hexList[i] = hexList[numBytes-i-1];
        hexList[numBytes-i-1] = tmp;
    }
}

static void reverseHexOutput ( void* input, void* output, size_t numBytes ) {
    if (input == NULL) return;
    unsigned char* inHexList = (unsigned char*) input;
    unsigned char* outHexList = (unsigned char*) output;
    
    for (int i = 0; i < numBytes; i++)
        outHexList[i] = inHexList[numBytes-i-1];
}



//==============================================================================
int main( ) { // run the program
//==============================================================================
    
    // int32
    int b = 112038;
    printf("%d\n", b);
    printHex( &b, sizeof(b) );
    int flipb = swap_int32(b);
    printHex( &flipb, sizeof(flipb) );
    
    // float
    printf("\n%f\n", (float)b);
    float bf = (float)b;
    printHex( &bf, sizeof(bf) );
    float flipbf = ReverseFloat(bf);
    printHex( &flipbf, sizeof(flipbf) );
    
    // int64
    long long int c = 1354684321356544;
    printf("\n%lld\n", c);
    printHex( &c, sizeof(c) );
    long long int flipc = swap_int64(c);
    printHex( &flipc, sizeof(flipc) );
    
    // double
    printf("\n%f\n", (double)c);
    double cf = (double)c;
    printHex( &cf, sizeof(cf) );
    double flipcf = ReverseFloat64(cf);
    printHex( &flipcf, sizeof(flipcf) );
    
    // generic endianness (edit input)
    printf("\n%f\n", (double)c);
    printHex( &cf, sizeof(cf) );
    reverseHex( &cf, sizeof(cf) );
    printHex( &cf, sizeof(cf) );
    printf("\n");
    
    // generic endianness (keep input, swap is an output)
    double input = (double)c, output;
    printHex( &input, sizeof(input) );
    reverseHexOutput( &input, &output, sizeof(input) );
    printHex( &output, sizeof(output) );
    printf("\n");
    
    return 0;
}




