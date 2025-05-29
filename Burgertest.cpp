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
// Template function để lấy và kiểm tra tính hợp lệ của dữ liệu nhập từ người dùng.
template <typename T>
T GetInputValidated(const string &prompt, const string &errorMessage = "  Lỗi: Dữ liệu nhập không hợp lệ. Vui lòng thử lại.")
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
// Vẽ một đường kẻ ngang với chiều dài và ký tự cho trước.
void VeDuongNgang(int chieuDai, char kyTu = '-')
{
    for (int i = 0; i < chieuDai; ++i)
    {
        cout << kyTu;
    }
    cout << endl;
}
// Chuyển đổi một chuỗi thành chữ hoa.
string StringToUpper(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}
// Đại diện cho một lựa chọn đổi điểm thưởng trong chương trình khách hàng thân thiết.
struct LuaChonDoiDiem
{
    int Id;
    int DiemCanDoi;
    string MoTaPhanThuong;
    string LoaiPhanThuong; // "QUA_TANG", "GIAM_GIA_PHAN_TRAM"
    double GiaTri;
    LuaChonDoiDiem(int _id, int _diem, string _moTa, string _loai, double _giaTri = 0)
        : Id(_id), DiemCanDoi(_diem), MoTaPhanThuong(_moTa), LoaiPhanThuong(_loai), GiaTri(_giaTri) {}
    void HienThi() const
    {
        cout << "  ID: " << Id << " | Điểm: " << DiemCanDoi << " | Phần thưởng: " << MoTaPhanThuong;
        if (LoaiPhanThuong == "GIAM_GIA_PHAN_TRAM")
        {
            cout << " (Giảm " << fixed << setprecision(0) << GiaTri * 100 << "%)";
        }
        cout << endl;
    }
};
// Lớp cơ sở cho các món ăn trong menu, bao gồm cả burger và Drink.
class MenuItem
{
private:
    string Ten;
    string MoTa;
    int SoLuong;
    double Gia;

protected:
    string TenGoc;

public:
    MenuItem(string _tenGoc, string _moTa, int _soLuong, double _gia)
        : TenGoc(_tenGoc), MoTa(_moTa), SoLuong(_soLuong), Gia(_gia) {}
    virtual ~MenuItem() {}
    virtual void CapNhatTenDayDu() = 0;
    string GetTen() const { return Ten; }
    string GetMoTa() const { return MoTa; }
    int GetSoLuong() const { return SoLuong; }
    double GetGia() const { return Gia; }
    string GetTenGocMenuItem() const { return TenGoc; }

    void SetTenDayDu(const string &newTen) { Ten = newTen; }
    void SetTenGocMenuItem(const string &newTenGoc)
    {
        TenGoc = newTenGoc;
        CapNhatTenDayDu();
    }
    void SetMoTa(const string &newMoTa) { MoTa = newMoTa; }
    void SetSoLuong(int newSoLuong) { SoLuong = newSoLuong; }
    void SetGia(double newGia) { Gia = newGia; }
    virtual string GetType() const = 0;
    virtual void HienThiThongTin() const
    {
        cout << "  Tên: " << Ten << endl;
        if (!MoTa.empty())
        {
            cout << "  Mô tả: " << MoTa << endl;
        }
        cout << "  Số lượng: " << SoLuong << endl;
        cout << "  Giá: " << fixed << setprecision(0) << Gia << " VNĐ" << endl;
    }
    virtual void LuuThongTinCoBanVaoFile(ofstream &ofs) const
    {
        ofs << TenGoc << endl;
        ofs << MoTa << endl;
        ofs << SoLuong << endl;
        ofs << Gia << endl;
    }
};
// Lớp đại diện cho một món Burger.
class Burger : public MenuItem
{
private:
    string LoaiThit;

public:
    Burger(string _tenGocBurger, string _moTaBurger, int _soLuong, double _gia, string _loaiThit)
        : MenuItem(_tenGocBurger, _moTaBurger, _soLuong, _gia), LoaiThit(_loaiThit)
    {
        CapNhatTenDayDu();
    }
    void CapNhatTenDayDu() override
    {
        SetTenDayDu("Burger - " + GetTenGocMenuItem());
    }
    string GetLoaiThit() const { return LoaiThit; }
    void SetLoaiThit(const string &newLoaiThit) { LoaiThit = newLoaiThit; }

    string GetType() const override { return "Burger"; }

    void HienThiThongTin() const override
    {
        MenuItem::HienThiThongTin();
        cout << "  Loại thịt: " << LoaiThit << endl;
    }
    void LuuVaoFile(ofstream &ofs) const
    {
        MenuItem::LuuThongTinCoBanVaoFile(ofs);
        ofs << LoaiThit << endl;
    }
};
// Lớp đại diện cho nước uống.
class Drink : public MenuItem
{
private:
    string KichThuoc;

public:
    Drink(string _tenGocNuocUong, int _soLuong, double _gia, string _kichThuocVal)
        : MenuItem(_tenGocNuocUong, "", _soLuong, _gia), KichThuoc(_kichThuocVal)
    {
        CapNhatTenDayDu();
    }

    void CapNhatTenDayDu() override
    {
        SetTenDayDu("Nước uống - " + GetTenGocMenuItem() + " (" + KichThuoc + ")");
    }

    string GetKichThuoc() const { return KichThuoc; }
    void SetKichThuoc(const string &newKichThuoc)
    {
        KichThuoc = newKichThuoc;
        CapNhatTenDayDu();
    }

    string GetType() const override { return "Drink"; }

    void HienThiThongTin() const override
    {
        MenuItem::HienThiThongTin();
        cout << "  Kích thước: " << KichThuoc << endl;
    }

    void LuuVaoFile(ofstream &ofs) const
    {
        MenuItem::LuuThongTinCoBanVaoFile(ofs);
        ofs << KichThuoc << endl;
    }
};
// Lớp đại diện cho thông tin Khách hàng.
class KhachHang
{
private:
    string Username;
    string Password;
    string Ten;
    string SoDienThoai;
    string DiaChi;
    bool DaMuaLanDau;
    int DiemTichLuy;

public:
    KhachHang(string _username, string _password, string _ten, string _sdt, string _dc, bool _daMua = false, int _diem = 0)
        : Username(_username), Password(_password), Ten(_ten), SoDienThoai(_sdt), DiaChi(_dc),
          DaMuaLanDau(_daMua), DiemTichLuy(_diem) {}
    KhachHang(string _ten, string _sdt, string _dc)
        : Username(""), Password(""), Ten(_ten), SoDienThoai(_sdt), DiaChi(_dc),
          DaMuaLanDau(true), DiemTichLuy(0) {}
    string GetUsername() const { return Username; }
    string GetPassword() const { return Password; }
    string GetTen() const { return Ten; }
    string GetSoDienThoai() const { return SoDienThoai; }
    string GetDiaChi() const { return DiaChi; }
    bool GetDaMuaLanDau() const { return DaMuaLanDau; }
    int GetDiemTichLuy() const { return DiemTichLuy; }

    void SetPassword(const string &newPass) { Password = newPass; }
    void SetTen(const string &newTen) { Ten = newTen; }
    void SetSoDienThoai(const string &newSdt) { SoDienThoai = newSdt; }
    void SetDiaChi(const string &newDc) { DiaChi = newDc; }
    void SetDaMuaLanDau(bool mua) { DaMuaLanDau = mua; }
    void ThemDiem(int diem)
    {
        if (diem > 0)
        {
            DiemTichLuy += diem;
        }
    }
    bool SuDungDiem(int diemCanDung)
    {
        if (diemCanDung > 0 && DiemTichLuy >= diemCanDung)
        {
            DiemTichLuy -= diemCanDung;
            return true;
        }
        return false;
    }

