// To fix the file's spaces
// sed -i 's/\xC2\xA0/ /g' task3.cpp
// To compile
// g++ -std=c++17 -O2 -Wall -Wextra task3.cpp -o task3

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <queue>
#include <string>

enum class AccessPattern {
    FREQUENT_FRONT_BACK,    // Queue-like operations
    FREQUENT_MIDDLE,        // Insert/delete at arbitrary positions
    FREQUENT_RANDOM_ACCESS, // Array-like access by index
    FREQUENT_SEARCH,        // Finding specific elements
    ORDERED_ITERATION,      // Need sorted order
    PRIORITY_PROCESSING,    // Process by importance
    UNIQUE_ELEMENTS,        // Set-like behavior
    KEY_VALUE_PAIRS         // Dictionary-like behavior
};

class ContainerSelector {
private:
    struct ContainerRecommendation {
        std::string containerType;
        std::string rationale;
        std::string timeComplexity;
        std::string alternativeOptions;
    };

    ContainerRecommendation analyzeRequirements(AccessPattern pattern, bool needsOrder, bool uniqueElements, int expectedSize) {
        ContainerRecommendation rec;

        switch (pattern) {
        case AccessPattern::FREQUENT_FRONT_BACK:
            if (needsOrder && expectedSize < 10000) {
                rec.containerType = "std::deque<T>";
                rec.rationale = "Efficient front/back operations with random access";
                rec.timeComplexity = "O(1) front/back, O(1) random access";
                rec.alternativeOptions = "std::queue<T> for strict FIFO, std::stack<T> for LIFO";
            }
            else {
                rec.containerType = "std::list<T>";
                rec.rationale = "Optimal for frequent front/back operations without random access needs";
                rec.timeComplexity = "O(1) front/back operations";
                rec.alternativeOptions = "std::deque<T> if random access needed";
            }
            break;

        case AccessPattern::FREQUENT_MIDDLE:
            rec.containerType = "std::list<T>";
            rec.rationale = "Constant time insertion/deletion at any position";
            rec.timeComplexity = "O(1) insert/delete at known position";
            rec.alternativeOptions = "std::deque<T> for better cache locality with moderate middle operations";
            break;

        case AccessPattern::FREQUENT_RANDOM_ACCESS:
            rec.containerType = "std::vector<T>";
            rec.rationale = "Contiguous memory provides fastest random access";
            rec.timeComplexity = "O(1) random access, O(1) amortized back insertion";
            rec.alternativeOptions = "std::deque<T> if front insertion also needed";
            break;

        case AccessPattern::FREQUENT_SEARCH:
            if (needsOrder) {
                rec.containerType = "std::set<T> or std::map<K,V>";
                rec.rationale = "Logarithmic search with maintained sorted order";
                rec.timeComplexity = "O(log n) search, insert, delete";
                rec.alternativeOptions = "std::multiset<T> for duplicate values";
            }
            else {
                rec.containerType = "std::unordered_set<T> or std::unordered_map<K,V>";
                rec.rationale = "Hash-based containers provide fastest average search";
                rec.timeComplexity = "O(1) average case search, insert, delete";
                rec.alternativeOptions = "std::set<T> if order or range queries needed";
            }
            break;

        case AccessPattern::PRIORITY_PROCESSING:
            rec.containerType = "std::priority_queue<T>";
            rec.rationale = "Heap-based structure always provides highest priority element";
            rec.timeComplexity = "O(1) top access, O(log n) insert/remove";
            rec.alternativeOptions = "std::multimap<Priority,T> for stable priority ordering";
            break;

        default:
            rec.containerType = "std::vector<T>";
            rec.rationale = "General-purpose container with good all-around performance";
            rec.timeComplexity = "O(1) random access and back operations";
            rec.alternativeOptions = "Analyze specific usage patterns for optimization";
        }

        return rec;
    }

public:
    void demonstrateContainerSelection() {
        std::cout << "=== STL CONTAINER SELECTION DECISION FRAMEWORK ===" << std::endl;
        std::cout << "Analyzing different application scenarios:\n" << std::endl;

        // Scenario 1: Task Queue System
        std::cout << "SCENARIO 1: Task Queue Processing System" << std::endl;
        std::cout << "Requirements: FIFO processing, frequent front/back operations" << std::endl;
        auto rec1 = analyzeRequirements(AccessPattern::FREQUENT_FRONT_BACK, false, false, 5000);
        printRecommendation(rec1);

        // Scenario 2: Text Editor Buffer
        std::cout << "\nSCENARIO 2: Text Editor Buffer" << std::endl;
        std::cout << "Requirements: Frequent insertion/deletion at cursor position" << std::endl;
        auto rec2 = analyzeRequirements(AccessPattern::FREQUENT_MIDDLE, false, false, 50000);
        printRecommendation(rec2);

        // Scenario 3: Game Physics Array
        std::cout << "\nSCENARIO 3: Game Physics Object Array" << std::endl;
        std::cout << "Requirements: Frequent random access, mathematical operations" << std::endl;
        auto rec3 = analyzeRequirements(AccessPattern::FREQUENT_RANDOM_ACCESS, false, false, 10000);
        printRecommendation(rec3);

        // Scenario 4: User Database
        std::cout << "\nSCENARIO 4: User Database with Sorted Reports" << std::endl;
        std::cout << "Requirements: Fast user lookup, ordered iteration for reports" << std::endl;
        auto rec4 = analyzeRequirements(AccessPattern::FREQUENT_SEARCH, true, false, 100000);
        printRecommendation(rec4);

        // Scenario 5: High-Frequency Trading
        std::cout << "\nSCENARIO 5: High-Frequency Trading System" << std::endl;
        std::cout << "Requirements: Fastest possible symbol lookup, no order needed" << std::endl;
        auto rec5 = analyzeRequirements(AccessPattern::FREQUENT_SEARCH, false, false, 50000);
        printRecommendation(rec5);

        // Scenario 6: Priority-Based Alert System
        std::cout << "\nSCENARIO 6: Critical Alert Processing" << std::endl;
        std::cout << "Requirements: Always process highest priority alerts first" << std::endl;
        auto rec6 = analyzeRequirements(AccessPattern::PRIORITY_PROCESSING, false, false, 1000);
        printRecommendation(rec6);
    }

