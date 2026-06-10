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
    TENKH nvarchar(50) not null,
    NGAYBD date not null,
    NGAYKT date not null,
    check (NGAYKT > NGAYBD),
);

create table CHUONGTRINH(
    MACT varchar(10) primary key,
    TENCT nvarchar(50) not null,
);

create table LOAILOP(
    MALOAI varchar(10) primary key,
    MACT varchar(10) not null,
    TENLOAI varchar(50) not null,
    foreign key (MACT) references CHUONGTRINH(MACT)
);

create table LOP(
    MALOP varchar(10) primary key,
    TENLOP nvarchar(50) not null,
    SISO int not null,
    check (SISO > 12),
    MAKH varchar(10) not null,
    MALOAI varchar(10) not null,
    foreign key (MAKH) references KHOAHOC(MAKH),
    foreign key (MALOAI) references LOAILOP(MALOAI),
);

create table HOCVIEN(
    MAHV varchar(10) primary key,
    TENHV nvarchar(50) not null,
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
    TENMH nVARCHAR(50) NOT NULL
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

SELECT * FROM KHOAHOC

--2 insert data into tables
INSERT INTO KHOAHOC VALUES('K001','Khóa 1','2020-01-10','2020-03-20');
INSERT INTO KHOAHOC VALUES('K002','Khóa 2','2020-02-28','2020-05-28');
INSERT INTO KHOAHOC VALUES('K003','Khóa 3','2020-04-10','2020-07-20');
INSERT INTO KHOAHOC VALUES('K004','Khóa 4','2020-06-15','2020-09-20');

INSERT INTO CHUONGTRINH VALUES('CT001',N'Tiếng Anh Tổng Quát');
INSERT INTO CHUONGTRINH VALUES('CT002',N'Tiếng Anh Trẻ Em');
INSERT INTO CHUONGTRINH VALUES('CT003',N'Tiếng Anh Luyện Kỹ Năng');
INSERT INTO CHUONGTRINH VALUES('CT004',N'Chương Trình TOEIC');
INSERT INTO CHUONGTRINH VALUES('CT005',N'Tiếng Anh IELTS');
INSERT INTO CHUONGTRINH VALUES('CT006',N'Chương Trình CamBridge');
INSERT INTO CHUONGTRINH VALUES('CT007',N'Chứng Chỉ Tiếng Anh 6 Bậc(A1,B1,B2,C1)');

INSERT INTO LOAILOP VALUES('LL001','CT001',N'Tiếng Anh cơ bản');
INSERT INTO LOAILOP VALUES('LL002','CT001',N'Tiếng Anh A1');
INSERT INTO LOAILOP VALUES('LL003','CT001',N'Tiếng Anh A2');
INSERT INTO LOAILOP VALUES('LL004','CT001',N'Tiếng Anh B1');
INSERT INTO LOAILOP VALUES('LL005','CT001',N'Tiếng Anh B2');
INSERT INTO LOAILOP VALUES('LL006','CT001',N'Tiếng Anh C1');
INSERT INTO LOAILOP VALUES('LL007','CT001',N'Tiếng Anh C2');
INSERT INTO LOAILOP VALUES('LL008','CT001',N'Tiếng Anh nâng cao');

INSERT INTO LOAILOP VALUES('LL009','CT002',N'Anh văn nhi đồng');
INSERT INTO LOAILOP VALUES('LL010','CT002',N'Anh văn thiếu nhi');
INSERT INTO LOAILOP VALUES('LL011','CT002',N'Anh văn thiếu niên');
INSERT INTO LOAILOP VALUES('LL012','CT002',N'Tiếng Anh tổng quát dành cho thiếu niên(B1)');
INSERT INTO LOAILOP VALUES('LL013','CT002',N'Tiếng Anh tổng quát dành cho thiếu niên(B1+)');
INSERT INTO LOAILOP VALUES('LL014','CT002',N'Tiếng Anh nâng cao');
INSERT INTO LOAILOP VALUES('LL015','CT002',N'IELTS');

INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH) VALUES ('L001','LL001',N'Lớp 1','30','K001');
INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH) VALUES ('L002','LL001',N'Lớp 2','30','K001');
INSERT INTO LOP(MALOP, MALOAI, TENLOP, SISO, MAKH) VALUES ('L003','LL002',N'Lớp 1','25','K001');

