#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>

// Utility function to print arrays or vectors
template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Merge Sort implementation
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    std::cout << "Merging: ";
    printVector(leftArr);
    printVector(rightArr);

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        std::cout << "Dividing: ";
        printVector(std::vector<int>(arr.begin() + left, arr.begin() + mid + 1));
        printVector(std::vector<int>(arr.begin() + mid + 1, arr.begin() + right + 1));
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort implementation
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        std::cout << "Pivot: " << arr[pi] << " | ";
        printVector(arr);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Maximum Subarray Problem (Kadane’s Algorithm)
int maximumSubarray(const std::vector<int>& arr, int& start, int& end) {
    int maxSum = std::numeric_limits<int>::min();
    int currentSum = 0;
    int tempStart = 0;

    start = 0;
    end = 0;

    for (int i = 0; i < arr.size(); ++i) {
        currentSum += arr[i];
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
        if (currentSum < 0) {
            currentSum = 0;
            tempStart = i + 1;
        }
    }

    return maxSum;
}

// Closest Pair of Points (Divide and Conquer)
struct Point {
    int x, y;
};

// Distance between two points
double distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force method for finding the closest pair
double closestPairBruteForce(std::vector<Point>& points, int left, int right) {
    double minDist = std::numeric_limits<double>::max();
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            double dist = distance(points[i], points[j]);
            minDist = std::min(minDist, dist);
        }
    }
    return minDist;
}

// Find the closest distance in a strip
double stripClosest(std::vector<Point>& strip, double d) {
    double minDist = d;
    std::sort(strip.begin(), strip.end(), [](const Point& p1, const Point& p2) { return p1.y < p2.y; });

    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = std::min(minDist, distance(strip[i], strip[j]));
        }
    }
    return minDist;
}

// Closest Pair of Points using Divide and Conquer
double closestPair(std::vector<Point>& points, int left, int right) {
    if (right - left <= 3) return closestPairBruteForce(points, left, right);

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = closestPair(points, left, mid);
    double dr = closestPair(points, mid + 1, right);

    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (std::abs(points[i].x - midPoint.x) < d) strip.push_back(points[i]);
    }

    return std::min(d, stripClosest(strip, d));
}

// Function to check login credentials
bool login() {
    /*
UserId=Moinul
Password=Moinul909
*/
    std::string userId, password;
    std::cout << "Enter UserId: ";
    std::cin >> userId;
    std::cout << "Enter Password: ";
    std::cin >> password;

    // Check if the credentials match
    if (userId == "Moinul" && password == "Moinul909") {
        std::cout << "Login successful!\n";
        return true;
    } else {
        std::cout << "Invalid UserId or Password. Access denied!\n";
        return false;
    }
}

int main() {
    if (!login()) {
        return 0;
    }

    int choice;
    std::cout << "Divide and Conquer Algorithm Projects\n";
    std::cout << "1. Merge Sort Visualization\n";
    std::cout << "2. Quick Sort Visualization\n";
    std::cout << "3. Maximum Subarray Problem (Kadane’s Algorithm)\n";
    std::cout << "4. Closest Pair of Points\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
            std::cout << "Original Array: ";
            printVector(arr);
            mergeSort(arr, 0, arr.size() - 1);
            std::cout << "Sorted Array: ";
            printVector(arr);
            break;
        }
        case 2: {
            std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
            std::cout << "Original Array: ";
            printVector(arr);
            quickSort(arr, 0, arr.size() - 1);
            std::cout << "Sorted Array: ";
            printVector(arr);
            break;
        }
        case 3: {
            std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
            int start, end;
            int maxSum = maximumSubarray(arr, start, end);
            std::cout << "Maximum Subarray Sum: " << maxSum << "\n";
            std::cout << "Subarray: ";
            for (int i = start; i <= end; ++i) std::cout << arr[i] << " ";
            std::cout << std::endl;
            break;
        }
        case 4: {
            std::vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
            std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
            double minDist = closestPair(points, 0, points.size() - 1);
            std::cout << "Closest Pair Distance: " << std::setprecision(6) << minDist << std::endl;
            break;
        }
        default:
            std::cout << "Invalid option!";
    }
    return 0;
}

