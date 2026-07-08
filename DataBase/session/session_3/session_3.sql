-- Cho CSDL về quản lý công trình gồm 7 bảng sau (Các cột in đậm là khóa chính)
-- 1. KTRUCSU (HOTEN_KTS, NAMS_KTS, PHAI, NOI_TN, DCHI_LL_KTS)
-- 2. CHUTHAU (TEN_THAU ,TEL, DCHI_THAU)
-- 3. CHUNHAN (TEN_CHU, DCHI_CHU)
-- 4. CONGNHAN (HOTEN_CN, NAMS_CN, NAM_VAO_N, CH_MON )
-- 5. CGTRINH (STT_CTR, TEN_CTR, DIACHI_CTR, TINH_THANH, KINH_PHI, TEN_CHU,
-- TEN_THAU, NGAY_BD )
-- 6. THAMGIA (HOTEN_CN, STT_CTR, NGAY_TGIA, SO_NGAY)
-- 7. THIETKE (HOTEN_KTS, STT_CTR, THU_LAO )
-- Đặt định dạng ngày : MON-DD-YYYY

CREATE TABLE CGTRINH
(
	STT_CTR int NOT NULL ,
	TEN_CTR varchar (20) NULL ,
	DIACHI_CTR varchar (20) NULL ,
	TINH_THANH varchar (15) NULL ,
	KINH_PHI int NULL ,
	TEN_CHU varchar (20) NULL ,
	TEN_THAU varchar (20) NULL ,
	NGAY_BD date NULL
)
;


CREATE TABLE CHUNHAN
(
	TEN_CHU varchar (20) NOT NULL ,
	DCHI_CHU varchar (20) NULL
)
;


CREATE TABLE CHUTHAU
(
	TEN_THAU varchar (20) NOT NULL ,
	TEL char (7) NULL ,
	DCHI_THAU varchar (20) NULL
)
;


CREATE TABLE CONGNHAN
(
	HOTEN_CN varchar (20) NOT NULL ,
	NAMS_CN int NULL ,
	NAM_VAO_N int NULL ,
	CH_MON varchar (10) NULL
)
;


CREATE TABLE KTRUCSU
(
	HOTEN_KTS varchar (20) NOT NULL ,
	NAMS_KTS int NULL ,
	PHAI char (2) NULL ,
	NOI_TN varchar (15) NULL ,
	DCHI_LL_KTS varchar (30) NULL
)
;


CREATE TABLE THAMGIA
(
	HOTEN_CN varchar (20) NOT NULL ,
	STT_CTR int NOT NULL ,
	NGAY_TGIA date NULL ,
	SO_NGAY int NULL
)
;


CREATE TABLE THIETKE
(
	HOTEN_KTS varchar (20) NOT NULL ,
	STT_CTR int NOT NULL ,
	THU_LAO int NULL
)
;


ALTER TABLE  CGTRINH ADD 
	CONSTRAINT PK_CGTRINH PRIMARY KEY  	(STT_CTR	)  ;


ALTER TABLE  CHUNHAN ADD 
	CONSTRAINT PK_CHUNHAN PRIMARY KEY  (	TEN_CHU	)  ;


ALTER TABLE  CHUTHAU ADD 
	CONSTRAINT PK_CHUTHAU PRIMARY KEY  (	TEN_THAU	)  ;


ALTER TABLE  CONGNHAN ADD 
	CONSTRAINT PK_CONGNHAN PRIMARY KEY  (	HOTEN_CN	)  ;


ALTER TABLE  KTRUCSU ADD 
	CONSTRAINT PK_KTRUCSU PRIMARY KEY  	(	HOTEN_KTS	)  ;


ALTER TABLE  THAMGIA ADD 
	CONSTRAINT PK_THAMGIA PRIMARY KEY  	(	HOTEN_CN,	STT_CTR	)  ;


ALTER TABLE  THIETKE ADD 
	CONSTRAINT PK_THIETKE PRIMARY KEY  	(	HOTEN_KTS,	STT_CTR	)  ;


ALTER TABLE  CGTRINH ADD 
	CONSTRAINT FK_CGTRINH_CHUNHAN FOREIGN KEY 	(	TEN_CHU	) REFERENCES  CHUNHAN (	TEN_CHU	);

ALTER TABLE  CGTRINH ADD 
	CONSTRAINT FK_CGTRINH_CHUTHAU FOREIGN KEY 
	(	TEN_THAU	) REFERENCES  CHUTHAU (	TEN_THAU	);


ALTER TABLE  THAMGIA ADD 
	CONSTRAINT FK_THAMGIA_CGTRINH FOREIGN KEY 
	(		STT_CTR	) REFERENCES  CGTRINH (		STT_CTR	);

