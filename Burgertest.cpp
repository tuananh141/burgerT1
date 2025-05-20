#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

template <typename T>
T getInputValidated(const string &prompt, const string &errorMessage = "  Lỗi: Dữ liệu nhập không hợp lệ. Vui lòng thử lại.")
{
    T value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMessage << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void veDuongNgang(int chieuDai, char kyTu = '-')
{
    for (int i = 0; i < chieuDai; ++i)
    {
        cout << kyTu;
    }
    cout << endl;
}

string stringToUpper(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

struct LuaChonDoiDiem
{
    int id;
    int diemCanDoi;
    string moTaPhanThuong;
    string loaiPhanThuong; // "QUA_TANG", "GIAM_GIA_PHAN_TRAM"
    double giaTri;         // Đối với GIAM_GIA_PHAN_TRAM, đây là % (vd: 0.12 cho 12%). Đối với QUA_TANG là 0.

    LuaChonDoiDiem(int _id, int _diem, string _moTa, string _loai, double _giaTri = 0)
        : id(_id), diemCanDoi(_diem), moTaPhanThuong(_moTa), loaiPhanThuong(_loai), giaTri(_giaTri) {}
    void hienThi() const
    {
        cout << "  ID: " << id << " | Điểm: " << diemCanDoi << " | Phần thưởng: " << moTaPhanThuong;
        if (loaiPhanThuong == "GIAM_GIA_PHAN_TRAM")
        {
            cout << " (Giảm " << fixed << setprecision(0) << giaTri * 100 << "%)";
        }
        cout << endl;
    }
};

class MenuItem
{
private:
    string ten;
    string moTa;
    int soLuong;
    double gia;

public:
    MenuItem(string ten, string moTa, int soLuong, double gia)
        : ten(ten), moTa(moTa), soLuong(soLuong), gia(gia) {}
    virtual ~MenuItem() {}
    string getTen() const { return ten; }
    string getMoTa() const { return moTa; }
    int getSoLuong() const { return soLuong; }
    double getGia() const { return gia; }
    void setTen(const string &newTen) { ten = newTen; }
    void setMoTa(const string &newMoTa) { moTa = newMoTa; }
    void setSoLuong(int newSoLuong) { soLuong = newSoLuong; }
    void setGia(double newGia) { gia = newGia; }

    virtual string getType() const = 0;

    virtual void hienThiThongTin() const
    {
        cout << "  Tên: " << ten << endl;
        if (!moTa.empty())
        {
            cout << "  Mô tả: " << moTa << endl;
        }
        cout << "  Số lượng: " << soLuong << endl;
        cout << "  Giá: " << fixed << setprecision(0) << gia << " VNĐ" << endl;
    }

    virtual void luuVaoFile(ofstream &ofs) const
    {
        ofs << ten << endl;
        ofs << moTa << endl;
        ofs << soLuong << endl;
        ofs << gia << endl;
    }
};

class Burger : public MenuItem
{
private:
    string loaiThit;

public:
    Burger(string tenGocBurger, string moTaBurger, int soLuong, double gia, string loaiThit)
        : MenuItem("Burger - " + tenGocBurger, moTaBurger, soLuong, gia), loaiThit(loaiThit) {}
    string getLoaiThit() const { return loaiThit; }
    void setLoaiThit(const string &newLoaiThit) { loaiThit = newLoaiThit; }

    string getType() const override { return "Burger"; }

    void hienThiThongTin() const override
    {
        MenuItem::hienThiThongTin();
        cout << "  Loại thịt: " << loaiThit << endl;
    }

    void luuVaoFile(ofstream &ofs) const override
    {
        ofs << getType() << endl;
        MenuItem::luuVaoFile(ofs);
        ofs << loaiThit << endl;
    }
};

class Drink : public MenuItem
{
private:
    string kichThuoc;

public:
    Drink(string tenGocNuocUong, int soLuong, double gia, string kichThuocVal)
        : MenuItem("Nước uống - " + tenGocNuocUong + " (" + kichThuocVal + ")", "", soLuong, gia),
          kichThuoc(kichThuocVal) {}
    string getKichThuoc() const { return kichThuoc; }
    void setKichThuoc(const string &newKichThuoc)
    {
        kichThuoc = newKichThuoc;
    }

    string getTenGoc() const
    {
        string tenDayDu = getTen();
        string prefix = "Nước uống - ";
        string suffix = " (" + kichThuoc + ")";
        if (tenDayDu.rfind(prefix, 0) == 0)
        {
            tenDayDu = tenDayDu.substr(prefix.length());
        }
        if (tenDayDu.length() >= suffix.length() &&
            tenDayDu.substr(tenDayDu.length() - suffix.length()) == suffix)
        {
            return tenDayDu.substr(0, tenDayDu.length() - suffix.length());
        }
        size_t openParen = tenDayDu.rfind(" (");
        if (openParen != string::npos)
        {
            return tenDayDu.substr(0, openParen);
        }
        return tenDayDu;
    }
    string getType() const override { return "Drink"; }

    void hienThiThongTin() const override
    {
        MenuItem::hienThiThongTin();
        cout << "  Kích thước: " << kichThuoc << endl;
    }

    void luuVaoFile(ofstream &ofs) const override
    {
        ofs << getType() << endl;
        MenuItem::luuVaoFile(ofs);
        ofs << kichThuoc << endl;
    }
};

class KhachHang
{
private:
    string username;
    string password;
    string ten;
    string soDienThoai;
    string diaChi;
    bool daMuaLanDau;
    int diemTichLuy;

public:
    KhachHang(string _username, string _password, string _ten, string _sdt, string _dc, bool _daMua = false, int _diem = 0)
        : username(_username), password(_password), ten(_ten), soDienThoai(_sdt), diaChi(_dc),
          daMuaLanDau(_daMua), diemTichLuy(_diem) {}

    KhachHang(string _ten, string _sdt, string _dc)
        : username(""), password(""), ten(_ten), soDienThoai(_sdt), diaChi(_dc),
          daMuaLanDau(true), diemTichLuy(0) {}
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getTen() const { return ten; }
    string getSoDienThoai() const { return soDienThoai; }
    string getDiaChi() const { return diaChi; }
    bool getDaMuaLanDau() const { return daMuaLanDau; }
    int getDiemTichLuy() const { return diemTichLuy; }

    void setPassword(const string &newPass) { password = newPass; }
    void setTen(const string &newTen) { ten = newTen; }
    void setSoDienThoai(const string &newSdt) { soDienThoai = newSdt; }
    void setDiaChi(const string &newDc) { diaChi = newDc; }
    void setDaMuaLanDau(bool mua) { daMuaLanDau = mua; }

    void themDiem(int diem)
    {
        if (diem > 0)
        {
            diemTichLuy += diem;
        }
    }
    bool suDungDiem(int diemCanDung)
    {
        if (diemCanDung > 0 && diemTichLuy >= diemCanDung)
        {
            diemTichLuy -= diemCanDung;
            return true;
        }
        return false;
    }

    void hienThiThongTin(bool laAdminXem = false) const
    {
        if (laAdminXem && !username.empty())
        {
            cout << "  Username: " << username << endl;
        }
        cout << "  Tên thành viên: " << ten << endl;
        cout << "  Số điện thoại: " << soDienThoai << endl;
        cout << "  Địa chỉ: " << diaChi << endl;
        cout << "  Điểm tích lũy: " << diemTichLuy << " điểm" << endl;
        if (!username.empty())
        {
            cout << "  Trạng thái mua lần đầu (thành viên): " << (daMuaLanDau ? "Đã áp dụng" : "Chưa áp dụng") << endl;
        }
    }

    void luuVaoFile(ofstream &ofs) const
    {
        ofs << username << endl;
        ofs << password << endl;
        ofs << ten << endl;
        ofs << soDienThoai << endl;
        ofs << diaChi << endl;
        ofs << daMuaLanDau << endl;
        ofs << diemTichLuy << endl;
    }
};

class NhanVien
{
private:
    int maNV;
    string tenNV;
    string soDienThoaiNV;
    string diaChiNV;

public:
    NhanVien(int ma, string ten, string sdt, string dc)
        : maNV(ma), tenNV(ten), soDienThoaiNV(sdt), diaChiNV(dc) {}
    int getMaNV() const { return maNV; }
    string getTenNV() const { return tenNV; }
    string getSoDienThoaiNV() const { return soDienThoaiNV; }
    string getDiaChiNV() const { return diaChiNV; }
    void setTenNV(const string &ten) { tenNV = ten; }
    void setSoDienThoaiNV(const string &sdt) { soDienThoaiNV = sdt; }
    void setDiaChiNV(const string &dc) { diaChiNV = dc; }
    void hienThiThongTin() const
    {
        cout << "  Mã nhân viên: " << maNV << endl;
        cout << "  Tên nhân viên: " << tenNV << endl;
        cout << "  Số điện thoại: " << soDienThoaiNV << endl;
        cout << "  Địa chỉ: " << diaChiNV << endl;
    }
    void luuVaoFile(ofstream &ofs) const
    {
        ofs << maNV << endl;
        ofs << tenNV << endl;
        ofs << soDienThoaiNV << endl;
        ofs << diaChiNV << endl;
    }
};

class DonHang
{
private:
    int maDonHang;
    KhachHang khachHangDat;
    vector<pair<MenuItem *, int>> danhSachMonAn;
    double tongTienGoc;
    double tongTienThucTe;
    vector<string> quaTangDaDoi;

public:
    DonHang(int ma, const KhachHang &kh) : maDonHang(ma), khachHangDat(kh), tongTienGoc(0), tongTienThucTe(0) {}
    DonHang(int ma, const KhachHang &kh, double goc, double thucte)
        : maDonHang(ma), khachHangDat(kh), tongTienGoc(goc), tongTienThucTe(thucte) {}
    int getMaDonHang() const { return maDonHang; }
    const KhachHang &getKhachHangDat() const { return khachHangDat; }
    const vector<pair<MenuItem *, int>> &getDanhSachMonAn() const { return danhSachMonAn; }
    double getTongTienGoc() const { return tongTienGoc; }
    double getTongTienThucTe() const { return tongTienThucTe; }
    const vector<string> &getQuaTangDaDoi() const { return quaTangDaDoi; }

    void themMonAn(MenuItem *mon, int soLuong)
    {
        danhSachMonAn.push_back({mon, soLuong});
        tinhLaiTongTienGoc();
    }
    void tinhLaiTongTienGoc()
    {
        tongTienGoc = 0;
        for (const auto &item : danhSachMonAn)
        {
            if (item.first)
                tongTienGoc += item.first->getGia() * item.second;
        }
    }
    void setTongTienThucTe(double amount)
    {
        tongTienThucTe = amount;
    }
    void themQuaTangDaDoi(const string &tenQua)
    {
        quaTangDaDoi.push_back(tenQua);
    }

    void hienThiThongTin() const
    {
        cout << "\n  --- Đơn hàng #" << maDonHang << " ---" << endl;
        cout << "  --- Thông tin khách đặt hàng ---" << endl;
        cout << "  Tên khách hàng: " << khachHangDat.getTen() << endl;
        cout << "  Số điện thoại: " << khachHangDat.getSoDienThoai() << endl;
        cout << "  Địa chỉ: " << khachHangDat.getDiaChi() << endl;
        cout << "  --- Món ăn đã đặt ---" << endl;
        for (const auto &item : danhSachMonAn)
        {
            if (item.first)
            {
                cout << "  - " << item.first->getTen() << " (x" << item.second << ") - "
                     << fixed << setprecision(0) << item.first->getGia() * item.second << " VNĐ" << endl;
            }
            else
            {
                cout << "  - [Món ăn không xác định] (x" << item.second << ")" << endl;
            }
        }
        if (!quaTangDaDoi.empty())
        {
            cout << "  --- Quà tặng đã đổi ---" << endl;
            for (const string &qua : quaTangDaDoi)
            {
                cout << "  - " << qua << endl;
            }
        }
        cout << "  Tổng tiền gốc: " << fixed << setprecision(0) << tongTienGoc << " VNĐ" << endl;
        if (tongTienThucTe != tongTienGoc && tongTienThucTe != 0)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << tongTienThucTe << " VNĐ" << endl;
        }
        else if (tongTienGoc > 0 && tongTienThucTe == 0 && tongTienGoc != tongTienThucTe)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << tongTienGoc << " VNĐ (Chưa bao gồm giảm giá/điểm)" << endl;
        }
        else if (tongTienGoc == tongTienThucTe && tongTienGoc != 0)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << tongTienThucTe << " VNĐ" << endl;
        }
        else if (tongTienGoc == 0 && tongTienThucTe == 0 && quaTangDaDoi.empty())
        {
            cout << "  Tổng tiền thanh toán: 0 VNĐ" << endl;
        }
        else if (tongTienGoc == 0 && !quaTangDaDoi.empty() && tongTienThucTe == 0)
        {
            cout << "  Tổng tiền thanh toán: 0 VNĐ (Đổi quà bằng điểm)" << endl;
        }
    }
    void luuVaoFile(ofstream &ofs) const
    {
        ofs << maDonHang << endl;
        ofs << khachHangDat.getSoDienThoai() << endl;
        ofs << khachHangDat.getTen() << endl;
        ofs << khachHangDat.getDiaChi() << endl;
        ofs << tongTienGoc << endl;
        ofs << tongTienThucTe << endl;
        ofs << danhSachMonAn.size() << endl;
        for (const auto &pair_item : danhSachMonAn)
        {
            if (pair_item.first)
            {
                ofs << pair_item.first->getTen() << endl;
                ofs << pair_item.second << endl;
            }
        }
        ofs << quaTangDaDoi.size() << endl;
        for (const string &qua : quaTangDaDoi)
        {
            ofs << qua << endl;
        }
    }
};

