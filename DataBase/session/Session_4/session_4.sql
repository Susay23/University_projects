CREATE TABLE khuvuc
(
    IP varchar(20) NOT NULL PRIMARY KEY,
    tenKhuvuc varchar(30) not null,
    tang smallint
);
----------------------------------------------------
CREATE TABLE phong
(
    MP varchar(20) NOT NULL PRIMARY KEy,
    tenphong varchar(20) not null,
    somay smallint,
    IP varchar(20),
    foreign key(IP) references khuvuc(IP)
);
----------------------------------------------------
create table loai
(
    idloai varchar(20) not null primary key,
    tenloai varchar(30) not null
);
----------------------------------------------------
create table may
(
    idMay varchar(20) not null primary key,
    tenmay varchar(20) not null,
    IP varchar(20),
    ad smallint check (ad BETWEEN 0 and 255),
    idloai varchar(20),
    MP varchar(20),
    foreign key(IP) references khuvuc(IP),
    foreign key(idloai) references loai(idloai)
);
----------------------------------------------------
create table phanmem
(
    idPM varchar(20) not null primary key,
    tenPM varchar(30) not null,
    ngaymua date,
    version varchar(20),
    idloai varchar(20),
    gia smallint check(gia>=0),
    foreign key(idloai) references loai(idloai)
);
----------------------------------------------------
create table caidat
(
    id varchar(20) not null primary key,
    idMay varchar(20),
    idPM varchar(20),
    ngaycai date default SYSDATE,
    foreign key(idMay) references may(idMay),
    foreign key(idPM) references phanmem(idPM)
);

----------------------------------------------------

insert into khuvuc
values('130.120.80', 'Brin RDC', null);
insert into khuvuc
values('130.120.81', 'Brin tang 1', null);
insert into khuvuc
values('130.120.82', 'Brin tang 2', null);

----------------------------------------------------

insert into phong
values('s01', 'salle 1', 3, '130.120.80');
insert into phong
values('s02', 'salle 2', 2, '130.120.80');
insert into phong
values('s03', 'salle 3', 2, '130.120.80');
insert into phong
values('s11', 'salle 11', 2, '130.120.81');
insert into phong
values('s12', 'salle 12', 1, '130.120.81');
insert into phong
values('s21', 'salle 21', 2, '130.120.82');


--select * from khuvuc;
--select * from phong;
----------------------------------------------------

insert into loai
values('TX', 'Terminal X-Window');
insert into loai
values('UNIX', 'System Unix');
insert into loai
values('PCNT', 'PC Windows NT');
insert into loai
values('PCWS', 'PC Windows');
insert into loai
values('NC', 'Network Computer');

-----------------------------------------------------
insert into may
values('p1', 'Poste 1', '130.120.80', 01, 'TX', 's01');
insert into may
values('p2', 'Poste 2', '130.120.80', 02, 'UNIX', 's01');
insert into may
values('p3', 'Poste 3', '130.120.80', 03, 'TX', 's01');
insert into may
values('p4', 'Poste 4', '130.120.80', 04, 'PCWS', 's02');
insert into may
values('p5', 'Poste 5', '130.120.80', 05, 'PCWS', 's02');
insert into may
values('p6', 'Poste 6', '130.120.80', 06, 'UNIX', 's03');
insert into may
values('p7', 'Poste 7', '130.120.80', 07, 'TX', 's03');
insert into may
values('p8', 'Poste 8', '130.120.81', 01, 'UNIX', 's11');
insert into may
values('p9', 'Poste 9', '130.120.81', 02, 'TX', 's11');
insert into may
values('p10', 'Poste 10', '130.120.81', 03, 'UNIX', 's12');
insert into may
values('p11', 'Poste 11', '130.120.82', 01, 'PCNT', 's21');
insert into may
values('p12', 'Poste 12', '130.120.82', 02, 'PCWS', 's21');
-----------------------------------------------------
insert into phanmem
values('log1', 'Oracle 6', '05-13-1995', '6.2', 'UNIX', 3000);
insert into phanmem
values('log2', 'Oracle 8', '09-15-1999', '8i', 'UNIX', 5600);
insert into phanmem
values('log3', 'SQL Server', '04-12-1998', '7', 'PCNT', 2700);
insert into phanmem
values('log4', 'Front Page', '06-03-1997', '5', 'PCWS', 500);
insert into phanmem
values('log5', 'WinDev', '05-12-1997', '5', 'PCWS', 750);
insert into phanmem
values('log6', 'SQL*Net', null, '2.0', 'UNIX', 500);
insert into phanmem
values('log7', 'I.I.S.', '04-12-2002', '2', 'PCNT', 810);

--SELECT * FROM PHANMEM;
-----------------------------------------------------
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p1', 'log1', '13', '08-10-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p1', 'log2', '14', '08-11-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p2', 'log1', '1', '05-15-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p2', 'log2', '2', '09-17-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p4', 'log5', '3', null);
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p6', 'log6', '4', '05-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p6', 'log1', '5', '05-2-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p8', 'log2', '6', '05-19-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p8', 'log6', '7', '05-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p8', 'log1', '12', '06-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p11', 'log3', '8', '04-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p12', 'log4', '9', '04-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p11', 'log7', '10', '04-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p7', 'log7', '11', '04-01-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p12', 'log6', '15', '07-25-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p12', 'log1', '16', '03-20-2003');
insert into caidat
    (idMay,idPM,id,ngaycai)
