#define MAX_SIZE_DG 8000
struct DocGia{
	int mathe;
	char ho[30];
	char ten[10];
	int phai;//0: Nam ; 1: Nu
	int trangthai; // 0: hoat dong, 1 : khoa
	short slmuon;
	NodeMuonTra First=NULL;
	NodeMuonTra Last=NULL;
};
struct nodeDocGia{
	DocGia member;
	nodeDocGia *left,*parent,*right;
	int height;
};
typedef nodeDocGia* NodeDocGia;
DocGia themdocgia(int mathe,char *ho, char *ten,int phai,int trangthai,short slmuon){
		DocGia tmp;
		tmp.mathe=mathe;
		strcpy(tmp.ho,ho);
		strcpy(tmp.ten,ten);
		tmp.phai=phai;
		tmp.slmuon=slmuon;
		tmp.trangthai=trangthai;
		tmp.slmuon=slmuon;
		return tmp;
}
struct CayDocGia{
	NodeDocGia root;
	CayDocGia(){
		root=NULL;
	}
	NodeDocGia themnodedocgia(DocGia member){
		NodeDocGia NewNodeDG=new nodeDocGia;
		NewNodeDG->member=member;
		NewNodeDG->left=NULL;
		NewNodeDG->right=NULL;
		NewNodeDG->parent=NULL;
		return NewNodeDG;
	}
	int maxheight(NodeDocGia t1,NodeDocGia t2){          // tinh chieu cao toi da cua 2 cay con
		int h1,h2;
		if (t1==NULL) h1=0;
		else h1=t1->height;
		if (t2==NULL) h2=0;
		else h2=t2->height;
		return (h1>=h2) ? h1:h2;
		
	}
	int diffheight(NodeDocGia t1,NodeDocGia t2){          // tinh chenh lech cua cao cua 2 cay con
		int h1,h2;
		if (t1==NULL) h1=0;
		else h1=t1->height;
		if (t2==NULL) h2=0;
		else h2=t2->height;
		return ((h1>=h2) ? (h1-h2):(h2-h1));
	}
	void recompheight(NodeDocGia x){
		while (x!=NULL){
			x->height=maxheight(x->left,x->right)+1;
			x=x->parent;
		}
	}
	NodeDocGia tallerchild(NodeDocGia p){
		if (p->left==NULL) return p->right;
		if (p->right==NULL) return p->left;
		if (p->left->height>p->right->height)
			return p->left;
		else 
			return p->right;
	}
	NodeDocGia findNode(int k){
		NodeDocGia curr,prev;
		curr=root;
		prev=root;
		while (curr!=NULL){
			if(k<curr->member.mathe){
				prev=curr;
				curr=curr->left;
			}
			else if (k>curr->member.mathe){
				prev=curr;
				curr=curr->right;
			}
			else return curr;
		}
		//khi khong tim dc thi tra ve nut cha
		return prev;
	}
	NodeDocGia tri_node_restructure(NodeDocGia x,NodeDocGia y,NodeDocGia z){
		//xac dinh moi quan he cha con giua (y,z) va (x,y)
		bool zIsLeftChild=(z==y->left);
		bool yIsLeftChild=(y==x->left);
		//tim ra node nao la vi tri a,b,c
		NodeDocGia a,b,c,T0,T1,T2,T3;
		if(zIsLeftChild&&yIsLeftChild) //truong hop trai - trai
		{
	       a = z;                      //          
	       b = y;                      //         
	       c = x;                      //       
	       T0 = z->left;               //     
	       T1 = z->right;              //  
	       T2 = y->right;              //   
	       T3 = x->right;              //  
	       
		}
		else if (!zIsLeftChild && yIsLeftChild) // truong hop trai-phai
	    { 
	       a = y;                      //      
	       b = z;                      //      
	       c = x;                      //    
	       T0 = y->left;               //   
	       T1 = z->left;               //  
	       T2 = z->right;              //    
	       T3 = x->right;              //    
	    }
        else if (zIsLeftChild && !yIsLeftChild) //truong hop phai trai
	    { 
	       a = x;                    
	       b = z;                      
	       c = y;                      
	       T0 = x->left;               
	       T1 = z->left;               
	       T2 = z->right;            
	       T3 = y->right;             
	    }
        else 								
        { 
	       a = x;                      //       
	       b = y;                      //      
	       c = z;                      //     
	       T0 = x->left;               //        
	       T1 = y->left;               //       
	       T2 = z->left;               //        
	       T3 = z->right;              //         
	    }
		//dat b vao cho cua x (bien b thanh nut cha cua cay con moi)
		if ( x == root )
	    {  //truong hop x la nut goc
	        root = b;                   // b la nut root
	        b->parent = NULL;
	    }
	    else
		{
		    NodeDocGia xParent;
	        xParent = x->parent;   // tim nut cha cua x
	        if ( x == xParent->left ) 
	        { /* Noi b vao nhanh ben trai cua xparent */
	          b->parent = xParent;
	          xParent->left = b;
	        }
	        else 
	        { /* Noi b vao nhanh ben phai cua xparent */
	          b->parent = xParent;
	          xParent->right = b;
	        }	
		}
	     /* ------------------
	        Make:   b
	               / \
	              a   c
	        ------------------ */
	    
	     b->left = a;
	     b->right = c; 
	     a->parent = b;
	     
	     c->parent = b;
	     
	     /* ------------------
	        Make:   b
	               / \
	              a   c
	             / \
	            T0 T1
	        ------------------ */
	     a->left = T0;
	     if ( T0 != NULL ) T0->parent = a;
	     a->right = T1;
	     if ( T1 != NULL ) T1->parent = a;
	     /* ------------------
	        Make:   b
	               / \
	              a   c
	                 / \
	                T2 T3
	        ------------------ */
	     c->left = T2;
	     if ( T2 != NULL ) T2->parent= c;
	     c->right= T3;
	     if ( T3 != NULL ) T3->parent= c;
	     recompheight(a);
	     recompheight(c);
	     return b;
	   
	} 
	void add(DocGia a){
		NodeDocGia p;
		if (root==NULL){ 	
			root=themnodedocgia(a);
			root->height=1;
			return;
		}	
		// tim node p voi key=k va thay doi data
		p=findNode(a.mathe);
		if (a.mathe==p->member.mathe){
			p->member=a;   // thay doi data member 
			return;
		}
		//chen mot nut moi ben duoi p
		NodeDocGia q=themnodedocgia(a);
		
		q->height=1;
		q->parent=p;
		if (a.mathe<p->member.mathe)
			p->left=q;
		else 
			p->right=q;
			
		recompheight(p);
		NodeDocGia x,y,z;
		
		x=q;y=q;z=q;       // x,y,z bat dau tu q
		while (x!=NULL){
			if (diffheight(x->left,x->right)<=1){
				z=y;
				y=x;
				x=x->parent;
			}
			else break;
		}
//		printtree();
		

		//tim duoc x la node mat can bang 
		if (x!=NULL){
			tri_node_restructure(x,y,z);
		}
		
	}
	void rebalance(NodeDocGia p){
		NodeDocGia x,y,z,q;
		while (p!=NULL){
			if (diffheight(p->left,p->right)>1){
				x=p;
				y=tallerchild(p);
				z=tallerchild(y);
				p=tri_node_restructure(x,y,z);
			}
			p=p->parent;
		}
	}
	void remove(int k){
		NodeDocGia p,q;
		NodeDocGia parent;
		NodeDocGia nodekevi;
		p=findNode(k);
		if (k!=p->member.mathe)
			return;
		if (p->left==NULL &&p->right==NULL) //Truong hop p ko co node con
		{	
			if (p->parent==NULL){
				root=NULL;
				delete p;
				return;
			}
			parent=p->parent;
			//xoa p khoi p->parent
			if (parent->left==p)
				parent->left=NULL;
			else 
				parent->right=NULL;
			recompheight(parent);
			rebalance(parent);
			return;
		}
		if (p->left==NULL)  //Truong hop p co 1 node ben phai
		{
			if (p->parent==NULL) {
				root=p->right;
				root->parent=NULL;
				delete p;
				return;
			}
			parent=p->parent;

			// noi node con ben phai cua p thanh con cua parent
			if (parent->left==p)
				parent->left=p->right;
			else 
				parent->right=p->right;
			p->right->parent=parent;
			
			recompheight(parent);
			rebalance(parent);
			return;
		}
		if (p->right==NULL)  //Truong hop p co 1 node ben trai
		{	
			if (p->parent==NULL) {
				root=p->left;
				root->parent=NULL;
				delete p;
				return;
			}
			 
			
			parent=p->parent;
			// noi node con ben phai cua p thanh con cua parent
			if (parent->left==p)
				parent->left=p->left;
			else parent->right=p->left;
			p->left->parent=parent;
			recompheight(parent);
			rebalance(parent);
			return;
		}   //  6
//		  2        12
//              6    12
//	                     
		//truong hop co 2 node con: tim nodekevi cua p la node trai nhat cua cay con ben phai
		nodekevi=p->right;
		while (nodekevi->left!=NULL)
			nodekevi=nodekevi->left;
	          // doi p thanh nodekevi
		p->member=nodekevi->member;
		//xoa nodekevi khoi nodekevi->parent
	parent=nodekevi->parent;
		if (nodekevi==p->right){
			if (nodekevi->right==NULL) {p->right=NULL;delete nodekevi;
			}
			else {
				p->right=nodekevi->right;
				nodekevi->right->parent=p;
			}
//			parent->right=nodekevi->right;
//			nodekevi->parent=NULL;
//			printtree();
			
		}
		else {
			parent->left=nodekevi->right;	
		}
		delete nodekevi;
//	    p=nodekevi;
//	    nodekevi=nodekevi->right;
		 // noi node con ben phai cua nodekevi vao ben trai parent
		recompheight(parent);
		rebalance(parent);
		return;
	}
	void printnode(NodeDocGia x,int h){
		std::cout<<"denday";
		for (int i=0;i<h;i++) std::cout<"              ";
		std::cout<<"["<<x->member.mathe<<","<<x->member.ten<<"](h="<<x->height<<")";
		if (diffheight(x->left,x->right)>1) std::cout<<"*"<<std::endl;
		else std::cout<<std::endl;
	}
	void printtree(){
		showR(root,0);
		std::cout<<"============================"<<std::endl;
	}
	void showR(NodeDocGia t,int h){
		if (t==NULL) return;
		else showR(t->right,h+1);
		printnode(t,h);
		showR(t->left,h+1);
	}
};
void DoCayVaoMang(NodeDocGia p,DocGia *MangDocGia,int &n){
		if (p!=NULL){
			DoCayVaoMang(p->left,MangDocGia,n);
			MangDocGia[n++]=p->member;
			DoCayVaoMang(p->right,MangDocGia,n);
		}
}
void DoMaTheVaoMang(NodeDocGia p,int *MangMaThe,int &n){
		if (p!=NULL){
			DoMaTheVaoMang(p->left,MangMaThe,n);
			MangMaThe[n++]=p->member.mathe;
			DoMaTheVaoMang(p->right,MangMaThe,n);
		}
}
void DoMuonTraVaoMang(NodeDocGia p,DocGia *MangMuonTra,int &n){
		NodeMuonTra mt,tmp;
		if (p!=NULL){
			DoMuonTraVaoMang(p->left,MangMuonTra,n);
			mt=p->member.First;
			while (mt!=NULL){
				if (mt->muontra.quahan>0 && mt->muontra.TrangThai==0) {
					tmp=mt;
					MangMuonTra[n]=p->member;
					MangMuonTra[n].First=tmp;
					n++;
				}
				mt=mt->right;
			}
			DoMuonTraVaoMang(p->right,MangMuonTra,n);
		}
}
void SortMT(DocGia *A, int q,int r)
  { DocGia temp;
    int i=q;
    int j=r;
    DocGia x = A[(q+r) / 2]; 
    do
    {  
      while (A[i].First->muontra.quahan >x.First->muontra.quahan )  i++; 
      while (A[j].First->muontra.quahan <x.First->muontra.quahan )  j--; 
      if (i<=j)   // Doi cho A[i] voi A[j]
     { temp = A[i];       A[i] =A[j];       A[j] = temp;
	i++ ;  j--;
   }
	} while (i<=j);   
  if (q<j) 	
	SortMT(A,q,j);
  if (i<r)   	
	SortMT(A,i,r);
}