class CuaHangBurger
{
private:
    vector<MenuItem *> danhSachMenu;
    vector<KhachHang> danhSachThanhVien;
    vector<DonHang> danhSachDonHang;
    vector<NhanVien> danhSachNhanVien;
    vector<LuaChonDoiDiem> danhSachLuaChonDoiDiem; // Sẽ được khởi tạo cố định

    KhachHang *thanhVienHienTai = nullptr;
    bool isAdminLoggedIn = false;
    string adminUsername = "admin";
    string adminPassword = "admin123";

    string tenCuaHang;
    string diaChiCuaHang;
    string soDienThoaiCuaHang;
    int maDonHangTiepTheo;
    int maNhanVienTiepTheo;
    double giamGiaLanDau = 0.1;
    int soLuongLonDeGiamGia = 5;
    double giamGiaSoLuongLon = 0.05;
    const int GIA_TRI_VND_CHO_MOT_DIEM = 1000;

    const string FILE_MENU = "menu.txt";
    const string FILE_THANHVIEN = "memberacc.txt";
    const string FILE_NHANVIEN = "nhanvien.txt";
    const string FILE_DONHANG = "donhang.txt";
    const string FILE_CUAHANG = "cuahang.txt";
    const string FILE_ADMINACC = "adminacc.txt";

    void khoiTaoLuaChonDoiDiemCoDinh()
    {
        danhSachLuaChonDoiDiem.clear(); // Xóa nếu có dữ liệu cũ (từ lần chạy trước nếu có lỗi)
        // ID 1: Giảm giá %; ID 2-4: Quà tặng
        danhSachLuaChonDoiDiem.emplace_back(1, 1000, "Giảm 12% giá trị đơn hàng hiện tại", "GIAM_GIA_PHAN_TRAM", 0.12);
        danhSachLuaChonDoiDiem.emplace_back(2, 150, "Móc khoá", "QUA_TANG", 0);
        danhSachLuaChonDoiDiem.emplace_back(3, 250, "Gấu bông", "QUA_TANG", 0);
        danhSachLuaChonDoiDiem.emplace_back(4, 500, "Bình nước giữ nhiệt", "QUA_TANG", 0);
    }

    void taiAdminAcc()
    {
        ifstream ifs(FILE_ADMINACC);
        if (ifs.is_open())
        {
            string line;
            if (getline(ifs, line))
            {
                stringstream ss(line);
                string user, pass;
                if (getline(ss, user, ':') && getline(ss, pass))
                {
                    adminUsername = user;
                    adminPassword = pass;
                }
            }
            ifs.close();
        }
        else
        {
            ofstream ofs(FILE_ADMINACC);
            if (ofs.is_open())
            {
                ofs << adminUsername << ":" << adminPassword << endl;
                ofs.close();
            }
        }
    }

