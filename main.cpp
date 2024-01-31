#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Node {
    int C{3};
    int M{3};
};

auto heuristic = [](const Node& h) { return h.C + h.M; };

std::vector<Node> findSol(Node head, bool boatOnLeft = true) {
    std::vector<Node> solution{};
    std::vector<Node> possible_combinations{};

    if (boatOnLeft) {
        for (int i{1}; i <= 2 && i <= head.C; i++) {
            possible_combinations.push_back({head.C - i, head.M});
        }
        for (int i{1}; i <= 2 && i <= head.M; i++) {
            possible_combinations.push_back({head.C, head.M - i});
        }

        if (head.C >= 1 && head.M >= 1) {
            possible_combinations.push_back({head.C - 1, head.M - 1});
        }
    } else {
        Node onRight = {3 - head.C, 3 - head.M};
        for (int i{1}; i <= 2 && i <= onRight.C; i++) {
            possible_combinations.push_back({head.C + i, head.M});
        }
        for (int i{1}; i <= 2 && i <= onRight.M; i++) {
            possible_combinations.push_back({head.C, head.M + i});
        }

        if (onRight.M >= 1 && onRight.C >= 1) {
            possible_combinations.push_back({head.C + 1, head.M + 1});
        }
    }

    std::erase_if(possible_combinations, [boatOnLeft](const auto& n) {
        return (!boatOnLeft ? (((n.C - 1) > n.M) && (n.M > 0)) ||
                                  ((3 - n.C) > (3 - n.M) && (n.M < 3))
                            : ((n.C > n.M) && (n.M > 0)) ||
                                  (((3 - n.C) - 1) > (3 - n.M) && (n.M < 3)));
    });

    if (possible_combinations.size() == 0) return std::vector<Node>{};

    std::sort(possible_combinations.begin(), possible_combinations.end(),
              [](const Node& a, const Node& b) {
                  return heuristic(a) < heuristic(b);
              });

    if (auto it = std::find_if(possible_combinations.begin(),
                               possible_combinations.end(),
                               [](Node& n) { return (n.C + n.M) == 0; });
        it != possible_combinations.end()) {
        solution.push_back(std::move(*it));

    } else {
        for (const auto& pc : possible_combinations) {
            auto s = findSol(pc, !boatOnLeft);
            if (s.size() > 0) {
                solution.push_back(std::move(pc));
                for (const auto& s_ : s) solution.push_back(std::move(s_));
                break;
            }
        }
    }

    return solution;
}

int main() {
    Node start_situation;
    auto i = findSol(start_situation);

    bool boatOnLeft = false;
    for (const auto& c : i) {
        std::cout << "C: " << c.C << ", M: " << c.M << (boatOnLeft ? " B" : "")
                  << "\t\t";
        std::cout << (!boatOnLeft ? "B " : "  ") << "C: " << 3 - c.C
                  << ", M: " << 3 - c.M << "\n";
        boatOnLeft = !boatOnLeft;
    }

    return 0;
}