ALTER TABLE  THAMGIA ADD 
	CONSTRAINT FK_THAMGIA_CONGNHAN FOREIGN KEY 
	(		HOTEN_CN	) REFERENCES  CONGNHAN (		HOTEN_CN	);


ALTER TABLE  THIETKE ADD 
	CONSTRAINT FK_THIETKE_CGTRINH FOREIGN KEY 	(STT_CTR) REFERENCES  CGTRINH (	STT_CTR	);

ALTER TABLE  THIETKE ADD 
	CONSTRAINT FK_THIETKE_KTRUCSU FOREIGN KEY 
	(	HOTEN_KTS	) REFERENCES  KTRUCSU (	HOTEN_KTS );

-- 1. Tìm sự thông thương giữa các bảng trong CSDL
-- 2. Mở các bảng dữ liệu để xem kiểu dữ liệu của từng trường và quan sát dữ liệu của từng bảng
select *
from ktrucsu;
select *
from chuthau;
select *
from chunhan;
select *
from congnhan;
select *
from cgtrinh;
SELECT *
from thamgia;
select *
from THIETKE;
-- 3. Hãy cho biết thông tin về các kiến trúc sư có họ là Lê và sinh năm 1956
select *
from ktrucsu
where HOTEN_KTS like '%le%' and NAMS_KTS = 1956;
-- 4. Hãy cho biết tên các công trình bắt đầu trong khoảng 1/9/1994 đến 20/10/1994
select *
from CGTRINH
where NGAY_BD between '09-01-1994' and '10-20-1994';
-- 5. Hãy cho biết tên và địa chỉ các công trình do chủ thầu ‘công ty xây dựng số 6’ thi công
-- (chú ý: xem dữ liệu để lấy đúng tên công ty xây dựng số 6)
select TEN_CTR, DIACHI_CTR
from CGTRINH
where TEN_THAU like '%6%';
-- 6. Tìm tên và địa chỉ liên lạc của các chủ thầu thi công công trình ở Cần Thơ do kiến trúc sư
-- Lê Kim Dung thiết kế
select TEN_THAU, DCHI_THAU
from CHUTHAU
where TEN_THAU in 
    (select TEN_THAU
from Cgtrinh
where tinh_thanh like '%can tho' and stt_ctr in 
        (select STT_CTR
	from THIETKE
	where HOTEN_KTS like 'le kim dung'));

--------------------------------------------------

select TEN_THAU, DCHI_THAu
from chuthau
where ten_thau in (
	select ct.ten_thau
from chuthau ct
	join cgtrinh c on ct.TEN_THAU = c.TEN_THAU
	join THIETKE t on c.STT_CTR = t.STT_CTR
where HOTEN_KTS like 'le kim dung'
);
-- 7. Hãy cho biết nơi tốt nghiệp của các kiến trúc sư đã thiết kế công trình Khách sạn quốc tế ở
-- Cần Thơ
select NOI_TN
from KTRUCSU
where HOTEN_KTS in (
	select HOTEN_KTS
from THIETKE tk
	join CGTRINH c on tk.STT_CTR = c.STT_CTR
where c.TEN_CTR = 'khach san quoc te' and TINH_THANH like '%can tho%'
)
-- 8. Cho biết họ tên, năm sinh và năm vào nghề của các công nhân có chuyên môn hàn hoặc
-- điện đã tham gia các công trình mà chủ thầu Lê Văn Sơn đã trúng thầu
select CN.HOTEN_CN, NAMS_CN, NAM_VAO_N
from CONGNHAN CN
	join thamgia tg on cn.HOTEN_CN = tg.HOTEN_CN
	join CGTRINH cg on tg.STT_CTR = cg.STT_CTR
where cg.TEN_THAU like 'le van son'
-- 9. Những công nhân nào đã bắt đầu tham gia sông trình Khách sạn Quốc tế ở Cần Thơ trong
-- giai đoạn từ ngày 15/12/1994 đến 31/12/1994
SELECT HOTEN_CN
from THAMGIA tg
	join CGTRINH cg on tg.STT_CTR = cg.STT_CTR
WHERE cg.TEN_CTR = 'khach san quoc te' and tg.NGAY_TGIA BETWEEN '12-15-1994' and '12-31-1994';
-- 10. Cho biết họ tên và năm sinh của các kiến trúc sư đã tốt nghiệp ở TP HCM và đã thiết kế ít
-- nhất một công trình có kinh phí đầu tư trên 400 triệu đồng
SELECT KT.HOTEN_KTS, NAMS_KTS
from KTRUCSU KT
	join THIETKE tk on KT.HOTEN_KTS = tk.HOTEN_KTS
	join CGTRINH cg on tk.STT_CTR = cg.STT_CTR
