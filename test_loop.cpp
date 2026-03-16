#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2};
    for(int i=0; i<3; i++) {
        std::cout << v[i] << " ";
    }
    return 0;
}
