#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;
enum loaivong {
    vongloai = 1,
    tuket = 2,
    banket = 3,
    chungket = 4
};

string doitenvong(loaivong loai) {
    switch (loai) {
        case vongloai:
            return "Vong loai";
        case tuket:
            return "Tu ket";
        case banket:
            return "Ban ket";
        case chungket:
            return "Chung ket";
        default:
            return "Khong xac dinh";
    }
}

class cauthu {
private:
    string macauthu;
    string tencauthu;
    int tuoi;
    string vitri;
    int soao;

public:
    cauthu() {
        tuoi = 0;
        soao = 0;
    }

    cauthu(string macauthu, string tencauthu, int tuoi, string vitri, int soao) {
        this->macauthu = macauthu;
        this->tencauthu = tencauthu;
        this->tuoi = tuoi;
        this->vitri = vitri;
        this->soao = soao;
    }

    void nhap() {
        cout << "Nhap ma cau thu: ";
        getline(cin, macauthu);

        cout << "Nhap ten cau thu: ";
        getline(cin, tencauthu);

        cout << "Nhap tuoi: ";
        cin >> tuoi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap vi tri thi dau: ";
        getline(cin, vitri);

        cout << "Nhap so ao: ";
        cin >> soao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void hienthi() const {
        cout << left
             << setw(15) << macauthu
             << setw(25) << tencauthu
             << setw(10) << tuoi
             << setw(20) << vitri
             << setw(10) << soao
             << endl;
    }

    string laytencauthu() const {
        return tencauthu;
    }
};

class doibong {
private:
    string madoi;
    string tendoi;
    string tenhuanluyenvien;
    vector<cauthu> danhsachcauthu;

    int diemso;
    int sotrandadau;
    int sotrangthang;
    int sotranhoa;
    int sotranthua;
    int tongbanthang;
    int tongbanthua;

public:
    doibong() {
        khoitaothongke();
    }

    doibong(string madoi, string tendoi, string tenhuanluyenvien) {
        this->madoi = madoi;
        this->tendoi = tendoi;
        this->tenhuanluyenvien = tenhuanluyenvien;
        khoitaothongke();
    }

    void khoitaothongke() {
        diemso = 0;
        sotrandadau = 0;
        sotrangthang = 0;
        sotranhoa = 0;
        sotranthua = 0;
        tongbanthang = 0;
        tongbanthua = 0;
    }

    void nhap() {
        cout << "Nhap ma doi: ";
        getline(cin, madoi);

        cout << "Nhap ten doi: ";
        getline(cin, tendoi);

        cout << "Nhap ten huan luyen vien: ";
        getline(cin, tenhuanluyenvien);

        khoitaothongke();
    }

    void themcauthu(const cauthu& cauthumoi) {
        danhsachcauthu.push_back(cauthumoi);
    }

    void nhapdanhsachcauthu() {
        int soluong;
        cout << "Nhap so cau thu cua doi " << tendoi << ": ";
        cin >> soluong;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < soluong; i++) {
            cout << "\n--- Nhap cau thu thu " << i + 1 << " ---\n";
            cauthu cauthumoi;
            cauthumoi.nhap();
            themcauthu(cauthumoi);
        }
    }

    void capnhatthongke(int sobanthang, int sobanthua) {
        sotrandadau++;
        tongbanthang += sobanthang;
        tongbanthua += sobanthua;

        if (sobanthang > sobanthua) {
            sotrangthang++;
            diemso += 3;
        } else if (sobanthang == sobanthua) {
            sotranhoa++;
            diemso += 1;
        } else {
            sotranthua++;
        }
    }

    int layhieuso() const {
        return tongbanthang - tongbanthua;
    }

    void hienthithongtincoban() const {
        cout << left
             << setw(12) << madoi
             << setw(25) << tendoi
             << setw(25) << tenhuanluyenvien
             << setw(10) << danhsachcauthu.size()
             << endl;
    }