where KT.NOI_TN = 'tp hcm' and cg.KINH_PHI > 400
-- 11. Tìm họ tên và chuyên môn của các công nhân tham gia các công trình do kiến trúc sư Lê
-- Thanh Tùng thiết kế
SELECT CN.HOTEN_CN, Ch_MON
from CONGNHAN cn
	join THAMGIA tg on cn.HOTEN_CN = tg.HOTEN_CN
	join THIETKE tk on tg.STT_CTR = tk.STT_CTR
where tk.HOTEN_KTS = 'le thanh tung'
-- 12. Cho biết tên công trình có kinh phí cao nhất
SELECT TEN_CTR
from CGTRINH
where KINH_PHI = (select MAX(KINH_PHI)
from CGTRINH)
-- 13. Cho biết họ tên kiến trúc sư trẻ tuổi nhất
SELECT HOTEN_KTS
from KTRUCSU KT
where KT.NAMS_KTS = (select max(NAMS_KTS)
from KTRUCSU)
-- 14. Tìm tổng kinh phí của các công trình theo từng chủ thầu
SELECT ten_thau, sum(Kinh_phi) TONG
from CGTRINH
GROUP BY TEN_THAU
-- 15. Tìm tên và địa chỉ những chủ thầu đã trúng thầu công trình có kinh phí thấp nhất
SELECT CT.TEN_THAU, DCHI_THAU
from CHUTHAU CT
	join CGTRINH cg on ct.TEN_THAU = cg.TEN_THAU
where KINH_PHI = (select min(KINH_PHI)
from CGTRINH)
-- 16. Cho biết họ tên các kiến trúc sư có tổng thù lao thiết kế các công trình lớn hơn 25 triệu
SELECT HOTEN_KTS
from THIETKE
GROUP BY HOTEN_KTS
HAVING sum(THU_LAO) > 25
-- 17. Cho biết số lượng các kiến trúc sư có tổng thù lao thiết kế các công trình lớn hơn 25 triệu
select count (*)
from THIETKE
where HOTEN_KTS in (
	SELECT HOTEN_KTS
from THIETKE
GROUP BY HOTEN_KTS
HAVING sum(THU_LAO) > 25
)
-- 18. Tính số công trình mà mỗi kiến trúc sư đã thiết kế
select HOTEN_KTS, count(*) sort
from THIETKE
GROUP BY HOTEN_KTS
-- 19. Tính tổng số công nhân đã tham gia mỗi công trình
SELECT t.STT_cTR, TEN_cTR, count(*) members
from THAMGIA t
join CGTRINH cg on t.STT_CTR = cg.STT_CTR
GROUP BY t.STT_CTR, TEN_CTR

-- 20. Tìm tên và địa chỉ công trình có tổng số công nhân tham gia nhiều nhất
select cg.ten_ctr, cg.diachi_ctr
from cgtrinh cg
join (select t.stt_ctr, count(*) as members
	from thamgia t
	group by t.stt_ctr) as temp on cg.stt_ctr = temp.stt_ctr
where temp.members = (select max(temp2.members)
	from (select t2.stt_ctr, count(*) as members
		from thamgia t2
		group by t2.stt_ctr) as temp2
	)

-- 21. Cho biết tên các thành phố và kinh phí trung bình của các công trình của từng thành phố
-- tương ứng
------------------------------------------------
-- 22. Cho biết tên và địa chỉ của các công trình mà công nhân Nguyễn Hồng Vân đang tham gia
-- vào ngày 18/12/1994
-- 23. Cho biết họ tên kiến trúc sư vừa thiết kế các công trình do Phòng dịch vụ Sở Xây dựng
-- thi công, vừa thiết kế các công trình do chủ thầu cty xây dựng số 6 thi công
-- 24. Cho biết họ tên các công nhân có tham gia các công trình ở Cần Thơ nhưng không tham
-- gia công trình ở Vĩnh Long
-- 25. Cho biết tên của các chủ thầu đã thi công các công trình có kinh phí lớn hơn tất cả các
-- công trình do chủ thầu Phòng dịch vụ sở xây dựng thi công
-- 26. Cho biết họ tên các kiến trúc sư có thù lao thiết kế cho một công trình nào đó dưới giá trị
-- trung bình thù lao thiết kế của các KTS.
-- 27. Cho biết họ tên các công nhân có tổng số ngày tham gia vào các công trình lớn hơn tổng
-- số ngày tham gia của công nhân Nguyễn Hồng Vân
-- 28. Cho biết họ tên công nhân có tham gia tất cả các công trình
-- 29. Cho biết họ tên các công nhân có tham gia tất cả các công trình mà công nhân Nguyen Hong
-- Van đã tham gia
-- 30. Tìm các cặp tên của chủ thầu có trúng thầu các công trình tại cùng một thành phố
-- 31. Tìm các cặp tên của các công nhân có lamg việc chung với nhau trong ít nhất là hai công
-- trình