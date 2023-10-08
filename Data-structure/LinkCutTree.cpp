struct LinkCutTree{
    struct Node{
        Node *l, *r, *p;
        int v,sum,sz;
        bool flip;

        Node(int v = 0, Node* p = nullptr):v(v),sum(v),p(p){
            l = r = nullptr; sz = 0; flip = false;
        }

        bool IsRoot() const { return !p || this != p->l && this != p->r; }
        bool IsLeft() const { return this == p->l; }
        void Rotate(){
            if(IsLeft()) r && (r->p = p), p->l = r, r = p;
            else l && (l->p = p), p->r = l, l = p;
            if(!p->IsRoot()) (p->IsLeft() ? p->p->l : p->p->r) = this;
            auto t = p; p = t->p; t->p = this;
            t->Update(); Update();
        }

        void Update(){
            sz = 1; sum = v;
            if(l) sz += l->sz, sum += l->sum;
            if(r) sz += r->sz, sum += r->sum;
        }

        void Push(){
            if(flip){
                swap(l, r);
                if(l) l->flip ^= 1;
                if(r) r->flip ^= 1;
                flip = 0;
            }
        }
    };

    Node ptr[101010];

    void Splay(Node* x){
        for(; !x->IsRoot(); x->Rotate()){
            if(!x->p->IsRoot()) x->p->p->Push(); x->p->Push(); x->Push();
            if(!x->p->IsRoot()) (x->IsLeft() ^ x->p->IsLeft() ? x : x->p)->Rotate();
        }
        x->Push();
    }

    void Access(Node* x){
        Splay(x); x->r = nullptr;
        for(; x->p; Splay(x)) Splay(x->p), x->p->r = x;
    }
    // p의 부모정점을 x로 만들어줌 이때 p는 무조건 트리의 루트여야함
    void Link(Node* x, Node* p){
        Access(x); Access(p);
        x->l = p; p->p = x;
        x->Update();
    }

    void Cut(Node* x){
        Access(x); if(!x->l) return;
        x->l = x->l->p = nullptr;
        x->Update();
    }

    Node* GetRoot(Node* x){
        Access(x); for(; x->l; x = x->l, x->Push());
        Access(x); return x;
    }

    Node* GetPar(Node* x){
        Access(x); if(!x->l) return nullptr;
        for(x = x->l, x->Push(); x->r; x = x->r, x->Push());
        Access(x); return x;
    }

    Node* GetLCA(Node* x, Node* y){
        Access(x); Access(y); Splay(x);
        return x->p ? x->p : x;
    }

    int GetDep(Node* x){
        Access(x);
        return x->l ? x->l->sz : 0;
    }

    void MakeRoot(Node* x){
        Access(x); Splay(x);
        x->flip ^= 1;
    }

    void Access(int x) { Access(ptr + x); }
    void Link(int x, int p) { Link(ptr + x, ptr + p); }
    void Cut(int x){ Cut(ptr + x); }
    Node* GetRoot(int x){ return GetRoot(ptr + x); }
    Node* GetPar(int x) { return GetPar(ptr + x); }
    Node* GetLCA(int x, int y){
        //if(GetRoot(x) != GetRoot(y)) return nullptr; // or -1
        return GetLCA(ptr + x, ptr + y);
    }
    int GetDep(int x){ return GetDep(ptr + x); }
    void MakeRoot(int x){ MakeRoot(ptr + x); }

    // for problem
    void VertexUpdate(Node* x, int val){
        Access(x); x->v = val;
        x->Update();
    }

    void VertexUpdate(int x, int val){
        VertexUpdate(ptr + x, val);
    }

    int PathQuery(Node* x, Node* y){
        Node* l = GetLCA(x, y);
        int ret = l->v;
        Access(x); Splay(l);
        if(l->r) ret = ret + l->r->sum;

        Access(y); Splay(l);
        if(l->r) ret = ret + l->r->sum;
        return ret;
    }

    int PathQuery(int a, int b){
        return PathQuery(ptr + a, ptr + b);
    }
} lct;