    void hienthicauthu() const {
        cout << "\nDANH SACH CAU THU DOI: " << tendoi << endl;
        cout << left
             << setw(15) << "Ma CT"
             << setw(25) << "Ten cau thu"
             << setw(10) << "Tuoi"
             << setw(20) << "Vi tri"
             << setw(10) << "So ao"
             << endl;
        cout << string(80, '-') << endl;

        if (danhsachcauthu.empty()) {
            cout << "Chua co cau thu nao.\n";
            return;
        }

        for (const cauthu& cau : danhsachcauthu) {
            cau.hienthi();
        }
    }

    void hienthixephang(int thuhang) const {
        cout << left
             << setw(6) << thuhang
             << setw(25) << tendoi
             << setw(8) << sotrandadau
             << setw(8) << sotrangthang
             << setw(8) << sotranhoa
             << setw(8) << sotranthua
             << setw(8) << tongbanthang
             << setw(8) << tongbanthua
             << setw(8) << layhieuso()
             << setw(8) << diemso
             << endl;
    }

    string laymadoi() const {
        return madoi;
    }

    string laytendoi() const {
        return tendoi;
    }

    int laydiemso() const {
        return diemso;
    }

    int laytongbanthang() const {
        return tongbanthang;
    }

    int laytongbanthua() const {
        return tongbanthua;
    }
};

class trandau {
private:
    doibong* doithunhat;
    doibong* doithuhai;
    string thoigian;
    loaivong loaivongdau;
    int banthangdoithunhat;
    int banthangdoithuhai;
    bool dadau;
    doibong* doithang;

public:
    trandau() {
        doithunhat = nullptr;
        doithuhai = nullptr;
        banthangdoithunhat = 0;
        banthangdoithuhai = 0;
        dadau = false;
        doithang = nullptr;
        loaivongdau = vongloai;
    }

    trandau(doibong* doithunhat, doibong* doithuhai, string thoigian, loaivong loaivongdau) {
        this->doithunhat = doithunhat;
        this->doithuhai = doithuhai;
        this->thoigian = thoigian;
        this->loaivongdau = loaivongdau;
        this->banthangdoithunhat = 0;
        this->banthangdoithuhai = 0;
        this->dadau = false;
        this->doithang = nullptr;
    }

    void nhapketqua() {
        if (doithunhat == nullptr || doithuhai == nullptr) {
            cout << "Tran dau khong hop le.\n";
            return;
        }

        cout << "\nNhap ket qua tran: "
             << doithunhat->laytendoi() << " vs " << doithuhai->laytendoi() << endl;

        cout << "So ban thang cua " << doithunhat->laytendoi() << ": ";
        cin >> banthangdoithunhat;

        cout << "So ban thang cua " << doithuhai->laytendoi() << ": ";
        cin >> banthangdoithuhai;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        dadau = true;

        if (loaivongdau == vongloai) {
            doithunhat->capnhatthongke(banthangdoithunhat, banthangdoithuhai);
            doithuhai->capnhatthongke(banthangdoithuhai, banthangdoithunhat);

            if (banthangdoithunhat > banthangdoithuhai) {
                doithang = doithunhat;
            } else if (banthangdoithuhai > banthangdoithunhat) {
                doithang = doithuhai;
            } else {
                doithang = nullptr;
            }
        } else {
            if (banthangdoithunhat > banthangdoithuhai) {
                doithang = doithunhat;
            } else if (banthangdoithuhai > banthangdoithunhat) {
                doithang = doithuhai;
            } else {
                int luachon;
                cout << "Tran loai truc tiep khong duoc hoa.\n";
                cout << "Chon doi thang sau hiep phu hoac penalty:\n";
                cout << "1. " << doithunhat->laytendoi() << endl;
                cout << "2. " << doithuhai->laytendoi() << endl;
                cout << "Lua chon: ";
                cin >> luachon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (luachon == 1) {
                    doithang = doithunhat;
                } else {
                    doithang = doithuhai;
                }
            }
        }

        cout << "Da cap nhat ket qua tran dau.\n";
    }

