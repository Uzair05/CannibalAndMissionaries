#include <iostream>
#include <vector>

struct Node {
    int C{3};
    int M{3};
};

int heuristic(Node h) { return h.C + h.M; }

void findSol(Node head, bool boatOnLeft = true) {
    std::vector<Node> possible_combinations{};

    if (boatOnLeft) {
        possible_combinations.push_back({head.C - 1, head.M});
        possible_combinations.push_back({head.C - 1, head.M - 1});
        possible_combinations.push_back({head.C, head.M - 1});
        possible_combinations.push_back({head.C - 2, head.M});
        possible_combinations.push_back({head.C, head.M - 2});
    } else {
        Node onRight = {3 - head.C, 3 - head.M};
        for (int i{1}; i <= 2 && i <= onRight.C; i++) {
            possible_combinations.push_back({head.C + i, head.M});
        }
        for (int i{1}; i <= 2 && i <= onRight.M; i++) {
            possible_combinations.push_back({head.C, head.M + i});
        }

        if (onRight.M > 1 and onRight.C > 1) {
            possible_combinations.push_back({head.C + 1, head.M + 1});
        }
    }

    for (const auto& i : possible_combinations) {
        std::cout << "C " << i.C << " : M " << i.M << "\n";
    }
}

int main() {
    Node start_situation{1, 1};
    findSol(start_situation, false);

    // std::vector<Node> sol{findSol(start_situation)};

    // for(const auto& i: sol){
    //     std::cout << "C " << i.C << " : M " << i.M <<"\n";
    // }std::cout << std::endl;

    return 0;
}
