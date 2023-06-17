#define maxDS 100
struct DauSach {
	char ISBN[20];//key
	char ten[50];
	int sotrang;
	char tacgia[50];
	int nxb;
	char theloai[50];
	NodeDMS FirstDMS;
	int soluong;
	int soluotmuon;
};
struct ListDauSach {
	int n=0;
	DauSach *dausach[maxDS];
};
DauSach dausach(char isbn[], char tensach[], int sotrang, char tacgia[], int nxb, char theloai[], int sl) {
	DauSach dauSach;
	strcpy(dauSach.ISBN, isbn);
	strcpy(dauSach.ten, tensach);
	dauSach.sotrang=sotrang;
	strcpy(dauSach.tacgia, tacgia);
	dauSach.nxb=nxb;
	strcpy(dauSach.theloai, theloai);
	dauSach.soluong=sl;
	NodeDMS tmp = dauSach.FirstDMS;
	return dauSach;
}
void searchTenSach(ListDauSach l,char masach[],char tensach[50]){
	char tmpISBN[20]="";int k=0;
	for (int i=0;i<=strlen(masach);i++){
		if (masach[i]>='A'&&masach[i]<='Z') {
			tmpISBN[k]=masach[i];k++;
		}
		if (masach[i]>='0'&&masach[i]<='9') break;
	}
	for (int i=0;i<l.n;i++){
		if (strcmp(l.dausach[i]->ISBN,tmpISBN)==0) {
			strcpy(tensach,l.dausach[i]->ten);
			return;
		}
	}
}
int InsertDauSach(ListDauSach &DSDS, DauSach dausach) {
	dausach.soluotmuon=0;
	int k=0;
	while (k<DSDS.n) {
		if (strcmp(dausach.ten,DSDS.dausach[k]->ten)>0) k++;
		else break;
	}
	if(DSDS.n==maxDS) {
		return 0;
	} else {
		DSDS.n++;
		for(int i=DSDS.n-1; i>k; i--) {		// Them dau sach vao vi tri pos
			DSDS.dausach[i]=DSDS.dausach[i-1]; // doi cac phan tu sau pos len 1 don vi
		}
		DSDS.dausach[k] = new DauSach(dausach);
	}
	return k;
}
int InsertDMS(ListDauSach DSDS, int k, char vitri[]) {
	int i=1;
	Khoitao(DSDS.dausach[k]->FirstDMS);
	NodeDMS Last;
	while (i<=DSDS.dausach[k]->soluong) {
		NodeDMS p=new nodeDMS;
		char numStr[10];
		sprintf(numStr, "%d", i);
		strcpy(p->data.MaSach,DSDS.dausach[k]->ISBN);
		strcat(p->data.MaSach,"-");
		strcat(p->data.MaSach,numStr);
		p->data.TrangThai=0;
		strcpy(p->data.ViTri,vitri);
		if (i==1) {
			DSDS.dausach[k]->FirstDMS=p;
			Last=p;
		} else {
			Last->next=p;
			Last=Last->next;
		}
		i++;
	}
	return 1;
}
void copyListDS(ListDauSach in, ListDauSach &out) {
	for  (int i = 0; i < in.n; i++)  {
		out.dausach[i]=in.dausach[i];
		out.n++;
	}
}
int deleteDauSach (ListDauSach &plist, int i)
{
	if(i < 0 || i >= plist.n || plist.n==0) return 0;
	for(int j = i+1;  j< plist.n ; j++)
		plist.dausach[j-1] = plist.dausach[j];
	if (i!=plist.n-1) {
		DauSach temp = *plist.dausach[plist.n-1];
		delete plist.dausach[plist.n-1];
		plist.dausach[plist.n-2] = new DauSach(temp);
	}
	else {
		delete plist.dausach[plist.n-1];
		
	}
	plist.n--;
	return 1; 
}
int checkTrungISBN(char isbn[], ListDauSach l) {
	for (int i = 0; i < l.n; i++) {
		if (strcmp(isbn,l.dausach[i]->ISBN)==0) {
			return 1;
		}
	}
	return 0;
}
void swap_dausach(DauSach *&a, DauSach *&b){
	DauSach *c=a;
	a=b;
	b=c;
}
void SortDS(ListDauSach &l, int q,int r)
  { int temp;
    int i=q;
    int j=r;
    DauSach *x = l.dausach[(q+r)/2]; //L?y ph?n t? gi?a c?a dãy c?n s?p th? t? làm ch?t
    do
    {  // Phân ?o?n dãy con a[q],..., a[r]
      while (l.dausach[i]->soluotmuon > x->soluotmuon)  i++; //Tìm ph?n t? ??u tiên có tr? l?n h?n hay b?ng x
      while (l.dausach[j]->soluotmuon < x->soluotmuon)  j--; //Tìm ph?n t? ??u tiên có tr? nh? h?n hay b?ng x
      if (i<=j)   // Doi cho A[i] voi A[j]
     { swap_dausach(l.dausach[i],l.dausach[j]);
	i++ ;  j--;
   }
} while (i<=j);
  if (q<j) 	// ph?n th? nh?t có t? 2 ph?n t? tr? lên
	SortDS(l,q,j);
  if (i<r)   	// ph?n th? ba có t? 2 ph?n t? tr? lên
	SortDS(l,i,r);
}
//const char* layChuInHoa(char text[]) {
//	std::string str = "";
//	std::string input(text);
//	for (int i = 0; i < strlen(text); i++) {
//		if ((text[i]>=65 && text[i]<=90)) str+=input[i];
//	}
//	return str.c_str();
//}
const char* layISBN(char text[]){
	std::string str="";
	std::string input(text);
	for (int i = 0; i < strlen(text); i++) 
		if (text[i]!=45) str+=input[i];
			else return str.c_str();
	return str.c_str();;
}
char* layTenSachtuMaSach(char masach[],ListDauSach l){
	std::cout<<layISBN(masach)<<"/"<<std::endl;

	for (int i=0;i<l.n;i++){
		if (strcmp(layISBN(masach),l.dausach[i]->ISBN)==0){
			std::cout<<l.dausach[i]->ten<<"/"<<std::endl;
			return l.dausach[i]->ten;
		}
	}
} 
//const char* layChuDauTien(char text[]) {
//	std::string str = "";
//	std::string input(text);
//	for (int i = 0; i < strlen(text); i++) {
//		if (!(text[i]>=48 && text[i]<=57)) str+=input[i];
//	}
//	return str.c_str();
//}
//int findDauSachTuMaSach(char masach[], ListDauSach l) {
//	for (int i = 0 ; i < l.n; i++) {
//		if (strcmp(layISBN(masach),l.dausach[i]->ISBN)==0) return i;
//	}
//}
int laySo(char text[]) {
	std::string str = "";
	std::string input(text);
	for (int i = 0; i < strlen(text); i++) {
		if ((text[i]>=48 && text[i]<=57)) str+=input[i];
	}
	return atoi(str.c_str());
}

