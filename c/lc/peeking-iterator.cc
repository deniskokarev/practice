class PeekingIterator : public Iterator {
	bool end;
	int nxt;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
		if (Iterator::hasNext()) {
			nxt = Iterator::next();
			end = false;
		} else {
			nxt = INT_MIN;
			end = true;
		}
	}
	
	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return nxt;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		if (!end) {
			int r = nxt;
			if (Iterator::hasNext())
				nxt = Iterator::next();
			else
				end = true;
			return r;
		} else {
			return INT_MIN;
		}
	}
	
	bool hasNext() const {
		return !end;
	}
};