INSERT INTO HOCVIEN VALUES('HV0001','Do Binh An','1','2000-01-01','917217036',N'Cờ Đỏ');
INSERT INTO HOCVIEN VALUES('HV0002','Do Gia Bao','1','1999-05-15','917217036',N'Ô Môn');
INSERT INTO HOCVIEN VALUES('HV0003','Do Phuc Vinh','1','2001-03-20','917217036',N'Cù Lao');
INSERT INTO HOCVIEN VALUES('HV0004','Thach Chi Tam','1','1998-07-10','9172170361',N'Châu Thành');
INSERT INTO HOCVIEN VALUES('HV0005','Le Cam Giao','0','2000-11-30','917217036',N'Phong Điền');
INSERT INTO HOCVIEN VALUES('HV0006','Huynh Gia Bao','1','1999-02-28','917217036',N'Phong Điền');
INSERT INTO HOCVIEN VALUES('HV0007','Phan Dang Phuc','1','2000-06-15','917217036',N'Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0008','Vo Truong Giang','1','2000-09-15','917217036',N'Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0009','Nguyen Van A','1','2001-03-15','917217036',N'Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0010','Tran Thi B','0','2000-07-20','917217036',N'Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0011','Le Van C','1','1999-11-10','917217036',N'Cần Thơ');

INSERT INTO MONHOC VALUES('MH001',N'Tiếng Anh Giao Tiếp');
INSERT INTO MONHOC VALUES('MH002', N'Tiếng Anh Nghe');
INSERT INTO MONHOC VALUES('MH003', N'Tiếng Anh Nói');
INSERT INTO MONHOC VALUES('MH004', N'Tiếng Anh Đọc');
INSERT INTO MONHOC VALUES('MH005', N'Tiếng Anh Viết');




INSERT INTO PHIEUTHU VALUES('PT00002','HV0002','L001','2020-01-15',1350000);
INSERT INTO PHIEUTHU VALUES('PT00003','HV0003','L001','2020-01-20',1350000);
INSERT INTO PHIEUTHU VALUES('PT00004','HV0004','L001','2020-01-25',1350000);
INSERT INTO PHIEUTHU VALUES('PT00005','HV0005','L001','2020-01-30',1350000);
INSERT INTO PHIEUTHU VALUES('PT00006','HV0006','L001','2020-02-05',1350000);
INSERT INTO PHIEUTHU VALUES('PT00007','HV0001','L001','2020-02-10',1350000);
INSERT INTO PHIEUTHU VALUES('PT00008','HV0007','L001','2021-06-07',1350000);
INSERT INTO PHIEUTHU VALUES('PT00009','HV0008','L001','2021-06-10',1350000);
INSERT INTO PHIEUTHU VALUES('PT00010','HV0001','L003','2020-04-15',1350000);
INSERT INTO PHIEUTHU VALUES('PT00011','HV0002','L002','2020-04-16',1350000);
INSERT INTO PHIEUTHU VALUES('PT00012','HV0003','L003','2020-04-17',1350000);

INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0001','L001',8.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0002','L001',6.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0003','L001',7.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0004','L001',9.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0005','L001',4.5);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0006','L001',8.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0007','L001',10.0);
INSERT INTO DIEM(MAMH, MAHV, MALOP, DIEM) VALUES('MH001','HV0008','L001',5.5);

INSERT INTO DIEM VALUES('MH002','HV0001','L001', 7.0);
INSERT INTO DIEM VALUES('MH003','HV0001','L001', 9.0);
INSERT INTO DIEM VALUES('MH004','HV0001','L001', 6.5);
INSERT INTO DIEM VALUES('MH005','HV0001','L001', 8.0);

INSERT INTO DIEM VALUES('MH002','HV0002','L001', 5.0);
INSERT INTO DIEM VALUES('MH003','HV0002','L001', 7.5);
INSERT INTO DIEM VALUES('MH004','HV0002','L001', 6.0);
INSERT INTO DIEM VALUES('MH005','HV0002','L001', 8.0);

INSERT INTO DIEM VALUES('MH002','HV0003','L001', 8.0);
INSERT INTO DIEM VALUES('MH003','HV0003','L001', 6.5);
INSERT INTO DIEM VALUES('MH004','HV0003','L001', 7.0);
INSERT INTO DIEM VALUES('MH005','HV0003','L001', 9.0);

INSERT INTO DIEM VALUES('MH002','HV0004','L001', 9.5);
INSERT INTO DIEM VALUES('MH003','HV0004','L001', 8.0);
INSERT INTO DIEM VALUES('MH004','HV0004','L001', 7.5);
INSERT INTO DIEM VALUES('MH005','HV0004','L001', 9.0);

INSERT INTO DIEM VALUES('MH002','HV0005','L001', 4.0);
INSERT INTO DIEM VALUES('MH003','HV0005','L001', 5.5);
INSERT INTO DIEM VALUES('MH004','HV0005','L001', 6.0);
INSERT INTO DIEM VALUES('MH005','HV0005','L001', 3.5);