    void printRecommendation(const ContainerRecommendation& rec) {
        std::cout << "  RECOMMENDED: " << rec.containerType << std::endl;
        std::cout << "  RATIONALE: " << rec.rationale << std::endl;
        std::cout << "  COMPLEXITY: " << rec.timeComplexity << std::endl;
        std::cout << "  ALTERNATIVES: " << rec.alternativeOptions << std::endl;
    }

    void provideSelectionGuidelines() {
        std::cout << "\n=== CONTAINER SELECTION QUICK REFERENCE ===" << std::endl;

        std::cout << "\n- SEQUENCE CONTAINERS:" << std::endl;
        std::cout << "• vector<T>     - Default choice, best random access, cache-friendly" << std::endl;
        std::cout << "• list<T>       - Frequent middle insert/delete, no random access needed" << std::endl;
        std::cout << "• deque<T>      - Queue operations + random access, good compromise" << std::endl;

        std::cout << "\n- ASSOCIATIVE CONTAINERS:" << std::endl;
        std::cout << "• map<K,V>      - Key-value pairs with sorted keys, range queries" << std::endl;
        std::cout << "• unordered_map - Key-value pairs, fastest lookup, no order" << std::endl;
        std::cout << "• set<T>        - Unique elements with sorted order" << std::endl;
        std::cout << "• unordered_set - Unique elements, fastest membership testing" << std::endl;

        std::cout << "\n- CONTAINER ADAPTORS:" << std::endl;
        std::cout << "• stack<T>      - LIFO operations (undo systems, recursion)" << std::endl;
        std::cout << "• queue<T>      - FIFO operations (task processing, BFS)" << std::endl;
        std::cout << "• priority_queue- Priority-based processing (event systems)" << std::endl;

        std::cout << "\n- SELECTION DECISION TREE:" << std::endl;
        std::cout << "1. Need key-value mapping? -> map/unordered_map" << std::endl;
        std::cout << "2. Need unique elements only? -> set/unordered_set" << std::endl;
        std::cout << "3. Need priority processing? -> priority_queue" << std::endl;
        std::cout << "4. Need LIFO/FIFO only? -> stack/queue" << std::endl;
        std::cout << "5. Need frequent middle insert/delete? -> list" << std::endl;
        std::cout << "6. Need random access + end operations? -> vector" << std::endl;
        std::cout << "7. Need both-end operations + random access? -> deque" << std::endl;

        std::cout << "\n- PERFORMANCE CONSIDERATIONS:" << std::endl;
        std::cout << "• Small datasets (<1000): Performance differences often negligible" << std::endl;
        std::cout << "• Large datasets (>100k): Container choice becomes critical" << std::endl;
        std::cout << "• Memory-constrained: Prefer ordered containers (no hash overhead)" << std::endl;
        std::cout << "• CPU-bound operations: Prefer unordered containers for speed" << std::endl;
    }
};

int main() {
    std::cout << "STL CONTAINER SELECTION FRAMEWORK" << std::endl;
    std::cout << "=================================" << std::endl;

    ContainerSelector selector;
    selector.demonstrateContainerSelection();
    selector.provideSelectionGuidelines();

    return 0;
}