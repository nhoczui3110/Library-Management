struct MuonTra{
	char MaSach[25];
	char NgayMuon[20];
	char NgayTra[20];
	short quahan;
	int TrangThai;
		// 0 chua tra
		// 1 da tra
		// 2 lam mat
	unsigned long Time_Muon;
	unsigned long Time_Tra;
};
struct nodeMuonTra{
	MuonTra muontra;
	nodeMuonTra *right;
	nodeMuonTra *left;
};
typedef nodeMuonTra* NodeMuonTra;

void NgayMuon(MuonTra &mt){
	time_t baygio=time(0);
	std::cout<<baygio;
	tm *ltm = localtime(&baygio);
	int day=ltm->tm_mday;
	char tmp[10];
	char ngay[10];
	char thang[10];
	char nam[10];
	mt.Time_Muon=baygio;
	strcpy(ngay , strcat(itoa(day,tmp,10),"/"))	;
	strcpy(thang,strcat(ngay,itoa(ltm->tm_mon+1,tmp,10)));
	strcpy(nam,strcat(thang,"/"));
	strcpy(mt.NgayMuon, strcat(nam,itoa(1900+ltm->tm_year,tmp,10)));
	strcpy(mt.NgayTra,"--/--/--");
}

void NgayTra(MuonTra &mt){
	time_t baygio=time(0);
	tm *ltm = localtime(&baygio);
//	std::cout<<"Thang : "<<ltm->tm_mon<<"\n";
	int day=ltm->tm_mday;
//	char ngaymuontra[20];
	char tmp[10];
	char ngay[10];
	char thang[10];
	char nam[10];
	strcpy(ngay , strcat(itoa(day,tmp,10),"/"))	;
	strcpy(thang,strcat(ngay,itoa(ltm->tm_mon+1,tmp,10)));
	strcpy(nam,strcat(thang,"/"));
	strcpy(mt.NgayTra, strcat(nam,itoa(1900+ltm->tm_year,tmp,10)));
//		std::cout<<"Ngay Tra : "<<mt.NgayTra<<"\n";
//		std::cout<<"Ngay muon : "<<ngay<<"\n";
//		std::cout<<"Ngay muon : "<<nam<<"\n";
//	return ngaymuontra;
}

NodeMuonTra NewMuonTra(MuonTra mt){
	NodeMuonTra CreMuonTra = new nodeMuonTra;
	CreMuonTra->muontra = mt;
	CreMuonTra->right=NULL;
	CreMuonTra->left=NULL;
	return CreMuonTra;
}


//void InsertFirstMuonTra	(NodeMuonTra &First, NodeMuonTra &Last, MuonTra x)
//{
//   NodeMuonTra p = NewMuonTra(x);
//   p->right = First;
//   if(First == NULL)      // truong hop danh sach rong
//      Last = p;
//   else First->left = p;        // tao lien ket giua p va First
//   First = p;
//}

void InsertLastMuonTra(MuonTra mt, NodeMuonTra &First, NodeMuonTra &Last,ListDauSach &l){
	NodeMuonTra tmp = new nodeMuonTra;
	for (int i = 0; i < l.n; i++) {
		if (strcmp(layISBN(mt.MaSach),l.dausach[i]->ISBN)==0) l.dausach[i]->soluotmuon++;
	}
	mt.quahan=0;
	if (mt.TrangThai==0){
		mt.quahan=(time(0)-mt.Time_Muon)/86400-7;
	}
	tmp->muontra=mt;
	tmp->left=NULL;
	tmp->right=NULL;
	if (First==NULL) {
		First=Last=tmp;
	}
	else {
		tmp->left = Last;
		Last->right = tmp;
		Last = tmp;
	}
	
}
bool checkMuonTrungDauSach(char ms[], NodeMuonTra First,ListDauSach l) {
	while (First!=NULL) {
		if ((strcmp(layTenSachtuMaSach(ms,l),layTenSachtuMaSach(First->muontra.MaSach,l))==0) && (First->muontra.TrangThai==0)) {
		return true;
		}
		First=First->right;
	}
	return false;
}

//char* timMaSachChuaMuon(ListDauSach l, char tensach[50]) {
//	for (int i = 0; i < l.n; i++) {
//		if (strcmp(l.dausach[i]->ten,tensach)==0) {
//			NodeDMS runner = l.dausach[i]->FirstDMS;
//			while (runner!=NULL) {
//				if (runner->data.TrangThai==0) {
//					return runner->data.MaSach;
//				}
//				runner=runner->next;
//			}
//		}
//	}
//	return 0;
//}

bool checkConDMS(ListDauSach l, int i) {
	NodeDMS runner = l.dausach[i]->FirstDMS;
	while (runner!=NULL) {
		if (runner->data.TrangThai==0) return true;
		runner=runner->next;
	}
	return false;
}
 
int checkDMSMuonChua(ListDauSach l, int i, char ms[]) {
	NodeDMS runner = l.dausach[i]->FirstDMS;
	while (runner!=NULL) {
		if (strcmp(runner->data.MaSach,ms)==0) {
			if (runner->data.TrangThai==1 || runner->data.TrangThai==2) return 1; // tra ve 1 neu khong the cho muon
			else return 2; // tra ve 2 neu co the cho muon
		};
		runner=runner->next;
	}	
	return 0; // tra ve 0 neu khong tim thay ms phu hop
}

int findDauSachTuMaSach(char MaSach[], ListDauSach &l) {
	for (int i = 0; i < l.n; i++) {
		if (strcmp(layISBN(MaSach),l.dausach[i]->ISBN)==0) return i;
	}
	return 999; // tra ve -1 neu khong tim thay ma sach
}

