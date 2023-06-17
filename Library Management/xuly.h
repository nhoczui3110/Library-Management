

void DocFile_Sach(std::fstream &Inp, DanhMucSach &sach) {

	std::string data_tmp;
	getline(Inp, data_tmp,',');
	strcpy(sach.MaSach,data_tmp.c_str());
	getline(Inp,data_tmp,',');
	strcpy(sach.ViTri,data_tmp.c_str());
	Inp>>sach.TrangThai;
	getline(Inp,data_tmp,'\n');
}
void DocFile_DMS(ListDauSach &DSDS) {
	std::fstream inp_DMS;
	inp_DMS.open("Data_DanhMucSach.txt",std::ios::in);
	if(inp_DMS.fail()) {
		std::cout<<"Loi File DauSach";
		return ;
	}
	if(DSDS.n==0) {
		message("DS trong!");
		return;
	}
	std::string data_tmp;
	for(int i=0; i<DSDS.n; i++) {
		for(int dem=0; dem<DSDS.dausach[i]->soluong; dem++) {
			std::cout<<"vaoday1";
			DanhMucSach sach;
			DocFile_Sach(inp_DMS,sach);
			std::cout<<DSDS.dausach[i]->ISBN;
			themcuoi(sach,DSDS.dausach[i]->FirstDMS);
			std::cout<<"vaoday2";
			std::cout<<sach.MaSach<<"|";
		}
		getline(inp_DMS,data_tmp,'\n');
	}

	inp_DMS.close();
}
void DocFile_DauSach(ListDauSach &DSDS) {
	std::fstream ds;
	ds.open("Data_DauSachh.txt", std::ios::in);
	if(ds.fail()) {
		std::cout<<"Loi File DauSachh";
		return ;
	}
	std::string datads;
	getline(ds,datads, '\n');
	DauSach in;
	in.soluotmuon=0;
	while(!ds.eof()) {
		//	getline(ds,datads, '\n');
		ds>> in.sotrang;
		getline(ds,datads, '\n');
		ds>> in.soluong;
		getline(ds,datads, '\n');
		ds>> in.nxb;
		getline(ds,datads, '\n');
		getline(ds,datads,'\n');
		strcpy(in.ISBN,datads.c_str());
		getline(ds,datads, '\n');
		strcpy(in.ten,datads.c_str());
		getline(ds,datads, '\n');
		strcpy(in.tacgia,datads.c_str());
		getline(ds,datads, '\n');
		strcpy(in.theloai,datads.c_str());
		std::cout<<datads<<"<<+++data==="<<std::endl;
		in.FirstDMS=NULL;
		InsertDauSach(DSDS,in);
	}
	ds.close();
}
int findDauSach(std::string info, ListDauSach l,int findDS[], int &nFindDS) {
	nFindDS = 0;
	bool isFound = false;
	int count=-1;
	inKhungDauSach();
	setbkcolor(pink);
	for (int i = 0; i < l.n; i++) {
		std::string str(l.dausach[i]->ten);
		if (str.find(info)!=std::string::npos) {
			++count;
			findDS[nFindDS]=i;
			nFindDS++;
			isFound = true;
			std::cout<<"tim thay";
		}
	}
	if (!isFound) {
		message("Khong tim thay!");
		return 0;
	}
	return 1;
}
void findDauSachTheoTheLoai(std::string MangTheLoai[], ListDauSach l,  int findDS[], int &nFindDS,int stttheloai) {
	nFindDS = 0;
	int count=-1;
	inKhungDauSach();
	setbkcolor(pink);
	for (int i = 0; i < l.n; i++) {
		if (l.dausach[i]->theloai==MangTheLoai[stttheloai]) {
			++count;
			findDS[nFindDS]=i;
			nFindDS++;
		}
	}
}
void InDauSachTheoDK(ListDauSach l, int height, int findDS[], int nFindDs,int page) {
	char tmp[50]= "";
	setbkcolor(pink);
	settextstyle(10,0,1);
	for (int i = 0; i < 10&& page*10-10+i<nFindDs; i++) {
		outtextxy(365,230+height*i,l.dausach[findDS[page*10-10+i]]->ISBN);
		outtextxy(480,230+height*i,l.dausach[findDS[page*10-10+i]]->ten);
		outtextxy(795,230+height*i,itoa(l.dausach[findDS[page*10-10+i]]->sotrang,tmp,10));
		outtextxy(900,230+height*i,l.dausach[findDS[page*10-10+i]]->tacgia);
		outtextxy(1100,230+height*i,itoa(l.dausach[findDS[page*10-10+i]]->nxb,tmp,10));
		outtextxy(1230,230+height*i,l.dausach[findDS[page*10-10+i]]->theloai);
	}
}
int Random( int minN, int maxN) {
	return minN + rand()%(maxN + 1-minN);
}
bool checkXoaDMS(DocGia *MangDocGia ,CayDocGia tree, char ms[]) {
	NodeMuonTra tmp;
	for (int i = 0; i < DemNut(tree.root); i++) {
		tmp = MangDocGia[i].First;
		while(tmp!=NULL) {
			if (strcmp(tmp->muontra.MaSach,ms)==0) {

				return true;
			}
			tmp=tmp->right;
		}
	}
	return false;
}
void xoaDMS(int demDMS, int pageDMS, int pageDS, int &maxPageDMS, int demDS, ListDauSach &l, int &checkXoaDS, CayDocGia tree, DocGia *MangDocGia) {
	int width[4] = {0,555,250,250};
//	highlightBox(330,180+40*(demDMS+1),40,width,6);
	if (l.dausach[pageDS*10-10+demDS]->FirstDMS==NULL) {
		return;
	} else if (pageDMS*10-10+demDMS==0) {
		highlightBox(330,180+40*(demDMS+1),40,width,6);
		std::cout<<"Ma sach muon xoa: "<<l.dausach[pageDS*10-10+demDS]->FirstDMS->data.MaSach<<" ";
		if (checkXoaDMS(MangDocGia,tree,l.dausach[pageDS*10-10+demDS]->FirstDMS->data.MaSach)) {
			message2("Sach da tung cho muon", "khong the xoa!");
		} else {
			if (yesnoBox("Ban co chac chan?",MAP)) {
				Delete_First(l.dausach[pageDS*10-10+demDS]->FirstDMS);
				maxPageDMS = tongLinkedList(l.dausach[pageDS*10-10+demDS]->FirstDMS)/10+1;
				inSoTrang(pageDMS,maxPageDMS);
				l.dausach[pageDS*10-10+demDS]->soluong--;
			}
		}
	} else {
		int j = 0;
		NodeDMS tmp = l.dausach[pageDS*10-10+demDS]->FirstDMS;
		if (tmp->next==NULL) return ;
		for (j = 0; j < pageDMS*10-10+demDMS-1; j++) {
			tmp=tmp->next;
			if (tmp->next==NULL) return ;
		}
		highlightBox(330,180+40*(demDMS+1),40,width,6);
		std::cout<<"Ma sach muon xoa: "<<tmp->next->data.MaSach<<" ";
		if (checkXoaDMS(MangDocGia,tree,tmp->next->data.MaSach)) {
			message2("Sach da tung cho muon", "khong the xoa!");
		} else {
			if (yesnoBox("Ban co chac chan?",MAP)) {
				Delete_after(tmp);
				maxPageDMS = tongLinkedList(l.dausach[pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[pageDS*10-10+demDS]->FirstDMS)/10+1;
				inSoTrang(pageDMS,maxPageDMS);
				l.dausach[pageDS*10-10+demDS]->soluong--;
			}
		}
	}
	inKhungDMS();
	inTableDMS(l,pageDMS,pageDS*10-10+demDS);
}
void addThemDMS(ListDauSach &DSDS, int pageDS, int demDS, int soluong, char vitri[]) {
	NodeDMS p;
	int sl = soluong, i = 2;
	char ISBNtemp[50]="";
	strcpy(ISBNtemp,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
	char temp[50] = "";
	DSDS.dausach[pageDS*10-10+demDS]->soluong+=sl;
	if (DSDS.dausach[pageDS*10-10+demDS]->FirstDMS==NULL) {
		p=new nodeDMS;
		char numStr[10];
		sprintf(numStr, "%d", 1);
		strcpy(p->data.MaSach,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
		strcat(p->data.MaSach,"-");
		strcat(p->data.MaSach,numStr);
		p->data.TrangThai=0;
		strcpy(p->data.ViTri,vitri);
		themdau(p->data,DSDS.dausach[pageDS*10-10+demDS]->FirstDMS);
		sl--;
		if (sl==0) {
			return;
		};
	}
	if (strcmp(DSDS.dausach[pageDS*10-10+demDS]->FirstDMS->data.MaSach,strcat(strcat(ISBNtemp,"-"),itoa(1,temp,10)))!=0) {
		p=new nodeDMS;
		char numStr[10];
		sprintf(numStr, "%d", 1);
		strcpy(p->data.MaSach,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
		strcat(p->data.MaSach,"-");
		strcat(p->data.MaSach,numStr);
		p->data.TrangThai=0;
		strcpy(p->data.ViTri,vitri);
		themdau(p->data,DSDS.dausach[pageDS*10-10+demDS]->FirstDMS);
		sl--;
		if (sl==0) {
			return;
		};
	}
	NodeDMS tmp = DSDS.dausach[pageDS*10-10+demDS]->FirstDMS;
	while (tmp->next!=NULL) {
		strcpy(ISBNtemp,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
		if (strcmp(tmp->next->data.MaSach,strcat(strcat(ISBNtemp,"-"),itoa(i,temp,10)))!=0) {
			p=new nodeDMS;
			char numStr[10];
			sprintf(numStr, "%d", i);
			strcpy(p->data.MaSach,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
			strcat(p->data.MaSach,"-");
			strcat(p->data.MaSach,numStr);
			p->data.TrangThai=0;
			strcpy(p->data.ViTri,vitri);
			Insert_after(tmp,p->data);
			sl--;
			if (sl==0) {
				return;
			};
		}
		i++;
		tmp=tmp->next;
	}
	while(sl!=0) {
		p=new nodeDMS;
		char numStr[10];
		sprintf(numStr, "%d", i);
		strcpy(p->data.MaSach,DSDS.dausach[pageDS*10-10+demDS]->ISBN);
		strcat(p->data.MaSach,"-");
		strcat(p->data.MaSach,numStr);
		p->data.TrangThai=0;
		strcpy(p->data.ViTri,vitri);
		themcuoi(p->data,tmp);
		sl--;
		i++;
	}
}
void swapint(int &a, int &b) {
	int temp  = a;
	a = b;
	b = temp;
}
int rdMang (int arr[], int sch) {
	int x = Random(0,7998-sch); //random tu 0 -> n-1
	swapint(arr[x],arr[7999-sch]);

	return arr[7999-sch];
}
void taoMangRd (int arr[], int min, int max) {
	for(int i = min; i <= max ; i++)
		arr[i-1]=i;
}
void DocFile_DocGia(CayDocGia &root) {
	std::fstream dg;
	dg.open("Data_DocGia.txt",std::ios::in);
	if(dg.fail()) {

		return ;
	}
	std::string luutam;
	int mathe;
	while(!dg.eof()) {
		DocGia member;
		dg>>member.mathe;
		getline(dg,luutam,'\n');
		dg>>member.trangthai;
		getline(dg,luutam,'\n');
		dg>>member.phai;
		member.slmuon=0;
		getline(dg,luutam,'\n');
		getline(dg,luutam,'\n');
		strcpy(member.ho, luutam.c_str());
		getline(dg,luutam,'\n');
		strcpy(member.ten,luutam.c_str());
		root.add(member);
	}
	dg.close();
}
void GhiDocGia(NodeDocGia node_temp) {
	std::ofstream outfile("Data_DocGia.txt",std::ios::app);
	outfile<<"\n"<<node_temp->member.mathe<<"\n";
	NodeMuonTra runner = node_temp->member.First;
	while (runner!=NULL) {
		if (runner->muontra.TrangThai==0 && runner->muontra.quahan>0) {
			node_temp->member.trangthai=1;
			break;
		}
		runner=runner->right;
	}
	outfile<<node_temp->member.trangthai<<"\n";
	outfile<<node_temp->member.phai<<"\n";
	outfile<<node_temp->member.ho<<"\n";
	outfile<<node_temp->member.ten;
	outfile.close();
}
void GhiFileDocGia(NodeDocGia node) {
	NodeDocGia Stack[MAX_SIZE_DG];
	std::ofstream outfile("Data_DocGia.txt");
	outfile<<"";
	NodeDocGia run=node;
	int sp=-1;
	while (run!=NULL) {
		GhiDocGia(run);
		if (run->right!=NULL) {
			Stack[++sp]=run->right;
		}
		if (run->left!=NULL) {
			run=run->left;
		} else if (sp==-1) {
			break;
		} else run=Stack[sp--];
	}
	outfile.close();
}
void DocFile_MuonTra(CayDocGia &tree,short &DemSach_qh, ListDauSach &l) {
	std::fstream Fin;
	Fin.open("Data_MuonTra.txt",std::ios::in);
	if(Fin.fail()) {
		message("Loi file MT");
		return;
	}
	NodeDocGia tmp;
	std::string luutam;
	int mathe;
	DemSach_qh=0;
	while(!Fin.eof()) {
		mathe=0;
		MuonTra mt;
		Fin>>mathe;
		getline(Fin,luutam,'\n');
		tmp=tree.findNode(mathe);
		Fin>>mt.TrangThai;
		getline(Fin,luutam,'\n');
		Fin>>mt.Time_Muon;
		getline(Fin,luutam,'\n');
		Fin>>mt.Time_Tra;
		getline(Fin,luutam,'\n');
		getline(Fin,luutam,'\n');
		strcpy(mt.MaSach,luutam.c_str());
		getline(Fin,luutam,'\n');
		strcpy(mt.NgayMuon,luutam.c_str());
		getline(Fin,luutam,'\n');
		strcpy(mt.NgayTra,luutam.c_str());
		mt.quahan=(time(0)-mt.Time_Muon)/86400-7;

		std::cout<<"sach dang muon co qua han: "<<mt.quahan;
		if (mt.TrangThai==0) {
			tmp->member.slmuon++;
		}
		InsertLastMuonTra(mt,tmp->member.First,tmp->member.Last,l);
		if (mt.quahan>0) DemSach_qh++;

	}
	Fin.close();
}
void findDocGia(int tt,DocGia *MangDocGia) {
	xoaTableDocGia();
	ininfoDocGiatuMang(tt,MangDocGia);
}
void GhiFile_DauSach(ListDauSach &DSDS) {
	std::ofstream outF;
	outF.open("Data_DauSachh.txt", std::ios::out);
	for(int i=0; i<DSDS.n; i++) {
		outF<<"\n\n";
		outF<<DSDS.dausach[i]->sotrang<<"\n";
		outF<<DSDS.dausach[i]->soluong<<"\n";
		outF<<DSDS.dausach[i]->nxb<<"\n";
		outF<<DSDS.dausach[i]->ISBN<<"\n";
		outF<<DSDS.dausach[i]->ten<<"\n";
		outF<<DSDS.dausach[i]->tacgia<<"\n";
		outF<<DSDS.dausach[i]->theloai;
	}
	outF.close();
}
void GhiFile_DMS(ListDauSach &DSDS) {
	NodeDMS chay;
	std::	ofstream outF_DMS;
	outF_DMS.open("Data_DanhMucSach.txt",std::ios:: out);

	for(int i=0; i<DSDS.n; i++) {
		for(chay=DSDS.dausach[i]->FirstDMS; chay!=NULL; chay=chay->next ) {
			outF_DMS<<chay->data.MaSach<<",";
			outF_DMS<<chay->data.ViTri<<",";
			outF_DMS<<chay->data.TrangThai<<"\n";
		}
		outF_DMS<<"\n";
	}
	outF_DMS.close();
}
void GhiFile_MuonTra(CayDocGia &tree) {
	std::ofstream Fout;
	Fout.open("Data_MuonTra.txt", std::ios::out);
	DocGia *MangDocGia=new DocGia[DemNut(tree.root)];
	int n=0;
	DoCayVaoMang(tree.root,MangDocGia,n);
	NodeMuonTra chay;
	for(int i=0; i<n; i++) {
		for(chay=MangDocGia[i].First; chay!=NULL; chay=chay->right) {
			Fout<<"\n"<<MangDocGia[i].mathe<<"\n";
			Fout<<chay->muontra.TrangThai<<"\n";
			Fout<<chay->muontra.Time_Muon<<"\n";
			Fout<<chay->muontra.Time_Tra<<"\n";
			Fout<<chay->muontra.MaSach<<"\n";
			Fout<<chay->muontra.NgayMuon<<"\n";
			Fout<<chay->muontra.NgayTra;
		}
	}
	Fout.close();
	delete MangDocGia;
	MangDocGia=NULL;
}
void choMuonSach(ListDauSach &l, int madocgia, NodeDocGia &target, char ms[]) {
	MuonTra mt;
	strcpy(mt.MaSach,ms);
	NodeDMS runner = l.dausach[findDauSachTuMaSach(ms,l)]->FirstDMS;
	std::cout<<"ma sach muon la: "<<runner->data.MaSach;
	while (runner!=NULL) {
		if (strcmp(ms,runner->data.MaSach)==0) {
			runner->data.TrangThai=1;
			break;
		}
		runner=runner->next;
	}
	NgayMuon(mt);
	mt.Time_Tra=0;
	mt.TrangThai=0;
	InsertLastMuonTra(mt,target->member.First,target->member.Last,l);
	target->member.slmuon++;
}
void trasach(NodeDocGia &target, int tt, ListDauSach &l) {
	NodeMuonTra tmp = target->member.First;
	int count = 0;
	while (tmp!=NULL) {
		std::cout<<tmp->muontra.MaSach<<" "<<tmp->muontra.TrangThai;
		if (tmp->muontra.TrangThai==0) {
			++count;
			if (count==tt) break;
		}
		tmp=tmp->right;
	}
	if (tmp==NULL) return;
	NgayTra(tmp->muontra);
	tmp->muontra.Time_Tra=time(0);
	tmp->muontra.TrangThai=1;
	--target->member.slmuon;
	tmp->muontra.quahan=0;
	NodeDMS runner = l.dausach[findDauSachTuMaSach(tmp->muontra.MaSach,l)]->FirstDMS;
	while (runner!=NULL) {
		if (strcmp(runner->data.MaSach,tmp->muontra.MaSach)==0) {
			runner->data.TrangThai=0;
		}
		runner=runner->next;
	}
}
void matsach(NodeDocGia &target, int tt, ListDauSach &l) {
	NodeMuonTra tmp = target->member.First;
	int count = 0;
	while (tmp!=NULL) {
		std::cout<<tmp->muontra.MaSach<<" "<<tmp->muontra.TrangThai;
		if (tmp->muontra.TrangThai==0) {
			++count;
			if (count==tt) break;
		}
		tmp=tmp->right;
	}
	if (tmp==NULL) return;
	tmp->muontra.TrangThai=2;
	--target->member.slmuon;
	tmp->muontra.quahan=0;
	NodeDMS runner = l.dausach[findDauSachTuMaSach(tmp->muontra.MaSach,l)]->FirstDMS;
	while (runner!=NULL) {
		if (strcmp(runner->data.MaSach,tmp->muontra.MaSach)==0) {
			runner->data.TrangThai=2;
		}
		runner=runner->next;
	}
}
void run() {
	srand(time(NULL));
	ListDauSach l;
	DocFile_DauSach(l);
	std::cout<<"hello";
	DocFile_DMS(l);
	CayDocGia tree;
	DocFile_DocGia(tree);
	short demsachqh;

	DocFile_MuonTra(tree,demsachqh,l);
	int n=8000;
	int arr_int[n];
	int arr_mathe_tree[DemNut(tree.root)];
	int m=0;
	DoMaTheVaoMang(tree.root,arr_mathe_tree,m);
	taoMangRd(arr_int,1,8000);
	int i=0;
	while (i<=n) {
		for (int j=0; j<=m; j++) {
			if (arr_int[i]==arr_mathe_tree[j]) {
				for (int k=i; k<n; k++) arr_int[k]=arr_int[k+1];
				n--;
				i--;
				break;
			}
		}
		i++;
	}
	DocGia *MangDocGia=new DocGia[DemNut(tree.root)];
	int quantityMDG = 0;
	DoCayVaoMang(tree.root,MangDocGia,quantityMDG);
	DocGia *MangMuonTra=new DocGia[demsachqh];
	int qh;

	int x;
	int y;
	showMenu();
	while (1) {
		x=-1;
		y=-1;
		delay(1);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if (x!=-1 && y!=-1) {
menu:
				switch(MAP[x][y]) {
					case 1: {
dausach:
						char isbn[20]="";
						int sotrang=0;
						int nxb=0;
						int soluong;
						char ten[50]="";
						char tacgia[50]="";
						char theloai[50]="";
						char vitri[50]="";
//						width 1 hang de highligh;
						int width[7]= {0,120,300,120,195,120,200};
						int height = 40;
						int flag=0;
						int maxPageDS = l.n==10 ? 1 : (l.n/10)+1;
						std::cout<<"Max Page DS: "<<maxPageDS;
						int pageDS = 1;
						int nFindDs = 0;
						int findDs[l.n];
						bool cantFind = false;
						resetDauSach(pageDS,maxPageDS,l);
						std::string MangTheLoai[20];
						int soluongtheloai=0,stttheloai=0,pageTL=0,maxpageTL=0;
						while (1) {
							x=-1;
							y=-1;
							delay(1);
							if (ismouseclick(WM_LBUTTONDOWN)) {
								getmouseclick(WM_LBUTTONDOWN,x,y);
								if (x!=-1 && y!=-1) {
									int chon = MAP[x][y];
									DauSach tmp;
									std::cout<<"y: "<<y<<"\n";
									switch(chon) {

										case 11: {
											if (flag!=0) continue;
											scannerCapslock(410,25,isbn,10,11,chon,MAP);
											break;
										}
										case 12: {
											if (flag!=0) continue;
											scannerHoTen(800,25,ten,20,12,chon,MAP);
											break;
										}
										case 13: {
											if (flag!=0) continue;
											setbkcolor(violet);
											setfillstyle(1,violet);
											bar(345,55,680,82);
											settextstyle(10,0,2);
											outtextxy(348,58,"So Trang: ");
											char tmp[]="";
											scannerNums(460,58,tmp,5,13,chon,MAP);
											sotrang=atoi(tmp);
											break;
										}
										case 14: {
											scannerHoTen(790,58,tacgia,20,14,chon,MAP);
											break;
										}
										case 15: {
											if (flag!=0) continue;
											setbkcolor(violet);
											setfillstyle(1,violet);
											bar(345,88,680,115);
											settextstyle(10,0,2);
											outtextxy(348,91,"Nam Xuat Ban: ");
											char tmp[]="";
											scannerNums(510,91,tmp,5,13,chon,MAP);
											nxb=atoi(tmp);
											break;
										}
										case 16: {
											if (flag!=0) continue;
											scannerString(800,91,theloai,20,16,chon,MAP);
											break;
										}
										case 17: {
											if (flag!=0) continue;
											setbkcolor(violet);
											setfillstyle(1,violet);
											bar(1077,22,1377,49);
											settextstyle(10,0,2);
											outtextxy(1080,25,"So Luong: ");
											char tmp[]="";
											scannerNums(1192,25,tmp,5,13,chon,MAP);
											soluong=atoi(tmp);
											break;
										}
										case 18: {
											if (flag!=0) continue;
											scannerString(1170,58,vitri,20,18,chon,MAP);
											break;
										}
										case 19: {
											if (flag!=0) continue;
											if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(vitri)==0 || nxb==0 || soluong ==0 || sotrang==0) {
												message("Khong duoc de trong");
											} else if (nxb>2023) {
												message("nxb khong hop le");
											} else if (checkTrungISBN(isbn,l)) {
												message("ISBN bi trung");
											} else {
												tmp=dausach(isbn,ten,sotrang,tacgia,nxb,theloai,soluong);
												int k = InsertDauSach(l,tmp);
												InsertDMS(l,k,vitri);
												maxPageDS=l.n/10+1;
												clearDauSach(isbn,sotrang,nxb,ten,tacgia,theloai,soluong,vitri);
												inKhungDauSach();
												inTableDauSach(l,pageDS);
												inSoTrang(pageDS,maxPageDS);
												message("Them dau sach thanh cong");
											}
											break;
										}
										case 111: {
											if (flag!=0) continue;
											clearDauSach(isbn,sotrang,nxb,ten,tacgia,theloai,soluong,vitri);
											break;
										}
										case 112: {
											if (flag!=0 || cantFind) continue;
											char tmp[50]="";
											bartrangcovien(900,124,1200,158);
											scannerHoTen(910,129,tmp,20,112,chon,MAP);
											if (strlen(tmp)!=0) {
												std::string str(tmp);
												if (findDauSach(str,l,findDs,nFindDs)==1) {
													std::cout<<"da tim thay"<<nFindDs;
													pageTL=1;
													maxpageTL=nFindDs/10+1;
													inKhungDauSach();
													InDauSachTheoDK(l,height,findDs,nFindDs,pageTL);
													inSoTrang(pageTL,maxpageTL);
												}
												strcpy(tmp,"");
											} else message("Khong duoc bo trong");
											break;
										}
										case 113: {
											flag=1;
											ListDauSach tmpListDS;
											copyListDS(l,tmpListDS);
											SortDS(tmpListDS,0,tmpListDS.n-1);
											int pageTopDS = 1;
											int rank=1;;
											int quantityTopDS = top10ds(tmpListDS,pageTopDS,rank);
//											std::cout<<quantityTopDS;
											int maxPageTopDS = quantityTopDS/10+1;
											inSoTrang(pageTopDS,maxPageTopDS);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if(ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 1131: {
																if(pageTopDS-1>=1) {
																	rank=1;
																	pageTopDS=1;
																	top10ds(tmpListDS,pageTopDS,rank);
																	inSoTrang(pageTopDS,maxPageTopDS);
																}
																break;
															}
															case 1132: {
																if(pageTopDS+1<=maxPageTopDS) {
																	++pageTopDS;
																	top10ds(tmpListDS,pageTopDS,rank);
																	inSoTrang(pageTopDS,maxPageTopDS);
																}
																break;
															}
															default: {
																if (MAP[x][y]==1 || MAP[x][y]==2 || MAP[x][y]==3 || MAP[x][y]==4) goto menu;
																continue;
																break;
															}
														}
													}
												}
											}
											break;
										}
										case 114: {
											if (nFindDs>0) {
												if (pageTL-1>=1) {
													pageTL--;
													inKhungDauSach();
													InDauSachTheoDK(l,height,findDs,nFindDs,pageTL);
													inSoTrang(pageTL,maxpageTL);
												}
											} else {
												if (pageDS-1>=1) {
													inKhungDauSach();
													inTableDauSach(l,--pageDS);
													inSoTrang(pageDS,maxPageDS);
												}
											}

											break;
										}
										case 115: {
											if (nFindDs>0) {
												if(pageTL+1<=maxpageTL) {
													pageTL++;
													inKhungDauSach();
													InDauSachTheoDK(l,height,findDs,nFindDs,pageTL);
													inSoTrang(pageTL,maxpageTL);
												}
											} else {
												if (pageDS+1<=maxPageDS) {
													inKhungDauSach();
													inTableDauSach(l,++pageDS);
													inSoTrang(pageDS,maxPageDS);
												}
											}

											break;
										}
										case 1127: {
											bool check;
											cantFind = true;
											for (int i=0; i<l.n; i++) {
												check=true;
												for (int j=0; j<soluongtheloai; j++) {
													if (strcmp(l.dausach[i]->theloai,MangTheLoai[j].c_str())==0) {
														check=false;
														break;
													}
												}
												if (check) {
													MangTheLoai[soluongtheloai]=l.dausach[i]->theloai;
													std::cout<<"|"<<MangTheLoai[soluongtheloai];
													soluongtheloai++;
												}
											}
											findDauSachTheoTheLoai(MangTheLoai,l,findDs,nFindDs,stttheloai);
											pageTL=1;
											maxpageTL=nFindDs/10+1;
											InDauSachTheoDK(l,height,findDs,nFindDs,pageTL);
											createButton(920,630,220,55," The Loai Ke Tiep",0,11271);
											createButton(620,630,110,55," Tro ve ",0,11272);
										}
										case 11271: {
											if (stttheloai==soluongtheloai-1) stttheloai=0;
											else stttheloai++;
											findDauSachTheoTheLoai(MangTheLoai,l,findDs,nFindDs,stttheloai);
											pageTL=1;
											maxpageTL=nFindDs/10+1;
											InDauSachTheoDK(l,height,findDs,nFindDs,pageTL);
											inSoTrang(pageTL,maxpageTL);
											break;
										}
										case 11272: {
											goto dausach;
											break;
										}
										case 101: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int demDS = nFindDs > 0 ? findDs[0] : 0;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*1,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms1:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms1;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 102: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (1<nFindDs) {
													demDS = findDs[1];
												} else continue;
											} else demDS=1;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*2,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms2:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms2;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 103: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (2<nFindDs) {
													demDS = findDs[2];
												} else continue;
											} else demDS=2;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*3,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms3:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms3;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 104: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (3<nFindDs) {
													demDS = findDs[3];
												} else continue;
											} else demDS=3;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*4,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms4:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms4;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 105: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (4<nFindDs) {
													demDS = findDs[4];
												} else continue;
											} else demDS=4;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*5,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms5:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms5;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 106: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (5<nFindDs) {
													demDS = findDs[5];
												} else continue;
											} else demDS=5;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*6,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms6:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms6;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 107: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int demDS;
											int checkXoaDS=0;
											if (nFindDs > 0) {
												if (6<nFindDs) {
													demDS = findDs[6];
												} else continue;
											} else demDS=6;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*7,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms7:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms7;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 108: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (7<nFindDs) {
													demDS = findDs[7];
												} else continue;
											} else demDS=7;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*8,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms8:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms8;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 109: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int demDS;
											int checkXoaDS=0;
											if (nFindDs > 0) {
												if (8<nFindDs) {
													demDS = findDs[8];
												} else continue;
											} else demDS=8;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*9,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms9:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms9;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										case 110: {
											setfillstyle(1,pink);
											bar(920,630,1140,685);
											bar(620,630,730,685);
											int checkXoaDS=0;
											int demDS;
											if (nFindDs > 0) {
												if (9<nFindDs) {
													demDS = findDs[9];
												} else continue;
											} else demDS=9;
											if (pageDS*10-10+demDS>=l.n) {
												continue;
											}
											highlightBox(330,180+height*10,40,width,6);
											tabDauSach(x+30,y+10);
											while(1) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN))  {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														switch(MAP[x][y]) {
															case 118: {
																if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL)
																	message2("Khong the xoa dau sach","co danh muc sach!");
																else deleteDauSach(l,pageDS*10-10+demDS);
																goto dausach;
																break;
															}
															case 116: {
																char temp[]="";
																strcpy(isbn,l.dausach[pageDS*10-10+demDS]->ISBN);
																nxb = l.dausach[pageDS*10-10+demDS]->nxb;
																int st = l.dausach[pageDS*10-10+demDS]->sotrang;
																strcpy(theloai,l.dausach[pageDS*10-10+demDS]->theloai);
																strcpy(tacgia,l.dausach[pageDS*10-10+demDS]->tacgia);
																strcpy(ten,l.dausach[pageDS*10-10+demDS]->ten);
																showHieuChinhDS();
																setbkcolor(violet);
																setcolor(0);
																outtextxy(770,275,isbn);
																outtextxy(760,325,ten);
																outtextxy(800,375,tacgia);
																outtextxy(810,425,theloai);
																outtextxy(750,475,itoa(nxb,temp,10));
																outtextxy(810,525,itoa(st,temp,10));
																while(1) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);

																		if (x!=-1 && y!=-1) {
																			std::cout<<MAP[x][y];
																			chon = MAP[x][y];
																			switch(chon) {
																				case 1161: {
																					if (l.dausach[pageDS*10-10+demDS]->FirstDMS!=NULL) {
																						message2("Khong the sua ISBN dau","sach co danh muc sach");
																					} else {
																						scannerCapslock(770,275,isbn,21,1161,chon,MAP);
																					}
																					break;
																				}
																				case 1162: {
																					scannerHoTen(760,325,ten,20,1161,chon,MAP);
																					break;
																				}
																				case 1163: {
																					scannerHoTen(800,375,tacgia,20,1161,chon,MAP);
																					break;
																				}
																				case 1164: {
																					scannerString(810,425,theloai,20,1161,chon,MAP);
																					break;
																				}
																				case 1165: {
																					strcpy(temp,itoa(nxb,temp,10));
																					scannerNums(750,475,temp,20,1161,chon,MAP);
																					nxb=atoi(temp);
																					break;
																				}
																				case 1166: {
																					strcpy(temp,itoa(st,temp,10));
																					scannerNums(810,525,temp,20,1161,chon,MAP);
																					st=atoi(temp);
																					break;
																				}
																				case 1167: {
																					if (strlen(isbn)==0 || strlen(ten)==0 || strlen(tacgia)==0 || strlen(theloai)==0 ||  nxb==0 || st==0) {
																						message("Khong duoc de trong");
																					} else if (nxb>2023) {
																						message("nxb khong hop le");
																					} else if (checkTrungISBN(isbn,l) && strcmp(isbn,l.dausach[pageDS*10-10+demDS]->ISBN)!=0) {
																						message("ISBN bi trung");
																					} else {
																						DauSach ds = dausach(isbn,ten,st,tacgia,nxb,theloai,l.dausach[pageDS*10-10+demDS]->soluong);
																						int slm=l.dausach[pageDS*10-10+demDS]->soluotmuon;
																						ds.FirstDMS=l.dausach[pageDS*10-10+demDS]->FirstDMS;
																						deleteDauSach(l,pageDS*10-10+demDS);
																						int k=InsertDauSach(l,ds);
																						l.dausach[k]->soluotmuon=slm;
																						message2("Hieu chinh dau sach thanh","cong!");
																						goto dausach;
																					}
																					break;
																				}
																				case 1168: {
																					goto dausach;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 117: {
dms10:
																char qty[50];
																strcpy(qty,"");
																char area[50];
																strcpy(area,"");
																int checkXoaDS=0;
																flag=1;
																int maxPageDMS = tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)==10 ? 1 : tongLinkedList(l.dausach[ pageDS*10-10+demDS]->FirstDMS)/10+1;
																int pageDMS = 1;
																inKhungDMS();
																inTableDMS(l,pageDMS,pageDS*10-10+demDS);
																while(1) {
																	x=-1;
																	y=-1;
																	inSoTrang(pageDMS,maxPageDMS);
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			switch(MAP[x][y]) {
																				case 111: {
																					if(pageDMS-1>=1) {
																						inKhungDMS();
																						inTableDMS(l,--pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 112: {
																					if(pageDMS+1<=maxPageDMS) {
																						inKhungDMS();
																						inTableDMS(l,++pageDMS,pageDS*10-10+demDS);
																						inSoTrang(pageDMS,maxPageDMS);
																					}
																					break;
																				}
																				case 113: {
																					bartrangcovien(550,136,650,160);
																					scannerNums(560,137,qty,2,113,chon,MAP);
																					break;
																				}
																				case 114: {
																					bartrangcovien(680,136,875,160);
																					scannerString(690,137,area,50,114,chon,MAP);
																					break;
																				}
																				case 115: {
																					std::cout<<"\n"<<area<<"\n";
																					if (strlen(qty)==0 || strlen(area) == 0) message("Khong duoc bo trong!");
																					else {
																						addThemDMS(l,pageDS,demDS,atoi(qty),area);
																						message("Them DMS thanh cong!");
																						goto dms10;
																					}
																					break;
																				}
																				case 101: {
																					xoaDMS(0,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 102: {
																					xoaDMS(1,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 103: {
																					xoaDMS(2,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 104: {
																					xoaDMS(3,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 105: {
																					xoaDMS(4,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 106: {
																					xoaDMS(5,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 107: {
																					xoaDMS(6,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 108: {
																					xoaDMS(7,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 109: {
																					xoaDMS(8,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				case 110: {
																					xoaDMS(9,pageDMS,pageDS,maxPageDMS,demDS,l,checkXoaDS,tree,MangDocGia);
																					break;
																				}
																				default:
																					if (MAP[x][y]!=111 && MAP[x][y]!=112 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																					nFindDs=0;
																					goto menu;
																			}
																		}
																	}
																}
																break;
															}
															default: {
																goto dausach;
																break;
															}
														}
													}
												}
											}
										}
										default:
											if (MAP[x][y]==0 || MAP[x][y]==100) {
												continue;
											};
											goto menu;
									}
								}
							}
						}
						break;
					}
					case 2: {
docgia:
						showMenu();
						chosenMenu(20,80,290,55," DANH SACH DOC GIA",textColor,2);
						showDocGia();
						int loc=0;
						int pageDG=1,maxpageDG;
						int height = 40;
						int width[6]= {0,150,300,200,200,205};
						bool checkadd=false;
						maxpageDG=DemNut(tree.root)==10 ? 1 : (DemNut(tree.root)/10)+1;
						InDocGia(tree.root,MangDocGia,pageDG,loc);
						inSoTrang(pageDG,maxpageDG);
						createTableID(330,180,40,1055,200,10);
						highlightred(439,127,510,158); //highlight sap xep theo id;
						while (1) {
							x=-1;
							y=-1;
							int	trangthai=-1;
							int phai=-1;
							//	bool flag_phai=false,flag_trangthai=false;
							delay(1);
							if (ismouseclick(WM_LBUTTONDOWN)) {
								getmouseclick(WM_LBUTTONDOWN,x,y);
								if (x!=-1 && y!=-1) {
									int chon = MAP[x][y];
									std::cout<<chon<<"\n";
									switch(chon) {
										case 215: { // sap xep ten
											loc=1;
											highlightred(359,127,430,158);
											xoahighlightredpink(439,127,510,158);
											showDocGia();
											InDocGia(tree.root,MangDocGia,pageDG,loc);
											inSoTrang(pageDG,maxpageDG);
											break;
										}
										case 216: { // sap xep mathe
											loc=0;
											highlightred(439,127,510,158);
											xoahighlightredpink(359,127,430,158);
											showDocGia();
											InDocGia(tree.root,MangDocGia,pageDG,loc);
											inSoTrang(pageDG,maxpageDG);
											break;
										}
										case 212: { //tim kiem theo ID
											bool checkFind = false;
											char numtmp[10]="";
											bartrangcovien(900,124,1200,158);
											scannerNums(910,129,numtmp,10,212,chon,MAP);
											int num=atoi(numtmp);
											NodeDocGia target;
											target=tree.findNode(num);
											std::cout<<"denday   ";
											if (target->member.mathe!=num)
												message("Khong tim thay");
											else {
												checkFind = true;
timkiemDG:
												xoaTableDocGia();
												ininfoDocGiaTuCay(target);
												inSachDGMuonTuCay(target,l);
												std::cout<<"da tim thay   ";
											}
											bool checksua=false,checkxoa=false,checkluu=false;
											while (checkluu==false && checkFind == true) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						showDocGia();
																						InDocGia(tree.root,MangDocGia,pageDG,loc);
																						inSoTrang(pageDG,maxpageDG);
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]==0 && MAP[x][y]==0) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto timkiemDG;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 213: {
																					goto timkiemDG;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 213: {
																					goto timkiemDG;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto timkiemDG;
																					}
																					break;
																				}
																				case 213: {
																					goto timkiemDG;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=23 && MAP[x][y]!=24) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 22: { //lui trang
											std::cout<<"Max page: "<<maxpageDG<<"Current Page"<<pageDG<<"\n";
											if (pageDG-1>=1) {
												std::cout<<"lui trang";
												pageDG--;
												showDocGia();
												InDocGia(tree.root,MangDocGia,pageDG,loc);
												inSoTrang(pageDG,maxpageDG);
											}
											break;
										}
										case 23: { //trang sau
											std::cout<<"Max page: "<<maxpageDG<<"Current Page"<<pageDG<<"\n";
											if (pageDG+1<=maxpageDG) {
												std::cout<<"sang trang";
												pageDG++;
												showDocGia();
												InDocGia(tree.root,MangDocGia,pageDG,loc);
												inSoTrang(pageDG,maxpageDG);
											}
											break;
										}
										case 24: { //them doc gia
											int mathe=rdMang(arr_int,m);
											settextstyle(10,0,2);
											createButton5(620,128,70,30," ADD",textColor,243); // tao nut add;
											char tmp[50]="";

											settextstyle(10,0,1);
											setbkcolor(violet);
											setcolor(0);
											outtextxy(438,25,itoa(mathe,tmp,10));

											char ho[30]="",ten[10]="";
											int phai=-1;
											trangthai=0;
											highlightred(1020,87,1145,117);
											scannerHoTen(384,58,ho,30,233,chon,MAP);
											xoahighlightredpink(1180,87,1310,117);
											while (checkadd==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 231: {
																std::cout<<"nam";
																phai=0;
																highlightred(1050,53,1120,83);
																xoahighlightredpink(1150,53,1215,83);
																break;
															}
															case 232: {
																std::cout<<"nu";
																highlightred(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																phai=1;
																break;
															}
															case 233: {
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																break;
															}
															case 234: {
																scannerHoTen(397,91,ten,30,234,chon,MAP);
																break;
															}
//															case 241:{
//																std::cout<<"active";
//																highlightred(1020,87,1145,117);
//																xoahighlightredpink(1180,87,1310,117);
//																trangthai=1;
//																break;
//																		}
//															case 242:{
//																std::cout<<"inac";
//																highlightred(1180,87,1310,117);
//																xoahighlightredpink(1020,87,1145,117);
//																trangthai=0;
//																break;
//																}
															case 243: {
																if (strlen(ho)==0 || strlen(ten)==0) {
																	message("Khong duoc bo trong!");
																} else if (phai==-1) message("Chon Gioi Tinh!");
																else {
																	std::cout<<"them dg "<<mathe;
																	DocGia newdg;
																	newdg=themdocgia(mathe,ho,ten,phai,trangthai,0);
																	m++;
																	tree.add(newdg);
																	maxpageDG=DemNut(tree.root)/10+1;
																	showDocGia();
																	InDocGia(tree.root,MangDocGia,pageDG,loc);
																	inSoTrang(pageDG,maxpageDG);
																	checkadd=true;
																}
																break;
															}
															default:
																if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=23 && MAP[x][y]!=24) continue;
																goto menu;
														}
													}
												}
											}
											xoahighlightredpink(1150,53,1215,83);
											xoahighlightredpink(1050,53,1120,83);
											xoahighlightredpink(1180,87,1310,117);
											xoahighlightredpink(1020,87,1145,117);
											break;
										}
										case 25: {
											break;
										}
										case 26: {
											break;
										}
										case 231: {
											break;
										}
										case 232: {
											break;
										}
										case 241: {
											break;
										}
										case 242: {
											break;
										}
										case 201: {

											if ((pageDG-1)*10 > DemNut(tree.root) || DemNut(tree.root)==0) continue;
											highlightBox(330,180+height*1,40,width,5);
docgia1:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														std::cout<<"ID: "<<chon<<"\n";
														switch(chon) {

															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=MangDocGia[(pageDG-1)*10].phai;
																trangthai=MangDocGia[(pageDG-1)*10].trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {

																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];

																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia1;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia1;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia1;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia1;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia1;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia1;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia1;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia1;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia1;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia1;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 202: {

											if ((pageDG-1)*10+1 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*2,40,width,5);
docgia2:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+1].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+1,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														std::cout<<"ID: "<<chon<<"\n";
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia2;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia2;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia2;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia2;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia2;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia2;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia2;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia2;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia2;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia2;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}

										case 203: {
											if ((pageDG-1)*10+2 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*3,40,width,5);
docgia3:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+2].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+2,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia3;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia3;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia3;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia3;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia3;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia3;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia3;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia3;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia3;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia3;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 204: {
											if ((pageDG-1)*10+3 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*4,40,width,5);
docgia4:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+3].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+3,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia4;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia4;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia4;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia4;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia4;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia4;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia4;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia4;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia4;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia4;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 205: {
											if ((pageDG-1)*10+4 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*5,40,width,5);
docgia5:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+4].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+4,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia5;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia5;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia5;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia5;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia5;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia5;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia5;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia5;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia5;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia5;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 206: {
											if ((pageDG-1)*10+5 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*6,40,width,5);
docgia6:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+5].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+5,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia6;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia6;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia6;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia6;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia6;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia6;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia6;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia6;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia6;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia6;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 207: {
											if ((pageDG-1)*10+6 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*7,40,width,5);
docgia7:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+6].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+6,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia7;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia7;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia7;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia7;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia7;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia7;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia7;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia7;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia7;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia7;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 208: {
											if ((pageDG-1)*10+7 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*8,40,width,5);
docgia8:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+7].mathe);
											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+7,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia8;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia8;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia8;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia8;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia8;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia8;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia8;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia8;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia8;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia8;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 209: {
											if ((pageDG-1)*10+8 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*9,40,width,5);
											bool checksua=false,checkxoa=false,checkluu=false;
docgia9:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+8].mathe);
											findDocGia((pageDG-1)*10+8,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="",ten[10]="";
																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,30,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia9;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia9;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia9;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia9;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia9;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia9;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia9;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia9;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia9;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia9;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										case 210: {
											if ((pageDG-1)*10+9 >= DemNut(tree.root)) continue;
											highlightBox(330,180+height*10,40,width,5);
docgia10:
											NodeDocGia target;
											target=tree.findNode(MangDocGia[(pageDG-1)*10+9].mathe);

											bool checksua=false,checkxoa=false,checkluu=false;
											findDocGia((pageDG-1)*10+9,MangDocGia);
											inSachDGMuonTuCay(target,l);
											while (checkluu==false) {
												x=-1;
												y=-1;
												delay(1);
												if (ismouseclick(WM_LBUTTONDOWN)) {
													getmouseclick(WM_LBUTTONDOWN,x,y);
													if (x!=-1 && y!=-1) {
														int chon = MAP[x][y];
														switch(chon) {
															case 21: { //sua
																fixkhunghoten();
																char ho[30]="";
																char ten[10]="";

																int phai=target->member.phai;
																trangthai=target->member.trangthai;
																if (phai==0) highlightred(1050,53,1120,83);
																else highlightred(1150,53,1215,83);
																if (trangthai==0) highlightred(1020,87,1145,117);
																else highlightred(1180,87,1310,117);
																strcpy(ho,target->member.ho);
																strcpy(ten,target->member.ten);
																settextstyle(10,0,1);
																outtextxy(386,58,ho);
																outtextxy(399,91,ten);
																settextstyle(10,0,2);
																scannerHoTen(384,58,ho,30,233,chon,MAP);
																std::cout<<ho<<"|"<<ten;
																while (checksua==false) {
																	x=-1;
																	y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 231: {
																					std::cout<<"nam";
																					highlightred(1050,53,1120,83);
																					xoahighlightredpink(1150,53,1215,83);
																					phai=0;
																					break;
																				}
																				case 232: {
																					std::cout<<"nu";
																					highlightred(1150,53,1215,83);
																					xoahighlightredpink(1050,53,1120,83);
																					phai=1;
																					break;
																				}
																				case 233: {
																					scannerHoTen(384,58,ho,30,233,chon,MAP);
																					break;
																				}
																				case 234: {
																					scannerHoTen(397,91,ten,10,234,chon,MAP);
																					break;
																				}
																				case 241: {
																					if (checkQuaHan(target)) {
																						message2("Doc gia qua han khong", "the mo khoa!");
																					} else {
																						std::cout<<"active";
																						highlightred(1020,87,1145,117);
																						xoahighlightredpink(1180,87,1310,117);
																						trangthai=0;
																					}
																					break;
																				}
																				case 242: {
																					std::cout<<"inac";
																					highlightred(1180,87,1310,117);
																					xoahighlightredpink(1020,87,1145,117);
																					trangthai=1;
																					break;
																				}
																				case 214: {
																					if (strlen(ten)==0 || strlen(ho)==0) message("Khong duoc bo trong!");
																					else if ((phai==-1)||(trangthai==-1)) message("Chon Phai, Trang thai");
																					else {
																						DocGia newdg;
																						newdg=themdocgia(target->member.mathe,ho,ten,phai,trangthai,target->member.slmuon);
																						newdg.First=target->member.First;
																						newdg.Last=target->member.Last;
																						tree.add(newdg);
																						checksua=true;
																						checksua=true;
																						checkluu=true;
																						goto docgia;
																					}
																					break;
																				}
																				default:
																					if (MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4 && MAP[x][y]!=231 && MAP[x][y]!=232 && MAP[x][y]!=233 && MAP[x][y]!=234 && MAP[x][y]!=241 && MAP[x][y]!=242) continue;
																					goto menu;
																			}
																		}
																	}
																}
																xoahighlightredpink(1150,53,1215,83);
																xoahighlightredpink(1050,53,1120,83);
																xoahighlightredpink(1180,87,1310,117);
																xoahighlightredpink(1020,87,1145,117);
																break;
															}
															case 24: { //xoa
																if (target->member.slmuon!=0) {
																	message2("Khong the xoa doc gia", "dang muon sach!");
																} else {
																	if (yesnoBox("Ban co muon xoa ?",MAP)) {
																		tree.remove(target->member.mathe);
																		message("Xoa doc gia thanh cong!");
																		goto docgia;
																	}
																}
																break;
															}
															case 25: {
																goto docgia;
																break;
															}
															case 26: {
																if (chechSLM(target)) message2("Khong the muon qua 3", "quyen sach!");
																else {
																	char tmp[50]="";
																	std::cout<<"Trang thai: "<<target->member.trangthai;
																	setbkcolor(0);
																	bartrangcovien(500,200,800,230);
																	scannerMaSach(510,204,tmp,50,26,chon,MAP);
																	int index = findDauSachTuMaSach(tmp,l);
																	if (index == 999)
																		message2("Khong tim thay ma sach", "phu hop!");
																	else if (checkDMSMuonChua(l,index,tmp)==0) message2("Khong tim thay ma sach", "phu hop!");
																	else if(target->member.trangthai==1) message2("The dang bi khoa khong","the muon!");
																	else if (!checkConDMS(l,index)) message2("Dau sach nay hien da het","sach!");
																	else if (checkDMSMuonChua(l,index,tmp)==1) message2("Ma sach da cho muon hoac","bi thanh li!");
																	else if(checkMuonTrungDauSach(tmp,target->member.First,l)) message2("Khong the muon trung dau","sach!");
																	else {
																		if (yesnoBox("Ban co chac chan?",MAP)) {
																			choMuonSach(l,target->member.mathe,target,tmp);
																			message("Da cho muon thanh cong");
																			goto docgia10;
																		}
																	}
																}
																break;
															}
															case 27: {
																if (target->member.slmuon<1) continue;
																xoahighlightred(330,420,330+1055,500);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,340,330+1055,420);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);

																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,1,l);
																						message("Sach da thanh li!");
																						goto docgia10;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,1,l);
																						message("Tra sach thanh cong!");
																						goto docgia10;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia10;
																					break;
																				}
																			}
																		}
																	}
																}
															}
															case 28: {
																if (target->member.slmuon<2) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,500,330+1055,580);
																highlightred(330,420,330+1055,500);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,2,l);
																						goto docgia10;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,2,l);
																						goto docgia10;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia10;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															case 29: {
																if (target->member.slmuon<3) continue;
																xoahighlightred(330,340,330+1055,420);
																xoahighlightred(330,420,330+1055,500);
																highlightred(330,500,330+1055,580);
																settextstyle(10,0,1);
																createButton5(950,200,70,30," DEN",15,211);
																createButton5(1050,200,70,30," TRA",15,212);
																createButton6(1150,200,70,30," HUY",15,213);
																while (true) {
																	int x=-1;
																	int y=-1;
																	delay(1);
																	if (ismouseclick(WM_LBUTTONDOWN)) {
																		getmouseclick(WM_LBUTTONDOWN,x,y);
																		if (x!=-1 && y!=-1) {
																			int chon = MAP[x][y];
																			switch(chon) {
																				case 211: {
																					if (yesnoBox("Ban co chac chan",MAP)) {
																						matsach(target,3,l);
																						goto docgia10;
																					}
																					break;
																				}
																				case 212: {
																					if(yesnoBox("Ban co chac chan", MAP)) {
																						trasach(target,3,l);
																						goto docgia10;
																					}
																					break;
																				}
																				case 213: {
																					goto docgia10;
																					break;
																				}
																			}
																		}
																	}
																}
																break;
															}
															default:
																if (MAP[x][y]!=21 && MAP[x][y]!=24 && MAP[x][y]!=1 && MAP[x][y]!=2 && MAP[x][y]!=3 && MAP[x][y]!=4) continue;
																goto menu;
														}
													}
												}
											}
											break;
										}
										default:
											if (MAP[x][y]==0 || MAP[x][y]==200 || MAP[x][y]==233 || MAP[x][y]==234 ) {
												continue;
											};
											goto menu;
									}
								}
							}
						}
					}
					case 3: {
						showMenu();
						qh=0;
						DoMuonTraVaoMang(tree.root,MangMuonTra,qh);
						SortMT(MangMuonTra,0,qh-1);
						chosenMenu(20,145,290,55,"  QUAN LI MUON TRA",textColor,3);
						int pageMT = 1;
						inKhungMuonTra();
						std::cout<<"showmuontra"<<std::endl;
						std::cout<<MangMuonTra[0].First->muontra.MaSach;
						showMuonTra(MangMuonTra,pageMT,qh,l);
						short maxPageMT = qh==14 ? 1 : (qh/14)+1;
						inSoTrang(pageMT,maxPageMT);
						while (1) {
							x=-1;
							y=-1;
							delay(1);
							if (ismouseclick(WM_LBUTTONDOWN)) {
								getmouseclick(WM_LBUTTONDOWN,x,y);
//								std::cout<<"ID: "<<MAP[x][y]<<"\n";
								if (x!=-1 && y!=-1) {
									switch(MAP[x][y]) {
										case 31: {
											std::cout<<"trang truoc\n";
											if (pageMT-1>=1) {
												inKhungMuonTra();
												showMuonTra(MangMuonTra,--pageMT,qh,l);
												inSoTrang(pageMT,maxPageMT);
											}
											break;
										}
										case 32: {
											std::cout<<"trang sau\n";
											if (pageMT+1<=maxPageMT) {
												inKhungMuonTra();
												showMuonTra(MangMuonTra,++pageMT,qh,l);
												inSoTrang(pageMT,maxPageMT);
											}
											break;
										}
										default:
											if (MAP[x][y]==1 || MAP[x][y]==2 || MAP[x][y]==3 || MAP[x][y]==4) goto menu;
											continue;;

									}
								}
							}
						}
						break;
					}
					case 4: {
						GhiFile_DauSach(l);
						GhiFile_DMS(l);
						GhiFile_MuonTra(tree);
						GhiFileDocGia(tree.root);
						std::cout<<"Ket thuc chuong trinh.";
						closegraph();
						return;
						break;
					}
				}
			}
		}
	}
}
