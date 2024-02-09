#include <stdio.h>
// gcd(a,m) = 1 then a inverse exists
// ax + my = gcd(a,m)
// x = y1 – (b/a) * x1
//  y = x1
 
// Funtion to compute gcd and linear coefficient 
int gcdExtended(int a, int b, int* x, int* y) {
    // initial condition
    if (a==0) { 
        *x = 0;
        *y = 1;
        return b;
    }

    int x1,y1;
    int g = gcdExtended(b%a, a, &x1, &y1); //recursive call
    //updating x and y
    *x = y1 - ((b/a) * x1) ;
    *y = x1;

    return g;
}

// Function to find modulo inverse of a
void modInverse(int a, int n) {
    int x,y;
    int gcd = gcdExtended(a, n, &x, &y);
    if(gcd!=1) {
        printf("Inverse doesn't exist");
    }
    else {
        x = (x+n) % n; //handles if inverse is negative
        printf("%d is inverse of %d mod %d", x, a, n);
    }
}

int main() {
    //Input
    int a, n;
    printf("a: ");
    scanf("%d",&a);
    printf("n: ");
    scanf("%d",&n);
    
    //Function Call
    modInverse(a,n);

    return 0;
}