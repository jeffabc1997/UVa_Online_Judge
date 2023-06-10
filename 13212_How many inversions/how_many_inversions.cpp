#include <iostream>
#include <vector>
#include <climits>
using namespace std;
/* modify merge sort */
long long int inv = 0;
void ms(vector<int>&, int, int);
void merge(vector<int>& , int, int , int );
void printarr(vector<int> &a) {
    for(int x: a) {
        cout << x << " ";
    }
    cout << endl;
}
void bf(vector<int>& a) {
    int n = a.size();
    int total_inv = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] > a[j]) {
                total_inv++;
            }
        }
    }
    cout << "brute force: " << total_inv << endl;
    
}
void session(int n) {
    vector<int> a(n);
    for(int i= 0; i < n; i++) {
        cin >> a[i];
    }
    //bf(a);
    ms(a, 0, n-1);
    cout <<inv << endl;
    //cout << "-----------" << endl;
    inv = 0;
}
void ms(vector<int>& a, int l, int r) {
    if(l >= r) return;
    int m = (l+r) /2;
    // cout << " begin "l;
    // printarr(a);
    ms(a, l, m);
    // cout << " left ";
    // printarr(a);
    ms(a, m+1, r);
    // cout << " right ";
    // printarr(a);
    merge(a, l, m, r);
    // cout << " finish: ";
    // printarr(a);
    
}
void merge(vector<int>& a, int l, int m, int r) {
    vector<int> left = vector<int>(a.begin()+l, a.begin() + m+1);
    vector<int> right = vector<int>(a.begin()+m+1, a.begin()+r+1);
    left.push_back(INT_MAX);
    right.push_back(INT_MAX);
    int i = 0, j = 0;
    int n1 = m-l;
    while(l <= r) {
        if(left[i] > right[j]) {
            a[l++] = right[j++];
            inv += n1 - i + 1;
        } else {
            a[l++] = left[i++];
        }
    }
}

int main() {
    int n = 0;
    cin >> n;
    while(n) {
        session(n);       
        cin >> n;
    }
    return 0;
}

// cout << " a " ;
    // printarr(a);
    // cout << "Left: ";
    // printarr(left);
    // cout <<"M: " << m << endl;
    // cout << "Right: ";
    // printarr(right);