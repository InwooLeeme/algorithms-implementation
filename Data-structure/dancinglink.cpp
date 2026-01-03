struct dlx{
    struct node{
        int row;
        int size;
        node* column;
        node* up;
        node* down;
        node* left;
        node* right;
    };

    void dlx_cover(node* c){
        c->right->left = c->left;
        c->left->right = c->right;
        for(node* it = c->down; it != c; it = it->down){
            for(node* j = it->right; j != it; j = j->right){
                j->down->up = j->up;
                j->up->down = j->down;
                j->column->size--;
            }
        }
    }

    void dlx_uncover(node* c){
        for (node* it = c->up; it != c; it = it->up) {
	    	for (node* jt = it->left; jt != it; jt = jt->left) {
	    		jt->down->up = jt;
	    		jt->up->down = jt;
	    		jt->column->size++;
	    	}
	    }
	    c->right->left = c;
	    c->left->right = c;
    }

    bool dlx_search(node* head, int k, vector<int>& sol){
        if(head->right == head) return 1;
        node* ptr = nullptr;
        int low = INF;
        for(node* it = head->right; it != head; it = it->right){
            if(it->size < low){
                if(it->size == 0) return 0;
                low = it->size;
                ptr = it;
            }
        }
        dlx_cover(ptr);
        for(node* it = ptr->down; it != ptr; it = it->down){
            sol.push_back(it->row);
            for(node* j = it->right; j != it; j = j->right){
                dlx_cover(j->column);
            }
            if(dlx_search(head, k + 1, sol)) return 1;
            else{
                sol.pop_back();
                for(node* j = it->left; j != it; j = j->left){
                    dlx_uncover(j->column);
                }
            }
        }
        dlx_uncover(ptr);
        return 0;
    }

    vector<int> solve(vector<vector<int>> input) {
    	int n = input[0].size();
    	vector<node> column(n);
    	node head;
    	head.right = &column[0];
    	head.left = &column[n - 1];
    	for (int i = 0; i < n; ++i) {
    		column[i].size = 0;
    		column[i].up = &column[i];
    		column[i].down = &column[i];
    		if (i == 0) column[i].left = &head;
    		else column[i].left = &column[i - 1];
    		if (i == n - 1) column[i].right = &head;
    		else column[i].right = &column[i + 1];
    	}

    	vector<node*> nodes;
    	for (int i = 0; i < input.size(); ++i) {
    		node* last = nullptr;
    		for (int j = 0; j < n; ++j) if (input[i][j]) {
    			node* now = new node;
    			now->row = i;
    			now->column = &column[j];
    			now->up = column[j].up;
    			now->down = &column[j];
    			if (last) {
    				now->left = last;
    				now->right = last->right;
    				last->right->left = now;
    				last->right = now;
    			}
    			else {
    				now->left = now;
    				now->right = now;
    			}
    			column[j].up->down = now;
    			column[j].up = now;
    			column[j].size++;
    			last = now;
    			nodes.push_back(now);
    		}
    	}
    	vector<int> sol;
    	dlx_search(&head, 0, sol);
    	for (node* ptr: nodes) delete ptr;
    	return sol;
    }
} DLX;
