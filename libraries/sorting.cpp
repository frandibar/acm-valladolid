///////////////////////////////////////////////////////////////////////////
template <class T>
int partition(vector<T> v, int l, int h)
// returns the index of partition, used with quicksort
{
	int p = h;	// p pivot element index
	int firsthigh = l;	// divider position for pivot
	for (int i = l; i < h; i++) {
		if (v[i] < v[p]) {
			swap(v[i], v[firsthigh]);
			firsthigh++;
		}
	}
	swap(v[p], v[firsthigh]);
	return 0;
}

///////////////////////////////////////////////////////////////////////////
template <class T>
void quicksort(vector<T> v, int l, int h)
{
	if ((h - l) > 0) {
		int p = partition(v, l, h);	// index of partition
		quicksort(s, l, p-1);
		quicksort(s, p+1, h);
	}
}

