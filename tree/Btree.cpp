#include <iostream> 
using namespace std; 
template <class E> 
class BTree{
    struct BNode{
        E element; 
        BNode * left, * right; 
        BNode(E e = E(), BNode * l = 0, BNode * r = 0) : element (e), left(l), right(r){}
        bool isLeaf() const{    return !left && !right;};
        bool isInternal() const{   return !isLeaf();};
    }; 
    BNode * root; 
    int size;
    // tiền tố
    void preOrderRec(const BNode * r)const {
        if(r){
            cout<<r->element<<"\t";
            preOrderRec(r->left);
            preOrderRec(r->right);
        }
    }
    // hậu tố
    void postOrderRec(const BNode *r)const {
        if(r){
            postOrderRec(r->left);
            postOrderRec(r->right);
            cout<<r->element<<"\t";
        }
    }
    // trung tố 
    void inOrderRec(const BNode *r)const {
        if(r){
            inOrderRec(r->left);
            cout<<r->element<<"\t";
            inOrderRec(r->right);
        }
    }
    // đếm số node
    int countNodeRec(const BNode * r) const{
        if(!r)   return 0;
        return 1 + countNodeRec(r->left) + countNodeRec(r->right);
    }
    // đếm lá
    int countLeafRec(const BNode * r) const{
        if(!r)  return 0;
        return r->isLeaf() + countLeafRec(r->left) + countLeafRec(r->right);

        // if(!r)  return 0;
        // if(r->isLeaf)   return 1;
        // return countLeafRec(r->left) + countLeafRec(r->right);
    }
    int countInternalNodeRec(const BNode * r) const{
        if (!r) return 0; 
        return r->isInternal() + countInternalNodeRec(r->left) 
                        + countInternalNodeRec(r->right); 
    }
    // int countLeftLeaf(const BNode * r) const{
        
    // }
    // int countRightLeaf(const BNode * r) const{

    // }
    int heightRec(const BNode * r) const{
        if(!r)  return -1;
        if(r->isLeaf()) return 0;
        return max(heightRec(r->left), heightRec(r->right)) + 1;
    }
    // thêm vào cây
    void addRec(BNode * & r,const E & e){
        //thêm vào cây thấp hơn trong 2 cây, nếu bằng nhau thì ưu tiên thêm vào trái
        // khi cây rỗng thì chính E là nút gốc
        if(!r)  {r = new BNode(e);}
        else{
            if(heightRec(r->left) <= heightRec(r->right))   {addRec(r->left,e);}    
            else    {addRec(r->right,e);} 
        }
           
    }
    // xóa cây
    void clearRec(BNode * &r){
        if(r){
            clearRec(r->left);
            clearRec(r->right);
            delete r;  
            r = 0;
        }
    }
    // hàm tạo sao chép
    void copyRec(BNode * & l,const BNode * r){
        if(!r) l = 0;
        else{
            l = new BNode(r->element);
            copyRec(l->left,r->left);
            copyRec(l->right,r->right);
        }
    }
public: 
    BTree(): root(0), size(0){};
    void preOder()const {preOrderRec(root);}
    void postOrder()const {postOrderRec(root);}
    void inOrder()const {inOrderRec(root);}
    int countNode () const{return countNodeRec(root);}
    int countLeaf () const{return countLeafRec(root);}
    int height()const {return heightRec(root);}
    void add(const E e) {addRec(root,e);}
    void clear()   {clearRec(root);}
    int countLeftLeaf () const { return countLeafRec(root->left); }
    int countRightLeaf () const { return countLeafRec(root->right); }
    int countInternalNode() const{return countInternalNodeRec(root); }
    BTree(const BTree<E> & r) {copyRec(root,r.root);}
    ~BTree(){clearRec(root);}
    BTree<E> operator = (const BTree<E> & r){
        clear();
        copyRec(root,r.root);
        return *this;
    }
};

int main(){
    BTree<int> a;
    a.add(5);
    a.add(7);
    a.add(9);
    a.add(6);
    a.add(2);
    a.inOrder();
    cout<<endl;
    BTree<int> d;
    d = a;
    d.inOrder();
    // BTree<int> b(a),c = a;// khởi gán
    // b.inOrder();
    // cout<<endl;
    // c.inOrder();
    return 0;
}
