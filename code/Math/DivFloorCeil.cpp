int CEIL(int a, int b) {
  return (a >= 0 ? (a + b - 1) / b : a / b);
}

int FLOOR(int a, int b) {
  return (a >= 0 ? a / b : (a - b + 1) / b);
}