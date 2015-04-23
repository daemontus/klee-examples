

int gcd (int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int main(int argc, void** argv) {
  int a;
  int b;
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");
  klee_assume(a > b);
  klee_assume(a > 0);
  klee_assume(b > 0);
  return gcd(a,b);
}