    void taiMenuTuFile()
    {
        ifstream ifs(FILE_MENU);
        if (!ifs.is_open())
            return;
        string line;
        while (getline(ifs, line))
        {
            string itemType = line;
            string tenDayDu, moTaBurgerHoacRong, loaiThit, kichThuocDrink;
            int soLuong;
            double gia;
            if (!getline(ifs, tenDayDu))
                break;
            if (!getline(ifs, moTaBurgerHoacRong))
                break;
            if (!(ifs >> soLuong))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> gia))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (itemType == "Burger")
            {
                if (!getline(ifs, loaiThit))
                    break;
                string tenGocBurger = tenDayDu;
                string prefixBurger = "Burger - ";
                if (tenDayDu.rfind(prefixBurger, 0) == 0)
                {
                    tenGocBurger = tenDayDu.substr(prefixBurger.length());
                }
                danhSachMenu.push_back(new Burger(tenGocBurger, moTaBurgerHoacRong, soLuong, gia, loaiThit));
            }
            else if (itemType == "Drink")
            {
                if (!getline(ifs, kichThuocDrink))
                    break;
                string tenGocDrink = tenDayDu;
                string prefixDrink = "Nước uống - ";
                string suffixDrink = " (" + kichThuocDrink + ")";
                if (tenDayDu.rfind(prefixDrink, 0) == 0)
                {
                    tenGocDrink = tenDayDu.substr(prefixDrink.length());
                }
                size_t suffixPos = tenGocDrink.rfind(suffixDrink);
                if (suffixPos != string::npos && suffixPos == tenGocDrink.length() - suffixDrink.length())
                {
                    tenGocDrink = tenGocDrink.substr(0, suffixPos);
                }
                danhSachMenu.push_back(new Drink(tenGocDrink, soLuong, gia, kichThuocDrink));
            }
        }
        ifs.close();
    }
    void luuMenuRaFile() const
    {
        ofstream ofs(FILE_MENU);
        if (!ofs.is_open())
            return;
        for (const auto *item : danhSachMenu)
        {
            item->luuVaoFile(ofs);
        }
        ofs.close();
    }

    void taiThanhVienTuFile()
    {
        ifstream ifs(FILE_THANHVIEN);
        if (!ifs.is_open())
            return;
        string username, password, ten, sdt, diaChi;
        bool daMua;
        int diem;
        while (getline(ifs, username))
        {
            getline(ifs, password);
            getline(ifs, ten);
            getline(ifs, sdt);
            getline(ifs, diaChi);
            if (!(ifs >> daMua))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> diem))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            danhSachThanhVien.emplace_back(username, password, ten, sdt, diaChi, daMua, diem);
        }
        ifs.close();
    }

    void luuThanhVienRaFile() const
    {
        ofstream ofs(FILE_THANHVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &tv : danhSachThanhVien)
        {
            tv.luuVaoFile(ofs);
        }
        ofs.close();
    }

    void taiNhanVienTuFile()
    {
        ifstream ifs(FILE_NHANVIEN);
        if (!ifs.is_open())
            return;
        int ma;
        string ten, sdt, dc;
        int maxMaNV = 0;
        while (ifs >> ma)
        {
            ifs.ignore();
            getline(ifs, ten);
            getline(ifs, sdt);
            getline(ifs, dc);
            danhSachNhanVien.emplace_back(ma, ten, sdt, dc);
            if (ma > maxMaNV)
                maxMaNV = ma;
        }
        maNhanVienTiepTheo = maxMaNV + 1;
        ifs.close();
    }
    void luuNhanVienRaFile() const
    {
        ofstream ofs(FILE_NHANVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &nv : danhSachNhanVien)
        {
            nv.luuVaoFile(ofs);
        }
        ofs.close();
    }

    MenuItem *timMonAnTheoTen(const string &tenMon)
    {
        for (auto *item : danhSachMenu)
        {
            if (item->getTen() == tenMon)
                return item;
        }
        return nullptr;
    }
    KhachHang *timThanhVienTheoUsername(const string &username)
    {
        for (auto &tv : danhSachThanhVien)
        {
            if (tv.getUsername() == username)
                return &tv;
        }
        return nullptr;
    }
    KhachHang *timThanhVienTheoSDT(const string &sdt)
    {
        for (auto &tv : danhSachThanhVien)
        {
            if (tv.getSoDienThoai() == sdt && !tv.getUsername().empty())
                return &tv;
        }
        return nullptr;
    }

    void taiDonHangTuFile()
    {
        ifstream ifs(FILE_DONHANG);
        if (!ifs.is_open())
            return;
        int maDon;
        string sdtKhachDat, tenKhachDat, diaChiKhachDat;
        double tongGoc, tongThucTe;
        int soLuongLoaiMon, soLuongQuaTang;
        int maxMaDon = 0;
        while (ifs >> maDon)
        {
            ifs.ignore();
            getline(ifs, sdtKhachDat);
            getline(ifs, tenKhachDat);
            getline(ifs, diaChiKhachDat);
            if (!(ifs >> tongGoc))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> tongThucTe))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            KhachHang khachHangSnapshot(tenKhachDat, sdtKhachDat, diaChiKhachDat);
            DonHang donMoi(maDon, khachHangSnapshot, tongGoc, tongThucTe);
            if (!(ifs >> soLuongLoaiMon))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            for (int i = 0; i < soLuongLoaiMon; ++i)
            {
                string tenMon;
                int sl;
                getline(ifs, tenMon);
                if (!(ifs >> sl))
                {
                    ifs.clear();
                    ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                ifs.ignore();
                MenuItem *monPtr = timMonAnTheoTen(tenMon);
                if (monPtr)
                    donMoi.themMonAn(monPtr, sl);
                else
                    cerr << "Canh bao: Khong tim thay mon an '" << tenMon << "' cho don hang #" << maDon << endl;
            }
            if (!(ifs >> soLuongQuaTang))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            for (int i = 0; i < soLuongQuaTang; ++i)
            {
                string tenQua;
                if (!getline(ifs, tenQua))
                    break;
                donMoi.themQuaTangDaDoi(tenQua);
            }
            danhSachDonHang.push_back(donMoi);
            if (maDon > maxMaDon)
                maxMaDon = maDon;
        }
        maDonHangTiepTheo = maxMaDon + 1;
        ifs.close();
    }
    void luuDonHangRaFile() const
    {
        ofstream ofs(FILE_DONHANG);
        if (!ofs.is_open())
            return;
        for (const auto &dh : danhSachDonHang)
        {
            dh.luuVaoFile(ofs);
        }
        ofs.close();
    }

    void taiThongTinCuaHangTuFile()
    {
        ifstream ifs(FILE_CUAHANG);
        if (!ifs.is_open())
        {
            tenCuaHang = "Burger Ngon Đà Nẵng";
            diaChiCuaHang = "[Địa chỉ chưa cập nhật]";
            soDienThoaiCuaHang = "[SĐT chưa cập nhật]";
            return;
        }
        getline(ifs, tenCuaHang);
        getline(ifs, diaChiCuaHang);
        getline(ifs, soDienThoaiCuaHang);
        ifs.close();
    }
    void luuThongTinCuaHangRaFile() const
    {
        ofstream ofs(FILE_CUAHANG);
        if (!ofs.is_open())
            return;
        ofs << tenCuaHang << endl;
        ofs << diaChiCuaHang << endl;
        ofs << soDienThoaiCuaHang << endl;
        ofs.close();
    }

