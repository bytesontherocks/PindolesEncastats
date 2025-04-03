# Checksums and compression

## Checksums

### Parity

b10110110 -> 5 x 1's (if parity is even we will append 1 to make a total of 6 1's and if it is odd we will append 0) -> b10110110P (P->parity bit)

With 1 bit parity we can detect 1 bit flip

10 11 01 10 
1  0  1  0
 0     1 
    1       P=1
        0
        
### XOR


- count the number of bits set in an integer