int DemNut(NodeDocGia p){
		if (p==NULL) return 0;
			else {
				int DemTrai=DemNut(p->left);
				int DemPhai=DemNut(p->right);
				return DemTrai+DemPhai+1;
			}
}
void swap(DocGia *a, DocGia *b){
	DocGia c= *a;
	*a=*b;
	*b=c;	
}
int Partition(DocGia *Arr,int low, int high){
	DocGia pivot = Arr[high];
	int i= low-1; // bien i co tac dung nam vi tri
	for (int j = low; j <= high - 1; j++)  
    {  // khi j bat dau chay tu 0-> pivot -1
        if (strcmp(Arr[j].ten,pivot.ten)<0)  
        {  // neu gtri tai j < pivot
            i++; 
            swap(&Arr[i], &Arr[j]); // thi doi gia tri tai j va gia tri tai i (i luc nay = 0) 
        } // muc tieu la sap xep cac gia tri < pivot sang ben trai.
		else if(strcmp(Arr[j].ten,pivot.ten)==0){
			if(strcmp(Arr[j].ten,pivot.ho)<=0);{
				i++; 
            	swap(&Arr[i], &Arr[j]);	
			}
		}  
    }  
	swap(&Arr[i + 1], &Arr[high]);  // sau cung la dua gtri pivot ve dung vi tri la i+1
    return (i + 1);
}
void quickSortTen(DocGia *Arr,int low, int high)  
{  	

    if (low < high)  
    {  
        int pi = Partition(Arr,low, high);  
        quickSortTen(Arr,low, pi - 1);  
        quickSortTen(Arr,pi + 1, high);  
    }  
}  
NodeDocGia SearchDG(int MA_THE, NodeDocGia &root ){
	NodeDocGia runS = root;
	while(runS!=NULL ){ 
		if(MA_THE < runS->member.mathe){
		    runS=runS->left;
		}
		else if(MA_THE > runS->member.mathe){
	    	runS=runS->right;
	    }
	    else	return runS;
	}
	return 0;
}
short TongSoSachMuon(DocGia *MangDocGia, int n) {
	short res=0;
	for (int i = 0; i < n;i++) {
		res += MangDocGia[i].slmuon;
	}	
	return res;
}
bool chechSLM(NodeDocGia docgia) {
	if (docgia->member.slmuon>=3) return true;
	else return false;
}
bool checkQuaHan(NodeDocGia docgia) {
	NodeMuonTra tmp = docgia->member.First;
	while(tmp!=NULL) {
		if (tmp->muontra.TrangThai==0 && tmp->muontra.quahan>0) return true;
		tmp=tmp->right;
	}
	return false;
}
