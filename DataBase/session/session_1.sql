/*
1. KHOAHOC (MAKH,TENKH,NGAYBD, NGAYKT)
2. CHUONGTRINH (MACT,TENCT)
3. LOAILOP (MALOAI, MACT, TENLOAI)
4. LOP (MALOP, MALOAI, TENLOP, SISO, MAKH)
5. HOCVIEN (MAHV,TENHV,GIOITINH,NGAYSINH,SDT,DIACHI)
6. PHIEUTHU(SOPT,MAHV, MALOP,NGAYLAPPHIEU,THANHTIEN)
7. MONHOC (MAMH, TENMH)
8. DIEM (MAMH,MAHV,MALOP,DIEM)
*/

--1. Create tables
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
    MALOAI varchar(10) primary key,
    MACT varchar(10) not null,
    TENLOAI varchar(50) not null,
    foreign key (MACT) references CHUONGTRINH(MACT)
);

create table LOP(
    MALOP varchar(10) primary key,
    TENLOP varchar(50) not null,
    SISO int not null,
    check (SISO > 12),
    MAKH varchar(10) not null,
    MALOAI varchar(10) not null,
    foreign key (MAKH) references KHOAHOC(MAKH),
    foreign key (MALOAI) references LOAILOP(MALOAI),
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

CREATE TABLE MONHOC (
    MAMH VARCHAR(10) PRIMARY KEY,
    TENMH VARCHAR(50) NOT NULL
);

create table DIEM(
    MAMH varchar(10) not null,
    MAHV varchar(10) not null,
    MALOP varchar(10) not null,
    DIEM decimal(5,2) not null,
    primary key (MAHV, MALOP, MAMH),
    check(DIEM >= 0 and DIEM <= 10),
    foreign key (MAMH) references MONHOC(MAMH),
    foreign key (MAHV) references HOCVIEN(MAHV),
    foreign key (MALOP) references LOP(MALOP)
);

--2 insert data into tables
    
INSERT INTO KHOAHOC VALUES('K001','Khóa 1','2020-01-10','2020-03-20');
INSERT INTO KHOAHOC VALUES('K002','Khóa 2','2020-02-28','2020-05-28');
INSERT INTO KHOAHOC VALUES('K003','Khóa 3','2020-04-10','2020-07-20');
INSERT INTO KHOAHOC VALUES('K004','Khóa 4','2020-06-15','2020-09-20');

INSERT INTO CHUONGTRINH VALUES('CT001','Ti?ng Anh T?ng Quát');
INSERT INTO CHUONGTRINH VALUES('CT002','Ti?ng Anh Tr? Em');
INSERT INTO CHUONGTRINH VALUES('CT003','Ti?ng Anh Luy?n K? N?ng');
INSERT INTO CHUONGTRINH VALUES('CT004','Ch??ng Trình TOEIC');
INSERT INTO CHUONGTRINH VALUES('CT005','Ti?ng Anh IELTS');
INSERT INTO CHUONGTRINH VALUES('CT006','Ch??ng Trình CamBridge');
INSERT INTO CHUONGTRINH VALUES('CT007','Ch?ng Ch? Ti?ng Anh 6 B?c(A1,B1,B2,C1)');

INSERT INTO LOAILOP VALUES('LL001','CT001','Ti?ng Anh c?n b?n');
INSERT INTO LOAILOP VALUES('LL002','CT001','Ti?ng Anh A1');
INSERT INTO LOAILOP VALUES('LL003','CT001','Ti?ng Anh A2');
INSERT INTO LOAILOP VALUES('LL004','CT001','Ti?ng Anh B1');
INSERT INTO LOAILOP VALUES('LL005','CT001','Ti?ng Anh B2');
INSERT INTO LOAILOP VALUES('LL006','CT001','Ti?ng Anh C1');
INSERT INTO LOAILOP VALUES('LL007','CT001','Ti?ng Anh C2');
INSERT INTO LOAILOP VALUES('LL008','CT001','Ti?ng Anh nâng cao');
--
INSERT INTO LOAILOP VALUES('LL009','CT002','Anh v?n nhi ??ng');
INSERT INTO LOAILOP VALUES('LL010','CT002','Anh v?n thi?u nhi');
INSERT INTO LOAILOP VALUES('LL011','CT002','Anh v?n thi?u niên');
INSERT INTO LOAILOP VALUES('LL012','CT002','Ti?ng Anh t?ng quát dành cho thi?u niên(B1)');
INSERT INTO LOAILOP VALUES('LL013','CT002','Ti?ng Anh t?ng quát dành cho thi?u niên(B1+)');
INSERT INTO LOAILOP VALUES('LL014','CT002','Ti?ng Anh nâng cao');
INSERT INTO LOAILOP VALUES('LL015','CT002','IELTS');

INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH)VALUES ('L001','LL001','L?p 1','30','K001');
INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH) VALUES ('L002','LL001','L?p 2','30','K001');
INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH) VALUES ('L003','LL002','L?p 1','25','K001');  

