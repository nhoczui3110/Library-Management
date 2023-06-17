struct DanhMucSach {
	char MaSach[25];//key
	int TrangThai; // 0: cho muon duoc, 1 : da duoc muon, 2: da thanh ly
	char ViTri[50];
};
struct nodeDMS {
	DanhMucSach data;
	nodeDMS* next;
};
typedef nodeDMS* NodeDMS;
void Khoitao(NodeDMS &First) {
	First=NULL;
}

NodeDMS NewNode(DanhMucSach &sach) {
	NodeDMS Newnode = new nodeDMS;
	Newnode->data=sach;
	Newnode->next=NULL;
	return Newnode;
}

void themdau(DanhMucSach sach,NodeDMS &first) {
	NodeDMS temp= NewNode(sach);
	if(first==NULL) {
		first = temp;
		return;
	} else {
		temp->next=first;
		first=temp;
	}
}

void Insert_after(NodeDMS &p, DanhMucSach x)
{
   NodeDMS q;
   if(p == NULL)
		return;
   else
   {
      q = new nodeDMS;
      q->data = x;
      q->next = p->next;
      p->next = q;
   }
}


void themcuoi(DanhMucSach &sach,NodeDMS &first) {
	NodeDMS tmp = NewNode(sach);
	if(first==NULL) {
		first=tmp;
		return;
	} else {
		NodeDMS nodechay= first;
		while(nodechay->next!=NULL) {
			nodechay=nodechay->next;
		}
		nodechay->next=tmp;
	}
}
int  Delete_after(NodeDMS p) {
	NodeDMS q;
	// n?u p là NULL ho?c sau p không có nút
	if((p == NULL) || (p->next == NULL))
		return 0;
	q = p->next;  // q chi nut can xoa
	p->next = q->next;
	delete q;
	return 1;
}
int Delete_First (NodeDMS  &First) {
	NodeDMS p;
	if (First==NULL)
	return 0;
	p = First;    // nut can xoa la nut dau
	First = p->next;
	delete p;
	return 1;
}
int tongLinkedList(NodeDMS First) {
	int res = 0;
	while (First!=NULL) {
		++res;
		First=First->next;
	}
	return res;
}

