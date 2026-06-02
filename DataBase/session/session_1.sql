--1 
create table KHOAHOC(
    MAKH varchar(10) primary key,
    TENKH varchar(50) not null,
    NGAYBD date not null,
    NGAYKT date not null,
    check (NGAYKT > NGAYBD),
);

create table CHUONGTRINH(
    MACT varchar(10) primary key,
    TENCT varchar(50) not null,
);

create table LOAILOP(
    MALOP varchar(10) primary key,
    MACT varchar(10) not null,
    TENLOAI varchar(50) not null,
    foreign key (MACT) references CHUONGTRINH(MACT)
);

create table LOP( -- lớp học có sĩ số > 12
    MALOP varchar(10) primary key,
    TENLOP varchar(50) not null,
    SISO int not null,
    check (SISO > 12),
    MAKH varchar(10) not null,
    MALOAI varchar(10) not null,
    foreign key (MAKH) references KHOAHOC(MAKH),
    foreign key (MALOAI) references LOAILOP(MALOP),
);

create table HOCVIEN(
    MAHV varchar(10) primary key,
    TENHV varchar(50) not null,
    GIOITINH varchar(10) not null,
    check(GIOITINH in ('0', '1')),
    NGAYSINH date not null,
    SDT varchar(15) not null,
    DIACHI varchar(100) not null,
);

create table PHIEUTHU(
    SOPT varchar(10) primary key,
    MAHV varchar(10) not null,
    MALOP varchar(10) not null,
    NGAYLAPPHIEU date not null,
    THANHTIEN decimal(18,2) not null,
    check(THANHTIEN > 0)
);

create table DIEM(
    MAMH varchar(10) not null,
    MAHV varchar(10) not null,
    MALOP varchar(10) not null,
    DIEM decimal(5,2) not null,
    primary key (MAHV, MALOP, MAMH),
    check(DIEM >= 0 and DIEM <= 10),
    foreign key (MAHV) references HOCVIEN(MAHV),
    foreign key (MALOP) references LOP(MALOP)
);