INSERT INTO HOCVIEN VALUES('HV0001','Do Binh An','1','2000-01-01','917217036','cờ đỏ');
INSERT INTO HOCVIEN VALUES('HV0002','Do Gia Bao','1','1999-05-15','917217036','ô môn');
INSERT INTO HOCVIEN VALUES('HV0003','Do Phuc Vinh','1','2001-03-20','917217036','Cù Lao');
INSERT INTO HOCVIEN VALUES('HV0004','Thach Chi Tam','1','1998-07-10','9172170361','Châu Thành');
INSERT INTO HOCVIEN VALUES('HV0005','Le Cam Giao','0','2000-11-30','917217036','Phong Điền');
INSERT INTO HOCVIEN VALUES('HV0006','Huynh Gia Bao','1','1999-02-28','917217036','Phong Điền');
INSERT INTO HOCVIEN VALUES('HV0007','Phan Dang Phuc','1','2000-06-15','917217036','Can tho');
InsERT INTO HOCVIEN VALUES('HV0008','Vo truong giang','1','2000-09-15','917217036','Can tho');

INSERT INTO MONHOC VALUES('MH001', 'Tiếng Anh Giao Tiếp');

INSERT INTO PHIEUTHU VALUES('PT00002','HV0002','L001','2020-01-15',1350000);
INSERT INTO PHIEUTHU VALUES('PT00003','HV0003','L001','2020-01-20',1350000);
INSERT INTO PHIEUTHU VALUES('PT00004','HV0004','L001','2020-01-25',1350000);
INSERT INTO PHIEUTHU VALUES('PT00005','HV0005','L001','2020-01-30',1350000);
INSERT INTO PHIEUTHU VALUES('PT00006','HV0006','L001','2020-02-05',1350000);
INSERT INTO PHIEUTHU VALUES('PT00007','HV0001','L001','2020-02-10',1350000);
Insert INTO PHIEUTHU VALUES('PT00008','HV0007','L001','2021-06-07',1350000);
Insert INTO PHIEUTHU VALUES('PT00009','HV0008','L001','2021-06-10',1350000);

INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0001', 'L001', 8.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0002', 'L001', 6.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0003', 'L001', 7.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0004', 'L001', 9.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0005', 'L001', 4.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0006', 'L001', 8.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0007', 'L001', 10.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001', 'HV0008', 'L001', 5.5);

--answer
--2. Tìm thông tin về các học viên nam
select * from HOCVIEN where GIOITINH = '1';
--3. Tìm thông tin về các học viên có địa chỉ ở Cần Thơ
select * from HOCVIEN where DIACHI = 'Can tho';
--4. Tìm thông tin về các lớp học của ‘khoá 1’
select * from LOP where MAKH = 'K001';
--5. Tìm mã và họ tên học viên có học ‘khoá 1’
select MAHV,TENHV from HOCVIEN where MAHV in (select MAHV from PHIEUTHU where MALOP in (select MALOP from LOP where MAKH = 'K001'));
--6. Tìm họ tên các học viên có bao gồm chữ ‘do’
select tenhv FROM HOCVIEN where TENHV like '%do%';
--7. Tìm thông tin các học viên sinh năm 2000 ?
select * from HOCVIEN where YEAR(NGAYSINH) = 2000;
--8. Tìm thông tin của các học viên sinh tháng 12 năm 2001 ?
select * from HOCVIEN where YEAR(NGAYSINH) = 2001 and MONTH(NGAYSINH) = 12;
--9. Tìm thông tin các học viên sinh từ năm 1998 đến 2000
select * from HOVIEN where Year(NGAYSINH) >= 1998 and Year(NGAYSINH)<=2000;
--10. Tìm thông tin các phiếu thu được thực hiện từ ngày 5 đến ngày 10 tháng 6 năm 2021 ?
SELECT * from Phieuthu where NGAYLAPPHIEU BETWEEN DATE '2021-06-05' and DATE '2021-06-10'; 
-- 11. In danh sách các học viên lớp ‘Lớp 1’ Tiếng anh căn bản
select MAHV, TENHV from HOCVIEN where MAHV in (
    select MAHV from PHIEUTHU where MALOP in (
        select MALOP from LOP where MALOAI in (
            select MALOAI from LOAILOP where MACT ='CT001'
        )
    )
)
--12. In danh sách các lớp thuộc chương trình ‘Tiếng anh tổng quát’
select TENLOP from Lop where MALOAI in(select MALOAI from LOAILOP where TENLOAI = 'Ti?ng Anh t?ng quát' );

--13. Liệt kê thông tin tất cả các phiếu thu của ‘lớp 1’ Tiếng anh A1?
select TENLOP from Lop where MALOAI in(select MALOAI from LOAILOP where TENLOAI = 'Ti?ng Anh A1' );

--14. Tìm họ tên học viên, tên môn và điểm thi các môn của các học viên học ‘khoá 1’

SELECT 
    hv.TENHV AS "Họ Tên Học Viên", 
    mh.TENMH AS "Tên Môn Học", 
    d.DIEM   AS "Điểm Thi"
FROM DIEM d
JOIN HOCVIEN hv ON d.MAHV = hv.MAHV
JOIN MONHOC mh  ON d.MAMH = mh.MAMH
JOIN LOP l      ON d.MALOP = l.MALOP
WHERE l.MAKH = 'K001';

--15. Có tất cả bao nhiêu học viên ?
select COUNT(*) As Soluonghocvien from hocvien

--16. ‘Lớp 1’ Tiếng anh căn bản có bao nhiêu học viên ?
--17. Tính tổng số tiền đã thu được của ‘Lớp 1’ Tiếng anh căn bản
--18. Tính tổng số tiền đã thu được của ‘Khoá 1’ ?
--19. Tính điểm trung bình của học viên 'Đỗ Gia Bảo', sinh ngày 02/12/2001 học ‘Lớp1’ Tiếng anh căn bản ?
--20. Tìm điểm lớn nhất ?
