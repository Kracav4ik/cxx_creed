int main() {
    int f0;
    int f1;
    f0 = f1 = 1;
    int i;
    while (i < 20) {
        int f2;
        f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
        i = i + 1;
    }
    return f1;
}
