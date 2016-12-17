#include "Node.h"
#include <unordered_map>
using namespace std;

//comparator used to modify priority queue from max to min.
struct compareNode : binary_function<Node*, Node*, bool>{
	bool operator()(Node* l, Node* r) {
		return l->element_value > r->element_value;
	}
};

/*
 * merge function
 * @param Input arrs to be merged
 * @param Input arrs_length of arrs
 * @param Output re_arr is merged array
 * @param Output re_size is length of merged array
 * @return function works well (0) or not (1)
 */
int merge(int *arrs[], int arrs_length[], int *re_arr, int & re_size){
	int k = sizeof(arrs_length);

	//declare min priority queue of nodes
	priority_queue <Node*, vector <Node*>, compareNode> pq;
	
	//create nodes out of first element of each array and push nodes to initialize pq
	for (int i = 0; i <= k; i++) {
		Node *temp_node = new Node(*(arrs[i]),i);
		pq.push(temp_node);
		arrs_length[i]--;
		arrs[i]++;
	}
	
	//as long as pq still had nodes, assign element value of top node to output array. Then pop that node out of queue and
	//push node from array the same array into pq
	int outputindex = 0;
	while (!pq.empty()) {
		Node *temp_node = pq.top();	
		re_arr[outputindex] = (*temp_node).element_value ;
		pq.pop();
		outputindex++;
		int i = temp_node->arr_num;

		//if array empty, delete node, continue to next iteration
		if (NULL ==  arrs_length[i]) {
			delete temp_node;
			continue;
		}

		temp_node->element_value = *(arrs[(*temp_node).arr_num]);
		pq.push(temp_node);
		arrs_length[i]--;
		arrs[i]++;
	}
    return 0;
}

/*
 * intersecteion function
 * @param Input arrs to be computed
 * @param Input arrs_length of arrs
 * @param Output re_arr is intersection
 * @param Output re_size is length of intersection
 * @return function works well (0) or not (1)
 */
int intersect(int *arrs[], int arrs_length[], int *re_arr, int & re_size) {
	
	//declare 4 unordered maps, one for each each of first 4 arrays
		unordered_map<int, int> umap0;
		unordered_map<int, int> umap1;
		unordered_map<int, int> umap2;
		unordered_map<int, int> umap3;

	//populate the maps with each of the first 4 arrays
		for (int i0 = 0; i0 < arrs_length[0]; i0++) {
			umap0[arrs[0][i0]];
		}
	
		for (int i1 = 0; i1 < arrs_length[1]; i1++) {
			umap1[arrs[1][i1]];
		}
		
		for (int i2 = 0; i2 < arrs_length[2]; i2++) {
			umap2[arrs[2][i2]];
		}
	
		for (int i3 = 0; i3 < arrs_length[3]; i3++) {
			umap3[arrs[3][i3]];
		}
	
	//check which elements of the 5th array appear in each map, if an element appears in every one of the maps, put into output array.
		int outputindex = 0;
		for (int i = 0; i < arrs_length[4]; i++) {
			if (umap0.count(arrs[4][i]) > 0 && umap1.count(arrs[4][i]) > 0 && umap2.count(arrs[4][i]) > 0 && umap3.count(arrs[4][i]) > 0) {
				re_arr[outputindex] = arrs[4][i];
				outputindex++;
			}
		re_size = outputindex;
		}
	
	return 0;
}

int main(){
    //test case
    int * arrs[5];
    int arrs_length[5];
    int arr0[] = {1, 5, 8};
    int arr1[] = {1, 2, 3, 5, 7, 10, 11, 15};
    int arr2[] = {1, 4, 5, 6};
    int arr3[] = {1, 5, 9, 14, 16, 19};
    int arr4[] = {1, 2, 4, 5, 6, 9, 9};
    arrs[0] = arr0;
    arrs_length[0] = sizeof(arr0) / sizeof(int);
    arrs[1] = arr1;
    arrs_length[1] = sizeof(arr1) / sizeof(int);
    arrs[2] = arr2;
    arrs_length[2] = sizeof(arr2) / sizeof(int);
    arrs[3] = arr3;
    arrs_length[3] = sizeof(arr3) / sizeof(int);
    arrs[4] = arr4;
    arrs_length[4] = sizeof(arr4) / sizeof(int);
    cout << "Input:" << endl;
    for (int i = 0; i < 5; i ++){
        cout << "[";
        for (int j = 0; j < arrs_length[i] - 1; j ++){
            cout << arrs[i][j] << ", ";
        }
        cout << arrs[i][arrs_length[i] - 1] << "]" << endl;
    }
    //sum length
    int sum_length = 0;
    for (int i = 0; i < 5; i ++){
        sum_length += arrs_length[i];
    }

    //intersection manipulation
    //expected output
    //[1, 5]
    int * intersection = new int[sum_length];
    int intersect_length = sum_length;
    if (intersect(arrs, arrs_length, intersection, intersect_length) == 0){
        cout << "Output:" << endl << "[";
        for (int i = 0; i < intersect_length - 1; i ++){
            cout << intersection[i] << ",";
        }
        cout << intersection[intersect_length - 1] << "]" << endl;   
    }

	//merge manipulation
	//expected output
	//[1, 1, 1, 1, 1, 2, 2, 3, 4, 4, 5, 5, 5, 5, 5, 6, 6, 7, 8, 9, 9, 9, 10, 11, 14, 15, 16, 19]
	int * merged = new int[sum_length];
	int merge_length = sum_length;
	if (merge(arrs, arrs_length, merged, merge_length) == 0) {
		cout << "Output:" << endl << "[";
		for (int i = 0; i < merge_length - 1; i++) {
			cout << merged[i] << ",";
		}
		cout << merged[sum_length - 1] << "]" << endl;
	}

	system("PAUSE");
    return 0;
}
