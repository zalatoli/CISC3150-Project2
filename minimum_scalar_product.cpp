//Minimum Scalar Product
//Zakareya Alatoli

//Sort one vector in ascending order and the other in descending order
//****************************************************************************************
//****************************************************************************************
//Mergesort code and comments from http://www.cprogramming.com/tutorial/computersciencetheory/merge.html
//****************************************************************************************
//****************************************************************************************
/* Helper function for finding the max of two numbers */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int max(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/* left is the index of the leftmost element of the subarray; right is one
 * past the index of the rightmost element */
void merge_helper(vector<int>& input, int left, int right, int *scratch)
{
    /* base case: one element */
    if(right == left + 1)
    {
        return;
    }
    else
    {
        int i = 0;
        int length = right - left;
        int midpoint_distance = length/2;
        /* l and r are to the positions in the left and right subarrays */
        int l = left, r = left + midpoint_distance;

        /* sort each subarray */
        merge_helper(input, left, left + midpoint_distance, scratch);
        merge_helper(input, left + midpoint_distance, right, scratch);

        /* merge the arrays together using scratch for temporary storage */
        for(i = 0; i < length; i++)
        {
            /* Check to see if any elements remain in the left array; if so,
             * we check if there are any elements left in the right array; if
             * so, we compare them.  Otherwise, we know that the merge must
             * use take the element from the left array */
            if(l < left + midpoint_distance &&
                    (r == right || max(input[l], input[r]) == input[l]))
            {
                scratch[i] = input[l];
                l++;
            }
            else
            {
                scratch[i] = input[r];
                r++;
            }
        }
        /* Copy the sorted subarray back to the input */
        for(i = left; i < right; i++)
        {
            input[i] = scratch[i - left];
        }
    }
}

/* mergesort returns true on success.  Note that in C++, you could also
 * replace malloc with new and if memory allocation fails, an exception will
 * be thrown.  If we don't allocate a scratch array here, what happens?
 *
 * Elements are sorted in reverse order -- greatest to least */

int mergesort(vector<int>& input)
{
    int *scratch = new int[input.size()];//replaced from the original code
    if(scratch != NULL)
    {
        merge_helper(input, 0, input.size(), scratch);
        delete[] scratch;
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(){
    int num_values;
    int val;
    vector<int> vec1, vec2;
    cout << "How many values are in each vector (must be the same for multiplication to work)? ";
    cin >> num_values;
    if(num_values <= 0){
        cout << "Vectors cannot have " << num_values << " or less elements!";
        return 0;
    }
    cout << "Enter values of the first vector: ";
    for(int i=0; i<num_values; i++){
        cin >> val;
        vec1.push_back(val);
    }
    cout << "Enter values of the second vector: ";
        for(int i=0; i<num_values; i++){
        cin >> val;
        vec2.push_back(val);
    }

    mergesort(vec1);
    mergesort(vec2);
    //Both can be in the same kind of order because we can just iterate through the elements
    //of one vector from end to beginning
    int min_scalar_product = 0;
    cout << "Optimal vector permutations: \n";
    for(int i=0; i<num_values; i++){
        cout << "| " << vec1[i] << " |\t| " << vec2[num_values-1-i] << " |\n";
        min_scalar_product += (vec1[i] * vec2[num_values-1-i]);
    }
    /* The largest values of the first vector are multiplied by the
    smallest values of the second vector, this produces the smallest
    possible scalar product */
    cout << "Minimum scalar product: " << min_scalar_product;

    return 0;
}