    void hienthi(int stt) const {
        cout << left
             << setw(6) << stt
             << setw(18) << doitenvong(loaivongdau)
             << setw(25) << (doithunhat ? doithunhat->laytendoi() : "NULL")
             << setw(25) << (doithuhai ? doithuhai->laytendoi() : "NULL")
             << setw(20) << thoigian;

        if (dadau) {
            string tyso = to_string(banthangdoithunhat) + " - " + to_string(banthangdoithuhai);
            cout << setw(15) << tyso;

            if (doithang != nullptr) {
                cout << setw(25) << doithang->laytendoi();
            } else {
                cout << setw(25) << "Hoa";
            }
        } else {
            cout << setw(15) << "Chua dau"
                 << setw(25) << "Chua xac dinh";
        }

        cout << endl;
    }

    bool laytrangthaidau() const {
        return dadau;
    }

    doibong* laydoithang() const {
        return doithang;
    }
};

class vongdau {
private:
    loaivong loaivongdau;
    vector<trandau> danhsachtrandau;

public:
    vongdau() {
        loaivongdau = vongloai;
    }

    vongdau(loaivong loaivongdau) {
        this->loaivongdau = loaivongdau;
    }

    void themtrandau(const trandau& tranmoi) {
        danhsachtrandau.push_back(tranmoi);
    }

    void nhaptatcaketqua() {
        if (danhsachtrandau.empty()) {
            cout << "Chua co tran dau nao trong " << doitenvong(loaivongdau) << ".\n";
            return;
        }

        for (int i = 0; i < (int)danhsachtrandau.size(); i++) {
            cout << "\n=== Tran " << i + 1 << " / " << danhsachtrandau.size() << " ===\n";
            if (!danhsachtrandau[i].laytrangthaidau()) {
                danhsachtrandau[i].nhapketqua();
            } else {
                cout << "Tran nay da nhap ket qua roi.\n";
            }
        }
    }

    void hienthilichthidau() const {
        cout << "\nLICH THI DAU / KET QUA: " << doitenvong(loaivongdau) << endl;
        cout << left
             << setw(6) << "STT"
             << setw(18) << "Vong"
             << setw(25) << "Doi 1"
             << setw(25) << "Doi 2"
             << setw(20) << "Thoi gian"
             << setw(15) << "Ty so"
             << setw(25) << "Doi thang"
             << endl;
        cout << string(134, '-') << endl;

        if (danhsachtrandau.empty()) {
            cout << "Chua co lich thi dau.\n";
            return;
        }

        for (int i = 0; i < (int)danhsachtrandau.size(); i++) {
            danhsachtrandau[i].hienthi(i + 1);
        }
    }

    vector<doibong*> laycacdoithang() const {
        vector<doibong*> cacdoithang;

        for (const trandau& tran : danhsachtrandau) {
            if (tran.laytrangthaidau() && tran.laydoithang() != nullptr) {
                cacdoithang.push_back(tran.laydoithang());
            }
        }

        return cacdoithang;
    }
};

class giaidau {
private:
    string tengiaidau;
    vector<doibong> danhsachdoi;
    vongdau vongdauphanloai;
    vongdau vongdautuket;
    vongdau vongdaubanket;
    vongdau vongdauchungket;
    doibong* doivochdich;

public:
    giaidau() {
        tengiaidau = "Giai dau bong da";
        vongdauphanloai = vongdau(vongloai);
        vongdautuket = vongdau(tuket);
        vongdaubanket = vongdau(banket);
        vongdauchungket = vongdau(chungket);
        doivochdich = nullptr;
    }