    void HienThiThongTin(bool laAdminXem = false) const
    {
        if (laAdminXem && !Username.empty())
        {
            cout << "  Username: " << Username << endl;
        }
        cout << "  Tên thành viên: " << Ten << endl;
        cout << "  Số điện thoại: " << SoDienThoai << endl;
        cout << "  Địa chỉ: " << DiaChi << endl;
        cout << "  Điểm tích lũy: " << DiemTichLuy << " điểm" << endl;
        if (!Username.empty())
        {
            cout << "  Trạng thái mua lần đầu (thành viên): " << (DaMuaLanDau ? "Đã áp dụng" : "Chưa áp dụng") << endl;
        }
    }
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << Username << endl;
        ofs << Password << endl;
        ofs << Ten << endl;
        ofs << SoDienThoai << endl;
        ofs << DiaChi << endl;
        ofs << DaMuaLanDau << endl;
        ofs << DiemTichLuy << endl;
    }
};
// Lớp đại diện cho thông tin Nhân viên.
class NhanVien
{
private:
    int MaNV;
    string TenNV;
    string SoDienThoaiNV;
    string DiaChiNV;

public:
    NhanVien(int ma, string ten, string sdt, string dc)
        : MaNV(ma), TenNV(ten), SoDienThoaiNV(sdt), DiaChiNV(dc) {}
    int GetMaNV() const { return MaNV; }
    string GetTenNV() const { return TenNV; }
    string GetSoDienThoaiNV() const { return SoDienThoaiNV; }
    string GetDiaChiNV() const { return DiaChiNV; }
    void SetTenNV(const string &ten) { TenNV = ten; }
    void SetSoDienThoaiNV(const string &sdt) { SoDienThoaiNV = sdt; }
    void SetDiaChiNV(const string &dc) { DiaChiNV = dc; }
    void HienThiThongTin() const
    {
        cout << "  Mã nhân viên: " << MaNV << endl;
        cout << "  Tên nhân viên: " << TenNV << endl;
        cout << "  Số điện thoại: " << SoDienThoaiNV << endl;
        cout << "  Địa chỉ: " << DiaChiNV << endl;
    }
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << MaNV << endl;
        ofs << TenNV << endl;
        ofs << SoDienThoaiNV << endl;
        ofs << DiaChiNV << endl;
    }
};
// Lớp đại diện cho Đơn hàng.
class DonHang
{
private:
    int MaDonHang;
    KhachHang KhachHangDat;
    vector<pair<MenuItem *, int>> DanhSachMonAn;
    double TongTienGoc;
    double TongTienThucTe;
    vector<string> QuaTangDaDoi;

public:
    DonHang(int _maDonHang, const KhachHang &_khachHangDat)
        : MaDonHang(_maDonHang), KhachHangDat(_khachHangDat), TongTienGoc(0), TongTienThucTe(0) {}
    DonHang(int _maDonHang, const KhachHang &_khachHangDat, double _tongGoc, double _thucTe)
        : MaDonHang(_maDonHang), KhachHangDat(_khachHangDat), TongTienGoc(_tongGoc), TongTienThucTe(_thucTe) {}
    int GetMaDonHang() const { return MaDonHang; }
    const KhachHang &GetKhachHangDat() const { return KhachHangDat; }
    const vector<pair<MenuItem *, int>> &GetDanhSachMonAn() const { return DanhSachMonAn; }
    double GetTongTienGoc() const { return TongTienGoc; }
    double GetTongTienThucTe() const { return TongTienThucTe; }
    const vector<string> &GetQuaTangDaDoi() const { return QuaTangDaDoi; }
    void ThemMonAn(MenuItem *mon, int soLuong)
    {
        DanhSachMonAn.push_back({mon, soLuong});
        TinhLaiTongTienGoc();
    }
    void TinhLaiTongTienGoc()
    {
        TongTienGoc = 0;
        for (const auto &item : DanhSachMonAn)
        {
            if (item.first)
                TongTienGoc += item.first->GetGia() * item.second;
        }
    }
    void SetTongTienThucTe(double amount)
    {
        TongTienThucTe = amount;
    }
    void ThemQuaTangDaDoi(const string &tenQua)
    {
        QuaTangDaDoi.push_back(tenQua);
    }

    void HienThiThongTin() const
    {
        cout << "\n  --- Đơn hàng #" << MaDonHang << " ---" << endl;
        cout << "  --- Thông tin khách đặt hàng ---" << endl;
        cout << "  Tên khách hàng: " << KhachHangDat.GetTen() << endl;
        cout << "  Số điện thoại: " << KhachHangDat.GetSoDienThoai() << endl;
        cout << "  Địa chỉ: " << KhachHangDat.GetDiaChi() << endl;
        cout << "  --- Món ăn đã đặt ---" << endl;
        for (const auto &item : DanhSachMonAn)
        {
            if (item.first)
            {
                cout << "  - " << item.first->GetTen() << " (x" << item.second << ") - "
                     << fixed << setprecision(0) << item.first->GetGia() * item.second << " VNĐ" << endl;
            }
            else
            {
                cout << "  - [Món ăn không xác định] (x" << item.second << ")" << endl;
            }
        }
        if (!QuaTangDaDoi.empty())
        {
            cout << "  --- Quà tặng đã đổi ---" << endl;
            for (const string &qua : QuaTangDaDoi)
            {
                cout << "  - " << qua << endl;
            }
        }
        cout << "  Tổng tiền gốc: " << fixed << setprecision(0) << TongTienGoc << " VNĐ" << endl;
        if (TongTienThucTe != TongTienGoc && TongTienThucTe != 0)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << TongTienThucTe << " VNĐ" << endl;
        }
        else if (TongTienGoc > 0 && TongTienThucTe == 0 && TongTienGoc != TongTienThucTe)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << TongTienGoc << " VNĐ (Chưa bao gồm giảm giá/điểm)" << endl;
        }
        else if (TongTienGoc == TongTienThucTe && TongTienGoc != 0)
        {
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << TongTienThucTe << " VNĐ" << endl;
        }
        else if (TongTienGoc == 0 && TongTienThucTe == 0 && QuaTangDaDoi.empty())
        {
            cout << "  Tổng tiền thanh toán: 0 VNĐ" << endl;
        }
        else if (TongTienGoc == 0 && !QuaTangDaDoi.empty() && TongTienThucTe == 0)
        {
            cout << "  Tổng tiền thanh toán: 0 VNĐ (Đổi quà bằng điểm)" << endl;
        }
    }
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << MaDonHang << endl;
        ofs << KhachHangDat.GetSoDienThoai() << endl;
        ofs << KhachHangDat.GetTen() << endl;
        ofs << KhachHangDat.GetDiaChi() << endl;
        ofs << TongTienGoc << endl;
        ofs << TongTienThucTe << endl;
        ofs << DanhSachMonAn.size() << endl;
        for (const auto &pair_item : DanhSachMonAn)
        {
            if (pair_item.first)
            {
                ofs << pair_item.first->GetTen() << endl;
                ofs << pair_item.second << endl;
            }
        }
        ofs << QuaTangDaDoi.size() << endl;
        for (const string &qua : QuaTangDaDoi)
        {
            ofs << qua << endl;
        }
    }
};
// Lớp chính quản lý toàn bộ hoạt động của cửa hàng burger.
class CuaHangBurger
{
private:
    vector<Burger *> DanhSachBurger;
    vector<Drink *> DanhSachNuocUong;
    vector<KhachHang> DanhSachThanhVien;
    vector<DonHang> DanhSachDonHang;
    vector<NhanVien> DanhSachNhanVien;
    vector<LuaChonDoiDiem> DanhSachLuaChonDoiDiem;

    KhachHang *ThanhVienHienTai = nullptr;
    bool IsAdminLoggedIn = false;
    string AdminUsername = "admin";
    string AdminPassword = "admin123";

    string TenCuaHang;
    string DiaChiCuaHang;
    string SoDienThoaiCuaHang;
    int MaDonHangTiepTheo;
    int MaNhanVienTiepTheo;
    double GiamGiaLanDau = 0.1;
    int SoLuongLonDeGiamGia = 5;
    double GiamGiaSoLuongLon = 0.05;

