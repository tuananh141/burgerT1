#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

// Hàm để vẽ khung cho menu
void veDuongNgang(int chieuDai, char kyTu = '-')
{
    for (int i = 0; i < chieuDai; ++i)
    {
        cout << kyTu;
    }
    cout << endl;
}
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
    string getTen() const { return ten; }
    string getMoTa() const { return moTa; }
    int getSoLuong() const { return soLuong; }
    double getGia() const { return gia; }
    void setTen(const string &newTen) { ten = newTen; }
    void setMoTa(const string &newMoTa) { moTa = newMoTa; }
    void setSoLuong(int newSoLuong) { soLuong = newSoLuong; }
    void setGia(double newGia) { gia = newGia; }
    virtual void hienThiThongTin() const
    {
        cout << "  Tên: " << ten << endl;
        cout << "  Mô tả: " << moTa << endl;
        cout << "  Số lượng: " << soLuong << endl;
        cout << "  Giá: " << fixed << setprecision(0) << gia << " VNĐ" << endl;
    }
};
class Burger : public MenuItem
{
private:
    string loaiThit;
    vector<string> topping;

public:
    Burger(string ten, string moTa, int soLuong, double gia, string loaiThit)
        : MenuItem("Burger - " + ten, moTa, soLuong, gia), loaiThit(loaiThit) {}
    string getLoaiThit() const { return loaiThit; }
    const vector<string> &getTopping() const { return topping; }
    void setLoaiThit(const string &newLoaiThit) { loaiThit = newLoaiThit; }
    void themTopping(const string &top) { topping.push_back(top); }
    void hienThiThongTin() const override
    {
        MenuItem::hienThiThongTin();
        cout << "  Loại thịt: " << loaiThit << endl;
        cout << "  Topping: ";
        if (topping.empty())
        {
            cout << "Không có" << endl;
        }
        else
        {
            for (size_t i = 0; i < topping.size(); ++i)
            {
                cout << topping[i] << (i < topping.size() - 1 ? ", " : "");
            }
            cout << endl;
        }
    }
};
class Drink : public MenuItem
{
private:
    string loaiNuoc;
    string kichThuoc;

public:
    Drink(string ten, string moTa, int soLuong, double gia, string loaiNuoc, string kichThuoc)
        : MenuItem("Nước uống - " + ten + " (" + kichThuoc + ")", moTa, soLuong, gia),
          loaiNuoc(loaiNuoc), kichThuoc(kichThuoc) {}
    string getLoaiNuoc() const { return loaiNuoc; }
    string getKichThuoc() const { return kichThuoc; }
    void setLoaiNuoc(const string &newLoaiNuoc) { loaiNuoc = newLoaiNuoc; }
    void setKichThuoc(const string &newKichThuoc) { kichThuoc = newKichThuoc; }
    void hienThiThongTin() const override
    {
        MenuItem::hienThiThongTin();
        cout << "  Loại nước: " << loaiNuoc << endl;
        cout << "  Kích thước: " << kichThuoc << endl;
    }
};
class KhachHang
{
private:
    string ten;
    string soDienThoai;
    string diaChi;
    bool daMuaLanDau;

public:
    KhachHang(string ten, string soDienThoai, string diaChi)
        : ten(ten), soDienThoai(soDienThoai), diaChi(diaChi), daMuaLanDau(false) {}
    string getTen() const { return ten; }
    string getSoDienThoai() const { return soDienThoai; }
    string getDiaChi() const { return diaChi; }
    bool getDaMuaLanDau() const { return daMuaLanDau; }
    void setDaMuaLanDau(bool mua) { daMuaLanDau = mua; }
    void hienThiThongTin() const
    {
        cout << "  Tên khách hàng: " << ten << endl;
        cout << "  Số điện thoại: " << soDienThoai << endl;
        cout << "  Địa chỉ: " << diaChi << endl;
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
};
class DonHang
{
private:
    int maDonHang;
    KhachHang khachHang;
    vector<pair<MenuItem *, int>> danhSachMonAn;
    double tongTien;

public:
    DonHang(int ma, const KhachHang &kh) : maDonHang(ma), khachHang(kh), tongTien(0) {}
    int getMaDonHang() const { return maDonHang; }
    const KhachHang &getKhachHang() const { return khachHang; }
    const vector<pair<MenuItem *, int>> &getDanhSachMonAn() const { return danhSachMonAn; }
    double getTongTien() const { return tongTien; }
    void themMonAn(MenuItem *mon, int soLuong)
    {
        danhSachMonAn.push_back({mon, soLuong});
        tongTien += mon->getGia() * soLuong;
    }
    void tinhTongTien()
    {
        tongTien = 0;
        for (const auto &item : danhSachMonAn)
        {
            tongTien += item.first->getGia() * item.second;
        }
    }
    void hienThiThongTin() const
    {
        cout << "\n  --- Đơn hàng #" << maDonHang << " ---" << endl;
        khachHang.hienThiThongTin();
        cout << "  --- Món ăn đã đặt ---" << endl;
        for (const auto &item : danhSachMonAn)
        {
            cout << "  - " << item.first->getTen() << " (x" << item.second << ") - "
                 << fixed << setprecision(2) << item.first->getGia() * item.second << " VNĐ" << endl;
        }
        cout << "  Tổng tiền: " << fixed << setprecision(2) << tongTien << " VNĐ" << endl;
    }
};
class CuaHangBurger
{
private:
    vector<MenuItem *> danhSachMenu;
    vector<KhachHang> danhSachKhachHang;
    vector<DonHang> danhSachDonHang;
    vector<NhanVien> danhSachNhanVien;
    string tenCuaHang;
    string diaChiCuaHang;
    string soDienThoaiCuaHang;
    int maDonHangTiepTheo;
    int maNhanVienTiepTheo;
    double giamGiaLanDau = 0.1;
    int soLuongLonDeGiamGia = 5;
    double giamGiaSoLuongLon = 0.05;

public:
    CuaHangBurger(string ten = "Burger Ngon Đà Nẵng", string diaChi = "[Địa chỉ]", string sdt = "[Số điện thoại]")
        : tenCuaHang(ten), diaChiCuaHang(diaChi), soDienThoaiCuaHang(sdt), maDonHangTiepTheo(1), maNhanVienTiepTheo(1) {}
    ~CuaHangBurger()
    {
        for (MenuItem *item : danhSachMenu)
        {
            delete item;
        }
    }
    // Chức năng chung
    MenuItem *timMonAn(int index, const vector<MenuItem *> &danhSach) const
    {
        if (index > 0 && index <= danhSach.size())
        {
            return danhSach[index - 1];
        }
        return 0;
    }
    NhanVien *timNhanVien(int maNV)
    {
        for (auto &nv : danhSachNhanVien)
        {
            if (nv.getMaNV() == maNV)
            {
                return &nv;
            }
        }
        return 0;
    }
    // Chức năng của chủ cửa hàng
    void nhapThongTinCuaHang()
    {
        cout << "\n  --- Nhập/Cập nhật thông tin cửa hàng ---" << endl;
        cin.ignore();
        cout << "  Nhập tên cửa hàng: ";
        getline(cin, tenCuaHang);
        cout << "  Nhập địa chỉ cửa hàng: ";
        getline(cin, diaChiCuaHang);
        cout << "  Nhập số điện thoại cửa hàng: ";
        getline(cin, soDienThoaiCuaHang);
        cout << "  Đã cập nhật thông tin cửa hàng!" << endl;
    }
    void themMonAn(bool Meal)
    {
        string ten, moTa, loaiThit, loaiNuoc, kichThuoc;
        int soLuong;
        double gia;
        cout << "\n  --- Thêm " << (Meal ? "burger" : "nước uống") << " ---" << endl;
        cin.ignore();
        cout << "  Nhập tên: ";
        getline(cin, ten);
        cout << "  Nhập mô tả: ";
        getline(cin, moTa);
        cout << "  Nhập số lượng: ";
        cin >> soLuong;
        while (cin.fail() || soLuong < 0)
        {
            cout << "  Lỗi: Vui lòng nhập số lượng hợp lệ." << endl;
            cin.clear();
            cin.ignore();
            cout << "  Nhập lại số lượng: ";
            cin >> soLuong;
        }
        cout << "  Nhập giá: ";
        cin >> gia;
        while (cin.fail() || gia < 0)
        {
            cout << "  Lỗi: Vui lòng nhập giá hợp lệ." << endl;
            cin.clear();
            cin.ignore();
            cout << "  Nhập lại giá: ";
            cin >> gia;
        }
        cin.ignore();
        if (Meal)
        {
            cout << "  Nhập loại thịt: ";
            getline(cin, loaiThit);
            danhSachMenu.push_back(new Burger(ten, moTa, soLuong, gia, loaiThit));
        }
        else
        {
            cout << "  Nhập loại nước: ";
            getline(cin, loaiNuoc);
            cout << "  Nhập kích thước (Nhỏ/Vừa/Lớn): ";
            getline(cin, kichThuoc);
            danhSachMenu.push_back(new Drink(ten, moTa, soLuong, gia, loaiNuoc, kichThuoc));
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
        cout << setw(5) << "STT" << setw(25) << "Tên" << setw(10) << "Số lượng" << setw(15) << "Giá (VNĐ)" << endl;
        veDuongNgang(55);
        for (size_t i = 0; i < danhSachMenu.size(); ++i)
        {
            cout << setw(5) << i + 1 << setw(25) << danhSachMenu[i]->getTen()
                 << setw(10) << danhSachMenu[i]->getSoLuong()
                 << setw(15) << fixed << setprecision(2) << danhSachMenu[i]->getGia() << endl;
        }
    }
    void chinhSuaMonAn()
    {
        hienThiDanhSachMenu();
        if (danhSachMenu.empty())
            return;
        int index;
        cout << "  Nhập STT món ăn muốn chỉnh sửa: ";
        cin >> index;
        MenuItem *monAnCanSua = timMonAn(index, danhSachMenu);
        if (!monAnCanSua)
        {
            cout << "  STT không hợp lệ." << endl;
            cin.ignore();
            return;
        }
        cin.ignore();
        cout << "\n  --- Chỉnh sửa món ăn: " << monAnCanSua->getTen() << " ---" << endl;
        string tenMoi, moTaMoi;
        int soLuongMoi = -1;
        double giaMoi = -1;
        cout << "  Tên mới (để trống để giữ nguyên): ";
        getline(cin, tenMoi);
        if (!tenMoi.empty())
            monAnCanSua->setTen(tenMoi);
        cout << "  Mô tả mới (để trống để giữ nguyên): ";
        getline(cin, moTaMoi);
        if (!moTaMoi.empty())
            monAnCanSua->setMoTa(moTaMoi);
        cout << "  Số lượng mới (nhập -1 để giữ nguyên): ";
        cin >> soLuongMoi;
        if (!cin.fail() && soLuongMoi != -1)
            monAnCanSua->setSoLuong(soLuongMoi);
        cin.ignore();
        cout << "  Giá mới (nhập -1 để giữ nguyên): ";
        cin >> giaMoi;
        if (!cin.fail() && giaMoi != -1)
            monAnCanSua->setGia(giaMoi);
        cin.ignore();
        if (Burger *burger = dynamic_cast<Burger *>(monAnCanSua))
        {
            string loaiThitMoi;
            cout << "  Loại thịt mới (để trống để giữ nguyên): ";
            getline(cin, loaiThitMoi);
            if (!loaiThitMoi.empty())
                burger->setLoaiThit(loaiThitMoi);
            // Thêm chỉnh sửa topping nếu cần
        }
        else if (Drink *drink = dynamic_cast<Drink *>(monAnCanSua))
        {
            string loaiNuocMoi, kichThuocMoi;
            cout << "  Loại nước mới (để trống để giữ nguyên): ";
            getline(cin, loaiNuocMoi);
            if (!loaiNuocMoi.empty())
                drink->setLoaiNuoc(loaiNuocMoi);
            cout << "  Kích thước mới (để trống để giữ nguyên): ";
            getline(cin, kichThuocMoi);
            if (!kichThuocMoi.empty())
                drink->setKichThuoc(kichThuocMoi);
        }
        cout << "  Đã cập nhật thông tin món ăn!" << endl;
    }
    void xoaMonAn()
    {
        hienThiDanhSachMenu();
        if (danhSachMenu.empty())
            return;
        int index;
        cout << "  Nhập STT món ăn muốn xóa: ";
        cin >> index;
        MenuItem *monAnCanXoa = timMonAn(index, danhSachMenu);
        if (!monAnCanXoa)
        {
            cout << "  STT không hợp lệ." << endl;
            cin.ignore();
            return;
        }
        cin.ignore();
        cout << "  Bạn có chắc chắn muốn xóa " << monAnCanXoa->getTen() << "? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y')
        {
            for (auto it = danhSachMenu.begin(); it != danhSachMenu.end(); ++it)
            {
                if (*it == monAnCanXoa)
                {
                    delete *it;
                    danhSachMenu.erase(it);
                    cout << "  Đã xóa món ăn thành công!" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "  Hủy bỏ xóa món ăn." << endl;
        }
        cin.ignore();
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
    void themDonHang()
    {
        cout << "\n  --- Thêm đơn hàng mới ---" << endl;
        cin.ignore();
        string tenKhachHang, soDienThoaiKhachHang, diaChiKhachHang;
        cout << "  Nhập tên khách hàng: ";
        getline(cin, tenKhachHang);
        cout << "  Nhập số điện thoại: ";
        getline(cin, soDienThoaiKhachHang);
        cout << "  Nhập địa chỉ: ";
        getline(cin, diaChiKhachHang);
        KhachHang khach(tenKhachHang, soDienThoaiKhachHang, diaChiKhachHang);
        danhSachKhachHang.push_back(khach);
        DonHang donMoi(maDonHangTiepTheo++, khach);
        char themMonAnYN;
        do
        {
            hienThiDanhSachMenu();
            if (danhSachMenu.empty())
                break;
            int indexMonAn, soLuongMua;
            cout << "  Nhập STT món ăn muốn thêm vào đơn hàng (0 để bỏ qua): ";
            cin >> indexMonAn;
            if (indexMonAn == 0)
                break;
            MenuItem *monAnDaChon = timMonAn(indexMonAn, danhSachMenu);
            if (monAnDaChon)
            {
                cout << "  Nhập số lượng: ";
                cin >> soLuongMua;
                if (soLuongMua > 0 && soLuongMua <= monAnDaChon->getSoLuong())
                {
                    donMoi.themMonAn(monAnDaChon, soLuongMua);
                    monAnDaChon->setSoLuong(monAnDaChon->getSoLuong() - soLuongMua);
                }
                else
                {
                    cout << "  Số lượng không hợp lệ hoặc không đủ." << endl;
                }
            }
            else
            {
                cout << "  STT món ăn không hợp lệ." << endl;
            }
            cout << "  Thêm món ăn khác vào đơn hàng này? (y/n): ";
            cin >> themMonAnYN;
        } while (themMonAnYN == 'y' || themMonAnYN == 'Y');
        danhSachDonHang.push_back(donMoi);
        cout << "  Đã thêm đơn hàng #" << donMoi.getMaDonHang() << " thành công!" << endl;
        cin.ignore();
    }
    void chinhSuaDonHang()
    {
        hienThiDanhSachDonHang();
        if (danhSachDonHang.empty())
            return;
        int maDonHangSua;
        cout << "  Nhập mã đơn hàng muốn chỉnh sửa: ";
        cin >> maDonHangSua;
        cin.ignore();
        DonHang *donHangCanSua = nullptr;
        for (auto &don : danhSachDonHang)
        {
            if (don.getMaDonHang() == maDonHangSua)
            {
                donHangCanSua = &don;
                break;
            }
        }
        if (!donHangCanSua)
        {
            cout << "  Mã đơn hàng không tồn tại." << endl;
            return;
        }
        cout << "\n  --- Chỉnh sửa đơn hàng #" << donHangCanSua->getMaDonHang() << " ---" << endl;
        cout << "  Các món ăn hiện có trong đơn hàng:" << endl;
        const auto &danhSachMATrongDon = donHangCanSua->getDanhSachMonAn();
        if (danhSachMATrongDon.empty())
        {
            cout << "  Đơn hàng hiện không có món nào." << endl;
        }
        else
        {
            for (size_t i = 0; i < danhSachMATrongDon.size(); ++i)
            {
                cout << "  " << i + 1 << ". " << danhSachMATrongDon[i].first->getTen() << " (x" << danhSachMATrongDon[i].second << ")" << endl;
            }
        }
        int choice;
        do
        {
            cout << "\n  Chọn thao tác:" << endl;
            cout << "  1. Thêm món ăn vào đơn hàng" << endl;
            cout << "  2. Xóa món ăn khỏi đơn hàng" << endl;
            cout << "  0. Hoàn tất chỉnh sửa" << endl;
            cout << "  Nhập lựa chọn: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
            {
                hienThiDanhSachMenu();
                if (danhSachMenu.empty())
                    break;
                int indexMonAnThem, soLuongThem;
                cout << "  Nhập STT món ăn muốn thêm: ";
                cin >> indexMonAnThem;
                MenuItem *monThem = timMonAn(indexMonAnThem, danhSachMenu);
                if (monThem)
                {
                    cout << "  Nhập số lượng thêm: ";
                    cin >> soLuongThem;
                    if (soLuongThem > 0 && soLuongThem <= monThem->getSoLuong())
                    {
                        donHangCanSua->themMonAn(monThem, soLuongThem);
                        monThem->setSoLuong(monThem->getSoLuong() - soLuongThem);
                        cout << "  Đã thêm món ăn vào đơn hàng." << endl;
                    }
                    else
                    {
                        cout << "  Số lượng không hợp lệ hoặc không đủ." << endl;
                    }
                }
                else
                {
                    cout << "  STT món ăn không hợp lệ." << endl;
                }
                cin.ignore();
                break;
            }
            case 2:
            {
                if (danhSachMATrongDon.empty())
                {
                    cout << "  Đơn hàng không có món để xóa." << endl;
                    break;
                }
                int indexMonAnXoa;
                cout << "  Nhập STT món ăn muốn xóa khỏi đơn hàng: ";
                cin >> indexMonAnXoa;
                if (indexMonAnXoa > 0 && indexMonAnXoa <= danhSachMATrongDon.size())
                {
                    MenuItem *monXoa = danhSachMATrongDon[indexMonAnXoa - 1].first;
                    int soLuongDaMua = danhSachMATrongDon[indexMonAnXoa - 1].second;

                    DonHang donHangMoi(donHangCanSua->getMaDonHang(), donHangCanSua->getKhachHang());
                    for (size_t i = 0; i < danhSachMATrongDon.size(); ++i)
                    {
                        if (i != indexMonAnXoa - 1)
                        {
                            donHangMoi.themMonAn(danhSachMATrongDon[i].first, danhSachMATrongDon[i].second);
                        }
                        else
                        {
                            monXoa->setSoLuong(monXoa->getSoLuong() + soLuongDaMua);
                        }
                    }
                    for (auto it = danhSachDonHang.begin(); it != danhSachDonHang.end(); ++it)
                    {
                        if (it->getMaDonHang() == donHangCanSua->getMaDonHang())
                        {
                            *it = donHangMoi;
                            cout << "  Đã xóa món ăn khỏi đơn hàng." << endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout << "  STT món ăn không hợp lệ." << endl;
                }
                cin.ignore();
                break;
            }
            case 0:
                cout << "  Hoàn tất chỉnh sửa đơn hàng #" << donHangCanSua->getMaDonHang() << endl;
                break;
            default:
                cout << "  Lựa chọn không hợp lệ." << endl;
            }
        } while (choice != 0);
    }
    void xoaDonHang()
    {
        hienThiDanhSachDonHang();
        if (danhSachDonHang.empty())
            return;
        int maDonHangXoa;
        cout << "  Nhập mã đơn hàng muốn xóa: ";
        cin >> maDonHangXoa;
        cin.ignore();
        for (auto it = danhSachDonHang.begin(); it != danhSachDonHang.end(); ++it)
        {
            if (it->getMaDonHang() == maDonHangXoa)
            {
                cout << "  Bạn có chắc chắn muốn xóa đơn hàng #" << maDonHangXoa << "? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    const auto &danhSachMATrongDon = it->getDanhSachMonAn();
                    for (const auto &item : danhSachMATrongDon)
                    {
                        item.first->setSoLuong(item.first->getSoLuong() + item.second);
                    }
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
    // Quản lý nhân viên
    void themNhanVien()
    {
        cout << "\n  --- Thêm nhân viên ---" << endl;
        cin.ignore();
        string ten, sdt, dc;
        cout << "  Nhập tên nhân viên: ";
        getline(cin, ten);
        cout << "  Nhập số điện thoại: ";
        getline(cin, sdt);
        cout << "  Nhập địa chỉ: ";
        getline(cin, dc);
        danhSachNhanVien.emplace_back(maNhanVienTiepTheo++, ten, sdt, dc);
        cout << "  Đã thêm nhân viên #" << maNhanVienTiepTheo - 1 << " thành công!" << endl;
    }
    void xemDanhSachNhanVien() const
    {
        cout << "\n  --- Danh sách nhân viên ---" << endl;
        if (danhSachNhanVien.empty())
        {
            cout << "  Chưa có nhân viên nào." << endl;
            return;
        }
        cout << setw(5) << "Mã NV" << setw(20) << "Tên nhân viên" << setw(15) << "Số điện thoại" << endl;
        veDuongNgang(50);
        for (const auto &nv : danhSachNhanVien)
        {
            cout << setw(5) << nv.getMaNV() << setw(20) << nv.getTenNV() << setw(15) << nv.getSoDienThoaiNV() << endl;
        }
    }
    void chinhSuaNhanVien()
    {
        xemDanhSachNhanVien();
        if (danhSachNhanVien.empty())
            return;
        int maNVChinhSua;
        cout << "  Nhập mã nhân viên muốn chỉnh sửa: ";
        cin >> maNVChinhSua;
        cin.ignore();
        NhanVien *nvCanSua = timNhanVien(maNVChinhSua);
        if (!nvCanSua)
        {
            cout << "  Không tìm thấy nhân viên có mã #" << maNVChinhSua << endl;
            return;
        }
        cout << "\n  --- Chỉnh sửa thông tin nhân viên #" << nvCanSua->getMaNV() << " ---" << endl;
        string tenMoi, sdtMoi, dcMoi;
        cout << "  Tên mới (để trống để giữ nguyên): ";
        getline(cin, tenMoi);
        if (!tenMoi.empty())
            nvCanSua->setTenNV(tenMoi);
        cout << "  Số điện thoại mới (để trống để giữ nguyên): ";
        getline(cin, sdtMoi);
        if (!sdtMoi.empty())
            nvCanSua->setSoDienThoaiNV(sdtMoi);
        cout << "  Địa chỉ mới (để trống để giữ nguyên): ";
        getline(cin, dcMoi);
        if (!dcMoi.empty())
            nvCanSua->setDiaChiNV(dcMoi);
        cout << "  Đã cập nhật thông tin nhân viên!" << endl;
    }
    void xoaNhanVien()
    {
        xemDanhSachNhanVien();
        if (danhSachNhanVien.empty())
            return;
        int maNVXoa;
        cout << "  Nhập mã nhân viên muốn xóa: ";
        cin >> maNVXoa;
        cin.ignore();
        for (auto it = danhSachNhanVien.begin(); it != danhSachNhanVien.end(); ++it)
        {
            if (it->getMaNV() == maNVXoa)
            {
                cout << "  Bạn có chắc chắn muốn xóa nhân viên #" << maNVXoa << " (" << it->getTenNV() << ")? (y/n): ";
                char confirm;
                cin >> confirm;
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
    // Chức năng của khách hàng
    void xemDanhSachMenuKhachHang() const
    {
        cout << "\n  --- Menu của cửa hàng ---" << endl;
        if (danhSachMenu.empty())
        {
            cout << "  Menu hiện chưa có món nào." << endl;
            return;
        }
        cout << setw(5) << "STT" << setw(25) << "Tên" << setw(15) << "Giá (VNĐ)" << endl;
        veDuongNgang(45);
        for (size_t i = 0; i < danhSachMenu.size(); ++i)
        {
            cout << setw(5) << i + 1 << setw(25) << danhSachMenu[i]->getTen()
                 << setw(15) << fixed << setprecision(2) << danhSachMenu[i]->getGia() << endl;
        }
        int luaChonXemChiTiet;
        cout << "Nhập STT món ăn để xem chi tiết (0 để bỏ qua): ";
        cin >> luaChonXemChiTiet;
        if (luaChonXemChiTiet > 0 && luaChonXemChiTiet <= danhSachMenu.size())
        {
            cout << "\n  --- Thông tin chi tiết ---" << endl;
            danhSachMenu[luaChonXemChiTiet - 1]->hienThiThongTin();
        }
    }
    void datMon()
    {
        cout << "\n  --- Đặt món ---" << endl;
        xemDanhSachMenuKhachHang();
        if (danhSachMenu.empty())
            return;
        cin.ignore();
        string tenKhachHang, soDienThoaiKhachHang, diaChiKhachHang;
        cout << "  Nhập tên của bạn: ";
        getline(cin, tenKhachHang);
        cout << "  Nhập số điện thoại: ";
        getline(cin, soDienThoaiKhachHang);
        cout << "  Nhập địa chỉ: ";
        getline(cin, diaChiKhachHang);
        KhachHang *khachHangHienTai = nullptr;
        for (auto &khach : danhSachKhachHang)
        {
            if (khach.getTen() == tenKhachHang && khach.getSoDienThoai() == soDienThoaiKhachHang)
            {
                khachHangHienTai = &khach;
                break;
            }
        }
        if (!khachHangHienTai)
        {
            danhSachKhachHang.push_back(KhachHang(tenKhachHang, soDienThoaiKhachHang, diaChiKhachHang));
            khachHangHienTai = &danhSachKhachHang.back();
        }
        DonHang donMoi(maDonHangTiepTheo++, *khachHangHienTai);
        char datTiep = 'y';
        while (datTiep == 'y' || datTiep == 'Y')
        {
            int indexMonAnDat, soLuongDat;
            cout << "  Nhập STT món ăn muốn đặt (0 để hoàn tất): ";
            cin >> indexMonAnDat;
            if (indexMonAnDat == 0)
                break;
            MenuItem *monAnDaChon = timMonAn(indexMonAnDat, danhSachMenu);
            if (monAnDaChon)
            {
                cout << "  Nhập số lượng: ";
                cin >> soLuongDat;
                if (soLuongDat > 0 && soLuongDat <= monAnDaChon->getSoLuong())
                {
                    donMoi.themMonAn(monAnDaChon, soLuongDat);
                    monAnDaChon->setSoLuong(monAnDaChon->getSoLuong() - soLuongDat);
                    cout << "  Đã thêm " << monAnDaChon->getTen() << " vào đơn hàng." << endl;
                }
                else
                {
                    cout << "  Số lượng không hợp lệ hoặc không đủ." << endl;
                }
            }
            else
            {
                cout << "  STT món ăn không hợp lệ." << endl;
            }
            cout << "  Muốn đặt thêm món khác? (y/n): ";
            cin >> datTiep;
        }
        double tongTienBanDau = donMoi.getTongTien();
        double tongTienSauGiamGia = tongTienBanDau;
        if (!khachHangHienTai->getDaMuaLanDau())
        {
            tongTienSauGiamGia *= (1 - giamGiaLanDau);
            cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaLanDau * 100 << "% cho lần đặt đầu!" << endl;
            khachHangHienTai->setDaMuaLanDau(true);
        }
        else if (donMoi.getDanhSachMonAn().size() >= soLuongLonDeGiamGia)
        {
            tongTienSauGiamGia *= (1 - giamGiaSoLuongLon);
            cout << "  Áp dụng giảm giá " << fixed << setprecision(0) << giamGiaSoLuongLon * 100 << "% cho đơn hàng số lượng lớn!" << endl;
        }
        cout << "  Tổng tiền đơn hàng (sau giảm giá): " << fixed << setprecision(2) << tongTienSauGiamGia << " VNĐ" << endl;
        danhSachDonHang.push_back(donMoi);
        cout << "  Đã tạo đơn hàng #" << donMoi.getMaDonHang() << " thành công!" << endl;
        cin.ignore();
    }
    void xemThongTinCuaHang() const
    {
        cout << "\n  --- Thông tin Cửa hàng Burger ---" << endl;
        cout << "  Chào mừng quý khách đến với " << tenCuaHang << " tại " << diaChiCuaHang << "!" << endl;
        cout << "  Chúng tôi phục vụ những chiếc burger ngon nhất và nhiều loại thức uống hấp dẫn." << endl;
        cout << "  Số điện thoại liên hệ: " << soDienThoaiCuaHang << endl;
    }
};
int main()
{
    CuaHangBurger cuaHang;
    int vaiTro;
    int menuWidth = 60;
    do
    {
        cout << "\n";
        veDuongNgang(menuWidth, '*');
        cout << "* PHẦN MỀM QUẢN LÝ CỬA HÀNG BURGER *" << endl;
        veDuongNgang(menuWidth, '*');
        cout << "* Bạn là:                                           *" << endl;
        cout << "* 1. Quản lý                                         *" << endl;
        cout << "* 2. Khách hàng                                       *" << endl;
        cout << "* 0. Thoát                                           *" << endl;
        veDuongNgang(menuWidth, '*');
        cout << "  Nhập vai trò của bạn: ";
        cin >> vaiTro;
        switch (vaiTro)
        {
        case 1:
        { // Quản lý
            int choiceQuanLy;
            do
            {
                cout << "\n";
                veDuongNgang(menuWidth, '-');
                cout << "  --- CHỨC NĂNG QUẢN LÝ ---" << endl;
                veDuongNgang(menuWidth, '-');
                cout << "  1. Nhập/Cập nhật thông tin cửa hàng" << endl;
                cout << "  2. Thêm burger" << endl;
                cout << "  3. Thêm nước uống" << endl;
                cout << "  4. Xem danh sách menu" << endl;
                cout << "  5. Chỉnh sửa món ăn" << endl;
                cout << "  6. Xóa món ăn" << endl;
                cout << "  7. Xem danh sách đơn hàng" << endl;
                cout << "  8. Thêm đơn hàng" << endl;
                cout << "  9. Chỉnh sửa đơn hàng" << endl;
                cout << "  10. Xóa đơn hàng" << endl;
                cout << "  11. Thêm nhân viên" << endl;
                cout << "  12. Xem danh sách nhân viên" << endl;
                cout << "  13. Chỉnh sửa nhân viên" << endl;
                cout << "  14. Xóa nhân viên" << endl;
                cout << "  0. Quay lại menu chính" << endl;
                cout << "  Nhập lựa chọn của bạn: ";
                cin >> choiceQuanLy;
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
                    cuaHang.themDonHang();
                    break;
                case 9:
                    cuaHang.chinhSuaDonHang();
                    break;
                case 10:
                    cuaHang.xoaDonHang();
                    break;
                case 11:
                    cuaHang.themNhanVien();
                    break;
                case 12:
                    cuaHang.xemDanhSachNhanVien();
                    break;
                case 13:
                    cuaHang.chinhSuaNhanVien();
                    break;
                case 14:
                    cuaHang.xoaNhanVien();
                    break;
                case 0:
                    cout << "  Quay lại menu chính." << endl;
                    break;
                default:
                    cout << "  Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
                }
            } while (choiceQuanLy != 0);
            break;
        }
        case 2:
        { // Khách hàng
            int choiceKhach;
            do
            {
                cout << "\n";
                veDuongNgang(menuWidth, '-');
                cout << "  --- CHỨC NĂNG KHÁCH HÀNG ---" << endl;
                veDuongNgang(menuWidth, '-');
                cout << "  1. Xem thông tin cửa hàng" << endl;
                cout << "  2. Xem menu" << endl;
                cout << "  3. Đặt món" << endl;
                cout << "  0. Quay lại menu chính" << endl;
                cout << "  Nhập lựa chọn của bạn: ";
                cin >> choiceKhach;
                switch (choiceKhach)
                {
                case 1:
                    cuaHang.xemThongTinCuaHang();
                    break;
                case 2:
                    cuaHang.xemDanhSachMenuKhachHang();
                    break;
                case 3:
                    cuaHang.datMon();
                    break;
                case 0:
                    cout << "  Quay lại menu chính." << endl;
                    break;
                default:
                    cout << "  Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
                }
            } while (choiceKhach != 0);
            break;
        }
        case 0:
            cout << "  Cảm ơn bạn đã sử dụng phần mềm!" << endl;
            cout << "  Hẹn gặp lại!" << endl;
            cout << "  Nhấn bất kỳ phím nào để thoát..." << endl;
            cin.ignore();
            cin.get();
            break;
        default:
            cout << "  Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    } while (vaiTro != 0);
    return 0;
}