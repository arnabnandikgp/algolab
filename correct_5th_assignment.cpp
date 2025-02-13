#include <iostream>
#include <cstdlib>

using namespace std;

// Structure to represent a rectangle
struct Rectangle {
    double x, y, width, height;
};

// Structure to represent a boundary point
struct Point {
    double x, y;
};

// Function to find a vertical piercing line in O(n) time
double find_piercing_line(Rectangle *rects, int n) {
    double min_x = rects[0].x, max_x = rects[0].x + rects[0].width;
    for (int i = 1; i < n; i++) {
        if (rects[i].x < min_x) min_x = rects[i].x;
        if (rects[i].x + rects[i].width > max_x) max_x = rects[i].x + rects[i].width;
    }
    return (min_x + max_x) / 2.0;  // Ensure double division
}

// Function to merge two boundaries
Point* merge_boundaries(Point *left, int left_size, Point *right, int right_size, int &merged_size) {
    Point *merged = new Point[left_size + right_size];
    int i = 0, j = 0, k = 0;
    
    double left_height = 0, right_height = 0, curr_height = 0;
    
    while (i < left_size && j < right_size) {
        double x;
        if (left[i].x < right[j].x) {
            x = left[i].x;
            left_height = left[i].y;
            i++;
        } else {
            x = right[j].x;
            right_height = right[j].y;
            j++;
        }
        double max_h = (left_height > right_height) ? left_height : right_height;
        if (max_h != curr_height) {
            merged[k].x = x;
            merged[k].y = max_h;
            k++;
            curr_height = max_h;
        }
    }
    
    while (i < left_size) {
        merged[k] = left[i];
        k++;
        i++;
    }
    
    while (j < right_size) {
        merged[k] = right[j];
        k++;
        j++;
    }

    merged_size = k;
    return merged;
}

// Function to compute the boundary using divide and conquer
Point* compute_boundary(Rectangle *rects, int n, int &size) {
    if (n == 1) {
        size = 4;
        Point *boundary = new Point[4];
        boundary[0].x = rects[0].x;
        boundary[0].y = rects[0].y;
        boundary[1].x = rects[0].x;
        boundary[1].y = rects[0].y + rects[0].height;
        boundary[2].x = rects[0].x + rects[0].width;
        boundary[2].y = rects[0].y + rects[0].height;
        boundary[3].x = rects[0].x + rects[0].width; 
        boundary[3].y =  rects[0].y;        
        return boundary;
    }

    double piercing_x = find_piercing_line(rects, n);
    
    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++) {
        if (rects[i].x + rects[i].width <= piercing_x) left_count++;
        else right_count++;
    }

    Rectangle *left_rects = new Rectangle[left_count];
    Rectangle *right_rects = new Rectangle[right_count];

    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (rects[i].x + rects[i].width <= piercing_x)
            left_rects[l++] = rects[i];
        else
            right_rects[r++] = rects[i];
    }

    int left_size, right_size;
    Point *left_boundary = compute_boundary(left_rects, left_count, left_size);
    Point *right_boundary = compute_boundary(right_rects, right_count, right_size);
    
    delete[] left_rects;
    delete[] right_rects;

    Point *merged_boundary = merge_boundaries(left_boundary, left_size, right_boundary, right_size, size);
    
    delete[] left_boundary;
    delete[] right_boundary;

    return merged_boundary;
}


int main() {
    int n;
    cout << "Enter number of rectangles: ";
    cin >> n;

    Rectangle *rects = new Rectangle[n];
    cout << "Enter rectangles (x y width height):\n";
    for (int i = 0; i < n; i++) {
        cin >> rects[i].x >> rects[i].y >> rects[i].width >> rects[i].height;
    }

    int boundary_size;
    Point *boundary = compute_boundary(rects, n, boundary_size);

    cout << "Boundary: ";
    for (int i = 0; i < boundary_size; i++) {
        cout << "(" << boundary[i].x << "," << boundary[i].y << ")";
        if (i != boundary_size - 1) cout << ",";
    }
    cout << endl;

    delete[] rects;
    delete[] boundary;

    return 0;
}