    const int GIA_TRI_VND_CHO_MOT_DIEM = 1000;
    const string FILE_BURGER = "burger.txt";
    const string FILE_DRINK = "drink.txt";
    const string FILE_THANHVIEN = "memberacc.txt";
    const string FILE_NHANVIEN = "nhanvien.txt";
    const string FILE_DONHANG = "donhang.txt";
    const string FILE_CUAHANG = "cuahang.txt";
    const string FILE_ADMINACC = "adminacc.txt";
    // Khởi tạo danh sách các lựa chọn đổi điểm cố định.
    void KhoiTaoLuaChonDoiDiemCoDinh()
    {
        DanhSachLuaChonDoiDiem.clear();
        DanhSachLuaChonDoiDiem.emplace_back(1, 1000, "Giảm 12% giá trị đơn hàng hiện tại", "GIAM_GIA_PHAN_TRAM", 0.12);
        DanhSachLuaChonDoiDiem.emplace_back(2, 150, "Móc khoá", "QUA_TANG", 0);
        DanhSachLuaChonDoiDiem.emplace_back(3, 250, "Gấu bông", "QUA_TANG", 0);
        DanhSachLuaChonDoiDiem.emplace_back(4, 500, "Bình nước giữ nhiệt", "QUA_TANG", 0);
    }
    // Tải thông tin tài khoản admin từ file, hoặc tạo mới nếu file không tồn tại.
    void TaiAdminAcc()
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
                    AdminUsername = user;
                    AdminPassword = pass;
                }
            }
            ifs.close();
        }
        else
        {
            ofstream ofs(FILE_ADMINACC);
            if (ofs.is_open())
            {
                ofs << AdminUsername << ":" << AdminPassword << endl;
                ofs.close();
            }
        }
    }
    // Tải danh sách burger từ file burger.txt.
    void TaiBurgerTuFile()
    {
        ifstream ifs(FILE_BURGER);
        if (!ifs.is_open())
            return;
        string tenGoc, moTa, loaiThit;
        int soLuong;
        double gia;
        while (getline(ifs, tenGoc))
        {
            if (!getline(ifs, moTa))
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
            if (!getline(ifs, loaiThit))
                break;
            DanhSachBurger.push_back(new Burger(tenGoc, moTa, soLuong, gia, loaiThit));
        }
        ifs.close();
    }
    // Lưu danh sách burger vào file burger.txt.
    void LuuBurgerRaFile() const
    {
        ofstream ofs(FILE_BURGER);
        if (!ofs.is_open())
            return;
        for (const auto *burger : DanhSachBurger)
        {
            burger->LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách đồ uống từ file drink.txt.
    void TaiNuocUongTuFile()
    {
        ifstream ifs(FILE_DRINK);
        if (!ifs.is_open())
            return;
        string tenGoc, kichThuoc, moTaTrong;
        int soLuong;
        double gia;
        while (getline(ifs, tenGoc))
        {
            if (!getline(ifs, moTaTrong))
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
            if (!getline(ifs, kichThuoc))
                break;
            DanhSachNuocUong.push_back(new Drink(tenGoc, soLuong, gia, kichThuoc));
        }
        ifs.close();
    }
    // Lưu danh sách đồ uống vào file drink.txt.
    void LuuNuocUongRaFile() const
    {
        ofstream ofs(FILE_DRINK);
        if (!ofs.is_open())
            return;
        for (const auto *drink : DanhSachNuocUong)
        {
            drink->LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách thành viên từ file.
    void TaiThanhVienTuFile()
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
            DanhSachThanhVien.emplace_back(username, password, ten, sdt, diaChi, daMua, diem);
        }
        ifs.close();
    }
    // Lưu danh sách thành viên vào file.
    void LuuThanhVienRaFile() const
    {
        ofstream ofs(FILE_THANHVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &tv : DanhSachThanhVien)
        {
            tv.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách nhân viên từ file.
    void TaiNhanVienTuFile()
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
            DanhSachNhanVien.emplace_back(ma, ten, sdt, dc);
            if (ma > maxMaNV)
                maxMaNV = ma;
        }
        MaNhanVienTiepTheo = maxMaNV + 1;
        ifs.close();
    }
    // Lưu danh sách nhân viên vào file.
    void LuuNhanVienRaFile() const
    {
        ofstream ofs(FILE_NHANVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &nv : DanhSachNhanVien)
        {
            nv.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tìm một món ăn (burger hoặc drink) dựa trên tên đầy đủ của nó.
    MenuItem *TimMonAnTheoTenDayDu(const string &tenDayDuMon)
    {
        for (auto *item : DanhSachBurger)
        {
            if (item->GetTen() == tenDayDuMon)
                return item;
        }
        for (auto *item : DanhSachNuocUong)
        {
            if (item->GetTen() == tenDayDuMon)
                return item;
        }
        return nullptr;
    }
    // Tìm thành viên dựa trên username.
    KhachHang *TimThanhVienTheoUsername(const string &username)
    {
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetUsername() == username)
                return &tv;
        }
        return nullptr;
    }
    // Tìm thành viên dựa trên số điện thoại.
    KhachHang *TimThanhVienTheoSDT(const string &sdt)
    {
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetSoDienThoai() == sdt && !tv.GetUsername().empty())
                return &tv;
        }
        return nullptr;
    }
    // Tải danh sách đơn hàng từ file.
    void TaiDonHangTuFile()
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
                string tenMonDayDu;
                int sl;
                getline(ifs, tenMonDayDu);
                if (!(ifs >> sl))
                {
                    ifs.clear();
                    ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                ifs.ignore();
                MenuItem *monPtr = TimMonAnTheoTenDayDu(tenMonDayDu);
                if (monPtr)
                    donMoi.ThemMonAn(monPtr, sl);
                else
                    cerr << "Canh bao: Khong tim thay mon an '" << tenMonDayDu << "' cho don hang #" << maDon << endl;
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
                donMoi.ThemQuaTangDaDoi(tenQua);
            }
            DanhSachDonHang.push_back(donMoi);
            if (maDon > maxMaDon)
                maxMaDon = maDon;
        }
        MaDonHangTiepTheo = maxMaDon + 1;
        ifs.close();
    }
    // Lưu danh sách đơn hàng vào file.
    void LuuDonHangRaFile() const
    {
        ofstream ofs(FILE_DONHANG);
        if (!ofs.is_open())
            return;
        for (const auto &dh : DanhSachDonHang)
        {
            dh.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải thông tin cửa hàng từ file.
    void TaiThongTinCuaHangTuFile()
    {
        ifstream ifs(FILE_CUAHANG);
        if (!ifs.is_open())
        {
            TenCuaHang = "Burger Ngon Đà Nẵng";
            DiaChiCuaHang = "[Địa chỉ chưa cập nhật]";
            SoDienThoaiCuaHang = "[SĐT chưa cập nhật]";
            return;
        }
        getline(ifs, TenCuaHang);
        getline(ifs, DiaChiCuaHang);
        getline(ifs, SoDienThoaiCuaHang);
        ifs.close();
    }
    // Lưu thông tin cửa hàng vào file.
    void LuuThongTinCuaHangRaFile() const
    {
        ofstream ofs(FILE_CUAHANG);
        if (!ofs.is_open())
            return;
        ofs << TenCuaHang << endl;
        ofs << DiaChiCuaHang << endl;
        ofs << SoDienThoaiCuaHang << endl;
        ofs.close();
    }

public:
    CuaHangBurger(string ten = "Burger Ngon Đà Nẵng", string diaChi = "[Địa chỉ]", string sdt = "[Số điện thoại]")
        : TenCuaHang(ten), DiaChiCuaHang(diaChi), SoDienThoaiCuaHang(sdt),
          MaDonHangTiepTheo(1), MaNhanVienTiepTheo(1)
    {
        TaiAdminAcc();
        KhoiTaoLuaChonDoiDiemCoDinh();
        TaiToanBoDuLieu();
    }
    ~CuaHangBurger()
    {
        LuuToanBoDuLieu();
        for (MenuItem *item : DanhSachBurger)
        {
            delete item;
        }
        DanhSachBurger.clear();
        for (MenuItem *item : DanhSachNuocUong)
        {
            delete item;
        }
        DanhSachNuocUong.clear();
    }

    void TaiToanBoDuLieu()
    {
        TaiThongTinCuaHangTuFile();
        TaiBurgerTuFile();
        TaiNuocUongTuFile();
        TaiThanhVienTuFile();
        TaiNhanVienTuFile();
        TaiDonHangTuFile();
    }
    void LuuToanBoDuLieu() const
    {
        LuuThongTinCuaHangRaFile();
        LuuBurgerRaFile();
        LuuNuocUongRaFile();
        LuuThanhVienRaFile();
        LuuNhanVienRaFile();
        LuuDonHangRaFile();
        cout << "Da luu du lieu ra file." << endl;
    }
    bool DangNhapAdmin()
    {
        string username, password_in;
        cout << "  --- Đăng nhập Quản lý ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password_in);
        if (username == AdminUsername && password_in == AdminPassword)
        {
            IsAdminLoggedIn = true;
            ThanhVienHienTai = nullptr;
            cout << "  Đăng nhập quản lý thành công!" << endl;
            return true;
        }
        cout << "  Sai username hoặc password quản lý." << endl;
        return false;
    }

    bool DangNhapThanhVien()
    {
        string username, password_in;
        cout << "  --- Đăng nhập Thành viên ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password_in);
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetUsername() == username && tv.GetPassword() == password_in)
            {
                ThanhVienHienTai = &tv;
                IsAdminLoggedIn = false;
                cout << "  Chào mừng trở lại, " << tv.GetTen() << "!" << endl;
                return true;
            }
        }
        cout << "  Sai username hoặc password thành viên." << endl;
        return false;
    }
    void DangKyThanhVien()
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
            for (const auto &tv : DanhSachThanhVien)
            {
                if (tv.GetUsername() == username)
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
            for (const auto &tv : DanhSachThanhVien)
            {
                if (tv.GetSoDienThoai() == sdt && !tv.GetUsername().empty())
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
        DanhSachThanhVien.emplace_back(username, password_in, ten, sdt, diachi, false, 0);
        cout << "  Đăng ký thành viên thành công! Username: " << username << endl;
        cout << "  Vui lòng đăng nhập để bắt đầu mua sắm và hưởng ưu đãi." << endl;
    }
    void DangXuat()
    {
        if (IsAdminLoggedIn)
        {
            IsAdminLoggedIn = false;
            cout << "  Đã đăng xuất khỏi tài khoản Quản lý." << endl;
        }
        else if (ThanhVienHienTai)
        {
            cout << "  Đã đăng xuất khỏi tài khoản Thành viên: " << ThanhVienHienTai->GetUsername() << endl;
            ThanhVienHienTai = nullptr;
        }
        else
        {
            cout << "  Không có ai đang đăng nhập." << endl;
        }
    }
    void ThayDoiThongTinCaNhan()
    {
        if (!ThanhVienHienTai)
        {
            cout << "  Lỗi: Bạn cần đăng nhập để sử dụng chức năng này." << endl;
            return;
        }
        cout << "\n  --- Thay đổi thông tin cá nhân ---" << endl;
        ThanhVienHienTai->HienThiThongTin();
        int choice = GetInputValidated<int>("  Bạn muốn thay đổi thông tin nào?\n  1. Họ tên\n  2. Số điện thoại\n  3. Địa chỉ\n  4. Mật khẩu\n  0. Quay lại\n  Nhập lựa chọn: ");
        string tenMoi, sdtMoi, dcMoi, passCu, passMoi1, passMoi2;
        switch (choice)
        {
        case 1:
            cout << "  Họ tên hiện tại: " << ThanhVienHienTai->GetTen() << endl;
            cout << "  Nhập họ tên mới: ";
            getline(cin, tenMoi);
            ThanhVienHienTai->SetTen(!tenMoi.empty() ? tenMoi : ThanhVienHienTai->GetTen());
            cout << (!tenMoi.empty() ? "  Đã cập nhật họ tên." : "  Không thay đổi họ tên.") << endl;
            break;
        case 2:
            cout << "  Số điện thoại hiện tại: " << ThanhVienHienTai->GetSoDienThoai() << endl;
            while (true)
            {
                cout << "  Nhập số điện thoại mới: ";
                getline(cin, sdtMoi);
                if (sdtMoi.empty())
                {
                    cout << "  Không thay đổi số điện thoại." << endl;
                    break;
                }
                if (sdtMoi == ThanhVienHienTai->GetSoDienThoai())
                {
                    cout << "  Số điện thoại mới trùng với số cũ. Không thay đổi." << endl;
                    break;
                }
                bool trungSDT = false;
                for (const auto &tv : DanhSachThanhVien)
                {
                    if (tv.GetSoDienThoai() == sdtMoi && tv.GetUsername() != ThanhVienHienTai->GetUsername())
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
                    ThanhVienHienTai->SetSoDienThoai(sdtMoi);
                    cout << "  Đã cập nhật số điện thoại." << endl;
                    break;
                }
            }
            break;
        case 3:
            cout << "  Địa chỉ hiện tại: " << ThanhVienHienTai->GetDiaChi() << endl;
            cout << "  Nhập địa chỉ mới: ";
            getline(cin, dcMoi);
            ThanhVienHienTai->SetDiaChi(!dcMoi.empty() ? dcMoi : ThanhVienHienTai->GetDiaChi());
            cout << (!dcMoi.empty() ? "  Đã cập nhật địa chỉ." : "  Không thay đổi địa chỉ.") << endl;
            break;
        case 4:
            cout << "  --- Thay đổi mật khẩu ---" << endl;
            cout << "  Nhập mật khẩu cũ: ";
            getline(cin, passCu);
            if (passCu == ThanhVienHienTai->GetPassword())
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
                        ThanhVienHienTai->SetPassword(passMoi1);
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
    void XemDanhSachLuaChonDoiDiemChoThanhVien(int diemHienCoCuaKhach, const string &loaiMuonXem) const
    {
        cout << "\n  --- Các lựa chọn đổi điểm có thể (" << (loaiMuonXem == "GIAM_GIA_PHAN_TRAM" ? "Giảm giá" : "Quà tặng") << ") ---" << endl;
        bool coLuaChonPhuHop = false;
        for (const auto &luaChon : DanhSachLuaChonDoiDiem)
        {
            if (luaChon.LoaiPhanThuong == loaiMuonXem && diemHienCoCuaKhach >= luaChon.DiemCanDoi)
            {
                luaChon.HienThi();
                coLuaChonPhuHop = true;
            }
        }
        if (!coLuaChonPhuHop)
        {
            cout << "  Bạn không đủ điểm cho bất kỳ lựa chọn " << (loaiMuonXem == "GIAM_GIA_PHAN_TRAM" ? "giảm giá" : "quà tặng") << " nào hiện tại." << endl;
        }
    }
    NhanVien *TimNhanVien(int maNV)
    {
        for (auto &nv : DanhSachNhanVien)
        {
            if (nv.GetMaNV() == maNV)
                return &nv;
        }
        return nullptr;
    }
    void NhapThongTinCuaHang()
    {
        cout << "\n  --- Nhập/Cập nhật thông tin cửa hàng ---" << endl;
        string tempTen, tempDiaChi, tempSDT;
        cout << "  Tên cửa hàng hiện tại: " << TenCuaHang << endl;
        cout << "  Nhập tên cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempTen);
        TenCuaHang = !tempTen.empty() ? tempTen : TenCuaHang;
        cout << "  Địa chỉ cửa hàng hiện tại: " << DiaChiCuaHang << endl;
        cout << "  Nhập địa chỉ cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempDiaChi);
        DiaChiCuaHang = !tempDiaChi.empty() ? tempDiaChi : DiaChiCuaHang;
        cout << "  Số điện thoại cửa hàng hiện tại: " << SoDienThoaiCuaHang << endl;
        cout << "  Nhập số điện thoại cửa hàng mới (để trống nếu không đổi): ";
        getline(cin, tempSDT);
        SoDienThoaiCuaHang = !tempSDT.empty() ? tempSDT : SoDienThoaiCuaHang;
        cout << "  Đã cập nhật thông tin cửa hàng!" << endl;
    }
    void ThemMonAn(bool laBurger)
    {
        string tenGoc, moTaBurger, loaiThit, kichThuoc;
        int soLuong;
        double gia;

        cout << (laBurger ? "\n  --- Thêm burger ---" : "\n  --- Thêm nước uống ---") << endl;
        cout << "  Nhập tên gốc " << (laBurger ? "burger (ví dụ: Bo Pho Mai, Ga Gion): " : "nước uống (ví dụ: Coca Cola, Tra Dao): ");
        getline(cin, tenGoc);
        if (laBurger)
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
                kichThuoc = StringToUpper(kichThuoc);
                if (kichThuoc == "S" || kichThuoc == "M" || kichThuoc == "L")
                    break;
                cout << "  Kích thước không hợp lệ. Vui lòng nhập S, M, hoặc L: ";
            }
        }
        soLuong = GetInputValidated<int>("  Nhập số lượng: ");
        while (soLuong < 0)
            soLuong = GetInputValidated<int>("  Lỗi: Số lượng phải là số không âm. Nhập lại: ");
        gia = GetInputValidated<double>("  Nhập giá: ");
        while (gia < 0)
            gia = GetInputValidated<double>("  Lỗi: Giá phải là số không âm. Nhập lại: ");
        if (laBurger)
        {
            DanhSachBurger.push_back(new Burger(tenGoc, moTaBurger, soLuong, gia, loaiThit));
        }
        else
        {
            DanhSachNuocUong.push_back(new Drink(tenGoc, soLuong, gia, kichThuoc));
        }
        cout << "  Đã thêm thành công!" << endl;
    }
    MenuItem *GetMonAnTheoSTTTongHop(int stt)
    {
        if (stt <= 0)
            return nullptr;
        if ((size_t)stt <= DanhSachBurger.size())
        {
            return DanhSachBurger[stt - 1];
        }
        stt -= DanhSachBurger.size();
        if ((size_t)stt <= DanhSachNuocUong.size())
        {
            return DanhSachNuocUong[stt - 1];
        }
        return nullptr;
    }
    void HienThiDanhSachMenuDayDu(bool laAdminXem) const
    {
        string titleText = "--- Menu Thực Đơn ---";
        const int W_STT = 5;
        const int W_TEN = 40;
        const int W_SOLUONG = 10;
        const int W_GIA = 15;
        int TableContentWidth;

        if (laAdminXem)
        {
            TableContentWidth = W_STT + W_TEN + W_SOLUONG + W_GIA;
        }
        else
        {
            TableContentWidth = W_STT + W_TEN + W_GIA;
        }
        int TitlePadding = (TableContentWidth - titleText.length()) / 2;
        TitlePadding = (TitlePadding < 0) ? 0 : TitlePadding;
        cout << "\n  " << string(TitlePadding, ' ') << titleText << endl;
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
        {
            cout << "  Menu hiện chưa có món nào." << endl;
            return;
        }
        cout << left;
        cout << "  " << setw(W_STT) << "STT"
             << setw(W_TEN) << "Tên";
        if (laAdminXem)
        {
            cout << setw(W_SOLUONG) << "Số lượng";
        }
        cout << setw(W_GIA) << "Giá (VNĐ)" << endl;
        cout << "  ";
        VeDuongNgang(TableContentWidth);
        int stt = 1;
        if (!DanhSachBurger.empty())
        {
            cout << "  --- Burger ---" << endl;
            for (const auto *burger : DanhSachBurger)
            {
                string sttDisplay = to_string(stt++) + ".";
                cout << "  " << setw(W_STT) << sttDisplay
                     << setw(W_TEN) << burger->GetTenGocMenuItem();
                if (laAdminXem)
                {
                    cout << setw(W_SOLUONG) << burger->GetSoLuong();
                }
                cout << setw(W_GIA) << fixed << setprecision(0) << burger->GetGia() << endl;
            }
        }
        if (!DanhSachNuocUong.empty())
        {
            cout << "  --- Nước uống ---" << endl;
            for (const auto *drink : DanhSachNuocUong)
            {
                string sttDisplay = to_string(stt++) + ".";
                string tenHienThi = drink->GetTenGocMenuItem() + " (" + drink->GetKichThuoc() + ")";
                cout << "  " << setw(W_STT) << sttDisplay
                     << setw(W_TEN) << tenHienThi;
                if (laAdminXem)
                {
                    cout << setw(W_SOLUONG) << drink->GetSoLuong();
                }
                cout << setw(W_GIA) << fixed << setprecision(0) << drink->GetGia() << endl;
            }
        }
    }
    void ChinhSuaMonAn()
    {
        HienThiDanhSachMenuDayDu(true);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int sttChon = GetInputValidated<int>("  Nhập STT món ăn muốn chỉnh sửa: ");
        MenuItem *monAnCanSua = GetMonAnTheoSTTTongHop(sttChon);
        if (!monAnCanSua)
        {
            cout << "  STT không hợp lệ." << endl;
            return;
        }
        cout << "\n  --- Chỉnh sửa món ăn: " << monAnCanSua->GetTen() << " ---" << endl;
        if (Burger *burger = dynamic_cast<Burger *>(monAnCanSua))
        {
            string moTaMoiBurger, loaiThitMoi;
            cout << "  Mô tả hiện tại: " << burger->GetMoTa() << endl;
            cout << "  Mô tả mới cho Burger (để trống để giữ nguyên): ";
            getline(cin, moTaMoiBurger);
            burger->SetMoTa(!moTaMoiBurger.empty() ? moTaMoiBurger : burger->GetMoTa());
            cout << "  Loại thịt hiện tại: " << burger->GetLoaiThit() << endl;
            cout << "  Loại thịt mới (để trống để giữ nguyên): ";
            getline(cin, loaiThitMoi);
            burger->SetLoaiThit(!loaiThitMoi.empty() ? loaiThitMoi : burger->GetLoaiThit());
        }
        else if (Drink *drink = dynamic_cast<Drink *>(monAnCanSua))
        {
            string kichThuocMoi;
            cout << "  Kích thước hiện tại: " << drink->GetKichThuoc() << endl;
            cout << "  Kích thước mới (S, M, L, để trống nếu không đổi): ";
            getline(cin, kichThuocMoi);
            if (!kichThuocMoi.empty())
            {
                kichThuocMoi = StringToUpper(kichThuocMoi);
                if (kichThuocMoi == "S" || kichThuocMoi == "M" || kichThuocMoi == "L")
                {
                    drink->SetKichThuoc(kichThuocMoi);
                }
                else
                {
                    cout << "  Kích thước không hợp lệ, không thay đổi." << endl;
                }
            }
        }
        cout << "  Số lượng mới (nhập số âm để giữ nguyên [" << monAnCanSua->GetSoLuong() << "]): ";
        string inputSL;
        getline(cin, inputSL);
        if (!inputSL.empty())
        {
            try
            {
                int sl = stoi(inputSL);
                if (sl >= 0)
                    monAnCanSua->SetSoLuong(sl);
            }
            catch (const std::exception &e)
            {
            }
        }
        cout << "  Giá mới (nhập số âm để giữ nguyên [" << fixed << setprecision(0) << monAnCanSua->GetGia() << "]): ";
        string inputG;
        getline(cin, inputG);
        if (!inputG.empty())
        {
            try
            {
                double g = stod(inputG);
                if (g >= 0)
                    monAnCanSua->SetGia(g);
            }
            catch (const std::exception &e)
            {
            }
        }
        cout << "  Đã cập nhật thông tin món ăn!" << endl;
    }

    void XoaMonAn()
    {
        HienThiDanhSachMenuDayDu(true);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int sttChon = GetInputValidated<int>("  Nhập STT món ăn muốn xóa: ");
        MenuItem *monAnCanXoa = nullptr;
        bool laBurgerMon = false;
        int indexTrongVector = -1;
        if (sttChon > 0 && (size_t)sttChon <= DanhSachBurger.size())
        {
            monAnCanXoa = DanhSachBurger[sttChon - 1];
            laBurgerMon = true;
            indexTrongVector = sttChon - 1;
        }
        else if (sttChon > DanhSachBurger.size() && (size_t)sttChon <= DanhSachBurger.size() + DanhSachNuocUong.size())
        {
            indexTrongVector = sttChon - DanhSachBurger.size() - 1;
            monAnCanXoa = DanhSachNuocUong[indexTrongVector];
            laBurgerMon = false;
        }
        if (!monAnCanXoa)
        {
            cout << "  STT không hợp lệ." << endl;
            return;
        }
        char confirm = GetInputValidated<char>("  Bạn có chắc chắn muốn xóa " + monAnCanXoa->GetTen() + "? (y/n): ");
        if (confirm == 'y' || confirm == 'Y')
        {
            delete monAnCanXoa;
            if (laBurgerMon)
            {
                DanhSachBurger.erase(DanhSachBurger.begin() + indexTrongVector);
            }
            else
            {
                DanhSachNuocUong.erase(DanhSachNuocUong.begin() + indexTrongVector);
            }
            cout << "  Đã xóa món ăn thành công!" << endl;
        }
        else
        {
            cout << "  Hủy bỏ xóa món ăn." << endl;
        }
    }
    void HienThiDanhSachDonHang() const
    {
        cout << "\n  --- Danh sách đơn hàng ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào." << endl;
            return;
        }
        for (const auto &don : DanhSachDonHang)
        {
            don.HienThiThongTin();
            VeDuongNgang(30, '-');
        }
    }
    void ThemDonHangChoKhachHoacThanhVien()
    {
        cout << "\n  --- Thêm đơn hàng mới (Quản lý) ---" << endl;
        int loaiKhach = GetInputValidated<int>("  Đơn hàng này cho:\n  1. Thành viên đã đăng ký\n  2. Khách vãng lai\n  Nhập lựa chọn: ");
        KhachHang *khachHangThucTe = nullptr;
        KhachHang khachHangDatDonHang("", "", "");
        if (loaiKhach == 1)
        {
            string idTimKiem;
            cout << "  Nhập Username hoặc SĐT của thành viên: ";
            getline(cin, idTimKiem);
            khachHangThucTe = TimThanhVienTheoUsername(idTimKiem);
            if (!khachHangThucTe)
                khachHangThucTe = TimThanhVienTheoSDT(idTimKiem);
            if (!khachHangThucTe)
            {
                cout << "  Không tìm thấy thành viên." << endl;
                return;
            }
            cout << "  Đơn hàng cho thành viên: " << khachHangThucTe->GetTen() << endl;
            khachHangDatDonHang = *khachHangThucTe;
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
        DonHang donMoi(MaDonHangTiepTheo, khachHangDatDonHang);
        char themMonAnYN;
        do
        {
            HienThiDanhSachMenuDayDu(false);
            if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            {
                cout << "Menu trống." << endl;
                break;
            }
            int sttChon = GetInputValidated<int>("  Nhập STT món ăn muốn thêm (0 để hoàn tất): ");
            if (sttChon == 0)
                break;
            MenuItem *monAnDaChon = GetMonAnTheoSTTTongHop(sttChon);
            if (!monAnDaChon)
            {
                cout << "STT không hợp lệ." << endl;
                themMonAnYN = 'y';
                continue;
            }
            int soLuongMua = GetInputValidated<int>("  Nhập số lượng: ");
            if (soLuongMua <= 0)
            {
                cout << "Số lượng không hợp lệ." << endl;
                themMonAnYN = 'y';
                continue;
            }
            if (soLuongMua <= monAnDaChon->GetSoLuong())
            {
                donMoi.ThemMonAn(monAnDaChon, soLuongMua);
                monAnDaChon->SetSoLuong(monAnDaChon->GetSoLuong() - soLuongMua);
            }
            else
            {
                cout << "  Số lượng không đủ trong kho." << endl;
            }
            themMonAnYN = GetInputValidated<char>("  Thêm món khác? (y/n): ");
        } while (themMonAnYN == 'y' || themMonAnYN == 'Y');
        if (donMoi.GetDanhSachMonAn().empty())
        {
            cout << "  Đơn hàng trống. Hủy thêm đơn hàng." << endl;
            return;
        }
        donMoi.TinhLaiTongTienGoc();
        double tongTienThanhToan = donMoi.GetTongTienGoc();
        if (khachHangThucTe)
        {
            if (!khachHangThucTe->GetDaMuaLanDau() && tongTienThanhToan > 0)
            {
                double tienGiam = tongTienThanhToan * GiamGiaLanDau;
                tongTienThanhToan -= tienGiam;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << GiamGiaLanDau * 100 << "% cho thành viên mua lần đầu." << endl;
                khachHangThucTe->SetDaMuaLanDau(true);
            }
            if (donMoi.GetDanhSachMonAn().size() >= (size_t)SoLuongLonDeGiamGia && tongTienThanhToan > 0)
            {
                double tienGiam = tongTienThanhToan * GiamGiaSoLuongLon;
                tongTienThanhToan -= tienGiam;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << GiamGiaSoLuongLon * 100 << "% cho đơn hàng số lượng lớn." << endl;
            }
            tongTienThanhToan = (tongTienThanhToan < 0) ? 0 : tongTienThanhToan;
            int diemThuong = static_cast<int>(tongTienThanhToan / GIA_TRI_VND_CHO_MOT_DIEM);
            if (diemThuong > 0)
            {
                khachHangThucTe->ThemDiem(diemThuong);
                cout << "  Thành viên " << khachHangThucTe->GetTen() << " được cộng " << diemThuong << " điểm." << endl;
                cout << "  Tổng điểm hiện tại: " << khachHangThucTe->GetDiemTichLuy() << " điểm." << endl;
            }
        }
        donMoi.SetTongTienThucTe(tongTienThanhToan);
        DanhSachDonHang.push_back(donMoi);
        MaDonHangTiepTheo++;
        cout << "  Đã thêm đơn hàng #" << donMoi.GetMaDonHang() << " thành công!" << endl;
        donMoi.HienThiThongTin();
    }

    void XoaDonHang()
    {
        HienThiDanhSachDonHang();
        if (DanhSachDonHang.empty())
            return;
        int maDonHangXoa = GetInputValidated<int>("  Nhập mã đơn hàng muốn xóa: ");
        for (auto it = DanhSachDonHang.begin(); it != DanhSachDonHang.end(); ++it)
        {
            if (it->GetMaDonHang() == maDonHangXoa)
            {
                char confirm = GetInputValidated<char>("  Bạn có chắc chắn muốn xóa đơn hàng #" + to_string(maDonHangXoa) + "? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    const auto &danhSachMATrongDon = it->GetDanhSachMonAn();
                    for (const auto &item : danhSachMATrongDon)
                    {
                        if (item.first)
                            item.first->SetSoLuong(item.first->GetSoLuong() + item.second);
                    }
                    cout << "  Lưu ý: Nếu đơn hàng này của thành viên và đã có giao dịch điểm/ưu đãi, việc hoàn lại các ưu đãi đó chưa được tự động xử lý." << endl;
                    DanhSachDonHang.erase(it);
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
    void ThemNhanVien()
    {
        cout << "\n  --- Thêm nhân viên ---" << endl;
        string ten, sdt, dc;
        cout << "  Nhập tên nhân viên: ";
        getline(cin, ten);
        cout << "  Nhập số điện thoại: ";
        getline(cin, sdt);
        cout << "  Nhập địa chỉ: ";
        getline(cin, dc);
        DanhSachNhanVien.emplace_back(MaNhanVienTiepTheo, ten, sdt, dc);
        cout << "  Đã thêm nhân viên #" << MaNhanVienTiepTheo++ << " thành công!" << endl;
    }
    void XemDanhSachNhanVien() const
    {
        cout << "\n  --- Danh sách nhân viên ---" << endl;
        if (DanhSachNhanVien.empty())
        {
            cout << "  Chưa có nhân viên nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(7) << "Mã NV" << setw(25) << "Tên nhân viên" << setw(18) << "Số điện thoại" << setw(30) << "Địa chỉ" << endl;
        VeDuongNgang(80);
        for (const auto &nv : DanhSachNhanVien)
        {
            cout << " " << setw(7) << nv.GetMaNV()
                 << setw(25) << nv.GetTenNV()
                 << setw(18) << nv.GetSoDienThoaiNV()
                 << setw(30) << nv.GetDiaChiNV() << endl;
        }
        cout << right;
    }
    void ChinhSuaNhanVien()
    {
        XemDanhSachNhanVien();
        if (DanhSachNhanVien.empty())
            return;
        int maNVChinhSua = GetInputValidated<int>("  Nhập mã nhân viên muốn chỉnh sửa: ");
        NhanVien *nvCanSua = TimNhanVien(maNVChinhSua);
        if (!nvCanSua)
        {
            cout << "  Không tìm thấy nhân viên có mã #" << maNVChinhSua << endl;
            return;
        }
        cout << "\n  --- Chỉnh sửa thông tin nhân viên #" << nvCanSua->GetMaNV() << " ---" << endl;
        string tenMoi, sdtMoi, dcMoi;
        cout << "  Tên mới (để trống để giữ nguyên [" << nvCanSua->GetTenNV() << "]): ";
        getline(cin, tenMoi);
        nvCanSua->SetTenNV(!tenMoi.empty() ? tenMoi : nvCanSua->GetTenNV());
        cout << "  Số điện thoại mới (để trống để giữ nguyên [" << nvCanSua->GetSoDienThoaiNV() << "]): ";
        getline(cin, sdtMoi);
        nvCanSua->SetSoDienThoaiNV(!sdtMoi.empty() ? sdtMoi : nvCanSua->GetSoDienThoaiNV());
        cout << "  Địa chỉ mới (để trống để giữ nguyên [" << nvCanSua->GetDiaChiNV() << "]): ";
        getline(cin, dcMoi);
        nvCanSua->SetDiaChiNV(!dcMoi.empty() ? dcMoi : nvCanSua->GetDiaChiNV());
        cout << "  Đã cập nhật thông tin nhân viên!" << endl;
    }
    void XoaNhanVien()
    {
        XemDanhSachNhanVien();
        if (DanhSachNhanVien.empty())
            return;
        int maNVXoa = GetInputValidated<int>("  Nhập mã nhân viên muốn xóa: ");
        for (auto it = DanhSachNhanVien.begin(); it != DanhSachNhanVien.end(); ++it)
        {
            if (it->GetMaNV() == maNVXoa)
            {
                char confirm = GetInputValidated<char>("  Bạn có chắc chắn muốn xóa nhân viên #" + to_string(maNVXoa) + " (" + it->GetTenNV() + ")? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    DanhSachNhanVien.erase(it);
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
    void HienThiDanhSachThanhVien() const
    {
        cout << "\n  --- Danh sách thành viên ---" << endl;
        if (DanhSachThanhVien.empty())
        {
            cout << "  Chưa có thành viên nào." << endl;
            return;
        }
        cout << left;
        cout << " " << setw(15) << "Username" << setw(25) << "Tên Khách Hàng" << setw(18) << "Số Điện Thoại" << setw(30) << "Địa Chỉ" << right << setw(10) << "Điểm" << setw(10) << "Mua Lần Đầu" << left << endl;
        VeDuongNgang(110);
        for (const auto &tv : DanhSachThanhVien)
        {
            cout << " " << setw(15) << tv.GetUsername()
                 << setw(25) << tv.GetTen()
                 << setw(18) << tv.GetSoDienThoai()
                 << setw(30) << tv.GetDiaChi()
                 << right << setw(10) << tv.GetDiemTichLuy()
                 << setw(10) << (tv.GetDaMuaLanDau() ? "Rồi" : "Chưa") << left << endl;
        }
        cout << right;
    }
    void BaoCaoDoanhThu() const
    {
        cout << "\n  --- Báo cáo doanh thu ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào để thống kê." << endl;
            return;
        }
        double tongDoanhThuGoc = 0, tongDoanhThuThucTe = 0;
        for (const auto &donHang : DanhSachDonHang)
        {
            tongDoanhThuGoc += donHang.GetTongTienGoc();
            tongDoanhThuThucTe += donHang.GetTongTienThucTe();
        }
        cout << "  Tổng số đơn hàng: " << DanhSachDonHang.size() << endl;
        cout << "  Tổng doanh thu (theo tiền gốc): " << fixed << setprecision(0) << tongDoanhThuGoc << " VNĐ" << endl;
        cout << "  Tổng doanh thu thực tế (sau giảm giá/điểm/quà): " << fixed << setprecision(0) << tongDoanhThuThucTe << " VNĐ" << endl;
    }
    void BaoCaoMonBanChay() const
    {
        cout << "\n  --- Báo cáo món bán chạy ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chưa có đơn hàng nào để thống kê." << endl;
            return;
        }
        map<string, int> soLuongMonDaBan;
        map<string, double> doanhThuTungMonGoc;
        for (const auto &donHang : DanhSachDonHang)
        {
            for (const auto &itemPair : donHang.GetDanhSachMonAn())
            {
                if (itemPair.first)
                {
                    MenuItem *mon = itemPair.first;
                    int soLuong = itemPair.second;
                    soLuongMonDaBan[mon->GetTen()] += soLuong;
                    doanhThuTungMonGoc[mon->GetTen()] += mon->GetGia() * soLuong;
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
        VeDuongNgang(63);
        for (size_t i = 0; i < vecSLMon.size() && i < 10; ++i)
        {
            cout << " " << setw(5) << i + 1 << setw(40) << vecSLMon[i].first << right << setw(15) << vecSLMon[i].second << left << endl;
        }
        cout << right;
        cout << "\n  --- Top món đóng góp DOANH THU GỐC cao nhất ---" << endl;
        cout << left << " " << setw(5) << "Hạng" << setw(40) << "Tên Món" << right << setw(20) << "Doanh Thu Gốc" << left << endl;
        VeDuongNgang(70);
        for (size_t i = 0; i < vecDTMon.size() && i < 10; ++i)
        {
            cout << " " << setw(5) << i + 1 << setw(40) << vecDTMon[i].first << right << setw(20) << fixed << setprecision(0) << vecDTMon[i].second << left << " VNĐ" << endl;
        }
        cout << right;
    }
    void XemThongTinCuaHang_User() const
    {
        cout << "\n  --- Thông tin Cửa hàng Burger ---" << endl;
        cout << "  Chào mừng quý khách đến với " << TenCuaHang << " tại " << DiaChiCuaHang << "!" << endl;
        cout << "  Chúng tôi phục vụ những chiếc burger ngon nhất và nhiều loại thức uống hấp dẫn." << endl;
        cout << "  Số điện thoại liên hệ: " << SoDienThoaiCuaHang << endl;
    }
    void XemMenu_User()
    {
        HienThiDanhSachMenuDayDu(false);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int luaChonXemChiTiet = GetInputValidated<int>("  Nhập STT món ăn để xem chi tiết (0 để bỏ qua): ", "Lựa chọn không hợp lệ.");
        if (luaChonXemChiTiet != 0)
        {
            MenuItem *monAnDuocChon = GetMonAnTheoSTTTongHop(luaChonXemChiTiet);
            if (monAnDuocChon)
            {
                cout << "\n  --- Thông tin chi tiết ---" << endl;
                monAnDuocChon->HienThiThongTin();
            }
            else
            {
                cout << "STT không hợp lệ." << endl;
            }
        }
    }
    void DatMon_User()
    {
        cout << "\n  --- Đặt món ---" << endl;
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
        {
            cout << "  Xin lỗi, menu hiện tại trống." << endl;
            return;
        }
        HienThiDanhSachMenuDayDu(false);
        KhachHang khachHangDatDonHang("", "", "");
        bool laThanhVienDat = (ThanhVienHienTai != nullptr);
        if (laThanhVienDat)
        {
            khachHangDatDonHang = *ThanhVienHienTai;
            cout << "  Đặt hàng với tư cách thành viên: " << ThanhVienHienTai->GetTen() << endl;
        }
        else
        {
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
        DonHang donMoi(MaDonHangTiepTheo, khachHangDatDonHang);
        char datTiep;
        do
        {
            int sttChon = GetInputValidated<int>("  Nhập STT món ăn muốn đặt (0 để hoàn tất): ");
            if (sttChon == 0)
                break;
            MenuItem *monAnDaChon = GetMonAnTheoSTTTongHop(sttChon);
            if (!monAnDaChon)
            {
                cout << "STT không hợp lệ." << endl;
                datTiep = 'y';
                continue;
            }
            int soLuongDat = GetInputValidated<int>("  Nhập số lượng: ");
            if (soLuongDat <= 0)
            {
                cout << "Số lượng không hợp lệ." << endl;
                datTiep = 'y';
                continue;
            }
            if (soLuongDat <= monAnDaChon->GetSoLuong())
            {
                donMoi.ThemMonAn(monAnDaChon, soLuongDat);
                monAnDaChon->SetSoLuong(monAnDaChon->GetSoLuong() - soLuongDat);
                cout << "  Đã thêm " << monAnDaChon->GetTen() << " vào đơn hàng." << endl;
            }
            else
            {
                cout << "  Số lượng không đủ trong kho. Chỉ còn " << monAnDaChon->GetSoLuong() << "." << endl;
            }
            datTiep = GetInputValidated<char>("  Muốn đặt thêm món khác? (y/n): ");
        } while (datTiep == 'y' || datTiep == 'Y');
        if (donMoi.GetDanhSachMonAn().empty())
        {
            cout << "  Đơn hàng trống. Hủy bỏ tạo đơn hàng." << endl;
            return;
        }
        donMoi.TinhLaiTongTienGoc();
        double tongTienTamTinh = donMoi.GetTongTienGoc();
        double tongTienCuoiCung = tongTienTamTinh;
        cout << "  Tổng giá tiền tạm tính: " << fixed << setprecision(0) << tongTienTamTinh << " VNĐ" << endl;
        if (laThanhVienDat && ThanhVienHienTai)
        {
            const LuaChonDoiDiem *luaChonGiamGia12 = nullptr;
            for (const auto &lc : DanhSachLuaChonDoiDiem)
            {
                if (lc.LoaiPhanThuong == "GIAM_GIA_PHAN_TRAM" && lc.DiemCanDoi == 1000)
                {
                    luaChonGiamGia12 = &lc;
                    break;
                }
            }
            if (luaChonGiamGia12 && ThanhVienHienTai->GetDiemTichLuy() >= luaChonGiamGia12->DiemCanDoi)
            {
                char chonGiamGia = GetInputValidated<char>("  Bạn có " + to_string(ThanhVienHienTai->GetDiemTichLuy()) + " điểm. Bạn có muốn dùng " + to_string(luaChonGiamGia12->DiemCanDoi) + " điểm để " + luaChonGiamGia12->MoTaPhanThuong + " không? (y/n): ");
                if (chonGiamGia == 'y' || chonGiamGia == 'Y')
                {
                    if (ThanhVienHienTai->SuDungDiem(luaChonGiamGia12->DiemCanDoi))
                    {
                        double tienGiam = tongTienCuoiCung * luaChonGiamGia12->GiaTri;
                        tongTienCuoiCung -= tienGiam;
                        cout << "  Đã áp dụng giảm giá " << fixed << setprecision(0) << luaChonGiamGia12->GiaTri * 100 << "%. Số tiền giảm: " << fixed << setprecision(0) << tienGiam << " VNĐ." << endl;
                        cout << "  Điểm còn lại: " << ThanhVienHienTai->GetDiemTichLuy() << " điểm." << endl;
                    }
                }
            }
            if (!ThanhVienHienTai->GetDaMuaLanDau() && tongTienCuoiCung > 0)
            {
                double tienGiamLanDau = tongTienCuoiCung * GiamGiaLanDau;
                tongTienCuoiCung -= tienGiamLanDau;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << GiamGiaLanDau * 100 << "% (tương đương " << fixed << setprecision(0) << tienGiamLanDau << " VNĐ) cho lần đặt đầu của thành viên!" << endl;
                ThanhVienHienTai->SetDaMuaLanDau(true);
            }
            if (donMoi.GetDanhSachMonAn().size() >= (size_t)SoLuongLonDeGiamGia && tongTienCuoiCung > 0)
            {
                double tienGiamSLDon = tongTienCuoiCung * GiamGiaSoLuongLon;
                tongTienCuoiCung -= tienGiamSLDon;
                cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << GiamGiaSoLuongLon * 100 << "% (tương đương " << fixed << setprecision(0) << tienGiamSLDon << " VNĐ) cho đơn hàng số lượng lớn!" << endl;
            }
            tongTienCuoiCung = (tongTienCuoiCung < 0) ? 0 : tongTienCuoiCung;
            donMoi.SetTongTienThucTe(tongTienCuoiCung);
            cout << "  Tổng tiền thanh toán cuối cùng: " << fixed << setprecision(0) << tongTienCuoiCung << " VNĐ" << endl;
            int diemThuong = (tongTienCuoiCung > 0) ? static_cast<int>(tongTienCuoiCung / GIA_TRI_VND_CHO_MOT_DIEM) : 0;
            if (diemThuong > 0)
            {
                ThanhVienHienTai->ThemDiem(diemThuong);
                cout << "  Bạn đã được cộng " << diemThuong << " điểm cho đơn hàng này." << endl;
            }
            cout << "  Tổng điểm tích lũy hiện tại của bạn là: " << ThanhVienHienTai->GetDiemTichLuy() << " điểm." << endl;
            char chonDoiQua = GetInputValidated<char>("  Bạn có muốn dùng điểm để đổi quà tặng không? (y/n): ");
            if (chonDoiQua == 'y' || chonDoiQua == 'Y')
            {
                XemDanhSachLuaChonDoiDiemChoThanhVien(ThanhVienHienTai->GetDiemTichLuy(), "QUA_TANG");
                if (any_of(DanhSachLuaChonDoiDiem.begin(), DanhSachLuaChonDoiDiem.end(),
                           [&](const LuaChonDoiDiem &lc)
                           { return lc.LoaiPhanThuong == "QUA_TANG" && ThanhVienHienTai->GetDiemTichLuy() >= lc.DiemCanDoi; }))
                {

                    int idLuaChonQua = GetInputValidated<int>("  Nhập ID quà tặng muốn đổi (0 để bỏ qua): ");
                    if (idLuaChonQua > 0)
                    {
                        const LuaChonDoiDiem *luaChonQuaDaChon = nullptr;
                        for (const auto &lc : DanhSachLuaChonDoiDiem)
                        {
                            if (lc.Id == idLuaChonQua && lc.LoaiPhanThuong == "QUA_TANG" && ThanhVienHienTai->GetDiemTichLuy() >= lc.DiemCanDoi)
                            {
                                luaChonQuaDaChon = &lc;
                                break;
                            }
                        }
                        if (luaChonQuaDaChon)
                        {
                            if (ThanhVienHienTai->SuDungDiem(luaChonQuaDaChon->DiemCanDoi))
                            {
                                donMoi.ThemQuaTangDaDoi(luaChonQuaDaChon->MoTaPhanThuong);
                                cout << "  Bạn đã đổi " << luaChonQuaDaChon->DiemCanDoi << " điểm để nhận: " << luaChonQuaDaChon->MoTaPhanThuong << endl;
                                cout << "  Số điểm còn lại: " << ThanhVienHienTai->GetDiemTichLuy() << " điểm." << endl;
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
        {
            donMoi.SetTongTienThucTe(tongTienCuoiCung);
            cout << "  Tổng tiền thanh toán: " << fixed << setprecision(0) << tongTienCuoiCung << " VNĐ" << endl;
        }
        DanhSachDonHang.push_back(donMoi);
        MaDonHangTiepTheo++;
        cout << "  Đã tạo đơn hàng #" << donMoi.GetMaDonHang() << " thành công!" << endl;
    }
    void XemThongTinTaiKhoan_User()
    {
        if (ThanhVienHienTai)
        {
            cout << "\n  --- Thông tin tài khoản của bạn ---" << endl;
            ThanhVienHienTai->HienThiThongTin();
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
        VeDuongNgang(menuWidth, '*');
        cout << string((menuWidth - 44) / 2, ' ') << "***** PHAN MEM QUAN LY CUA HANG BURGER *****" << endl;
        VeDuongNgang(menuWidth, '*');
        cout << "* " << setw((menuWidth - 30) / 2) << "" << "CHÀO MỪNG ĐẾN VỚI CỬA HÀNG!" << setw((menuWidth - 28) / 2) << " *" << endl;
        cout << "* " << setw((menuWidth - 26) / 2) << "" << "1. Đăng nhập Quản lý" << setw((menuWidth - 18) / 2) << " *" << endl;
        cout << "* " << setw((menuWidth - 26) / 2) << "" << "2. Đăng nhập Thành viên" << setw((menuWidth - 24) / 2) << " *" << endl;
        cout << "* " << setw((menuWidth - 26) / 2) << "" << "3. Đăng ký Thành viên mới" << setw((menuWidth - 28) / 2) << " *" << endl;
        cout << "* " << setw((menuWidth - 26) / 2) << "" << "4. Tiếp tục là Khách" << setw((menuWidth - 18) / 2) << " *" << endl;
        cout << "* " << setw((menuWidth - 26) / 2) << "" << "0. Thoát chương trình" << setw((menuWidth - 20) / 2) << " *" << endl;
        VeDuongNgang(menuWidth, '*');
        luaChonBanDau = GetInputValidated<int>("  Nhập lựa chọn của bạn: ", "  Lựa chọn không hợp lệ. Vui lòng nhập số.");
        switch (luaChonBanDau)
        {
        case 1:
            if (cuaHang.DangNhapAdmin())
            {
                int choiceQuanLy;
                do
                {
                    cout << "\n";
                    VeDuongNgang(menuWidth, '-');
                    cout << string((menuWidth - 26) / 2, ' ') << "--- CHỨC NĂNG QUẢN LÝ ---" << endl;
                    VeDuongNgang(menuWidth, '-');
                    cout << "  1. Nhập/Cập nhật thông tin cửa hàng\n"
                         << "  2. Thêm burger\n"
                         << "  3. Thêm nước uống\n"
                         << "  4. Xem danh sách menu\n"
                         << "  5. Chỉnh sửa món ăn\n"
                         << "  6. Xóa món ăn\n"
                         << "  7. Xem danh sách đơn hàng\n"
                         << "  8. Thêm đơn hàng (cho khách/thành viên)\n"
                         << "  9. Xóa đơn hàng\n"
                         << "  10. Thêm nhân viên\n"
                         << "  11. Xem danh sách nhân viên\n"
                         << "  12. Chỉnh sửa nhân viên\n"
                         << "  13. Xóa nhân viên\n"
                         << "  14. Xem danh sách thành viên\n"
                         << "  15. Báo cáo doanh thu\n"
                         << "  16. Báo cáo món bán chạy\n"
                         << "  17. Đăng xuất\n"
                         << "  0. Thoát khỏi menu quản lý (Sẽ đăng xuất)" << endl;
                    choiceQuanLy = GetInputValidated<int>("  Nhập lựa chọn của bạn: ");
                    switch (choiceQuanLy)
                    {
                    case 1:
                        cuaHang.NhapThongTinCuaHang();
                        break;
                    case 2:
                        cuaHang.ThemMonAn(true);
                        break;
                    case 3:
                        cuaHang.ThemMonAn(false);
                        break;
                    case 4:
                        cuaHang.HienThiDanhSachMenuDayDu(true);
                        break;
                    case 5:
                        cuaHang.ChinhSuaMonAn();
                        break;
                    case 6:
                        cuaHang.XoaMonAn();
                        break;
                    case 7:
                        cuaHang.HienThiDanhSachDonHang();
                        break;
                    case 8:
                        cuaHang.ThemDonHangChoKhachHoacThanhVien();
                        break;
                    case 9:
                        cuaHang.XoaDonHang();
                        break;
                    case 10:
                        cuaHang.ThemNhanVien();
                        break;
                    case 11:
                        cuaHang.XemDanhSachNhanVien();
                        break;
                    case 12:
                        cuaHang.ChinhSuaNhanVien();
                        break;
                    case 13:
                        cuaHang.XoaNhanVien();
                        break;
                    case 14:
                        cuaHang.HienThiDanhSachThanhVien();
                        break;
                    case 15:
                        cuaHang.BaoCaoDoanhThu();
                        break;
                    case 16:
                        cuaHang.BaoCaoMonBanChay();
                        break;
                    case 17:
                        cuaHang.DangXuat();
                        choiceQuanLy = 0;
                        break;
                    case 0:
                        cuaHang.DangXuat();
                        cout << "  Đã đăng xuất và quay lại menu chính." << endl;
                        break;
                    default:
                        cout << "  Lựa chọn không hợp lệ." << endl;
                    }
                    if (choiceQuanLy != 0 && choiceQuanLy != 17)
                    {
                        cout << "\n  Nhấn Enter để tiếp tục...";
                        cin.get();
                    }
                } while (choiceQuanLy != 0);
            }
            break;
        case 2:
            if (cuaHang.DangNhapThanhVien())
            {
                int choiceThanhVien;
                do
                {
                    cout << "\n";
                    VeDuongNgang(menuWidth, '-');
                    cout << string((menuWidth - 30) / 2, ' ') << "--- CHỨC NĂNG THÀNH VIÊN ---" << endl;
                    VeDuongNgang(menuWidth, '-');
                    cout << "  1. Xem thông tin cửa hàng\n  2. Xem menu\n  3. Đặt món\n  4. Xem thông tin tài khoản và điểm\n  5. Thay đổi thông tin cá nhân\n  6. Đăng xuất\n  0. Thoát khỏi menu thành viên (Sẽ đăng xuất)" << endl;
                    choiceThanhVien = GetInputValidated<int>("  Nhập lựa chọn của bạn: ");
                    switch (choiceThanhVien)
                    {
                    case 1:
                        cuaHang.XemThongTinCuaHang_User();
                        break;
                    case 2:
                        cuaHang.XemMenu_User();
                        break;
                    case 3:
                        cuaHang.DatMon_User();
                        break;
                    case 4:
                        cuaHang.XemThongTinTaiKhoan_User();
                        break;
                    case 5:
                        cuaHang.ThayDoiThongTinCaNhan();
                        break;
                    case 6:
                        cuaHang.DangXuat();
                        choiceThanhVien = 0;
                        break;
                    case 0:
                        cuaHang.DangXuat();
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
            cuaHang.DangKyThanhVien();
            cout << "\n  Nhấn Enter để quay lại menu chính...";
            cin.get();
            break;
        case 4:
        {
            int choiceKhach;
            do
            {
                cout << "\n";
                VeDuongNgang(menuWidth, '-');
                cout << string((menuWidth - 28) / 2, ' ') << "--- CHỨC NĂNG KHÁCH HÀNG ---" << endl;
                VeDuongNgang(menuWidth, '-');
                cout << "  1. Xem thông tin cửa hàng\n  2. Xem menu\n  3. Đặt món\n  0. Quay lại menu chính" << endl;
                choiceKhach = GetInputValidated<int>("  Nhập lựa chọn của bạn: ");
                switch (choiceKhach)
                {
                case 1:
                    cuaHang.XemThongTinCuaHang_User();
                    break;
                case 2:
                    cuaHang.XemMenu_User();
                    break;
                case 3:
                    cuaHang.DatMon_User();
                    break;
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