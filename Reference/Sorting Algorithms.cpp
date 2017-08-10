#include <iostream>
#include <vector>
#include <string>
#include <chrono> // for timing

#define vi std::vector<int>

// Compile & run - 
// g++ -std=c++14 sorting.cpp -o sorting && ./sorting

void display(std::string, vi);
// Simple, In-place - Insertion, Selection sort
vi insertion_sort(vi);
vi selection_sort(vi);
// Bubble sort
vi bubble_sort(vi);
// Efficient - Merge, Heap, Quick sort
vi merge_sort(vi);
vi merge(vi, vi);
vi quick_sort(vi);
vi heap_sort(vi);



int main () {
	vi arr = {31, 22, 45, 61, 12, 19, 54, 27};

	vi ins_arr = insertion_sort(arr);
	display("Insertion Sort", ins_arr);

	vi sel_arr = selection_sort(arr);
	display("Selection Sort", sel_arr);

	vi bub_arr = bubble_sort(arr);
	display("Bubble    Sort", bub_arr);

	vi mer_arr = merge_sort(arr);
	display("Merge     Sort", mer_arr);

	vi qui_arr = quick_sort(arr);
	display("Quick     Sort", qui_arr);

	vi hea_arr = quick_sort(arr);
	display("Heap      Sort", hea_arr);

	vi stl_arr = arr;
	// this sort internally uses a combination of quick sort initially 
	// and then moves to heap sort below a certain size threshold
	std::sort(stl_arr.begin(), stl_arr.end());
	display("STL       Sort", stl_arr);

	return 0;
}



void display(std::string msg, vi arr) {
	std::cout << "[" << msg << "]:\t";
	for (auto x: arr) {
		std::cout << x << (x != arr[arr.size()-1] ? ", " : "\n");
	}
}


vi insertion_sort(vi arr) {
	int n = arr.size();
	for ( int i=1; i<n; i++ ) {
		// insert arr[i] to sorted array arr[0...i]
		int val = arr[i], pos=0;

		// find position to put val in
		while (arr[pos] < val && pos < i) pos++;

		// shift array elements by 1 position from pos+1 till i
		for(int j=i; j>pos; j--) {
			arr[j] = arr[j-1];
		}

		// insert val to arr[pos]
		arr[pos] = val;
	}

	return arr;
}

vi selection_sort(vi arr) {
	int n = arr.size();
	for (int i=0; i < n-1; i++) {
		// select smallest element from arr[i...n-1]
		int pos=i, val=arr[i];
		for (int j=i+1; j<n; j++) {
			if (arr[j] < val) {
				val = arr[j];
				pos = j;
			}
		}

		// shift array elements by 1 position from i+1 till pos
		for (int j=pos; j>i; j--) {
			arr[j] =  arr[j-1];
		} 

		// move val to arr[i]
		arr[i] = val;
	}

	return arr;
}

vi bubble_sort(vi arr) {
	int n = arr.size();
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			// pairwise comparison for all elements
			if (arr[i] > arr[j]) {
				std::swap(arr[i], arr[j]);
			}
		}
	}

	return arr;
}

vi merge(vi l, vi r) {
	// merge two sorted arrays
	vi res;

	// display("L", l);
	// display("R", r);

	while (!l.empty() && !r.empty()) {
		if (l[0] > r[0]) {
			res.push_back(r[0]);
			r.erase(r.begin());
		}
		else {
			res.push_back(l[0]);
			l.erase(l.begin());
		}
	}

	while (!l.empty()) {
		res.push_back(l[0]);
		l.erase(l.begin());
	}

	while (!r.empty()) {
		res.push_back(r[0]);
		r.erase(r.begin());
	}

	// display("Merged", res);

	return res;
}

vi merge_sort(vi arr) {
	int n = arr.size();
	if (n <= 1) {
		// arr of zero or one elements is sorted, by definition
		return arr;
	}
	else {
		// break into two parts & recursively sort
		vi l, r;
		for(int i=0; i<n; i++) {
			if (i < int(n/2)) {
				l.push_back(arr[i]);
			}
			else {
				r.push_back(arr[i]);
			}
		}

		l = merge_sort(l);
		r = merge_sort(r);

 		return merge(l, r);
	}
}


vi quick_sort(vi arr) {
	int n = arr.size();
	
	if (n <= 1) {
		// arr of zero or one elements is sorted, by definition
		return arr;
	}

	// choose pivot
	int pivot = arr[rand()%n];

	// low, high and final result
	vi l, h, res;

	for (int i=0; i<n; i++) {
		// partition arr using pivot
		if (arr[i] < pivot) {
			l.push_back(arr[i]);
		}
		else if (arr[i] > pivot) {
			h.push_back(arr[i]);
		}
	}

	// display("L", l);
	// display("H", h);

	l = quick_sort(l);
	h = quick_sort(h);

	// append low to result
	res = l;
	// append pivot to result
	res.push_back(pivot);
	// append high to result
	res.insert(res.end(), h.begin(), h.end());

	return res;
}


vi heap_sort(vi arr) {
	int n = arr.size();

	// build max heap
	std::make_heap(arr.begin(), arr.end());

	for (int i=0; i<n-1; i++) {
		// move max element to back
		std::pop_heap(arr.begin(), arr.end() - i);
		// heapify remaining
		std::make_heap(arr.begin(), arr.end() - i - 1);
	}

	return arr;
}