INSERT INTO DIEM VALUES('MH002','HV0006','L001', 7.5);
INSERT INTO DIEM VALUES('MH003','HV0006','L001', 8.5);
INSERT INTO DIEM VALUES('MH004','HV0006','L001', 9.0);
INSERT INTO DIEM VALUES('MH005','HV0006','L001', 7.0);

INSERT INTO DIEM VALUES('MH002','HV0007','L001', 10.0);
INSERT INTO DIEM VALUES('MH003','HV0007','L001', 9.5);
INSERT INTO DIEM VALUES('MH004','HV0007','L001', 9.0);
INSERT INTO DIEM VALUES('MH005','HV0007','L001', 10.0);

INSERT INTO DIEM VALUES('MH002','HV0008','L001', 6.0);
INSERT INTO DIEM VALUES('MH003','HV0008','L001', 5.0);
INSERT INTO DIEM VALUES('MH004','HV0008','L001', 7.0);
INSERT INTO DIEM VALUES('MH005','HV0008','L001', 4.5);

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
select * from HOCVIEN where Year(NGAYSINH) >= 1998 and Year(NGAYSINH)<=2000;
--10. Tìm thông tin các phiếu thu được thực hiện từ ngày 5 đến ngày 10 tháng 6 năm 2021 ?
SELECT * from Phieuthu where NGAYLAPPHIEU BETWEEN '2021-06-05' and '2021-06-10'; 
-- 11. In danh sách các học viên lớp ‘Lớp 1’ Tiếng anh căn bản
select MAHV, TENHV from HOCVIEN where MAHV in (
    select MAHV from PHIEUTHU where MALOP in (
        select MALOP from LOP where MALOAI in (
            select MALOAI from LOAILOP where MACT ='CT001'
        )
    )
);
--12. In danh sách các lớp thuộc chương trình ‘Tiếng anh tổng quát’ sử dụng khóa Join để link 2 bảng CHUONGTRINH và LOAILOP lại vì CHUONGTRINH ko có mã loại nên phải link bằng MACT 

Select TENLOP from LOP where MALOAI in (
    Select LL.MALOAI from LOAILOP LL
    join CHUONGTRINH CT on LL.MACT = CT.MACT
    where TENCT like N'%Tiếng anh tổng quát%'
);



--13. Liệt kê thông tin tất cả các phiếu thu của ‘lớp 1’ Tiếng anh A1?

Select PT.* from PHIEUTHU PT 
Join LOP ML on PT.MALOP = ML.MALOP
Join LOAILOP ML1 on ML.MALOAI = ML1.MALOAI
where ML.TENLOP = N'Lớp 1' AND ML1.TENLOAI = N'Tiếng Anh A1'


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

select COUNT(*) As soluonghoclop1 from PHIEUTHU PT
join LOP L on PT.MALOP = L.MALOP
where L.TENLOP = N'Lớp 1'

--17. Tính tổng số tiền đã thu được của ‘Lớp 1’ Tiếng anh căn bản

SELECT sum(THANHTIEN) As tongsotienlop from PHIEUTHU PT
join LOP L on PT.MALOP = L.MALOP 
join LOAILOP LL on L.MALOAI = LL.MALOAI
where L.TENLOP = N'Lớp 1' AND LL.TENLOAI = N'Tiếng Anh cơ bản';

--18. Tính tổng số tiền đã thu được của ‘Khoá 1’ ?
SELECT sum(THANHTIEN) As tongsotienkhoa1 from PHIEUTHU PT
join LOP L on PT.MALOP = L.MALOP 
join KHOAHOC KH on L.MAKH = KH.MAKH
where KH.TENKH = N'Khóa 1'

--19. Tính điểm trung bình của học viên 'Đỗ Gia Bảo', sinh ngày 02/12/2001 học ‘Lớp1’ Tiếng anh căn bản ?

Select Avg(DIEM) As diemtrungbinhcuabao From DIEM D
join HOCVIEN hv on D.MAHV = hv.MAHV
join LOP L on D.MALOP = L.MALOP
join LOAILOP LL on L.MALOAI = LL.MALOAI
where hv.TENHV = N'Do Gia Bao' and L.TENLOP = N'Lớp 1' And LL.TENLOAI = N'Tiếng Anh cơ bản'

--20. Tìm điểm lớn nhất ?

SELECT Max(DIEMTB) As Diemlonnhat from (
    select AVG(diem) as DiemTB from DIEM GROUP BY MAHV
)as TB
