//
// Created by cmtheit on 23-6-13.
//

class Abc {
public:
    operator int();
};

Abc::operator int() {
    return 0;
}

int main() {
    Abc l;
    l + 10 * l;
}