values('p3', 'log1', '17', '03-20-2003');

--1) Vẽ sơ đồ thông thương của các quan hệ
--2) Tìm loại của máy 'p8'
select *
from loai
where idloai in (select idloai
from may
where idmay = 'p8');
--3) Tên của các phần mềm 'UNIX'
select tenPM
from phanmem
where idloai = 'UNIX';
--4) Tên phòng, địa chỉ IP phòng, mã phòng của các máy loại 'UNIX' hoặc 'PCWS'
select tenphong, mp, IP
from phong
where somay in (select somay
from may
where idloai = 'UNIX' or idloai = 'PCWS');
--5) Tên phòng, địa chỉ IP phòng, mã phòng của các máy loại 'UNIX' hoặc 'PCWS' ở
--khu vực '130.120.80', sắp xếp kết quả tăng dần theo mã phòng
select tenphong, p.mp, p.IP
from phong p
    join may m on p.mp = m.mp
where (m.idloai = 'UNIX' or m.idloai = 'PCWS')
    AND p.ip like '%130.120.80%'
;
--6) Tính số các phần mềm được cài đặt trên máy 'p6'
select idMay, count(idPM) as soluongphanmem
from caidat
where idMay = 'p6'
group by idMay;
--7) Tính Số các máy đã cài phần mềm 'log1'
select idPM, count(idMay) as soluongmay
from caidat
where idPM = 'log1'
GROUP by idPM;
--8) Tên và địa chỉ IP đầy đủ (ví dụ: 130.120.80.1) của các máy loại 'TX'
select tenmay, concat(IP,concat('.',ad)) as IPdaydu
from may
where idloai = 'TX';
--9) Tính số phần mềm đã cài đặt trên mỗi máy
select idMay, count(idPM) as sophanmemdacai
from caidat
group by idMay;
--10) Tính số cài lần cài đặt của mỗi phần mềm
select idPM, count(idMay) as solancaidat
from caidat
group by idPM;
--11) Giá trung bình của các phần mềm UNIX
select idloai, avg(gia) as giatrungbinh
from phanmem
where idloai = 'UNIX'
group by idloai;
--12) Ngày mua phần mềm gần nhất
select ngaymua
from phanmem
where ngaymua =(select max(ngaymua)
from phanmem )
--13) Số máy có ít nhất 2 phần mềm
select idMay, count(idPM) as sophanmemdacai
from caidat
group by idMay
having count(idPM) > =2;
--14) Tìm các loại không thuộc loại máy
select *
from loai l
    left join may m on l.idloai = m.idloai
where m.idloai is NULL
--16)Tìm các loại thuộc cả hai loại máy và loại phần mềm
select *
from loai l
where exists (select *
from may m
where l.idloai = m.idloai );
--17)Tìm các loại máy không phải là loại phần mềm
select *
from loai l
where not exists (select 1
from may m
where l.idloai = m.idloai );
--18) Địa chỉ IP đầy đủ của các máy cài phần mềm 'log6'
select pm.tenpm, concat(IP,concat('.',ad)) as IPdaydu
from may m
    join phanmem pm on m.idloai = pm.idloai
where pm.idPM = 'log6';
--19) Địa chỉ IP đầy đủ của các máy cài phần mềm tên 'Oracle 8'
select pm.tenpm, concat(IP,concat('.',ad)) as IPdaydu
from may m
    join phanmem pm on m.idloai = pm.idloai
where pm.tenpm = 'Oracle 8';
--20) Tên của các khu vực có chính xác 3 máy loại 'TX'
select tenkhuvuc
from khuvuc kv
    join may m on kv.IP = m.IP
where m.idloai = 'TX'
group by tenkhuvuc
having count(m.idloai) = 3;
--21) Tên phòng có ít nhất một máy cài phần mềm tên 'Oracle 6'
select tenphong
from phong p
    join may m on p.IP = m.IP
    join phanmem pm on m.idloai = pm.idloai
where tenPM = 'Oracle 6'
group by tenphong
having count(pm.tenPM) >=1;
--22) Tên phần mềm được mua gần nhất
select tenPM
from phanmem
where ngaymua = (select max(ngaymua)
from phanmem);
--23) Tên của phần mềm PCNT có giá lớn hơn bất kỳ giá của một phần mềm UNIX nào
select tenPM
from phanmem
where idloai = 'PCNT' and gia > Any(select gia
    from phanmem
    where idloai = 'UNIX');
--24) Tên của phần mềm UNIX có giá lớn hơn tất cả các giá của các phần mềm PCNT
select tenPM
from phanmem
where idloai = 'UNIX' and gia > ALL(select gia
    from phanmem
    where idloai = 'PCNT');
--25) Tên của máy có ít nhất một phần mềm chung với máy 'p6'
select distinct m.tenmay
from may m
    join caidat cd on m.idMay = cd.idMay
where cd.idPM in (select cd2.idPM
    from caidat cd2
        join may m2 on cd2.idMay = m2.idMay
    where m2.idMay = 'p6')
    AND m.idMay <> 'p6';
--26) Tên của các máy có cài tất cả phần mềm như máy 'p6'
select m.tenmay
from may m
where m.idMay <> 'p6' and not exists (
    (
        select cd.idPM
    from caidat cd
       join may m6 on cd.idMay = m6.idMay
    where m6.idMay = 'p6'
        )
    EXCEPT
        (
        select cdx.idPM
        from caidat cdx
        where cdx.idmay = m.idmay
    )
);