    void nhapthongtingiaidau() {
        cout << "Nhap ten giai dau: ";
        getline(cin, tengiaidau);
        cout << "Da khoi tao giai dau: " << tengiaidau << endl;
    }

    void nhapdanhsachdoi() {
        int soluong;
        cout << "Nhap so doi tham gia: ";
        cin >> soluong;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        danhsachdoi.clear();

        for (int i = 0; i < soluong; i++) {
            cout << "\n--- Nhap thong tin doi thu " << i + 1 << " ---\n";
            doibong doimoi;
            doimoi.nhap();
            danhsachdoi.push_back(doimoi);
        }
    }

    void nhapcauthuchotungdoi() {
        if (danhsachdoi.empty()) {
            cout << "Chua co doi bong. Vui long nhap danh sach doi truoc.\n";
            return;
        }

        for (doibong& doi : danhsachdoi) {
            cout << "\n==============================\n";
            doi.nhapdanhsachcauthu();
        }
    }

    void hienthidanhsachdoi() const {
        cout << "\nDANH SACH DOI BONG - " << tengiaidau << endl;
        cout << left
             << setw(12) << "Ma doi"
             << setw(25) << "Ten doi"
             << setw(25) << "HLV"
             << setw(10) << "So CT"
             << endl;
        cout << string(75, '-') << endl;

        if (danhsachdoi.empty()) {
            cout << "Chua co doi bong nao.\n";
            return;
        }

        for (const doibong& doi : danhsachdoi) {
            doi.hienthithongtincoban();
        }
    }

    void hienthidanhsachcauthu() const {
        if (danhsachdoi.empty()) {
            cout << "Chua co doi bong nao.\n";
            return;
        }

        for (const doibong& doi : danhsachdoi) {
            doi.hienthicauthu();
        }
    }

    void taolichvongloai() {
        if (danhsachdoi.size() < 2) {
            cout << "Can it nhat 2 doi de tao lich thi dau.\n";
            return;
        }

        vongdauphanloai = vongdau(vongloai);
        int sothutran = 1;

        for (int i = 0; i < (int)danhsachdoi.size(); i++) {
            for (int j = i + 1; j < (int)danhsachdoi.size(); j++) {
                string thoigian = "Ngay " + to_string(sothutran);
                vongdauphanloai.themtrandau(trandau(&danhsachdoi[i], &danhsachdoi[j], thoigian, vongloai));
                sothutran++;
            }
        }

        cout << "Da tao lich thi dau vong loai theo the thuc vong tron.\n";
    }

    vector<doibong*> laybangxephang() const {
        vector<doibong*> bangxephang;

        for (const doibong& doi : danhsachdoi) {
            bangxephang.push_back(const_cast<doibong*>(&doi));
        }

        sort(bangxephang.begin(), bangxephang.end(), [](doibong* doia, doibong* doib) {
            if (doia->laydiemso() != doib->laydiemso()) {
                return doia->laydiemso() > doib->laydiemso();
            }

            if (doia->layhieuso() != doib->layhieuso()) {
                return doia->layhieuso() > doib->layhieuso();
            }

            if (doia->laytongbanthang() != doib->laytongbanthang()) {
                return doia->laytongbanthang() > doib->laytongbanthang();
            }

            return doia->laytendoi() < doib->laytendoi();
        });

        return bangxephang;
    }

    void hienthibangxephang() const {
        vector<doibong*> bangxephang = laybangxephang();

        cout << "\nBANG XEP HANG VONG LOAI - " << tengiaidau << endl;
        cout << left
             << setw(6) << "Hang"
             << setw(25) << "Doi bong"
             << setw(8) << "Tran"
             << setw(8) << "Thang"
             << setw(8) << "Hoa"
             << setw(8) << "Thua"
             << setw(8) << "BT"
             << setw(8) << "BB"
             << setw(8) << "HS"
             << setw(8) << "Diem"
             << endl;
        cout << string(95, '-') << endl;

        if (bangxephang.empty()) {
            cout << "Chua co du lieu xep hang.\n";
            return;
        }

        for (int i = 0; i < (int)bangxephang.size(); i++) {
            bangxephang[i]->hienthixephang(i + 1);
        }
    }