public:
    CuaHangBurger(string ten = "Burger Ngon Đà Nẵng", string diaChi = "[Địa chỉ]", string sdt = "[Số điện thoại]")
        : tenCuaHang(ten), diaChiCuaHang(diaChi), soDienThoaiCuaHang(sdt),
          maDonHangTiepTheo(1), maNhanVienTiepTheo(1) // Bỏ idLuaChonTiepTheo
    {
        taiAdminAcc();
        khoiTaoLuaChonDoiDiemCoDinh(); // Khởi tạo các lựa chọn đổi điểm cố định
        taiToanBoDuLieu();
    }
    ~CuaHangBurger()
    {
        luuToanBoDuLieu();
        for (MenuItem *item : danhSachMenu)
        {
            delete item;
        }
    }

    void taiToanBoDuLieu()
    {
        taiThongTinCuaHangTuFile();
        taiMenuTuFile();
        taiThanhVienTuFile();
        taiNhanVienTuFile();
        taiDonHangTuFile();
    }

    void luuToanBoDuLieu() const
    {
        luuThongTinCuaHangRaFile();
        luuMenuRaFile();
        luuThanhVienRaFile();
        luuNhanVienRaFile();
        luuDonHangRaFile();
        cout << "Da luu du lieu ra file." << endl;
    }

    bool dangNhapAdmin()
    {
        string username, password_in;
        cout << "  --- Đăng nhập Quản lý ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password_in);
        if (username == adminUsername && password_in == adminPassword)
        {
            isAdminLoggedIn = true;
            thanhVienHienTai = nullptr;
            cout << "  Đăng nhập quản lý thành công!" << endl;
            return true;
        }
        cout << "  Sai username hoặc password quản lý." << endl;
        return false;
    }

    bool dangNhapThanhVien()
    {
        string username, password_in;
        cout << "  --- Đăng nhập Thành viên ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password_in);
        for (auto &tv : danhSachThanhVien)
        {
            if (tv.getUsername() == username && tv.getPassword() == password_in)
            {
                thanhVienHienTai = &tv;
                isAdminLoggedIn = false;
                cout << "  Chào mừng trở lại, " << tv.getTen() << "!" << endl;
                return true;
            }
        }
        cout << "  Sai username hoặc password thành viên." << endl;
        return false;
    }

    void dangKyThanhVien()
    {
        cout << "\n  --- Đăng ký tài khoản Thành viên mới ---" << endl;
        string username, password_in, ten, sdt, diachi;
        while (true)
        {
            cout << "  Nhập Username mong muốn: ";
            getline(cin, username);
            if (username.empty())
            {
                cout << "  Username không được để trống." << endl;
                continue;
            }
            bool trungUser = false;
            for (const auto &tv : danhSachThanhVien)
            {
                if (tv.getUsername() == username)
                {
                    trungUser = true;
                    break;
                }
            }
            if (trungUser)
            {
                cout << "  Username này đã tồn tại. Vui lòng chọn username khác." << endl;
            }
            else
            {
                break;
            }
        }
        while (true)
        {
            cout << "  Nhập Password (ít nhất 8 ký tự): ";
            getline(cin, password_in);
            if (password_in.length() < 8)
            {
                cout << "  Password quá ngắn. Phải có ít nhất 8 ký tự." << endl;
            }
            else
            {
                break;
            }
        }
        cout << "  Nhập Họ tên: ";
        getline(cin, ten);
        while (true)
        {
            cout << "  Nhập Số điện thoại: ";
            getline(cin, sdt);
            if (sdt.empty())
            {
                cout << "  Số điện thoại không được để trống." << endl;
                continue;
            }
            bool trungSDT = false;
            for (const auto &tv : danhSachThanhVien)
            {
                if (tv.getSoDienThoai() == sdt && !tv.getUsername().empty())
                {
                    trungSDT = true;
                    break;
                }
            }
            if (trungSDT)
            {
                cout << "  Số điện thoại này đã được đăng ký bởi một thành viên khác." << endl;
            }
            else
            {
                break;
            }
        }
        cout << "  Nhập Địa chỉ: ";
        getline(cin, diachi);
        danhSachThanhVien.emplace_back(username, password_in, ten, sdt, diachi, false, 0);
        cout << "  Đăng ký thành viên thành công! Username: " << username << endl;
        cout << "  Vui lòng đăng nhập để bắt đầu mua sắm và hưởng ưu đãi." << endl;
    }

    void dangXuat()
    {
        if (isAdminLoggedIn)
        {
            isAdminLoggedIn = false;
            cout << "  Đã đăng xuất khỏi tài khoản Quản lý." << endl;
        }
        else if (thanhVienHienTai)
        {
            cout << "  Đã đăng xuất khỏi tài khoản Thành viên: " << thanhVienHienTai->getUsername() << endl;
            thanhVienHienTai = nullptr;
        }
        else
        {
            cout << "  Không có ai đang đăng nhập." << endl;
        }
    }

    void thayDoiThongTinCaNhan()
    {
        if (!thanhVienHienTai)
        {
            cout << "  Lỗi: Bạn cần đăng nhập để sử dụng chức năng này." << endl;
            return;
        }
        cout << "\n  --- Thay đổi thông tin cá nhân ---" << endl;
        thanhVienHienTai->hienThiThongTin();
        int choice = getInputValidated<int>("  Bạn muốn thay đổi thông tin nào?\n  1. Họ tên\n  2. Số điện thoại\n  3. Địa chỉ\n  4. Mật khẩu\n  0. Quay lại\n  Nhập lựa chọn: ");
        string tenMoi, sdtMoi, dcMoi, passCu, passMoi1, passMoi2;
        switch (choice)
        {
        case 1:
            cout << "  Họ tên hiện tại: " << thanhVienHienTai->getTen() << endl;
            cout << "  Nhập họ tên mới: ";
            getline(cin, tenMoi);
            thanhVienHienTai->setTen(!tenMoi.empty() ? tenMoi : thanhVienHienTai->getTen());
            cout << (!tenMoi.empty() ? "  Đã cập nhật họ tên." : "  Không thay đổi họ tên.") << endl;
            break;
        case 2:
            cout << "  Số điện thoại hiện tại: " << thanhVienHienTai->getSoDienThoai() << endl;
            while (true)
            {
                cout << "  Nhập số điện thoại mới: ";
                getline(cin, sdtMoi);
                if (sdtMoi.empty())
                {
                    cout << "  Không thay đổi số điện thoại." << endl;
                    break;
                }
                if (sdtMoi == thanhVienHienTai->getSoDienThoai())
                {
                    cout << "  Số điện thoại mới trùng với số cũ. Không thay đổi." << endl;
                    break;
                }
                bool trungSDT = false;
                for (const auto &tv : danhSachThanhVien)
                {
                    if (tv.getSoDienThoai() == sdtMoi && tv.getUsername() != thanhVienHienTai->getUsername())
                    {
                        trungSDT = true;
                        break;
                    }
                }
                if (trungSDT)
                {
                    cout << "  Số điện thoại này đã được đăng ký bởi một thành viên khác." << endl;
                }
                else
                {
                    thanhVienHienTai->setSoDienThoai(sdtMoi);
                    cout << "  Đã cập nhật số điện thoại." << endl;
                    break;
                }
            }
            break;
        case 3:
            cout << "  Địa chỉ hiện tại: " << thanhVienHienTai->getDiaChi() << endl;
            cout << "  Nhập địa chỉ mới: ";
            getline(cin, dcMoi);
            thanhVienHienTai->setDiaChi(!dcMoi.empty() ? dcMoi : thanhVienHienTai->getDiaChi());
            cout << (!dcMoi.empty() ? "  Đã cập nhật địa chỉ." : "  Không thay đổi địa chỉ.") << endl;
            break;
        case 4:
            cout << "  --- Thay đổi mật khẩu ---" << endl;
            cout << "  Nhập mật khẩu cũ: ";
            getline(cin, passCu);
            if (passCu == thanhVienHienTai->getPassword())
            {
                while (true)
                {
                    cout << "  Nhập mật khẩu mới (ít nhất 8 ký tự): ";
                    getline(cin, passMoi1);
                    if (passMoi1.length() < 8)
                    {
                        cout << "  Mật khẩu mới quá ngắn." << endl;
                        continue;
                    }
                    cout << "  Xác nhận mật khẩu mới: ";
                    getline(cin, passMoi2);
                    if (passMoi1 == passMoi2)
                    {
                        thanhVienHienTai->setPassword(passMoi1);
                        cout << "  Đã cập nhật mật khẩu." << endl;
                        break;
                    }
                    else
                    {
                        cout << "  Mật khẩu xác nhận không khớp." << endl;
                    }
                }
            }
            else
            {
                cout << "  Mật khẩu cũ không đúng." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "  Lựa chọn không hợp lệ." << endl;
        }
    }

    // Hiển thị các lựa chọn đổi điểm cho thành viên (chỉ quà hoặc chỉ giảm giá)
    void xemDanhSachLuaChonDoiDiemChoThanhVien(int diemHienCoCuaKhach, const string &loaiMuonXem) const
    {
        cout << "\n  --- Các lựa chọn đổi điểm có thể (" << (loaiMuonXem == "GIAM_GIA_PHAN_TRAM" ? "Giảm giá" : "Quà tặng") << ") ---" << endl;
        bool coLuaChonPhuHop = false;
        for (const auto &luaChon : danhSachLuaChonDoiDiem)
        {
            if (luaChon.loaiPhanThuong == loaiMuonXem && diemHienCoCuaKhach >= luaChon.diemCanDoi)
            {
                luaChon.hienThi();
                coLuaChonPhuHop = true;
            }
        }
        if (!coLuaChonPhuHop)
        {
            cout << "  Bạn không đủ điểm cho bất kỳ lựa chọn " << (loaiMuonXem == "GIAM_GIA_PHAN_TRAM" ? "giảm giá" : "quà tặng") << " nào hiện tại." << endl;
        }
    }
    MenuItem *timMonAn(int index, const vector<MenuItem *> &danhSach) const
    {
        return (index > 0 && (size_t)index <= danhSach.size()) ? danhSach[index - 1] : nullptr;
    }
    NhanVien *timNhanVien(int maNV)
    {
        for (auto &nv : danhSachNhanVien)
        {
            if (nv.getMaNV() == maNV)
                return &nv;
        }
        return nullptr;
    }

    void nhapThongTinCuaHang()
    {
        cout << "\n  --- Nhập/Cập nhật thông tin cửa hàng ---" << endl;
        string tempTen, tempDiaChi, tempSDT;
        cout << "  Tên cửa hàng hiện tại: " << tenCuaHang << endl;
        cout << "  Nhập tên cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempTen);
        tenCuaHang = !tempTen.empty() ? tempTen : tenCuaHang;
        cout << "  Địa chỉ cửa hàng hiện tại: " << diaChiCuaHang << endl;
        cout << "  Nhập địa chỉ cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempDiaChi);
        diaChiCuaHang = !tempDiaChi.empty() ? tempDiaChi : diaChiCuaHang;
        cout << "  Số điện thoại cửa hàng hiện tại: " << soDienThoaiCuaHang << endl;
        cout << "  Nhập số điện thoại cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempSDT);
        soDienThoaiCuaHang = !tempSDT.empty() ? tempSDT : soDienThoaiCuaHang;
        cout << "  Đã cập nhật thông tin cửa hàng!" << endl;
    }

    void themMonAn(bool Meal)
    {
        string tenGoc, moTaBurger, loaiThit, kichThuoc;
        int soLuong;
        double gia;
        cout << (Meal ? "\n  --- Thêm burger ---" : "\n  --- Thêm nước uống ---") << endl;
        cout << "  Nhập tên gốc " << (Meal ? "burger (ví dụ: Bo Pho Mai, Ga Gion): " : "nước uống (ví dụ: Coca Cola, Tra Dao): ");
        getline(cin, tenGoc);

        if (Meal)
        {
            cout << "  Nhập mô tả cho burger: ";
            getline(cin, moTaBurger);
            cout << "  Nhập loại thịt: ";
            getline(cin, loaiThit);
        }
        else
        {
            cout << "  Nhập kích thước (S, M, L): ";
            while (true)
            {
                getline(cin, kichThuoc);
                kichThuoc = stringToUpper(kichThuoc);
                if (kichThuoc == "S" || kichThuoc == "M" || kichThuoc == "L")
                    break;
                cout << "  Kích thước không hợp lệ. Vui lòng nhập S, M, hoặc L: ";
            }
        }

        soLuong = getInputValidated<int>("  Nhập số lượng: ");
        while (soLuong < 0)
            soLuong = getInputValidated<int>("  Lỗi: Số lượng phải là số không âm. Nhập lại: ");

        gia = getInputValidated<double>("  Nhập giá: ");
        while (gia < 0)
            gia = getInputValidated<double>("  Lỗi: Giá phải là số không âm. Nhập lại: ");

        if (Meal)
        {
            danhSachMenu.push_back(new Burger(tenGoc, moTaBurger, soLuong, gia, loaiThit));
        }
        else
        {
            danhSachMenu.push_back(new Drink(tenGoc, soLuong, gia, kichThuoc));
        }
        cout << "  Đã thêm thành công!" << endl;
    }

    void hienThiDanhSachMenu() const
    {
        cout << "\n  --- Danh sách món ăn trong menu ---" << endl;
        if (danhSachMenu.empty())
        {
            cout << "  Menu hiện chưa có món nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(5) << "STT" << setw(40) << "Tên" << setw(12) << "Số lượng" << setw(15) << "Giá (VNĐ)" << endl;
        veDuongNgang(72);
        for (size_t i = 0; i < danhSachMenu.size(); ++i)
        {
            cout << " " << setw(5) << i + 1
                 << setw(40) << danhSachMenu[i]->getTen()
                 << setw(12) << danhSachMenu[i]->getSoLuong()
                 << setw(15) << fixed << setprecision(0) << danhSachMenu[i]->getGia() << endl;
        }
        cout << right;
    }

    void chinhSuaMonAn()
    {
        hienThiDanhSachMenu();
        if (danhSachMenu.empty())
            return;
        int index = getInputValidated<int>("  Nhập STT món ăn muốn chỉnh sửa: ");
        if (index <= 0 || (size_t)index > danhSachMenu.size())
        {
            cout << "  STT không hợp lệ." << endl;
            return;
        }
        MenuItem *monAnCanSua = danhSachMenu[index - 1];
        cout << "\n  --- Chỉnh sửa món ăn: " << monAnCanSua->getTen() << " ---" << endl;
        if (Burger *burger = dynamic_cast<Burger *>(monAnCanSua))
        {
            string moTaMoiBurger, loaiThitMoi;
            cout << "  Mô tả hiện tại: " << burger->getMoTa() << endl;
            cout << "  Mô tả mới cho Burger (để trống để giữ nguyên): ";
            getline(cin, moTaMoiBurger);
            burger->setMoTa(!moTaMoiBurger.empty() ? moTaMoiBurger : burger->getMoTa());
            cout << "  Loại thịt hiện tại: " << burger->getLoaiThit() << endl;
            cout << "  Loại thịt mới (để trống để giữ nguyên): ";
            getline(cin, loaiThitMoi);
            burger->setLoaiThit(!loaiThitMoi.empty() ? loaiThitMoi : burger->getLoaiThit());
        }
        else if (Drink *drink = dynamic_cast<Drink *>(monAnCanSua))
        {
            string kichThuocMoi;
            cout << "  Kích thước hiện tại: " << drink->getKichThuoc() << endl;
            cout << "  Kích thước mới (S, M, L, để trống nếu không đổi): ";
            getline(cin, kichThuocMoi);
            if (!kichThuocMoi.empty())
            {
                kichThuocMoi = stringToUpper(kichThuocMoi);
                if (kichThuocMoi == "S" || kichThuocMoi == "M" || kichThuocMoi == "L")
                {
                    string tenGocCu = drink->getTenGoc();
                    drink->setKichThuoc(kichThuocMoi);
                    drink->setTen("Nước uống - " + tenGocCu + " (" + kichThuocMoi + ")");
                }
                else
                {
                    cout << "  Kích thước không hợp lệ, không thay đổi." << endl;
                }
            }
        }
        cout << "  Số lượng mới (nhập số âm để giữ nguyên [" << monAnCanSua->getSoLuong() << "]): ";
        string inputSL;
        getline(cin, inputSL);
        if (!inputSL.empty())
        {
            try
            {
                int sl = stoi(inputSL);
                if (sl >= 0)
                    monAnCanSua->setSoLuong(sl);
            }
            catch (const std::exception &e)
            {
            }
        }

        cout << "  Giá mới (nhập số âm để giữ nguyên [" << fixed << setprecision(0) << monAnCanSua->getGia() << "]): ";
        string inputG;
        getline(cin, inputG);
        if (!inputG.empty())
        {
            try
            {
                double g = stod(inputG);
                if (g >= 0)
                    monAnCanSua->setGia(g);
            }
            catch (const std::exception &e)
            {
            }
        }
        cout << "  Đã cập nhật thông tin món ăn!" << endl;
    }

    void xoaMonAn()
    {
        hienThiDanhSachMenu();
        if (danhSachMenu.empty())
            return;
        int index = getInputValidated<int>("  Nhập STT món ăn muốn xóa: ");

        if (index <= 0 || (size_t)index > danhSachMenu.size())
        {
            cout << "  STT không hợp lệ." << endl;
            return;
        }
        MenuItem *monAnCanXoa = danhSachMenu[index - 1];
        char confirm = getInputValidated<char>("  Bạn có chắc chắn muốn xóa " + monAnCanXoa->getTen() + "? (y/n): ");
        if (confirm == 'y' || confirm == 'Y')
        {
            delete monAnCanXoa;
            danhSachMenu.erase(danhSachMenu.begin() + (index - 1));
            cout << "  Đã xóa món ăn thành công!" << endl;
        }
        else
        {
            cout << "  Hủy bỏ xóa món ăn." << endl;
        }
    }

    void hienThiDanhSachDonHang() const
    {
        cout << "\n  --- Danh sách đơn hàng ---" << endl;
        if (danhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào." << endl;
            return;
        }
        for (const auto &don : danhSachDonHang)
        {
            don.hienThiThongTin();
            veDuongNgang(30, '-');
        }
    }

    void themDonHangChoKhachHoacThanhVien()
    { // Admin tạo đơn
        cout << "\n  --- Thêm đơn hàng mới (Quản lý) ---" << endl;
        int loaiKhach = getInputValidated<int>("  Đơn hàng này cho:\n  1. Thành viên đã đăng ký\n  2. Khách vãng lai\n  Nhập lựa chọn: ");
        KhachHang *khachHangThucTe = nullptr;      // Con trỏ tới thành viên thực sự trong danhSachThanhVien
        KhachHang khachHangDatDonHang("", "", ""); // Thông tin sẽ được lưu vào đơn hàng
        if (loaiKhach == 1)
        {
            string idTimKiem;
            cout << "  Nhập Username hoặc SĐT của thành viên: ";
            getline(cin, idTimKiem);
            khachHangThucTe = timThanhVienTheoUsername(idTimKiem);
            if (!khachHangThucTe)
                khachHangThucTe = timThanhVienTheoSDT(idTimKiem);
            if (!khachHangThucTe)
            {
                cout << "  Không tìm thấy thành viên." << endl;
                return;
            }
            cout << "  Đơn hàng cho thành viên: " << khachHangThucTe->getTen() << endl;
            khachHangDatDonHang = *khachHangThucTe; // Sao chép thông tin thành viên vào đơn
        }
        else if (loaiKhach == 2)
        {
            string ten, sdt, dc;
            cout << "  Xin mời nhập tên: ";
            getline(cin, ten);
            cout << "  Xin mời nhập số điện thoại: ";
            getline(cin, sdt);
            cout << "  Xin mời nhập địa chỉ: ";
            getline(cin, dc);
            khachHangDatDonHang = KhachHang(ten, sdt, dc);
        }
        else
        {
            cout << "  Lựa chọn không hợp lệ." << endl;
            return;
        }

        DonHang donMoi(maDonHangTiepTheo, khachHangDatDonHang);
        char themMonAnYN;
        do
        {
            hienThiDanhSachMenu();
            if (danhSachMenu.empty())
            {
                cout << "Menu trống." << endl;
                break;
            }
            int indexMonAn = getInputValidated<int>("  Nhập STT món ăn muốn thêm (0 để hoàn tất): ");
            if (indexMonAn == 0)
                break;
            if (indexMonAn < 0 || (size_t)indexMonAn > danhSachMenu.size())
            {
                cout << "STT không hợp lệ." << endl;
                themMonAnYN = 'y';
                continue;
            }
            MenuItem *monAnDaChon = danhSachMenu[indexMonAn - 1];
            int soLuongMua = getInputValidated<int>("  Nhập số lượng: ");
            if (soLuongMua <= 0)
            {
                cout << "Số lượng không hợp lệ." << endl;
                themMonAnYN = 'y';
                continue;
            }
            if (monAnDaChon && soLuongMua <= monAnDaChon->getSoLuong())
            {
                donMoi.themMonAn(monAnDaChon, soLuongMua);
                monAnDaChon->setSoLuong(monAnDaChon->getSoLuong() - soLuongMua);
            }
            else
            {
                cout << "  Số lượng không đủ trong kho hoặc món không hợp lệ." << endl;
            }
            themMonAnYN = getInputValidated<char>("  Thêm món khác? (y/n): ");
        } while (themMonAnYN == 'y' || themMonAnYN == 'Y');

        if (donMoi.getDanhSachMonAn().empty())
        {
            cout << "  Đơn hàng trống. Hủy thêm đơn hàng." << endl;
            return;
        }
        donMoi.tinhLaiTongTienGoc();
        double tongTienThanhToan = donMoi.getTongTienGoc();
        // Admin tạo đơn: KHÔNG đổi điểm, chỉ cộng điểm và áp dụng ưu đãi tự động
        if (khachHangThucTe)
        { // Nếu là đơn hàng cho thành viên
            if (!khachHangThucTe->getDaMuaLanDau() && tongTienThanhToan > 0)
            {
                double tienGiam = tongTienThanhToan * giamGiaLanDau;
                tongTienThanhToan -= tienGiam;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaLanDau * 100 << "% cho thành viên mua lần đầu." << endl;
                khachHangThucTe->setDaMuaLanDau(true);
            }
            if (donMoi.getDanhSachMonAn().size() >= (size_t)soLuongLonDeGiamGia && tongTienThanhToan > 0)
            {
                double tienGiam = tongTienThanhToan * giamGiaSoLuongLon;
                tongTienThanhToan -= tienGiam;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaSoLuongLon * 100 << "% cho đơn hàng số lượng lớn." << endl;
            }
            tongTienThanhToan = (tongTienThanhToan < 0) ? 0 : tongTienThanhToan;
            int diemThuong = static_cast<int>(tongTienThanhToan / GIA_TRI_VND_CHO_MOT_DIEM);
            if (diemThuong > 0)
            {
                khachHangThucTe->themDiem(diemThuong);
                cout << "  Thành viên " << khachHangThucTe->getTen() << " được cộng " << diemThuong << " điểm." << endl;
                cout << "  Tổng điểm hiện tại: " << khachHangThucTe->getDiemTichLuy() << " điểm." << endl;
            }
        }
        donMoi.setTongTienThucTe(tongTienThanhToan);
        danhSachDonHang.push_back(donMoi);
        maDonHangTiepTheo++;
        cout << "  Đã thêm đơn hàng #" << donMoi.getMaDonHang() << " thành công!" << endl;
        donMoi.hienThiThongTin();
    }

    void xoaDonHang()
    {
        hienThiDanhSachDonHang();
        if (danhSachDonHang.empty())
            return;
        int maDonHangXoa = getInputValidated<int>("  Nhập mã đơn hàng muốn xóa: ");

        for (auto it = danhSachDonHang.begin(); it != danhSachDonHang.end(); ++it)
        {
            if (it->getMaDonHang() == maDonHangXoa)
            {
                char confirm = getInputValidated<char>("  Bạn có chắc chắn muốn xóa đơn hàng #" + to_string(maDonHangXoa) + "? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    const auto &danhSachMATrongDon = it->getDanhSachMonAn();
                    for (const auto &item : danhSachMATrongDon)
                    {
                        if (item.first)
                            item.first->setSoLuong(item.first->getSoLuong() + item.second);
                    }
                    cout << "  Lưu ý: Nếu đơn hàng này của thành viên và đã có giao dịch điểm/ưu đãi, việc hoàn lại các ưu đãi đó chưa được tự động xử lý." << endl;
                    danhSachDonHang.erase(it);
                    cout << "  Đã xóa đơn hàng #" << maDonHangXoa << " thành công!" << endl;
                }
                else
                {
                    cout << "  Hủy bỏ xóa đơn hàng." << endl;
                }
                return;
            }
        }
        cout << "  Không tìm thấy đơn hàng #" << maDonHangXoa << endl;
    }

    void themNhanVien()
    {
        cout << "\n  --- Thêm nhân viên ---" << endl;
        string ten, sdt, dc;
        cout << "  Nhập tên nhân viên: ";
        getline(cin, ten);
        cout << "  Nhập số điện thoại: ";
        getline(cin, sdt);
        cout << "  Nhập địa chỉ: ";
        getline(cin, dc);
        danhSachNhanVien.emplace_back(maNhanVienTiepTheo, ten, sdt, dc);
        cout << "  Đã thêm nhân viên #" << maNhanVienTiepTheo++ << " thành công!" << endl;
    }

    void xemDanhSachNhanVien() const
    {
        cout << "\n  --- Danh sách nhân viên ---" << endl;
        if (danhSachNhanVien.empty())
        {
            cout << "  Chưa có nhân viên nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(7) << "Mã NV" << setw(25) << "Tên nhân viên" << setw(18) << "Số điện thoại" << setw(30) << "Địa chỉ" << endl;
        veDuongNgang(80);
        for (const auto &nv : danhSachNhanVien)
        {
            cout << " " << setw(7) << nv.getMaNV()
                 << setw(25) << nv.getTenNV()
                 << setw(18) << nv.getSoDienThoaiNV()
                 << setw(30) << nv.getDiaChiNV() << endl;
        }
        cout << right;
    }

    void chinhSuaNhanVien()
    {
        xemDanhSachNhanVien();
        if (danhSachNhanVien.empty())
            return;
        int maNVChinhSua = getInputValidated<int>("  Nhập mã nhân viên muốn chỉnh sửa: ");
        NhanVien *nvCanSua = timNhanVien(maNVChinhSua);
        if (!nvCanSua)
        {
            cout << "  Không tìm thấy nhân viên có mã #" << maNVChinhSua << endl;
            return;
        }
        cout << "\n  --- Chỉnh sửa thông tin nhân viên #" << nvCanSua->getMaNV() << " ---" << endl;
        string tenMoi, sdtMoi, dcMoi;
        cout << "  Tên mới (để trống để giữ nguyên [" << nvCanSua->getTenNV() << "]): ";
        getline(cin, tenMoi);
        nvCanSua->setTenNV(!tenMoi.empty() ? tenMoi : nvCanSua->getTenNV());
        cout << "  Số điện thoại mới (để trống để giữ nguyên [" << nvCanSua->getSoDienThoaiNV() << "]): ";
        getline(cin, sdtMoi);
        nvCanSua->setSoDienThoaiNV(!sdtMoi.empty() ? sdtMoi : nvCanSua->getSoDienThoaiNV());
        cout << "  Địa chỉ mới (để trống để giữ nguyên [" << nvCanSua->getDiaChiNV() << "]): ";
        getline(cin, dcMoi);
        nvCanSua->setDiaChiNV(!dcMoi.empty() ? dcMoi : nvCanSua->getDiaChiNV());
        cout << "  Đã cập nhật thông tin nhân viên!" << endl;
    }

    void xoaNhanVien()
    {
        xemDanhSachNhanVien();
        if (danhSachNhanVien.empty())
            return;
        int maNVXoa = getInputValidated<int>("  Nhập mã nhân viên muốn xóa: ");

        for (auto it = danhSachNhanVien.begin(); it != danhSachNhanVien.end(); ++it)
        {
            if (it->getMaNV() == maNVXoa)
            {
                char confirm = getInputValidated<char>("  Bạn có chắc chắn muốn xóa nhân viên #" + to_string(maNVXoa) + " (" + it->getTenNV() + ")? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    danhSachNhanVien.erase(it);
                    cout << "  Đã xóa nhân viên #" << maNVXoa << " thành công!" << endl;
                }
                else
                {
                    cout << "  Hủy bỏ xóa nhân viên." << endl;
                }
                return;
            }
        }
        cout << "  Không tìm thấy nhân viên có mã #" << maNVXoa << endl;
    }

    void hienThiDanhSachThanhVien() const
    {
        cout << "\n  --- Danh sách thành viên ---" << endl;
        if (danhSachThanhVien.empty())
        {
            cout << "  Chưa có thành viên nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(15) << "Username" << setw(25) << "Tên Khách Hàng" << setw(18) << "Số Điện Thoại" << setw(30) << "Địa Chỉ" << right << setw(10) << "Điểm" << setw(10) << "Mua Lần Đầu" << left << endl;
        veDuongNgang(110);
        for (const auto &tv : danhSachThanhVien)
        {
            cout << " " << setw(15) << tv.getUsername()
                 << setw(25) << tv.getTen()
                 << setw(18) << tv.getSoDienThoai()
                 << setw(30) << tv.getDiaChi()
                 << right << setw(10) << tv.getDiemTichLuy()
                 << setw(10) << (tv.getDaMuaLanDau() ? "Rồi" : "Chưa") << left << endl;
        }
        cout << right;
    }
    void baoCaoDoanhThu() const
    {
        cout << "\n  --- Báo cáo doanh thu ---" << endl;
        if (danhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào để thống kê." << endl;
            return;
        }
        double tongDoanhThuGoc = 0, tongDoanhThuThucTe = 0;
        for (const auto &donHang : danhSachDonHang)
        {
            tongDoanhThuGoc += donHang.getTongTienGoc();
            tongDoanhThuThucTe += donHang.getTongTienThucTe();
        }
        cout << "  Tổng số đơn hàng: " << danhSachDonHang.size() << endl;
        cout << "  Tổng doanh thu (theo tiền gốc): " << fixed << setprecision(0) << tongDoanhThuGoc << " VNĐ" << endl;
        cout << "  Tổng doanh thu thực tế (sau giảm giá/điểm/quà): " << fixed << setprecision(0) << tongDoanhThuThucTe << " VNĐ" << endl;
    }
    void baoCaoMonBanChay() const
    {
        cout << "\n  --- Báo cáo món bán chạy ---" << endl;
        if (danhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào để thống kê." << endl;
            return;
        }
        map<string, int> soLuongMonDaBan;
        map<string, double> doanhThuTungMonGoc;
        for (const auto &donHang : danhSachDonHang)
        {
            for (const auto &itemPair : donHang.getDanhSachMonAn())
            {
                if (itemPair.first)
                {
                    MenuItem *mon = itemPair.first;
                    int soLuong = itemPair.second;
                    soLuongMonDaBan[mon->getTen()] += soLuong;
                    doanhThuTungMonGoc[mon->getTen()] += mon->getGia() * soLuong;
                }
            }
        }
        if (soLuongMonDaBan.empty())
        {
            cout << "  Không có món nào được bán trong các đơn hàng đã ghi nhận." << endl;
            return;
        }
        vector<pair<string, int>> vecSLMon(soLuongMonDaBan.begin(), soLuongMonDaBan.end());
        sort(vecSLMon.begin(), vecSLMon.end(), [](const pair<string, int> &a, const pair<string, int> &b)
             { return a.second > b.second; });
        vector<pair<string, double>> vecDTMon(doanhThuTungMonGoc.begin(), doanhThuTungMonGoc.end());
        sort(vecDTMon.begin(), vecDTMon.end(), [](const pair<string, double> &a, const pair<string, double> &b)
             { return a.second > b.second; });
        cout << "  --- Top món bán chạy nhất theo SỐ LƯỢNG ---" << endl;
        cout << left << " " << setw(5) << "Hạng" << setw(40) << "Tên Món" << right << setw(15) << "Số Lượng Bán" << left << endl;
        veDuongNgang(63);
        for (size_t i = 0; i < vecSLMon.size() && i < 10; ++i)
        {
            cout << " " << setw(5) << i + 1 << setw(40) << vecSLMon[i].first << right << setw(15) << vecSLMon[i].second << left << endl;
        }
        cout << right;
        cout << "\n  --- Top món đóng góp DOANH THU GỐC cao nhất ---" << endl;
        cout << left << " " << setw(5) << "Hạng" << setw(40) << "Tên Món" << right << setw(20) << "Doanh Thu Gốc" << left << endl;
        veDuongNgang(70);
        for (size_t i = 0; i < vecDTMon.size() && i < 10; ++i)
        {
            cout << " " << setw(5) << i + 1 << setw(40) << vecDTMon[i].first << right << setw(20) << fixed << setprecision(0) << vecDTMon[i].second << left << " VNĐ" << endl;
        }
        cout << right;
    }

    void xemThongTinCuaHang_User() const
    {
        cout << "\n  --- Thông tin Cửa hàng Burger ---" << endl;
        cout << "  Chào mừng quý khách đến với " << tenCuaHang << " tại " << diaChiCuaHang << "!" << endl;
        cout << "  Chúng tôi phục vụ những chiếc burger ngon nhất và nhiều loại thức uống hấp dẫn." << endl;
        cout << "  Số điện thoại liên hệ: " << soDienThoaiCuaHang << endl;
    }
    void xemMenu_User() const
    {
        cout << "\n  --- Menu của cửa hàng " << tenCuaHang << " ---" << endl;
        if (danhSachMenu.empty())
        {
            cout << "  Menu hiện chưa có món nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(5) << "STT" << setw(40) << "Tên" << setw(15) << "Giá (VNĐ)" << endl;
        veDuongNgang(60);
        for (size_t i = 0; i < danhSachMenu.size(); ++i)
        {
            cout << " " << setw(5) << i + 1
                 << setw(40) << danhSachMenu[i]->getTen()
                 << setw(15) << fixed << setprecision(0) << danhSachMenu[i]->getGia() << endl;
        }
        cout << right;
        int luaChonXemChiTiet = getInputValidated<int>("  Nhập STT món ăn để xem chi tiết (0 để bỏ qua): ", "Lựa chọn không hợp lệ.");
        if (luaChonXemChiTiet > 0 && (size_t)luaChonXemChiTiet <= danhSachMenu.size())
        {
            cout << "\n  --- Thông tin chi tiết ---" << endl;
            danhSachMenu[luaChonXemChiTiet - 1]->hienThiThongTin();
        }
        else if (luaChonXemChiTiet != 0)
        {
            cout << "STT không hợp lệ." << endl;
        }
    }

    void datMon_User()
    { // Thành viên tự đặt món
        cout << "\n  --- Đặt món ---" << endl;
        if (!thanhVienHienTai && !isAdminLoggedIn) // Chỉ cho phép thành viên đang đăng nhập tự đặt
        {
            cout << "  Vui lòng đăng nhập với tư cách thành viên để đặt món và hưởng ưu đãi." << endl;
        }
        if (danhSachMenu.empty())
        {
            cout << "  Xin lỗi, menu hiện tại trống." << endl;
            return;
        }
        xemMenu_User();
        KhachHang khachHangDatDonHang("", "", ""); // Thông tin khách sẽ được lưu vào đơn hàng
        bool laThanhVienDat = (thanhVienHienTai != nullptr);
        if (laThanhVienDat)
        {
            khachHangDatDonHang = *thanhVienHienTai;
            cout << "  Đặt hàng với tư cách thành viên: " << thanhVienHienTai->getTen() << endl;
        }
        else
        { // Khách vãng lai
            string ten, sdt, dc;
            cout << "  Vui lòng nhập thông tin đặt hàng:" << endl;
            cout << "  Nhập tên của bạn: ";
            getline(cin, ten);
            cout << "  Nhập số điện thoại: ";
            getline(cin, sdt);
            cout << "  Nhập địa chỉ: ";
            getline(cin, dc);
            khachHangDatDonHang = KhachHang(ten, sdt, dc);
        }

        DonHang donMoi(maDonHangTiepTheo, khachHangDatDonHang);
        char datTiep;
        do
        {
            int indexMonAnDat = getInputValidated<int>("  Nhập STT món ăn muốn đặt (0 để hoàn tất): ");
            if (indexMonAnDat == 0)
                break;
            if (indexMonAnDat < 0 || (size_t)indexMonAnDat > danhSachMenu.size())
            {
                cout << "STT không hợp lệ." << endl;
                datTiep = 'y';
                continue;
            }
            MenuItem *monAnDaChon = danhSachMenu[indexMonAnDat - 1];
            int soLuongDat = getInputValidated<int>("  Nhập số lượng: ");
            if (soLuongDat <= 0)
            {
                cout << "Số lượng không hợp lệ." << endl;
                datTiep = 'y';
                continue;
            }
            if (monAnDaChon && soLuongDat <= monAnDaChon->getSoLuong())
            {
                donMoi.themMonAn(monAnDaChon, soLuongDat);
                monAnDaChon->setSoLuong(monAnDaChon->getSoLuong() - soLuongDat);
                cout << "  Đã thêm " << monAnDaChon->getTen() << " vào đơn hàng." << endl;
            }
            else
            {
                cout << "  Số lượng không đủ trong kho hoặc món không hợp lệ. Chỉ còn " << (monAnDaChon ? monAnDaChon->getSoLuong() : 0) << "." << endl;
            }
            datTiep = getInputValidated<char>("  Muốn đặt thêm món khác? (y/n): ");
        } while (datTiep == 'y' || datTiep == 'Y');
        if (donMoi.getDanhSachMonAn().empty())
        {
            cout << "  Đơn hàng trống. Hủy bỏ tạo đơn hàng." << endl;
            return;
        }
        donMoi.tinhLaiTongTienGoc();
        double tongTienTamTinh = donMoi.getTongTienGoc();
        double tongTienCuoiCung = tongTienTamTinh;
        bool daApDungGiamGiaPhanTram = false;
        cout << "  Tổng giá tiền tạm tính: " << fixed << setprecision(0) << tongTienTamTinh << " VNĐ" << endl;
        if (laThanhVienDat && thanhVienHienTai)
        {
            // Bước 1: Ưu đãi giảm giá % bằng điểm (chỉ có 1 lựa chọn là 12% cho 1000đ)
            const LuaChonDoiDiem *luaChonGiamGia12 = nullptr;
            for (const auto &lc : danhSachLuaChonDoiDiem)
            {
                if (lc.loaiPhanThuong == "GIAM_GIA_PHAN_TRAM" && lc.diemCanDoi == 1000)
                {
                    luaChonGiamGia12 = &lc;
                    break;
                }
            }
            if (luaChonGiamGia12 && thanhVienHienTai->getDiemTichLuy() >= luaChonGiamGia12->diemCanDoi)
            {
                char chonGiamGia = getInputValidated<char>("  Bạn có " + to_string(thanhVienHienTai->getDiemTichLuy()) + " điểm. Bạn có muốn dùng " + to_string(luaChonGiamGia12->diemCanDoi) + " điểm để " + luaChonGiamGia12->moTaPhanThuong + " không? (y/n): ");
                if (chonGiamGia == 'y' || chonGiamGia == 'Y')
                {
                    if (thanhVienHienTai->suDungDiem(luaChonGiamGia12->diemCanDoi))
                    {
                        double tienGiam = tongTienCuoiCung * luaChonGiamGia12->giaTri; // giaTri là 0.12
                        tongTienCuoiCung -= tienGiam;
                        daApDungGiamGiaPhanTram = true;
                        cout << "  Đã áp dụng giảm giá " << fixed << setprecision(0) << luaChonGiamGia12->giaTri * 100 << "%. Số tiền giảm: " << fixed << setprecision(0) << tienGiam << " VNĐ." << endl;
                        cout << "  Điểm còn lại: " << thanhVienHienTai->getDiemTichLuy() << " điểm." << endl;
                    }
                }
            }
            // Ưu đãi cố định (mua lần đầu, số lượng lớn) - áp dụng sau khi đã có thể giảm giá bằng điểm %
            if (!thanhVienHienTai->getDaMuaLanDau() && tongTienCuoiCung > 0)
            {
                double tienGiamLanDau = tongTienCuoiCung * giamGiaLanDau;
                tongTienCuoiCung -= tienGiamLanDau;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaLanDau * 100 << "% (tương đương " << fixed << setprecision(0) << tienGiamLanDau << " VNĐ) cho lần đặt đầu của thành viên!" << endl;
                thanhVienHienTai->setDaMuaLanDau(true);
            }
            if (donMoi.getDanhSachMonAn().size() >= (size_t)soLuongLonDeGiamGia && tongTienCuoiCung > 0)
            {
                double tienGiamSLDon = tongTienCuoiCung * giamGiaSoLuongLon;
                tongTienCuoiCung -= tienGiamSLDon;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaSoLuongLon * 100 << "% (tương đương " << fixed << setprecision(0) << tienGiamSLDon << " VNĐ) cho đơn hàng số lượng lớn!" << endl;
            }
            tongTienCuoiCung = (tongTienCuoiCung < 0) ? 0 : tongTienCuoiCung;
            donMoi.setTongTienThucTe(tongTienCuoiCung);
            cout << "  Tổng tiền thanh toán cuối cùng: " << fixed << setprecision(0) << tongTienCuoiCung << " VNĐ" << endl;
            // Bước 2: Cộng điểm cho đơn hàng hiện tại
            int diemThuong = (tongTienCuoiCung > 0) ? static_cast<int>(tongTienCuoiCung / GIA_TRI_VND_CHO_MOT_DIEM) : 0;
            if (diemThuong > 0)
            {
                thanhVienHienTai->themDiem(diemThuong);
                cout << "  Bạn đã được cộng " << diemThuong << " điểm cho đơn hàng này." << endl;
            }
            cout << "  Tổng điểm tích lũy hiện tại của bạn là: " << thanhVienHienTai->getDiemTichLuy() << " điểm." << endl;
            // Bước 3: Hỏi đổi quà tặng (sau khi đã cộng điểm mới)
            char chonDoiQua = getInputValidated<char>("  Bạn có muốn dùng điểm để đổi quà tặng không? (y/n): ");
            if (chonDoiQua == 'y' || chonDoiQua == 'Y')
            {
                xemDanhSachLuaChonDoiDiemChoThanhVien(thanhVienHienTai->getDiemTichLuy(), "QUA_TANG");
                if (any_of(danhSachLuaChonDoiDiem.begin(), danhSachLuaChonDoiDiem.end(),
                           [&](const LuaChonDoiDiem &lc)
                           { return lc.loaiPhanThuong == "QUA_TANG" && thanhVienHienTai->getDiemTichLuy() >= lc.diemCanDoi; }))
                {
                    int idLuaChonQua = getInputValidated<int>("  Nhập ID quà tặng muốn đổi (0 để bỏ qua): ");
                    if (idLuaChonQua > 0)
                    {
                        LuaChonDoiDiem *luaChonQuaDaChon = nullptr;
                        for (auto &lc : danhSachLuaChonDoiDiem)
                        {
                            if (lc.id == idLuaChonQua && lc.loaiPhanThuong == "QUA_TANG" && thanhVienHienTai->getDiemTichLuy() >= lc.diemCanDoi)
                            {
                                luaChonQuaDaChon = &lc;
                                break;
                            }
                        }
                        if (luaChonQuaDaChon)
                        {
                            if (thanhVienHienTai->suDungDiem(luaChonQuaDaChon->diemCanDoi))
                            {
                                donMoi.themQuaTangDaDoi(luaChonQuaDaChon->moTaPhanThuong);
                                cout << "  Bạn đã đổi " << luaChonQuaDaChon->diemCanDoi << " điểm để nhận: " << luaChonQuaDaChon->moTaPhanThuong << endl;
                                cout << "  Số điểm còn lại: " << thanhVienHienTai->getDiemTichLuy() << " điểm." << endl;
                            }
                        }
                        else
                        {
                            cout << "  Lựa chọn quà tặng không hợp lệ hoặc bạn không đủ điểm." << endl;
                        }
                    }
                }
            }
        }
        else
        {                                               // Khách vãng lai
            donMoi.setTongTienThucTe(tongTienCuoiCung); // tongTienCuoiCung == tongTienTamTinh
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << tongTienCuoiCung << " VNĐ" << endl;
        }
        danhSachDonHang.push_back(donMoi);
        maDonHangTiepTheo++; // Tăng mã cho đơn hàng tiếp theo
        cout << "  Đã tạo đơn hàng #" << donMoi.getMaDonHang() << " thành công!" << endl;
    }

    void xemThongTinTaiKhoan_User()
    {
        if (thanhVienHienTai)
        {
            cout << "\n  --- Thông tin tài khoản của bạn ---" << endl;
            thanhVienHienTai->hienThiThongTin();
        }
        else
        {
            cout << "  Bạn chưa đăng nhập. Vui lòng đăng nhập để xem thông tin tài khoản." << endl;
            cout << "  Khách vãng lai không có tài khoản lưu trữ." << endl;
        }
    }
};

int main()
{
    CuaHangBurger cuaHang;
    int luaChonBanDau;
    const int menuWidth = 70;
    do
    {
        cout << "\n";
        veDuongNgang(menuWidth, '*');
        cout << string((menuWidth - 38) / 2, ' ') << "***** PHAN MEM QUAN LY CUA HANG BURGER *****" << endl;
        veDuongNgang(menuWidth, '*');
        cout << " * " << setw((menuWidth - 4) / 2 - 16) << "" << "CHÀO MỪNG ĐẾN VỚI CỬA HÀNG!" << setw((menuWidth - 4) / 2 - 0) << "" << " *" << endl;
        cout << " * " << setw((menuWidth - 4) / 2 - 12) << "" << "1. Đăng nhập Quản lý" << setw((menuWidth - 4) / 2 - 6) << "" << " *" << endl;
        cout << " * " << setw((menuWidth - 4) / 2 - 12) << "" << "2. Đăng nhập Thành viên" << setw((menuWidth - 4) / 2 - 7) << "" << " *" << endl;
        cout << " * " << setw((menuWidth - 4) / 2 - 12) << "" << "3. Đăng ký Thành viên mới" << setw((menuWidth - 4) / 2 - 9) << "" << " *" << endl;
        cout << " * " << setw((menuWidth - 4) / 2 - 12) << "" << "4. Tiếp tục là Khách" << setw((menuWidth - 4) / 2 - 6) << "" << " *" << endl;
        cout << " * " << setw((menuWidth - 4) / 2 - 12) << "" << "0. Thoát chương trình" << setw((menuWidth - 4) / 2 - 7) << "" << " *" << endl;
        veDuongNgang(menuWidth, '*');
        luaChonBanDau = getInputValidated<int>("  Nhập lựa chọn của bạn: ", "  Lựa chọn không hợp lệ. Vui lòng nhập số.");
        switch (luaChonBanDau)
        {
        case 1:
            if (cuaHang.dangNhapAdmin())
            {
                int choiceQuanLy;
                do
                {
                    cout << "\n";
                    veDuongNgang(menuWidth, '-');
                    cout << string((menuWidth - 26) / 2, ' ') << "--- CHỨC NĂNG QUẢN LÝ ---" << endl;
                    veDuongNgang(menuWidth, '-');
                    cout << "  1. Nhập/Cập nhật thông tin cửa hàng\n"
                         << "  2. Thêm burger\n"
                         << "  3. Thêm nước uống\n"
                         << "  4. Xem danh sách menu\n"
                         << "  5. Chỉnh sửa món ăn\n"
                         << "  6. Xóa món ăn\n"
                         << "  7. Xem danh sách đơn hàng\n"
                         << "  8. Thêm đơn hàng (cho khách/thành viên)\n"
                         // << "  9. Chỉnh sửa đơn hàng (ĐÃ BỎ)\n" // Chức năng này đã bị bỏ
                         << "  9. Xóa đơn hàng\n" // Đổi số thứ tự
                         << "  10. Thêm nhân viên\n"
                         << "  11. Xem danh sách nhân viên\n"
                         << "  12. Chỉnh sửa nhân viên\n"
                         << "  13. Xóa nhân viên\n"
                         << "  14. Xem danh sách thành viên\n"
                         << "  15. Báo cáo doanh thu\n"
                         << "  16. Báo cáo món bán chạy\n"
                         // << "  18. Quản lý lựa chọn đổi điểm (ĐÃ BỎ)\n" // Chức năng này đã bị bỏ
                         << "  17. Đăng xuất\n" // Đổi số thứ tự
                         << "  0. Thoát khỏi menu quản lý (Sẽ đăng xuất)" << endl;

                    choiceQuanLy = getInputValidated<int>("  Nhập lựa chọn của bạn: ");
                    switch (choiceQuanLy)
                    {
                    case 1:
                        cuaHang.nhapThongTinCuaHang();
                        break;
                    case 2:
                        cuaHang.themMonAn(true);
                        break;
                    case 3:
                        cuaHang.themMonAn(false);
                        break;
                    case 4:
                        cuaHang.hienThiDanhSachMenu();
                        break;
                    case 5:
                        cuaHang.chinhSuaMonAn();
                        break;
                    case 6:
                        cuaHang.xoaMonAn();
                        break;
                    case 7:
                        cuaHang.hienThiDanhSachDonHang();
                        break;
                    case 8:
                        cuaHang.themDonHangChoKhachHoacThanhVien();
                        break;
                    // case 9: // Chỉnh sửa đơn hàng - ĐÃ BỎ
                    case 9:
                        cuaHang.xoaDonHang();
                        break; // Trước là 10
                    case 10:
                        cuaHang.themNhanVien();
                        break; // Trước là 11
                    case 11:
                        cuaHang.xemDanhSachNhanVien();
                        break; // Trước là 12
                    case 12:
                        cuaHang.chinhSuaNhanVien();
                        break; // Trước là 13
                    case 13:
                        cuaHang.xoaNhanVien();
                        break; // Trước là 14
                    case 14:
                        cuaHang.hienThiDanhSachThanhVien();
                        break; // Trước là 15
                    case 15:
                        cuaHang.baoCaoDoanhThu();
                        break; // Trước là 16
                    case 16:
                        cuaHang.baoCaoMonBanChay();
                        break; // Trước là 17
                    // case 18: // Quản lý đổi điểm - ĐÃ BỎ
                    case 17:
                        cuaHang.dangXuat();
                        choiceQuanLy = 0;
                        break; // Trước là 19
                    case 0:
                        cuaHang.dangXuat();
                        cout << "  Đã đăng xuất và quay lại menu chính." << endl;
                        break;
                    default:
                        cout << "  Lựa chọn không hợp lệ." << endl;
                    }
                    if (choiceQuanLy != 0 && choiceQuanLy != 17)
                    { // Điều chỉnh số cho đăng xuất
                        cout << "\n  Nhấn Enter để tiếp tục...";
                        cin.get();
                    }
                } while (choiceQuanLy != 0);
            }
            break;
        case 2:
            if (cuaHang.dangNhapThanhVien())
            {
                int choiceThanhVien;
                do
                {
                    cout << "\n";
                    veDuongNgang(menuWidth, '-');
                    cout << string((menuWidth - 30) / 2, ' ') << "--- CHỨC NĂNG THÀNH VIÊN ---" << endl;
                    veDuongNgang(menuWidth, '-');
                    cout << "  1. Xem thông tin cửa hàng\n  2. Xem menu\n  3. Đặt món\n  4. Xem thông tin tài khoản và điểm\n  5. Thay đổi thông tin cá nhân\n  6. Đăng xuất\n  0. Thoát khỏi menu thành viên (Sẽ đăng xuất)" << endl;
                    choiceThanhVien = getInputValidated<int>("  Nhập lựa chọn của bạn: ");
                    switch (choiceThanhVien)
                    {
                    case 1:
                        cuaHang.xemThongTinCuaHang_User();
                        break;
                    case 2:
                        cuaHang.xemMenu_User();
                        break;
                    case 3:
                        cuaHang.datMon_User();
                        break;
                    case 4:
                        cuaHang.xemThongTinTaiKhoan_User();
                        break;
                    case 5:
                        cuaHang.thayDoiThongTinCaNhan();
                        break;
                    case 6:
                        cuaHang.dangXuat();
                        choiceThanhVien = 0;
                        break;
                    case 0:
                        cuaHang.dangXuat();
                        cout << "  Đã đăng xuất và quay lại menu chính." << endl;
                        break;
                    default:
                        cout << "  Lựa chọn không hợp lệ." << endl;
                    }
                    if (choiceThanhVien != 0 && choiceThanhVien != 6)
                    {
                        cout << "\n  Nhấn Enter để tiếp tục...";
                        cin.get();
                    }
                } while (choiceThanhVien != 0);
            }
            break;
        case 3:
            cuaHang.dangKyThanhVien();
            cout << "\n  Nhấn Enter để quay lại menu chính...";
            cin.get();
            break;
        case 4:
        {
            int choiceKhach;
            do
            {
                cout << "\n";
                veDuongNgang(menuWidth, '-');
                cout << string((menuWidth - 28) / 2, ' ') << "--- CHỨC NĂNG KHÁCH HÀNG ---" << endl;
                veDuongNgang(menuWidth, '-');
                cout << "  1. Xem thông tin cửa hàng\n  2. Xem menu\n  3. Đặt món\n  0. Quay lại menu chính" << endl;
                choiceKhach = getInputValidated<int>("  Nhập lựa chọn của bạn: ");
                switch (choiceKhach)
                {
                case 1:
                    cuaHang.xemThongTinCuaHang_User();
                    break;
                case 2:
                    cuaHang.xemMenu_User();
                    break;
                case 3:
                    cuaHang.datMon_User();
                    break; // Khách vãng lai sẽ không có phần đổi điểm trong hàm này
                case 0:
                    cout << "  Quay lại menu chính." << endl;
                    break;
                default:
                    cout << "  Lựa chọn không hợp lệ." << endl;
                }
                if (choiceKhach != 0)
                {
                    cout << "\n  Nhấn Enter để tiếp tục...";
                    cin.get();
                }
            } while (choiceKhach != 0);
        }
        break;
        case 0:
            cout << "  Xin cảm ơn bạn đã sử dụng dịch vụ!" << endl;
            cout << "  Hẹn gặp lại!" << endl;
            break;
        default:
            cout << "  Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
            cout << "\n  Nhấn Enter để thử lại...";
            cin.get();
        }
    } while (luaChonBanDau != 0);
    return 0;
}