    vector<doibong*> chondoimanhnhat(int soluongchon) const {
        vector<doibong*> bangxephang = laybangxephang();
        vector<doibong*> cacdoiduocchon;
        int gioihan = min(soluongchon, (int)bangxephang.size());

        for (int i = 0; i < gioihan; i++) {
            cacdoiduocchon.push_back(bangxephang[i]);
        }

        return cacdoiduocchon;
    }

    void taovongloaitructiep(loaivong loaicanlap, const vector<doibong*>& cacdoiduocchon) {
        if (cacdoiduocchon.size() < 2 || cacdoiduocchon.size() % 2 != 0) {
            cout << "So doi khong hop le de tao " << doitenvong(loaicanlap) << ".\n";
            return;
        }

        vongdau vongmoi(loaicanlap);
        int benphai = (int)cacdoiduocchon.size() - 1;
        int bentrai = 0;
        int sothutran = 1;

        while (bentrai < benphai) {
            string thoigian = doitenvong(loaicanlap) + " - Tran " + to_string(sothutran);
            vongmoi.themtrandau(trandau(cacdoiduocchon[bentrai], cacdoiduocchon[benphai], thoigian, loaicanlap));
            bentrai++;
            benphai--;
            sothutran++;
        }

        if (loaicanlap == tuket) {
            vongdautuket = vongmoi;
        } else if (loaicanlap == banket) {
            vongdaubanket = vongmoi;
        } else if (loaicanlap == chungket) {
            vongdauchungket = vongmoi;
        }

        cout << "Da tao lich thi dau " << doitenvong(loaicanlap) << ".\n";
    }

    void taotuket() {
        int soluongdoi;
        cout << "Nhap so doi vao tu ket, thuong la 8 doi: ";
        cin >> soluongdoi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (soluongdoi <= 0 || soluongdoi % 2 != 0) {
            cout << "So doi phai la so chan va lon hon 0.\n";
            return;
        }

        vector<doibong*> cacdoiduocchon = chondoimanhnhat(soluongdoi);

        cout << "\nCAC DOI DUOC CHON VAO TU KET:\n";
        for (doibong* doi : cacdoiduocchon) {
            cout << "- " << doi->laytendoi() << endl;
        }

        taovongloaitructiep(tuket, cacdoiduocchon);
    }

    void taobanket() {
        vector<doibong*> cacdoithang = vongdautuket.laycacdoithang();

        if (cacdoithang.empty()) {
            cout << "Chua co ket qua tu ket hoac chua tao tu ket.\n";
            return;
        }

        taovongloaitructiep(banket, cacdoithang);
    }

    void taochungket() {
        vector<doibong*> cacdoithang = vongdaubanket.laycacdoithang();

        if (cacdoithang.empty()) {
            cout << "Chua co ket qua ban ket hoac chua tao ban ket.\n";
            return;
        }

        taovongloaitructiep(chungket, cacdoithang);
    }

    void nhapketquatheovong() {
        int luachon;
        cout << "\nChon vong can nhap ket qua:\n";
        cout << "1. Vong loai\n";
        cout << "2. Tu ket\n";
        cout << "3. Ban ket\n";
        cout << "4. Chung ket\n";
        cout << "Lua chon: ";
        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luachon) {
            case 1:
                vongdauphanloai.nhaptatcaketqua();
                break;
            case 2:
                vongdautuket.nhaptatcaketqua();
                break;
            case 3:
                vongdaubanket.nhaptatcaketqua();
                break;
            case 4:
                vongdauchungket.nhaptatcaketqua();
                capnhatdoivochdich();
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }

    void capnhatdoivochdich() {
        vector<doibong*> cacdoithang = vongdauchungket.laycacdoithang();

        if (!cacdoithang.empty()) {
            doivochdich = cacdoithang[0];
        }
    }

    void hienthilichvaketqua() const {
        int luachon;
        cout << "\nChon lich thi dau / ket qua can xem:\n";
        cout << "1. Vong loai\n";
        cout << "2. Tu ket\n";
        cout << "3. Ban ket\n";
        cout << "4. Chung ket\n";
        cout << "5. Tat ca\n";
        cout << "Lua chon: ";
        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luachon) {
            case 1:
                vongdauphanloai.hienthilichthidau();
                break;
            case 2:
                vongdautuket.hienthilichthidau();
                break;
            case 3:
                vongdaubanket.hienthilichthidau();
                break;
            case 4:
                vongdauchungket.hienthilichthidau();
                break;
            case 5:
                vongdauphanloai.hienthilichthidau();
                vongdautuket.hienthilichthidau();
                vongdaubanket.hienthilichthidau();
                vongdauchungket.hienthilichthidau();
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }

    void hienthidoivochdich() const {
        if (doivochdich == nullptr) {
            cout << "Chua xac dinh doi vo dich. Hay nhap ket qua tran chung ket truoc.\n";
        } else {
            cout << "\n====================================\n";
            cout << "DOI VO DICH GIAI DAU: " << doivochdich->laytendoi() << endl;
            cout << "====================================\n";
        }
    }

    void menutaovongdau() {
        int luachon;

        cout << "\nTAO VONG DAU\n";
        cout << "1. Tao lich vong loai\n";
        cout << "2. Chon doi va tao tu ket tu bang xep hang\n";
        cout << "3. Tao ban ket tu doi thang tu ket\n";
        cout << "4. Tao chung ket tu doi thang ban ket\n";
        cout << "Lua chon: ";
        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luachon) {
            case 1:
                taolichvongloai();
                break;
            case 2:
                taotuket();
                break;
            case 3:
                taobanket();
                break;
            case 4:
                taochungket();
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }
};

void hienthimenu() {
    cout << "\n================ MENU QUAN LY GIAI DAU BONG DA ================\n";
    cout << "1. Khoi tao / nhap ten giai dau\n";
    cout << "2. Nhap danh sach doi tham gia\n";
    cout << "3. Nhap cau thu cho tung doi\n";
    cout << "4. Hien thi danh sach doi bong\n";
    cout << "5. Hien thi danh sach cau thu\n";
    cout << "6. Tao cac vong dau / lich thi dau\n";
    cout << "7. Nhap ket qua tran dau\n";
    cout << "8. Hien thi lich thi dau va ket qua\n";
    cout << "9. Hien thi bang xep hang\n";
    cout << "10. Hien thi doi vo dich\n";
    cout << "0. Thoat\n";
    cout << "================================================================\n";
    cout << "Nhap lua chon: ";
}

int main() {
    giaidau giaidaubongda;
    int luachon;

    do {
        hienthimenu();
        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luachon) {
            case 1:
                giaidaubongda.nhapthongtingiaidau();
                break;
            case 2:
                giaidaubongda.nhapdanhsachdoi();
                break;
            case 3:
                giaidaubongda.nhapcauthuchotungdoi();
                break;
            case 4:
                giaidaubongda.hienthidanhsachdoi();
                break;
            case 5:
                giaidaubongda.hienthidanhsachcauthu();
                break;
            case 6:
                giaidaubongda.menutaovongdau();
                break;
            case 7:
                giaidaubongda.nhapketquatheovong();
                break;
            case 8:
                giaidaubongda.hienthilichvaketqua();
                break;
            case 9:
                giaidaubongda.hienthibangxephang();
                break;
            case 10:
                giaidaubongda.hienthidoivochdich();
                break;
            case 0:
                cout << "Dang thoat chuong trinh...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    } while (luachon != 0);

    return 0;
}
